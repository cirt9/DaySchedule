#include "monthboard.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>

MonthBoard::MonthBoard(QWidget * parent) : QGroupBox(parent)
{
    //monthBoardLayout init
    QVBoxLayout * monthBoardLayout = new QVBoxLayout();
    setLayout(monthBoardLayout);

    //header

    QHBoxLayout * headerLayout = new QHBoxLayout();
    headerLayout->setSpacing(0);

    QLabel * monthName = new QLabel(QString("July"));
    monthName->setStyleSheet("background: grey;");
    monthName->setMaximumHeight(80);
    monthName->setAlignment(Qt::AlignCenter);

    headerLayout->addWidget(monthName);

    //day cards

    QGridLayout * cardsLayout = new QGridLayout();

    QWidget * card1 = new QWidget();
    card1->setMinimumSize(100, 100);
    card1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    card1->setStyleSheet("background: black;");

    QWidget * card2 = new QWidget();
    card2->setMinimumSize(100, 100);
    card2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    card2->setStyleSheet("background: black;");

    QWidget * card3 = new QWidget();
    card3->setMinimumSize(100, 100);
    card3->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    card3->setStyleSheet("background: black;");

    QWidget * card4 = new QWidget();
    card4->setMinimumSize(100, 100);
    card4->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    card4->setStyleSheet("background: black;");

    QWidget * card5 = new QWidget();
    card5->setMinimumSize(100, 100);
    card5->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    card5->setStyleSheet("background: black;");

    QWidget * card6 = new QWidget();
    card6->setMinimumSize(100, 100);
    card6->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    card6->setStyleSheet("background: black;");

    cardsLayout->addWidget(card1,0,0);
    cardsLayout->addWidget(card2,0,1);
    cardsLayout->addWidget(card3,0,2);
    cardsLayout->addWidget(card4,1,0);
    cardsLayout->addWidget(card5,1,1);
    cardsLayout->addWidget(card6,1,2);

    //footer

    QHBoxLayout * footerLayout = new QHBoxLayout();
    footerLayout->setSpacing(0);

    QLabel * footerText = new QLabel(QString("footer"));
    footerText->setStyleSheet("background: grey;");
    footerText->setMaximumHeight(80);
    footerText->setAlignment(Qt::AlignCenter);

    footerLayout->addWidget(footerText);

    //monthBoardLayout finish

    monthBoardLayout->addLayout(headerLayout);
    monthBoardLayout->addLayout(cardsLayout);
    monthBoardLayout->setAlignment(cardsLayout, Qt::AlignTop);
    monthBoardLayout->addLayout(footerLayout);
}
