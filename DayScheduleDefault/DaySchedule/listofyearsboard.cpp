#include "listofyearsboard.h"

ListOfYearsBoard::ListOfYearsBoard(QString footerText, QSharedPointer<QDate> currUsedDate, QWidget * parent)
: BoardTemplate(currUsedDate, parent)
{
    createHeaderLayout(QString("Header"));
    createYearsCardsLayout();
    createFooterLayout(footerText);
}

void ListOfYearsBoard::createYearsCardsLayout()
{
    QGridLayout * yearsCardsLayout = new QGridLayout();
    yearsCardsLayout->setSpacing(1);
    yearsCardsLayout->setContentsMargins(20, 5, 20, 5);

    for(int row=0, year=2017; row<ROWS; row++)
    {
        for(int column=0; column<COLUMNS; column++, year++)
        {
            CalendarCard * yearCard = new CalendarCard(QString::number(year));
            yearCard->setObjectName("ListOfYearsBoardYearCard");
            yearCard->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            yearCard->setMinimumWidth(70);

            connect(yearCard, SIGNAL(cardClicked(QString&)), SLOT(updateCurrentlyUsedDateYear(QString&)));

            yearsCardsLayout->addWidget(yearCard, row, column);
        }
    }
    BoardTemplate::roundCornersOfTheGrid(yearsCardsLayout, "ListOfYearsBoardYearCard");

    boardLayout->insertLayout(1, yearsCardsLayout);
}

void ListOfYearsBoard::updateCurrentlyUsedDateYear(QString & yearValue)
{
    int newYear = yearValue.toInt();
    int month = 1;
    int day = 1;

    currentlyUsedDate->setDate(newYear, month, day);
    emit currentlyUsedDateHasChanged();
}

void ListOfYearsBoard::save()
{
    DatabaseManager & db = DatabaseManager::getInstance();
    QSqlQuery query = db.yearsCheckIfExistsQuery(1);

    if(db.recordAlreadyExists(query))
    {
        if(somethingChanged())
        {
            query = db.yearsUpdateQuery(1, footerLineEdit->text());
            db.execQuery(query);
        }
    }
    else
    {
        query = db.yearsInsertQuery(1, footerLineEdit->text());
        db.execQuery(query);
    }
}

void ListOfYearsBoard::load()
{
    DatabaseManager & db = DatabaseManager::getInstance();
    QSqlQuery query = db.yearsCheckIfExistsQuery(1);

    if(db.recordAlreadyExists(query))
    {
        query = db.yearsSelectDescriptionQuery(1);
        db.execQuery(query);

        query.first();
        QString footerText = query.value(0).toString();

        footerLineEdit->setText(footerText);
    }
}

bool ListOfYearsBoard::somethingChanged()
{
    DatabaseManager & db = DatabaseManager::getInstance();
    QSqlQuery query = db.yearsSelectDescriptionQuery(1);
    db.execQuery(query);

    query.first();
    return footerLineEdit->text() == query.value(0).toString() ? false : true;
}
