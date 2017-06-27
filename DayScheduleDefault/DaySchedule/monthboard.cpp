#include "monthboard.h"

MonthBoard::MonthBoard(QSharedPointer<QDate> currUsedDate, QWidget * parent) : BoardTemplate(currUsedDate, parent)
{
    maxNumberOfCards = 42;

    QString headerDate = createHeaderDate();
    createHeaderLayout(headerDate);
    createDayCardsLayout();
    createFooterLayout(QString("Footer"));
}

QString MonthBoard::createHeaderDate()
{
    QLocale locale(QLocale::English);
    QString monthName = locale.monthName(currentlyUsedDate->month());
    QString year = QString::number(currentlyUsedDate->year());

    return monthName + QString(" ") + year;
}

void MonthBoard::createDayCardsLayout()
{
    QGridLayout * cardsLayout = new QGridLayout();
    cardsLayout->setContentsMargins(20, 5, 20, 5);
    cardsLayout->setSpacing(1);

    createDaysNames(cardsLayout);

    int row = 1;
    int column = 0;

    createBlankCardsOnTheFront(row, column, cardsLayout);
    createDayCards(row, column, cardsLayout);
    createBlankCardsOnTheEnd(row, column, cardsLayout);

    BoardTemplate::roundCornersOfTheGrid(cardsLayout, "MonthBoardDayCard",
                   cardsLayout->rowCount()-1, cardsLayout->columnCount());

    boardLayout->addLayout(cardsLayout);
}

void MonthBoard::createDaysNames(QGridLayout * cardsLayout)
{
    for(int dayNumber=1, column=0; dayNumber<8; dayNumber++, column++)
    {
        QLocale locale(QLocale::English);
        QString name = locale.dayName(dayNumber);
        QLabel * dayName = new QLabel(name);
        dayName->setAlignment(Qt::AlignCenter);
        dayName->setObjectName("MonthBoardDayNameLabel");

        cardsLayout->addWidget(dayName, 0, column);
    }
}

void MonthBoard::createBlankCardsOnTheFront(int & row, int & column, QGridLayout * cardsLayout)
{
    int firstDayNumber = calculateFirstDayOfTheMonthValue()-1;

    for(int blankCards=0; blankCards<firstDayNumber; blankCards++)
    {
        CalendarCard * blankCard = new CalendarCard(QString(""));
        blankCard->setMinimumSize(100, 100);
        blankCard->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        blankCard->setObjectName("MonthBoardDayCard");
        blankCard->setDisabled(true);
        cardsLayout->addWidget(blankCard, row, column);
        column++;
    }
}

int MonthBoard::calculateFirstDayOfTheMonthValue()
{
    int currentYear = currentlyUsedDate->year();
    int currentMonth = currentlyUsedDate->month();
    int firstDay = 1;
    QDate firstDayOfTheMonth(currentYear, currentMonth, firstDay);

    return firstDayOfTheMonth.dayOfWeek();
}

void MonthBoard::createDayCards(int & row, int & column, QGridLayout * cardsLayout)
{
    for(int numberOfCards=0; numberOfCards<currentlyUsedDate->daysInMonth(); numberOfCards++)
    {
        if(column == 7)
        {
            column = 0;
            row++;
        }

        CalendarCard * dayCard = new CalendarCard(QString::number(numberOfCards+1));
        dayCard->setMinimumSize(100, 100);
        dayCard->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        dayCard->setObjectName("MonthBoardDayCard");

        connect(dayCard, SIGNAL(cardClicked(QString&)), this, SLOT(updateCurrentlyUsedDateDay(QString&)));

        cardsLayout->addWidget(dayCard, row, column);
        column++;
    }
}

void MonthBoard::updateCurrentlyUsedDateDay(QString & dayValue)
{
    int year = currentlyUsedDate->year();
    int month = currentlyUsedDate->month();
    int newDay = dayValue.toInt();

    currentlyUsedDate->setDate(year, month, newDay);
    emit currentlyUsedDateHasChanged();
}

void MonthBoard::createBlankCardsOnTheEnd(int & row, int & column, QGridLayout * cardsLayout)
{
    int numberOfCreatedCards = (row-1) * MAX_ROW_SIZE + column;

    if(numberOfCreatedCards <= 35)
        maxNumberOfCards = 35;

    for(int blankCards=numberOfCreatedCards; blankCards<maxNumberOfCards; blankCards++)
    {
        if(column == 7)
        {
            column = 0;
            row++;
        }

        CalendarCard * blankCard = new CalendarCard(QString(""));
        blankCard->setMinimumSize(100, 100);
        blankCard->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        blankCard->setObjectName("MonthBoardDayCard");
        blankCard->setDisabled(true);
        cardsLayout->addWidget(blankCard, row, column);
        column++;
    }
}
