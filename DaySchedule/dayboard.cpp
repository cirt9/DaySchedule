#include "dayboard.h"

#include <QLabel>
#include <QTimeEdit>
#include <QLineEdit>
#include <QCheckBox>
#include <QSpacerItem>

#include <QHBoxLayout>
#include <QVBoxLayout>

DayBoard::DayBoard(QWidget * parent) : QGroupBox(parent)
{
    setMaximumSize(800, 900);
    setStyleSheet("background: yellow; padding:10px;");

    //topLayout
    QHBoxLayout * topLayout = new QHBoxLayout();

    QLabel * icon = new QLabel();
    icon->setText("ICON");
    icon->setAlignment(Qt::AlignHCenter);
    icon->setStyleSheet("background: green");

    QLabel * date = new QLabel();
    date->setText("MONTH DAY YEAR");
    //date->setMaximumHeight(50);
    date->setAlignment(Qt::AlignHCenter);
    date->setStyleSheet("background: green");

    QLabel * progress = new QLabel();
    progress->setText("100%");
    progress->setAlignment(Qt::AlignHCenter);
    progress->setStyleSheet("background: green");

    topLayout->addWidget(icon);
    topLayout->addWidget(date);
    topLayout->addWidget(progress);

    //botLayout
    QHBoxLayout * botLayout = new QHBoxLayout();

    QTimeEdit * t = new QTimeEdit();
    QLineEdit * l = new QLineEdit();
    QCheckBox * c = new QCheckBox();
    t->setStyleSheet("background: green");
    l->setStyleSheet("background: green");
    c->setStyleSheet("background: green");

    botLayout->addWidget(t);
    botLayout->addWidget(l);
    botLayout->addWidget(c);

    //totalLayout

    QVBoxLayout * vLayout = new QVBoxLayout();
    vLayout->addLayout(topLayout);
    vLayout->addLayout(botLayout);

    setLayout(vLayout);
}
