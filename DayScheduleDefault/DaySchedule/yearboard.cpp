#include "yearboard.h"

YearBoard::YearBoard(QString footerText, QSharedPointer<QDate> currUsedDate, QWidget * parent)
: BoardTemplate(currUsedDate, parent)
{
    createHeaderLayout(QString::number(currentlyUsedDate->year()));
    createMonthCardsLayout();
    createFooterLayout(footerText);
}

void YearBoard::createMonthCardsLayout()
{
    QGridLayout * monthsCardsLayout = new QGridLayout();
    monthsCardsLayout->setSpacing(1);
    monthsCardsLayout->setContentsMargins(20, 5, 20, 5);

    for(int row=0, monthNumber=1; row<ROWS; row++)
    {
        for(int column=0; column<COLUMNS; column++, monthNumber++)
        {
            QLocale locale(QLocale::English);
            QString monthName = locale.monthName(monthNumber);

            CalendarCard * monthCard = new CalendarCard(monthName);
            monthCard->setObjectName("YearBoardMonthCard");
            monthCard->setMinimumWidth(210);
            monthCard->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

            connect(monthCard, SIGNAL(cardClicked(QString&)), this, SLOT(updateCurrentlyUsedDateMonth(QString&)));

            monthsCardsLayout->addWidget(monthCard, row, column);
        }
    }
    BoardTemplate::roundCornersOfTheGrid(monthsCardsLayout, "YearBoardMonthCard");

    boardLayout->addLayout(monthsCardsLayout);
}

void YearBoard::updateCurrentlyUsedDateMonth(QString & monthName)
{
    int year = currentlyUsedDate->year();
    int newMonth = convertMonthNameToMonthValue(monthName);

    if(newMonth == 0)
        emit errorDetected(QString("The application has encountered an unexpected error."));

    int day = 1;

    currentlyUsedDate->setDate(year, newMonth, day);
    emit currentlyUsedDateHasChanged();
}

int YearBoard::convertMonthNameToMonthValue(QString & name)
{
    QLocale locale(QLocale::English);

    for(int monthValue=1; monthValue<=12; monthValue++)
    {
        if(name == locale.monthName(monthValue))
            return monthValue;
    }
    return 0;
}

void YearBoard::save()
{
    DatabaseManager & db = DatabaseManager::getInstance();
    QSqlQuery query;
    query.prepare("SELECT 1 FROM year WHERE year_id=:id LIMIT 1");
    query.bindValue(":id", currentlyUsedDate->year());

    if(db.recordAlreadyExists(query))
    {
        if(somethingChanged())
        {
            query.prepare("UPDATE year SET description=:description WHERE year_id=:id");
            query.bindValue(":description", footerLineEdit->text());
            query.bindValue(":id", currentlyUsedDate->year());
            db.execQuery(query);
        }
    }
    else
    {
        query.prepare("INSERT INTO year (year_id, description)"
                       "VALUES (:id, :description)");
        query.bindValue(":id", currentlyUsedDate->year());
        query.bindValue(":description", footerLineEdit->text());
        db.execQuery(query);
    }
}

void YearBoard::load()
{
    DatabaseManager & db = DatabaseManager::getInstance();
    QSqlQuery query;
    query.prepare("SELECT 1 FROM year WHERE year_id=:id LIMIT 1");
    query.bindValue(":id", currentlyUsedDate->year());

    if(db.recordAlreadyExists(query))
    {
        query.prepare("SELECT description FROM year WHERE year_id=:id");
        query.bindValue(":id", currentlyUsedDate->year());
        db.execQuery(query);

        query.first();
        QString footerText = query.value(0).toString();

        footerLineEdit->setText(footerText);
    }
}

bool YearBoard::somethingChanged()
{
    DatabaseManager & db = DatabaseManager::getInstance();

    QSqlQuery validationQuery;
    validationQuery.prepare("SELECT description FROM year WHERE year_id=:id");
    validationQuery.bindValue(":id", currentlyUsedDate->year());
    db.execQuery(validationQuery);

    validationQuery.first();
    return footerLineEdit->text() == validationQuery.value(0).toString() ? false : true;
}
