#include "dayboard.h"

DayBoard::DayBoard(QSharedPointer<QDate> currUsedDate, bool alarmsEnabled, QWidget * parent) :
BoardTemplate(currUsedDate, parent), timeSystem(new TimeRangeSystem)
{
    progress = nullptr;
    footerButtonsBarContainer = nullptr;
    currentActivityIndex = -1;

    createDateAndProgressLayout();
    createActivitiesLayout();
    createBottomMenuLayout();

    alarmsButton->setChecked(alarmsEnabled);
}

void DayBoard::createDateAndProgressLayout()
{
    QHBoxLayout * dateProgressLayout = new QHBoxLayout();
    dateProgressLayout->setSpacing(0);

    QString headerDateText = createHeaderDate();
    QLabel * date = new QLabel(headerDateText);
    date->setMaximumHeight(80);
    date->setMinimumWidth(400);
    date->setAlignment(Qt::AlignCenter);
    date->setObjectName("DayBoardDateLabel");

    progress = new QLabel("0%");
    progress->setMaximumHeight(80);
    progress->setAlignment(Qt::AlignCenter);
    progress->setFixedWidth(120);
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
    footerButtonsBarContainer = new QGroupBox();
    footerButtonsBarContainer->setMaximumHeight(80);
    footerButtonsBarContainer->setLayout(buttonsBarLayout);
    footerButtonsBarContainer->setObjectName("DayBoardButtonsBarContainer");

    QPushButton * addActivityButton = new QPushButton("Add New Activity");
    addActivityButton->setObjectName("DayBoardButton");
    connect(addActivityButton, SIGNAL(clicked()), this, SLOT(addNewActivity()));

    QPushButton * copyButton = new QPushButton("Copy Day");
    copyButton->setObjectName("DayBoardButton");
    connect(copyButton, SIGNAL(clicked()), this, SLOT(selectDateToCopyActivity()));

    QPushButton * clearButton = new QPushButton("Clear Activities");
    clearButton->setObjectName("DayBoardButton");
    connect(clearButton, SIGNAL(clicked()), this, SLOT(clearInactiveActivities()));

    alarmsButton = new QCheckBox();
    alarmsButton->setObjectName("DayBoardAlarmsButton");
    alarmsButton->setFixedSize(40, 40);

    buttonsBarLayout->addWidget(addActivityButton);
    buttonsBarLayout->addWidget(copyButton);
    buttonsBarLayout->addWidget(clearButton);
    buttonsBarLayout->addWidget(alarmsButton);

    boardLayout->addWidget(footerButtonsBarContainer);
    boardLayout->setAlignment(footerButtonsBarContainer, Qt::AlignBottom);
}

void DayBoard::addNewActivity()
{
    Activity * activity = createActivity();
    activitiesLayout->addWidget(activity);
    activities.push_back(activity);

    updateProgress();
}

Activity * DayBoard::createActivity()
{
    Activity * activity = new Activity(timeSystem, *currentlyUsedDate);
    connect(activity, SIGNAL(activityDeleted(QWidget*)), this, SLOT(eraseActivityFromList(QWidget*)));

    connect(activity, SIGNAL(fail()), this, SLOT(updateProgress()));
    connect(activity, SIGNAL(activityStarted()), this, SLOT(updateProgress()));
    connect(activity, &Activity::activityStarted, this,
           [=]{setCurrentActivityIndex(findCurrentActivityIndex());});
    connect(activity, SIGNAL(success()), this, SLOT(updateProgress()));
    connect(activity, SIGNAL(destroyed()), this, SLOT(updateProgress()));

    return activity;
}

void DayBoard::assignActivitesToCurrentlyUsedDate()
{
    for(auto activity : activities)
        activity->setAssignedDay(*currentlyUsedDate);
}

void DayBoard::selectDateToCopyActivity()
{
    footerButtonsBarContainer->setVisible(false);

    DateSelectingWidget * dateSelecting = new DateSelectingWidget();
    dateSelecting->setMaximumHeight(80);
    dateSelecting->setConfirmButtonText(QString("Copy"));
    dateSelecting->setDateRanges(QDate(2017, 1, 1), QDate(2093, 12, 31));

    connect(dateSelecting, SIGNAL(canceled()), this, SLOT(copyingCanceled()));
    connect(dateSelecting, SIGNAL(confirmed(QDate)), this, SLOT(copyingConfirmed(QDate)));

    boardLayout->insertWidget(boardLayout->count(), dateSelecting);
}

