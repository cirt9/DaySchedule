#include "activity.h"

Activity::Activity(QSharedPointer<TimeRangeSystem> tSystem, QDate date, QWidget * parent)
                   : QGroupBox(parent)
{
    fromTime = nullptr;
    toTime = nullptr;
    description = nullptr;
    summaryLayout = nullptr;
    state = ActivityState();
    timeSystem = tSystem;
    assignedDay = date;
    setFixedHeight(FIXED_HEIGHT_START_END);

    QHBoxLayout * timeRangeLayout = createTimeRangeLayout();
    QHBoxLayout * iconsLayout = createControlButtonsLayout();

    QHBoxLayout * timeAndIconsLayout = new QHBoxLayout();
    timeAndIconsLayout->addLayout(timeRangeLayout);
    timeAndIconsLayout->addLayout(iconsLayout);
    timeAndIconsLayout->setSpacing(20);

    QHBoxLayout * descriptionLayout = createDescriptionLayout();

    activityLayout = new QVBoxLayout();
    activityLayout->addLayout(timeAndIconsLayout);
    activityLayout->addLayout(descriptionLayout);

    setLayout(activityLayout);
}

QHBoxLayout * Activity::createTimeRangeLayout()
{
    QHBoxLayout * timeRangeLayout = new QHBoxLayout();

    QLabel * fromTimeLabel = new QLabel();
    fromTimeLabel->setText(QString("From: "));
    fromTimeLabel->setAlignment(Qt::AlignVCenter);
    fromTimeLabel->setFixedHeight(50);
    fromTimeLabel->setObjectName("ActivityFromTimeLabel");

    fromTime = new QTimeEdit();
    fromTime->setFixedHeight(50);
    fromTime->setObjectName("ActivityFromTimeEdit");

    QLabel * toTimeLabel = new QLabel();
    toTimeLabel->setText(QString("To: "));
    toTimeLabel->setAlignment(Qt::AlignCenter);
    toTimeLabel->setFixedHeight(50);
    toTimeLabel->setObjectName("ActivityToTimeLabel");

    toTime = new QTimeEdit();
    toTime->setFixedHeight(50);
    toTime->setObjectName("ActivityToTimeEdit");

    timeRangeLayout->addWidget(fromTimeLabel);
    timeRangeLayout->addWidget(fromTime);
    timeRangeLayout->addWidget(toTimeLabel);
    timeRangeLayout->addWidget(toTime);
    timeRangeLayout->setSpacing(0);

    return timeRangeLayout;
}

QHBoxLayout * Activity::createControlButtonsLayout()
{
    QHBoxLayout * controlButtonsLayout = new QHBoxLayout();

    readyButton = new QPushButton();
    readyButton->setFixedSize(40, 40);
    readyButton->setObjectName("ActivityReadyButton");
    connect(readyButton, SIGNAL(clicked()), this, SLOT(startActivity()));

    deleteButton = new QPushButton();
    deleteButton->setFixedSize(40, 40);
    deleteButton->setObjectName("ActivityDeleteButton");
    connect(deleteButton, SIGNAL(clicked()), this, SLOT(deleteActivity()));

    controlButtonsLayout->addWidget(readyButton);
    controlButtonsLayout->addWidget(deleteButton);

    return controlButtonsLayout;
}

QHBoxLayout * Activity::createDescriptionLayout()
{
    QHBoxLayout * descriptionLayout = new QHBoxLayout();
    descriptionLayout->setSpacing(0);

    descriptionLabel = new QLabel();
    descriptionLabel->setText(QString("Description: "));
    descriptionLabel->setAlignment(Qt::AlignCenter);
    descriptionLabel->setFixedHeight(50);
    descriptionLabel->setObjectName("ActivityDescriptionLabel");

    description = new QLineEdit();
    description->setMaxLength(100);
    description->setFixedHeight(50);
    description->setObjectName("ActivityDescriptionLineEdit");

    descriptionLayout->addWidget(descriptionLabel);
    descriptionLayout->addWidget(description);

    return descriptionLayout;
}

QHBoxLayout * Activity::createSummaryLayout()
{
    QHBoxLayout * summaryLayout = new QHBoxLayout();

    QPushButton * doneButton = new QPushButton("I did it!");
    doneButton->setObjectName("ActivityButton");
    connect(doneButton, SIGNAL(clicked()), this, SLOT(succeeded()));

    QPushButton * failedButton = new QPushButton("I failed!");
    failedButton->setObjectName("ActivityButton");
    connect(failedButton, SIGNAL(clicked()), this, SLOT(failed()));

    summaryLayout->addWidget(doneButton);
    summaryLayout->addWidget(failedButton);

    return summaryLayout;
}

void Activity::deleteActivity()
{
    if(getConfirmationOfActiveActivityDeletion())
    {
        emit activityDeleted(this);

        if(state.getState() != ActivityState::INACTIVE)
            timeSystem->removeInterval(fromTime->time(), toTime->time());

        LayoutDeleter deleter(this->layout(), true);
        deleter.clearLayout();

        if(state.getState() != ActivityState::INACTIVE)
            deleteActivityFromDatabase();

        delete this;
    }
}

