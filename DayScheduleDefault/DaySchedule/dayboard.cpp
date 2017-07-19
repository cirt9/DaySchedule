#include "dayboard.h"

DayBoard::DayBoard(QSharedPointer<QDate> currUsedDate, QWidget * parent) :
BoardTemplate(currUsedDate, parent), timeSystem(new TimeRangeSystem)
{
    progress = nullptr;

    createDateAndProgressLayout();
    createActivitiesLayout();
    createBottomMenuLayout();
}

void DayBoard::createDateAndProgressLayout()
{
    QHBoxLayout * dateProgressLayout = new QHBoxLayout();
    dateProgressLayout->setSpacing(0);

    QString headerDateText = createHeaderDate();
    QLabel * date = new QLabel(headerDateText);
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

    boardLayout->addLayout(dateProgressLayout);
}

QString DayBoard::createHeaderDate()
{
    QString date = currentlyUsedDate->toString("dd.MM.yyyy");

    QLocale locale(QLocale::English);
    QString dayName = locale.dayName(currentlyUsedDate->dayOfWeek());

    return date + QString(", ") + dayName;
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

    boardLayout->addWidget(scroll);
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

    alarmsButton = new QCheckBox();
    alarmsButton->setObjectName("DayBoardAlarmsButton");
    alarmsButton->setFixedSize(40, 40);

    buttonsBarLayout->addWidget(addActivityButton);
    buttonsBarLayout->addWidget(copyButton);
    buttonsBarLayout->addWidget(clearButton);
    buttonsBarLayout->addWidget(alarmsButton);

    boardLayout->addWidget(buttonsBarContainer);
    boardLayout->setAlignment(buttonsBarContainer, Qt::AlignBottom);
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

int DayBoard::getProgress()
{
    QString stringProgress = progress->text();
    stringProgress.chop(1);

    return stringProgress.toInt();
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

void DayBoard::save()
{
    DatabaseManager & db = DatabaseManager::getInstance();
    QSqlQuery query = db.dayCheckIfExistsQuery(*currentlyUsedDate);

    if(db.recordAlreadyExists(query))
    {
        if(somethingChanged())
        {
            query = db.dayUpdateQuery(*currentlyUsedDate,
                                      getProgress(),
                                      alarmsButton->isChecked());
            db.execQuery(query);
        }
    }
    else
    {
        query = db.dayInsertQuery(*currentlyUsedDate,
                                  getProgress(),
                                  alarmsButton->isChecked());
        db.execQuery(query);
    }
}

void DayBoard::load()
{
    DatabaseManager & db = DatabaseManager::getInstance();
    QSqlQuery query = db.dayCheckIfExistsQuery(*currentlyUsedDate);

    if(db.recordAlreadyExists(query))
    {
        query = db.daySelectDataQuery(*currentlyUsedDate);
        db.execQuery(query);

        query.first();
        QString loadedProgress = query.value(0).toString() + QString("%");
        bool loadedAlarmsState = query.value(1).toBool();

        progress->setText(loadedProgress);
        alarmsButton->setChecked(loadedAlarmsState);
    }
}

bool DayBoard::somethingChanged()
{
    DatabaseManager & db = DatabaseManager::getInstance();
    QSqlQuery query = db.daySelectDataQuery(*currentlyUsedDate);

    db.execQuery(query);
    query.first();

    if(query.value(0).toString() == progress->text())
        return false;
    else if(query.value(1).toBool() == alarmsButton->isChecked())
        return false;
    else
        return true;
}
