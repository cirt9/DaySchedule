#include "monthboard.h"

MonthBoard::MonthBoard(QWidget * parent) : QGroupBox(parent)
{
    monthBoardLayout = new QVBoxLayout();
    monthBoardLayout->setSpacing(20);
    monthBoardLayout->setContentsMargins(0, 0, 0, 0);
    setLayout(monthBoardLayout);

    maxNumberOfCards = 42;
    date = QDate(2017, 6, 1);

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
    cardsLayout->setContentsMargins(20, 5, 20, 5);
    cardsLayout->setSpacing(1);

    createDaysNames(cardsLayout);

    int row = 1;
    int column = 0;

    createBlankCardsOnTheFront(row, column, cardsLayout);
    createDayCards(row, column, cardsLayout);
    createBlankCardsOnTheEnd(row, column, cardsLayout);
    roundEdgesOfTheCornerCards(cardsLayout);

    monthBoardLayout->addLayout(cardsLayout);
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
    int firstDayNumber = date.dayOfWeek()-1;

    for(int blankCards=0; blankCards<firstDayNumber; blankCards++)
    {
        QPushButton * blankCard = new QPushButton();
        blankCard->setMinimumSize(100, 100);
        blankCard->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        blankCard->setObjectName("MonthBoardDayCard");
        blankCard->setDisabled(true);
        cardsLayout->addWidget(blankCard, row, column);
        column++;
    }
}

void MonthBoard::createDayCards(int & row, int & column, QGridLayout * cardsLayout)
{
    for(int numberOfCards=0; numberOfCards<date.daysInMonth(); numberOfCards++)
    {
        if(column == 7)
        {
            column = 0;
            row++;
        }

        QPushButton * dayCard = new QPushButton(QString::number(numberOfCards+1));
        dayCard->setMinimumSize(100, 100);
        dayCard->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        dayCard->setObjectName("MonthBoardDayCard");

        cardsLayout->addWidget(dayCard, row, column);
        column++;
    }
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

        QPushButton * blankCard = new QPushButton();
        blankCard->setMinimumSize(100, 100);
        blankCard->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        blankCard->setObjectName("MonthBoardDayCard");
        blankCard->setDisabled(true);
        cardsLayout->addWidget(blankCard, row, column);
        column++;
    }
}

void MonthBoard::roundEdgesOfTheCornerCards(QGridLayout * cardsLayout)
{
    QList<QPushButton *> dayCards;

    for (int i=0; i<cardsLayout->count(); i++)
    {
        if(cardsLayout->itemAt(i)->widget()->objectName() == "MonthBoardDayCard")
        {
            QPushButton * dayCard = dynamic_cast<QPushButton *>(cardsLayout->itemAt(i)->widget());
            dayCards.push_back(dayCard);
        }
    }

    dayCards[0]->setObjectName("MonthBoardDayCardTopLeftCorner");
    dayCards[MAX_ROW_SIZE-1]->setObjectName("MonthBoardDayCardTopRightCorner");
    dayCards[maxNumberOfCards-MAX_ROW_SIZE]->setObjectName("MonthBoardDayCardBottomLeftCorner");
    dayCards[maxNumberOfCards-1]->setObjectName("MonthBoardDayCardBottomRightCorner");

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
