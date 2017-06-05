#include "dayboard.h"

DayBoard::DayBoard(QString date, QWidget * parent) : QGroupBox(parent), timeSystem(new TimeRangeSystem)
{
    dayBoardLayout = new QVBoxLayout();
    dayBoardLayout->setSpacing(20);
    dayBoardLayout->setContentsMargins(0, 0, 0, 0);
    setLayout(dayBoardLayout);

    progress = nullptr;
    alarmsEnabled = false;
    dayBoardDate = date;

    createDateAndProgressLayout();
    createActivitiesLayout();
    createBottomMenuLayout();
}

void DayBoard::createDateAndProgressLayout()
{
    QHBoxLayout * dateProgressLayout = new QHBoxLayout();
    dateProgressLayout->setSpacing(0);

    QLabel * date = new QLabel(dayBoardDate);
    date->setMaximumHeight(80);
    date->setAlignment(Qt::AlignCenter);
    date->setObjectName("DayBoardDateLabel");

    progress = new QLabel("0%");
    progress->setMaximumHeight(80);
    progress->setAlignment(Qt::AlignCenter);
    progress->setMaximumWidth(120);
    progress->setObjectName("DayBoardProgressLabel");

    dateProgressLayout->addWidget(date);
    dateProgressLayout->addWidget(progress);

    dayBoardLayout->addLayout(dateProgressLayout);
}

void DayBoard::createActivitiesLayout()
{
    activitiesLayout = new QVBoxLayout();
    activitiesLayout->setSpacing(20);
    activitiesLayout->setAlignment(Qt::AlignTop);
    activitiesLayout->setContentsMargins(30, 5, 30, 5);

    QLabel * activitiesTitle = new QLabel("Activities");
    activitiesTitle->setObjectName("DayBoardActivitiesTitleLabel");

    activitiesLayout->addWidget(activitiesTitle);
    activitiesLayout->setAlignment(activitiesTitle, Qt::AlignHCenter);

    createScrollBar();
}

void DayBoard::createScrollBar()
{
    QScrollArea * scroll = new QScrollArea();
    scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scroll->setWidgetResizable(true);
    scroll->setObjectName("DayBoardScroll");

    QWidget * scrollArea = new QWidget();
    scrollArea->setObjectName("DayBoardScrollArea");
    scrollArea->setLayout(activitiesLayout);
    scroll->setWidget(scrollArea);

    dayBoardLayout->addWidget(scroll);
}

void DayBoard::createBottomMenuLayout()
{
    QHBoxLayout * buttonsBarLayout = new QHBoxLayout();
    QGroupBox * buttonsBarContainer = new QGroupBox();
    buttonsBarContainer->setMaximumHeight(80);
    buttonsBarContainer->setLayout(buttonsBarLayout);
    buttonsBarContainer->setObjectName("DayBoardButtonsBarContainer");

    QPushButton * addActivityButton = new QPushButton("Add New Activity");
    addActivityButton->setObjectName("DayBoardButton");
    connect(addActivityButton, SIGNAL(clicked()), this, SLOT(addNewActivity()));

    QPushButton * copyButton = new QPushButton("Copy Other Day");
    copyButton->setObjectName("DayBoardButton");

    QPushButton * clearButton = new QPushButton("Clear Activities");
    clearButton->setObjectName("DayBoardButton");
    connect(clearButton, SIGNAL(clicked()), this, SLOT(clearActivities()));

    QCheckBox * alarmsButton = new QCheckBox();
    alarmsButton->setObjectName("DayBoardAlarmsButton");
    alarmsButton->setFixedSize(40, 40);
    connect(alarmsButton, SIGNAL(toggled(bool)), this, SLOT(setAlarmsState(bool)));

    buttonsBarLayout->addWidget(addActivityButton);
    buttonsBarLayout->addWidget(copyButton);
    buttonsBarLayout->addWidget(clearButton);
    buttonsBarLayout->addWidget(alarmsButton);

    dayBoardLayout->addWidget(buttonsBarContainer);
    dayBoardLayout->setAlignment(buttonsBarContainer, Qt::AlignBottom);
}

void DayBoard::addNewActivity()
{
    Activity * activity = new Activity(timeSystem);
    connect(activity, SIGNAL(activityDeleted(QWidget*)), this, SLOT(eraseActivityFromList(QWidget*)));

    connect(activity, SIGNAL(fail()), this, SLOT(updateProgress()));
    connect(activity, SIGNAL(success()), this, SLOT(updateProgress()));
    connect(activity, SIGNAL(destroyed()), this, SLOT(updateProgress()));

    activitiesLayout->addWidget(activity);
    activities.push_back(activity);

    updateProgress();
}

void DayBoard::clearActivities()
{
    auto it = activities.begin();
    while(it != activities.end())
    {
        if((*it)->getState() == ActivityState::INACTIVE)
        {
            LayoutDeleter deleter((*it)->layout(), true);
            deleter.clearLayout();
            (*it)->deleteLater();

            it = activities.erase(it);
        }
        else
            ++it;
    }
}

void DayBoard::setAlarmsState(bool state)
{
    alarmsEnabled = state;
}

void DayBoard::eraseActivityFromList(QWidget * activity)
{
    for(auto it = activities.begin(); it != activities.end(); ++it)
    {
        if(*it == activity)
        {
            it = activities.erase(it);
            break;
        }
    }
}

void DayBoard::updateProgress()
{
    QString updatedProgress = QString::number(calculateProgress()) + QString("%");

    progress->setText(updatedProgress);
}

int DayBoard::calculateProgress()
{
    int numberOfSucceededActivities = 0;

    for(auto activity : activities)
    {
        if(activity->getState() == ActivityState::SUCCESS)
            numberOfSucceededActivities++;
    }
    if(activities.size() == 0)
        return 0;

    else
        return numberOfSucceededActivities * 100 / activities.size();
}

bool DayBoard::getAlarmsEnabled() const
{
    return alarmsEnabled;
}

void DayBoard::setAlarmsEnabled(bool value)
{
    alarmsEnabled = value;
}
