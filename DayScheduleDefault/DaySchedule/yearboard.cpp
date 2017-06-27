#include "yearboard.h"

YearBoard::YearBoard(QSharedPointer<QDate> currUsedDate, QWidget * parent) : BoardTemplate(currUsedDate, parent)
{
    createHeaderLayout(QString::number(currentlyUsedDate->year()));
    createMonthCardsLayout();
    createFooterLayout(QString("Footer"));
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
    int day = currentlyUsedDate->day();

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
