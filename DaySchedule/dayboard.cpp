#include "dayboard.h"

DayBoard::DayBoard(QWidget * parent) : QGroupBox(parent)
{
    setStyleSheet("DayBoard{background: rgb(255,240,235); border-radius: 10px;}");

    dayBoardLayout = new QVBoxLayout();
    dayBoardLayout->setSpacing(20);
    dayBoardLayout->setContentsMargins(0, 0, 0, 0);
    setLayout(dayBoardLayout);

    createDateAndProgressLayout();
    createActivitiesLayout();
    createScrollBar();
    createBottomMenuLayout();
}


void DayBoard::createDateAndProgressLayout()
{
    QHBoxLayout * dateProgressLayout = new QHBoxLayout();
    dateProgressLayout->setSpacing(0);

    QLabel * date = new QLabel("13.05.2017, Saturday");
    date->setMaximumHeight(80);
    date->setAlignment(Qt::AlignCenter);
    date->setStyleSheet("background: rgb(51,102,153); border-right: 2px dotted rgb(255,240,235); padding: 10px;"
                        "color: rgb(255,240,235); font-size: 35px; border-top-left-radius: 3px;");

    QLabel * progress = new QLabel("100%");
    progress->setMaximumHeight(80);
    progress->setAlignment(Qt::AlignCenter);
    progress->setMaximumWidth(120);
    progress->setStyleSheet("background: rgb(51,102,153); border-left: 2px dotted rgb(255,240,235); padding: 10px;"
                            "color: rgb(255,240,235); font-size: 35px; border-top-right-radius: 3px;");

    dateProgressLayout->addWidget(date);
    dateProgressLayout->addWidget(progress);

    dayBoardLayout->addLayout(dateProgressLayout);
}

void DayBoard::createActivitiesLayout()
{
    activitiesLayout = new QVBoxLayout();
    activitiesLayout->setSpacing(5);
    activitiesLayout->setAlignment(Qt::AlignTop);

    QLabel * activitiesTitle = new QLabel("Activities");
    activitiesTitle->setStyleSheet("color: rgb(51,102,153); font-size: 35px;");
    activitiesLayout->addWidget(activitiesTitle);
    activitiesLayout->setAlignment(activitiesTitle, Qt::AlignHCenter);
}

void DayBoard::createBottomMenuLayout()
{
    QHBoxLayout * buttonsBarLayout = new QHBoxLayout();
    QGroupBox * buttonsBarContainer = new QGroupBox();
    buttonsBarContainer->setMaximumHeight(80);
    buttonsBarContainer->setLayout(buttonsBarLayout);
    buttonsBarContainer->setStyleSheet("background: rgb(51,102,153); padding: 10px;"
                                       "border-bottom-left-radius: 3px; border-bottom-right-radius: 3px;");

    QPushButton * addActivityButton = new QPushButton("Add New Activity");
    connect(addActivityButton, SIGNAL(clicked()), this, SLOT(addNewActivity()));
    addActivityButton->setStyleSheet("QPushButton{background: rgb(46, 48, 51); border: 2px solid transparent;"
                                    "border-radius: 3px; font-size: 15px; color: rgb(255,240,235);}"
                                    "QPushButton:hover{background: rgb(22, 25, 27); border: 1px solid rgb(255,240,235);}"
                                    "QPushButton:pressed{border: 2px solid rgb(255,240,235);}");

    QPushButton * copyButton = new QPushButton("Copy Other Day");
    copyButton->setStyleSheet("QPushButton{background: rgb(46, 48, 51); border: 2px solid transparent;"
                            "border-radius: 3px; font-size: 15px; color: rgb(255,240,235);}"
                            "QPushButton:hover{background: rgb(22, 25, 27); border: 1px solid rgb(255,240,235);}"
                            "QPushButton:pressed{border: 2px solid rgb(255,240,235);}");

    QPushButton * deleteAllButton = new QPushButton("Delete All Activities");
    deleteAllButton->setStyleSheet("QPushButton{background: rgb(46, 48, 51); border: 2px solid transparent;"
                                 "border-radius: 3px; font-size: 15px; color: rgb(255,240,235);}"
                                 "QPushButton:hover{background: rgb(22, 25, 27); border: 1px solid rgb(255,240,235);}"
                                 "QPushButton:pressed{border: 2px solid rgb(255,240,235);}");

    QCheckBox * alarmsButton = new QCheckBox();
    alarmsButton->setFixedSize(40, 40);
    alarmsButton->setStyleSheet("QCheckBox{width: 40px; height: 40px; padding: 0px;}"
                                "QCheckBox::indicator{width: 40px; height: 40px;}"
                                "QCheckBox::indicator::unchecked{image: url(:/icons/icons/alarmsInactive.jpg);}"
                                "QCheckBox::indicator::checked{image: url(:/icons/icons/alarmsActive.jpg);}");

    buttonsBarLayout->addWidget(addActivityButton);
    buttonsBarLayout->addWidget(copyButton);
    buttonsBarLayout->addWidget(deleteAllButton);
    buttonsBarLayout->addWidget(alarmsButton);

    dayBoardLayout->addWidget(buttonsBarContainer);
    dayBoardLayout->setAlignment(buttonsBarContainer, Qt::AlignBottom);
}

void DayBoard::createScrollBar()
{
    QScrollArea * scroll = new QScrollArea();
    scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scroll->setWidgetResizable(true);
    scroll->setStyleSheet("QWidget{background: transparent; border: none;}"
                          "QScrollBar{background: rgb(51,102,153);}");

    QWidget * scrollArea = new QWidget();
    scrollArea->setLayout(activitiesLayout);
    scroll->setWidget(scrollArea);

    dayBoardLayout->addWidget(scroll);
}

void DayBoard::addNewActivity()
{
    Activity * activity = new Activity();

    activitiesLayout->addWidget(activity);
    activities.push_back(activity);
}
