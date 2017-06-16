#include "listofyearsboard.h"

ListOfYearsBoard::ListOfYearsBoard(QWidget * parent) : QGroupBox(parent)
{
    yearsBoardLayout = new QVBoxLayout();
    yearsBoardLayout->setSpacing(20);
    yearsBoardLayout->setContentsMargins(0, 0, 0, 0);
    setLayout(yearsBoardLayout);

    createHeaderLayout();
    createYearsCardsLayout();
    createFooterLayout();
}

void ListOfYearsBoard::createHeaderLayout()
{
    QHBoxLayout * headerLayout = new QHBoxLayout();

    QLabel * headerText = new QLabel(QString("Header"));
    headerText->setObjectName("ListOfYearsBoardHeaderTextLabel");
    headerText->setMaximumHeight(80);
    headerText->setAlignment(Qt::AlignCenter);

    headerLayout->addWidget(headerText);

    yearsBoardLayout->addLayout(headerLayout);
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
            QPushButton * yearCard = new QPushButton(QString::number(year));
            yearCard->setObjectName("ListOfYearsBoardYearCard");
            yearCard->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

            yearsCardsLayout->addWidget(yearCard, row, column);
        }
    }
    roundEdgesOfTheCornerCards(yearsCardsLayout);

    yearsBoardLayout->addLayout(yearsCardsLayout);
}

void ListOfYearsBoard::roundEdgesOfTheCornerCards(QGridLayout * cardsLayout)
{
    QList<QPushButton *> yearCards;

    for (int i=0; i<cardsLayout->count(); i++)
    {
        if(cardsLayout->itemAt(i)->widget()->objectName() == "ListOfYearsBoardYearCard")
        {
            QPushButton * yearCard = dynamic_cast<QPushButton *>(cardsLayout->itemAt(i)->widget());
            yearCards.push_back(yearCard);
        }
    }

    yearCards[0]->setObjectName("ListOfYearsBoardYearCardTopLeftCorner");
    yearCards[COLUMNS-1]->setObjectName("ListOfYearsBoardYearCardTopRightCorner");
    yearCards[ROWS * COLUMNS - COLUMNS]->setObjectName("ListOfYearsBoardYearCardBottomLeftCorner");
    yearCards[ROWS * COLUMNS - 1]->setObjectName("ListOfYearsBoardYearCardBottomRightCorner");
}

void ListOfYearsBoard::createFooterLayout()
{
    QHBoxLayout * footerLayout = new QHBoxLayout();

    QLabel * footerText = new QLabel(QString("Footer"));
    footerText->setObjectName("ListOfYearsBoardFooterTextLabel");
    footerText->setMaximumHeight(80);
    footerText->setAlignment(Qt::AlignCenter);

    footerLayout->addWidget(footerText);

    yearsBoardLayout->addLayout(footerLayout);
}
