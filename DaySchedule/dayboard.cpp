#include "dayboard.h"

#include <QTimeEdit>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>

DayBoard::DayBoard(QWidget * parent) : QGroupBox(parent)
{
    setStyleSheet("DayBoard{background: rgb(255,240,235); border-radius: 10px;}");

    dayBoardLayout = new QVBoxLayout();
    dayBoardLayout->setSpacing(20);
    dayBoardLayout->setContentsMargins(0, 0, 0, 0);
    setLayout(dayBoardLayout);
    numberOfLayoutsInMainLayout = 0;

    makeDateAndProgressLayout();
    makeBottomIconsLayout();

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
                        "color: rgb(255,240,235); font-size: 35px; border-top-left-radius: 3px; border-bottom-left-radius: 3px");

    QLabel * progress = new QLabel("100%");
    progress->setMaximumHeight(80);
    progress->setAlignment(Qt::AlignCenter);
    progress->setMaximumWidth(120);
    progress->setStyleSheet("background: rgb(51,102,153); border-left: 2px dotted rgb(255,240,235); padding: 10px;"
                            "color: rgb(255,240,235); font-size: 35px; border-top-right-radius: 3px; border-bottom-right-radius: 3px");

    dateProgressLayout->addWidget(date);
    dateProgressLayout->addWidget(progress);

    dayBoardLayout->addLayout(dateProgressLayout);
    numberOfLayoutsInMainLayout++;
}

void DayBoard::makeBottomIconsLayout()
{
    QHBoxLayout * iconsBarLayout = new QHBoxLayout();
    QGroupBox * iconsBarContainer = new QGroupBox();
    iconsBarContainer->setMaximumHeight(80);
    iconsBarContainer->setStyleSheet("background: rgb(51,102,153); padding: 10px; border-radius: 3px;");
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
    numberOfLayoutsInMainLayout++;
}

void DayBoard::addNewActivityLayout()
{
    QGroupBox * activitiesContainer = new QGroupBox();
    activitiesContainer->setStyleSheet("background: rgb(51,102,153); margin-left: 20px; margin-right: 20px; border-radius: 3px;");

    QHBoxLayout * timeRangeLayout = new QHBoxLayout();
    QHBoxLayout * iconsLayout = new QHBoxLayout();

    QLabel * fromLabel = new QLabel();
    fromLabel->setText(QString("From: "));
    fromLabel->setStyleSheet("background: rgb(255,240,235); font-size: 20px; border-top-right-radius: 0px; border-bottom-right-radius: 0px; margin: 0px;");
    fromLabel->setAlignment(Qt::AlignCenter);
    fromLabel->setFixedHeight(50);

    QTimeEdit * fromTime = new QTimeEdit();
    fromTime->setStyleSheet("background: rgb(255,240,235); font-size: 20px; border-radius: 0px; margin: 0px;");
    fromTime->setFixedHeight(50);

    QLabel * toLabel = new QLabel();
    toLabel->setText(QString("To: "));
    toLabel->setStyleSheet("background: rgb(255,240,235); font-size: 20px; border-radius: 0px; margin: 0px;");
    toLabel->setAlignment(Qt::AlignCenter);
    toLabel->setFixedHeight(50);

    QTimeEdit * toTime = new QTimeEdit();
    toTime->setStyleSheet("background: rgb(255,240,235); font-size: 20px; border-top-left-radius: 0px; border-bottom-left-radius: 0px; margin: 0px;");
    toTime->setFixedHeight(50);

    timeRangeLayout->addWidget(fromLabel);
    timeRangeLayout->addWidget(fromTime);
    timeRangeLayout->addWidget(toLabel);
    timeRangeLayout->addWidget(toTime);
    timeRangeLayout->setSpacing(0);

    QPushButton * startIcon = new QPushButton();
    startIcon->setStyleSheet("background-image:url(:/placeholderimage.jpg) no-repeat center center fixed; border: none; margin: 0px;");
    startIcon->setFixedSize(40, 40);

    QPushButton * deleteIcon = new QPushButton();
    deleteIcon->setStyleSheet("background-image:url(:/placeholderimage.jpg) no-repeat center center fixed; border: none; margin: 0px;");
    deleteIcon->setFixedSize(40, 40);

    iconsLayout->addWidget(startIcon);
    iconsLayout->addWidget(deleteIcon);

    QHBoxLayout * timeAndIconsLayout = new QHBoxLayout();
    timeAndIconsLayout->addLayout(timeRangeLayout);
    timeAndIconsLayout->addLayout(iconsLayout);
    timeAndIconsLayout->setSpacing(20);

    QHBoxLayout * descriptionLayout = new QHBoxLayout();
    descriptionLayout->setSpacing(0);

    QLabel * descriptionLabel = new QLabel();
    descriptionLabel->setText(QString("Description: "));
    descriptionLabel->setStyleSheet("background: rgb(255,240,235);; font-size: 20px; border-top-right-radius: 0px; border-bottom-right-radius: 0px; margin: 0px;");
    descriptionLabel->setAlignment(Qt::AlignCenter);
    descriptionLabel->setFixedHeight(50);

    QLineEdit * description = new QLineEdit();
    description->setStyleSheet("background: rgb(255,240,235);; font-size: 20px; border-top-left-radius: 0px; border-bottom-left-radius: 0px; margin: 0px;");
    description->setFixedHeight(50);

    descriptionLayout->addWidget(descriptionLabel);
    descriptionLayout->addWidget(description);

    QVBoxLayout * activitiesContainerLayout = new QVBoxLayout();
    activitiesContainerLayout->addLayout(timeAndIconsLayout);
    activitiesContainerLayout->addLayout(descriptionLayout);

    activitiesContainer->setLayout(activitiesContainerLayout);

    dayBoardLayout->insertWidget(numberOfLayoutsInMainLayout-1, activitiesContainer);
    dayBoardLayout->setAlignment(activitiesContainer, Qt::AlignTop);
    numberOfLayoutsInMainLayout++;
}
