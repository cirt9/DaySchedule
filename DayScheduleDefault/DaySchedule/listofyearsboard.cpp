#include "listofyearsboard.h"

ListOfYearsBoard::ListOfYearsBoard(QSharedPointer<QDate> currUsedDate, QWidget * parent) : BoardTemplate(currUsedDate, parent)
{
    createHeaderLayout(QString("Header"));
    createYearsCardsLayout();
    createFooterLayout(QString("Footer"));
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
    int month = currentlyUsedDate->month();
    int day = currentlyUsedDate->day();

    currentlyUsedDate->setDate(newYear, month, day);
    emit currentlyUsedDateHasChanged();
}
