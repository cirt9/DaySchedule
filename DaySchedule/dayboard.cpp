#include "dayboard.h"

DayBoard::DayBoard(QWidget * parent) : QGroupBox(parent)
{
    setStyleSheet("DayBoard{background: rgb(255,240,235); border-radius: 10px;}");

    dayBoardLayout = new QVBoxLayout();
    dayBoardLayout->setSpacing(20);
    dayBoardLayout->setContentsMargins(0, 0, 0, 0);
    setLayout(dayBoardLayout);

    activitiesLayout = new QVBoxLayout();
    activitiesLayout->setSpacing(5);

    makeDateAndProgressLayout();
    dayBoardLayout->addLayout(activitiesLayout);
    makeBottomIconsLayout();

    addNewActivityLayout();
    addNewActivityLayout();
    addNewActivityLayout();
    addNewActivityLayout();
    addNewActivityLayout();
    addNewActivityLayout();
    addNewActivityLayout();
    addNewActivityLayout();
}


void DayBoard::makeDateAndProgressLayout()
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

void DayBoard::makeBottomIconsLayout()
{
    QHBoxLayout * iconsBarLayout = new QHBoxLayout();
    QGroupBox * iconsBarContainer = new QGroupBox();
    iconsBarContainer->setMaximumHeight(80);
    iconsBarContainer->setStyleSheet("background: rgb(51,102,153); padding: 10px;"
                                     "border-bottom-left-radius: 3px; border-bottom-right-radius: 3px;");
    iconsBarContainer->setLayout(iconsBarLayout);

    QPushButton * alarmsIcon = new QPushButton();
    alarmsIcon->setStyleSheet("background-image:url(:/placeholderimage.jpg); border: none");
    alarmsIcon->setFixedSize(40, 40);

    QPushButton * addNewIcon = new QPushButton();
    addNewIcon->setStyleSheet("background-image:url(:/placeholderimage.jpg); border: none");
    addNewIcon->setFixedSize(40, 40);

    QPushButton * deleteAllIcon = new QPushButton();
    deleteAllIcon->setStyleSheet("background-image:url(:/placeholderimage.jpg); border: none");
    deleteAllIcon->setFixedSize(40, 40);

    QPushButton * copyIcon = new QPushButton();
    copyIcon->setStyleSheet("background-image:url(:/placeholderimage.jpg); border: none");
    copyIcon->setFixedSize(40, 40);

    iconsBarLayout->addWidget(alarmsIcon);
    iconsBarLayout->addWidget(addNewIcon);
    iconsBarLayout->addWidget(deleteAllIcon);
    iconsBarLayout->addWidget(copyIcon);

    dayBoardLayout->addWidget(iconsBarContainer);
    dayBoardLayout->setAlignment(iconsBarContainer, Qt::AlignBottom);
}

void DayBoard::addNewActivityLayout()
{
    Activity * activity = new Activity();

    activitiesLayout->addWidget(activity);
    activities.push_back(activity);
}
