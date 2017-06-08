#include "monthboard.h"

MonthBoard::MonthBoard(QWidget * parent) : QGroupBox(parent)
{
    monthBoardLayout = new QVBoxLayout();
    monthBoardLayout->setSpacing(20);
    monthBoardLayout->setContentsMargins(0, 0, 0, 0);
    setLayout(monthBoardLayout);

    createHeaderLayout();
    createDayCardsLayout();
    createFooterLayout();
}

void MonthBoard::createHeaderLayout()
{
    QHBoxLayout * headerLayout = new QHBoxLayout();

    QLabel * monthName = new QLabel(QString("June 2017"));
    monthName->setObjectName("MonthBoardMonthNameLabel");
    monthName->setMaximumHeight(80);
    monthName->setAlignment(Qt::AlignCenter);

    headerLayout->addWidget(monthName);

    monthBoardLayout->addLayout(headerLayout);
}

void MonthBoard::createDayCardsLayout()
{
    QGridLayout * cardsLayout = new QGridLayout();
    cardsLayout->setSpacing(10);

    int row = 0;
    int column = 0;

    for(int numberOfCards=0; numberOfCards<31; numberOfCards++)
    {
        if(column == 7)
        {
            column = 0;
            row++;
        }

        QWidget * dayCard = new QWidget();
        dayCard->setMinimumSize(80, 90);
        dayCard->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        dayCard->setStyleSheet("background: green; margin: 0px;");

        cardsLayout->addWidget(dayCard, row, column);

        column++;
    }

    QGroupBox * dayCardsContainer = new QGroupBox();
    dayCardsContainer->setStyleSheet("margin-left: 15px; margin-right: 15px;");
    dayCardsContainer->setLayout(cardsLayout);

    monthBoardLayout->addWidget(dayCardsContainer);
}

void MonthBoard::createFooterLayout()
{
    QHBoxLayout * footerLayout = new QHBoxLayout();

    QLabel * footerText = new QLabel(QString("Footer"));
    footerText->setObjectName("MonthBoardFooterTextLabel");
    footerText->setMaximumHeight(60);
    footerText->setAlignment(Qt::AlignCenter);

    footerLayout->addWidget(footerText);

    monthBoardLayout->addLayout(footerLayout);
}
