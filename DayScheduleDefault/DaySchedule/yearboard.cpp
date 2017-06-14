#include "yearboard.h"

YearBoard::YearBoard(QWidget * parent) : QGroupBox(parent)
{
    yearBoardLayout = new QVBoxLayout();
    yearBoardLayout->setSpacing(20);
    yearBoardLayout->setContentsMargins(0, 0, 0, 0);
    setLayout(yearBoardLayout);

    setStyleSheet("background: black;");


    QHBoxLayout * headerLayout = new QHBoxLayout();

    QLabel * yearNumber = new QLabel(QString("2017"));
    yearNumber->setStyleSheet("background: white;");
    yearNumber->setMaximumHeight(80);
    yearNumber->setAlignment(Qt::AlignCenter);

    headerLayout->addWidget(yearNumber);

    yearBoardLayout->addLayout(headerLayout);



    QGridLayout * monthsCardsLayout = new QGridLayout();

    QPushButton * monthCard1 = new QPushButton();
    monthCard1->setStyleSheet("background:white;");
    monthCard1->setMinimumHeight(100);
    monthCard1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QPushButton * monthCard2 = new QPushButton();
    monthCard2->setStyleSheet("background:white;");
    monthCard2->setMinimumHeight(100);
    monthCard2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QPushButton * monthCard3 = new QPushButton();
    monthCard3->setStyleSheet("background:white;");
    monthCard3->setMinimumHeight(100);
    monthCard3->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QPushButton * monthCard4 = new QPushButton();
    monthCard4->setStyleSheet("background:white;");
    monthCard4->setMinimumHeight(100);
    monthCard4->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    monthsCardsLayout->addWidget(monthCard1, 0, 0);
    monthsCardsLayout->addWidget(monthCard2, 0, 1);
    monthsCardsLayout->addWidget(monthCard3, 1, 0);
    monthsCardsLayout->addWidget(monthCard4, 1, 1);

    yearBoardLayout->addLayout(monthsCardsLayout);
    yearBoardLayout->setAlignment(monthsCardsLayout, Qt::AlignTop);



    QHBoxLayout * footerLayout = new QHBoxLayout();

    QLabel * footerText = new QLabel(QString("Footer"));
    footerText->setStyleSheet("background: white;");
    footerText->setMaximumHeight(60);
    footerText->setAlignment(Qt::AlignCenter);

    footerLayout->addWidget(footerText);

    yearBoardLayout->addLayout(footerLayout);
}