void DayBoard::copyingConfirmed(QDate selectedDate)
{
    deleteCopyDateSelectingWidget();
    footerButtonsBarContainer->setVisible(true);

    DatabaseManager & db = DatabaseManager::getInstance();
    QSqlQuery query = db.dayCheckIfExistsQuery(selectedDate);

    if(db.recordAlreadyExists(query))
    {
        clearAllActivities();
        QDate savedDate = *currentlyUsedDate;

        currentlyUsedDate->setDate(selectedDate.year(), selectedDate.month(), selectedDate.day());
        assignActivitesToCurrentlyUsedDate();
        load();

        currentlyUsedDate->setDate(savedDate.year(), savedDate.month(), savedDate.day());
        assignActivitesToCurrentlyUsedDate();
        save();
    }
    else
        QMessageBox::information(this, QString("Information"), QString("Day to copy doesn't exist."));
}

void DayBoard::copyingCanceled()
{
    deleteCopyDateSelectingWidget();
    footerButtonsBarContainer->setVisible(true);
}

void DayBoard::deleteCopyDateSelectingWidget()
{
    QWidget * dateSelectingWidget = boardLayout->itemAt(boardLayout->count()-1)->widget();

    LayoutDeleter deleter(dateSelectingWidget->layout(), true);
    deleter.clearLayout();
    delete dateSelectingWidget;
}

void DayBoard::clearAllActivities()
{
    auto it = activities.begin();
    while(it != activities.end())
    {
        if((*it)->getState() != ActivityState::INACTIVE)
            timeSystem->removeInterval((*it)->getFromTime(), (*it)->getToTime());

        LayoutDeleter deleter((*it)->layout(), true);
        deleter.clearLayout();
        (*it)->deleteLater();

        it = activities.erase(it);
    }
}

void DayBoard::clearInactiveActivities()
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
    setCurrentActivityIndex(findCurrentActivityIndex());
}

void DayBoard::eraseActivityFromList(QWidget * activity)
{
    for(auto it = activities.begin(); it != activities.end(); ++it)
    {
        if(*it == activity)
        {
            it = activities.erase(it);
            setCurrentActivityIndex(findCurrentActivityIndex());
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
    int numberOfInactiveActivities = 0;

    for(auto activity : activities)
    {
        if(activity->getState() == ActivityState::SUCCESS)
            numberOfSucceededActivities++;

        else if(activity->getState() == ActivityState::INACTIVE)
            numberOfInactiveActivities++;
    }
    int divider = activities.size() - numberOfInactiveActivities;

    if(divider == 0)
        return 0;
    else
        return numberOfSucceededActivities * 100 / divider;
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
        saveActivities();
    }
    else
    {
        query = db.dayInsertQuery(*currentlyUsedDate,
                                  getProgress(),
                                  alarmsButton->isChecked());
        db.execQuery(query);
        saveActivities();
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

        loadActivities();
    }
}

bool DayBoard::somethingChanged()
{
    DatabaseManager & db = DatabaseManager::getInstance();
    QSqlQuery query = db.daySelectDataQuery(*currentlyUsedDate);

    db.execQuery(query);
    query.first();

    if(query.value(0).toInt() == getProgress())
    {
        if(query.value(1).toBool() == alarmsButton->isChecked())
            return false;
    }
    return true;
}

void DayBoard::saveActivities()
{
    for(auto activity : activities)
        activity->save();
}

void DayBoard::loadActivities()
{
    DatabaseManager & db = DatabaseManager::getInstance();
    QSqlQuery query = db.daySelectActivityIntervals(*currentlyUsedDate);
    db.execQuery(query);

    while(query.next())
    {
        QTime from = query.value(0).toTime();
        QTime to = query.value(1).toTime();

        Activity * activity = createActivity();
        activitiesLayout->addWidget(activity);
        activities.push_back(activity);

        activity->load(from, to);
    }
}

int DayBoard::findCurrentActivityIndex()
{
    for(int i=0; i<activities.size(); i++)
    {
        if(QTime::currentTime() >= activities[i]->getFromTime() &&
           QTime::currentTime() <= activities[i]->getToTime() &&
           activities[i]->getState() == ActivityState::ACTIVE )
        {
            return i;
        }
    }
    return -1;
}

void DayBoard::setCurrentActivityIndex(int index)
{
    if(QDate::currentDate() == *currentlyUsedDate)
    {
        if(currentActivityIndex != index)
        {
            currentActivityIndex = index;
            if(currentActivityIndex == -1)
                emit currentActivityChanged(QTime(0, 0), QTime(0, 0), QString("No task"));

            else
            {
                emit currentActivityChanged(activities[currentActivityIndex]->getFromTime(),
                                            activities[currentActivityIndex]->getToTime(),
                                            activities[currentActivityIndex]->getDescription());
            }
        }
    }
}

void DayBoard::updateCurrentActivity()
{
    setCurrentActivityIndex(findCurrentActivityIndex());
}
