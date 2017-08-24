#include "taskmanager.h"

TaskManager::TaskManager()
{
    taskEndTimer = new QTimer(this);
    resetTask();
    taskSeekingTimer = new QTimer(this);

    connectTimers();
}

void TaskManager::resetTask()
{
    fromTime = QTime(0, 0);
    toTime = QTime(0, 0);
    description = QString("No task");

    taskEndTimer->stop();
}

void TaskManager::startSeekingForTask()
{
    taskSeekingTimer->start(60000);
    lookForTask();
}

void TaskManager::lookForTask()
{
    updateTask();
    if(toTime == QTime(0, 0))
        emit lookingForTask();
}

void TaskManager::endOfTask()
{
    taskEndTimer->stop();
    emit taskEnded();
}

void TaskManager::updateTask()
{
    DatabaseManager & db = DatabaseManager::getInstance();
    QSqlQuery query = db.taskSelectCurrentActivity();
    db.execQuery(query);

    query.first();
    if(query.isValid())
    {
        if(taskIsntTheSame(query.value(0).toTime(), query.value(1).toTime(), query.value(2).toString()))
        {
            fromTime = query.value(0).toTime();
            toTime = query.value(1).toTime();
            description = query.value(2).toString();

            taskSeekingTimer->stop();
            taskEndTimer->start(QTime::currentTime().msecsTo(toTime));

            emit updated();
            emit newTaskStarted();
        }
    }
    else if(toTime != QTime(0, 0))
    {
        resetTask();
        emit updated();
    }
}

void TaskManager::updateTaskLive(QTime fromT, QTime toT, QString descript)
{
    if(toT != QTime(0, 0))
    {
        if(taskIsntTheSame(fromT, toT, descript))
        {
            fromTime = fromT;
            toTime = toT;
            description = descript;

            taskSeekingTimer->stop();
            taskEndTimer->start(QTime::currentTime().msecsTo(toTime));

            emit updated();
            emit newTaskStarted();
        }
    }
    else if(toT != toTime)
    {
        resetTask();
        emit updated();
    }
}

bool TaskManager::taskIsntTheSame(QTime from, QTime to, QString des)
{
    if(fromTime != from || toTime != to || description != des)
        return true;

    return false;
}

QTime TaskManager::getFromTime() const
{
    return fromTime;
}

QTime TaskManager::getToTime() const
{
    return toTime;
}

QString TaskManager::getDescription() const
{
    return description;
}

QTime TaskManager::getTimeTillEndOfTask()
{
    if(toTime < QTime::currentTime())
        resetTask();

    if(toTime == QTime(0, 0))
        return QTime(0, 0);
    else
    {
        int msecTillEndOfTask = QTime::currentTime().msecsTo(toTime);
        return QTime(0, 0).addMSecs(msecTillEndOfTask);
    }
}

void TaskManager::clear()
{
    resetTask();
    taskSeekingTimer->stop();
    disconnectTimers();
}

void TaskManager::connectTimers()
{
    connect(taskEndTimer, SIGNAL(timeout()), this, SLOT(endOfTask()));
    connect(taskSeekingTimer, SIGNAL(timeout()), this, SLOT(lookForTask()));
}

void TaskManager::disconnectTimers()
{
    disconnect(taskEndTimer, SIGNAL(timeout()), this, SLOT(endOfTask()));
    disconnect(taskSeekingTimer, SIGNAL(timeout()), this, SLOT(lookForTask()));
}