bool Activity::getConfirmationOfActiveActivityDeletion()
{
    if(state.getState() == ActivityState::INACTIVE)
        return true;

    QMessageBox::StandardButton reply;
    reply = QMessageBox::information(this, "Information",
                                  "Please do not cheat by removing locked activities."
                                  "<br>Do you still want to delete this activity?",
                                  QMessageBox::Yes|QMessageBox::No);
    if(reply == QMessageBox::Yes)
        return true;
    else
        return false;
}

void Activity::startActivity()
{
    try
    {
        checkCorrectnessOfInput();
        timeSystem->addInterval(fromTime->time(), toTime->time());

        setFixedHeight(FIXED_HEIGHT_ACTIVATED);

        fromTime->setDisabled(true);
        toTime->setDisabled(true);
        description->setDisabled(true);
        readyButton->setDisabled(true);

        state.setState(ActivityState::ACTIVE);

        summaryLayout = createSummaryLayout();
        activityLayout->addLayout(summaryLayout);

        emit activityStarted();
    }
    catch(QString e)
    {
        QMessageBox::warning(this, QString("Failure"), e);
    }
}

void Activity::checkCorrectnessOfInput()
{
    if(fromTime->time() >= toTime->time())
        throw QString("Time does not run backwards.<br>You gave the wrong time!");

    if(description->text().isEmpty())
        throw QString("Description cannot be empty!");
}

void Activity::failed()
{
    if(activityHasEnded())
    {
        clearSummaryLayout();

        state.setState(ActivityState::FAIL);

        description->setStyleSheet("background: rgb(255, 154, 154);");
        descriptionLabel->setStyleSheet("background: rgb(255, 154, 154);");

        emit fail();
    }
    else
        QMessageBox::information(this, "Information", "You can't do this before the end of task.");
}

void Activity::succeeded()
{
    if(activityHasEnded())
    {
        clearSummaryLayout();

        state.setState(ActivityState::SUCCESS);

        description->setStyleSheet("background: rgb(177, 238, 144);");
        descriptionLabel->setStyleSheet("background: rgb(177, 238, 144);");

        emit success();
    }
    else
        QMessageBox::information(this, "Information", "You can't do this before the end of task.");
}

void Activity::clearSummaryLayout()
{
    LayoutDeleter deleter(summaryLayout, true, true);
    deleter.clearLayout();
    summaryLayout = nullptr;
    setFixedHeight(FIXED_HEIGHT_START_END);
}

bool Activity::activityHasEnded()
{
    bool activityHasEnded = assignedDay <= QDate::currentDate();
    if(assignedDay == QDate::currentDate())
        activityHasEnded = toTime->time() <= QTime::currentTime();

    return activityHasEnded;
}


QString Activity::getState() const
{
    return state.getState();
}

void Activity::setAssignedDay(QDate day)
{
    assignedDay = day;
}

QTime Activity::getFromTime() const
{
    return fromTime->time();
}

QTime Activity::getToTime() const
{
    return toTime->time();
}

QString Activity::getDescription() const
{
    return description->text();
}

void Activity::save()
{
    DatabaseManager & db = DatabaseManager::getInstance();
    QSqlQuery query = db.actvCheckIfExistsQuery(assignedDay, fromTime->time(), toTime->time());

    if(db.recordAlreadyExists(query) && state.getState() != ActivityState::INACTIVE)
    {
        if(stateChanged())
        {
            query = db.actvUpdateQuery(assignedDay, fromTime->time(), toTime->time(), state.getState());
            db.execQuery(query);
        }
    }
    else if(state.getState() != ActivityState::INACTIVE)
    {
        query = db.actvInsertQuery(assignedDay, getState(), description->text(),
                                   fromTime->time(), toTime->time());
        db.execQuery(query);
    }
}

void Activity::load(const QTime & fromT, const QTime & toT)
{
    DatabaseManager & db = DatabaseManager::getInstance();
    QSqlQuery query = db.actvCheckIfExistsQuery(assignedDay, fromT, toT);

    if(db.recordAlreadyExists(query))
    {
        query = db.actvSelectDataQuery(assignedDay, fromT, toT);
        db.execQuery(query);

        query.first();
        QString loadedState = query.value(0).toString();
        QTime loadedFromTime = query.value(1).toTime();
        QTime loadedToTime = query.value(2).toTime();
        QString loadedDescription = query.value(3).toString();

        fromTime->setTime(loadedFromTime);
        toTime->setTime(loadedToTime);
        description->setText(loadedDescription);

        startActivity();
        if(loadedState == ActivityState::SUCCESS)
            succeeded();

        else if(loadedState == ActivityState::FAIL)
            failed();
    }
}

bool Activity::stateChanged()
{
    DatabaseManager & db = DatabaseManager::getInstance();
    QSqlQuery query = db.actvSelectStateQuery(assignedDay, fromTime->time(), toTime->time());

    db.execQuery(query);
    query.first();

    if(query.value(0).toString() == state.getState())
        return false;

    return true;
}

void Activity::deleteActivityFromDatabase()
{
    DatabaseManager & db = DatabaseManager::getInstance();
    QSqlQuery query = db.actvCheckIfExistsQuery(assignedDay, fromTime->time(), toTime->time());

    if(db.recordAlreadyExists(query))
    {
        query = db.actvDeleteQuery(assignedDay, fromTime->time(), toTime->time());
        db.execQuery(query);
    }
}
