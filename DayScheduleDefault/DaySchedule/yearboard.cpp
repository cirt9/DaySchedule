#include "yearboard.h"

YearBoard::YearBoard(QWidget * parent) : QGroupBox(parent)
{
    yearBoardLayout = new QVBoxLayout();
    yearBoardLayout->setSpacing(20);
    yearBoardLayout->setContentsMargins(0, 0, 0, 0);
    setLayout(yearBoardLayout);

    createHeaderLayout();
    createMonthCardsLayout();
    createFooterLayout();
}

void YearBoard::createHeaderLayout()
{
    QHBoxLayout * headerLayout = new QHBoxLayout();

    QLabel * yearNumber = new QLabel(QString("2017"));
    yearNumber->setObjectName("YearBoardYearNumberLabel");
    yearNumber->setMaximumHeight(80);
    yearNumber->setAlignment(Qt::AlignCenter);

    headerLayout->addWidget(yearNumber);

    yearBoardLayout->addLayout(headerLayout);
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
    roundEdgesOfTheCornerCards(monthsCardsLayout);

    yearBoardLayout->addLayout(monthsCardsLayout);
}

void YearBoard::roundEdgesOfTheCornerCards(QGridLayout * cardsLayout)
{
    QList<QPushButton *> monthsCards;

    for (int i=0; i<cardsLayout->count(); i++)
    {
        if(cardsLayout->itemAt(i)->widget()->objectName() == "YearBoardMonthCard")
        {
            QPushButton * monthCard = dynamic_cast<QPushButton *>(cardsLayout->itemAt(i)->widget());
            monthsCards.push_back(monthCard);
        }
    }

    monthsCards[0]->setObjectName("YearBoardMonthCardTopLeftCorner");
    monthsCards[COLUMNS-1]->setObjectName("YearBoardMonthCardTopRightCorner");
    monthsCards[ROWS * COLUMNS - COLUMNS]->setObjectName("YearBoardMonthCardBottomLeftCorner");
    monthsCards[ROWS * COLUMNS - 1]->setObjectName("YearBoardMonthCardBottomRightCorner");
}

void YearBoard::createFooterLayout()
{
    QHBoxLayout * footerLayout = new QHBoxLayout();

    QLabel * footerText = new QLabel(QString("Footer"));
    footerText->setObjectName("YearBoardFooterTextLabel");
    footerText->setMaximumHeight(80);
    footerText->setAlignment(Qt::AlignCenter);

    footerLayout->addWidget(footerText);

    yearBoardLayout->addLayout(footerLayout);
}
