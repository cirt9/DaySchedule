#include "yearboard.h"

YearBoard::YearBoard(QWidget * parent) : BoardTemplate(parent)
{
    createHeaderLayout(QString("2017"));
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

            QPushButton * monthCard = new QPushButton(monthName);
            monthCard->setObjectName("YearBoardMonthCard");
            monthCard->setMinimumWidth(210);
            monthCard->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

            monthsCardsLayout->addWidget(monthCard, row, column);
        }
    }
    BoardTemplate::roundCornersOfTheGrid(monthsCardsLayout, "YearBoardMonthCard");

    boardLayout->addLayout(monthsCardsLayout);
}
