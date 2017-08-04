#include "taskmanager.h"

TaskManager::TaskManager()
{
    resetTask();
    taskSeekingTimer = new QTimer(this);
    connect(taskSeekingTimer, SIGNAL(timeout()), this, SLOT(updateTask()));
}

void TaskManager::resetTask()
{
    fromTime = QTime(0, 0, 0);
    toTime = QTime(0, 0, 0);
    description = QString("No task");
}

void TaskManager::updateTask()
{
    DatabaseManager & db = DatabaseManager::getInstance();
    QSqlQuery query = db.taskSelectCurrentActivity();
    db.execQuery(query);

    query.first();
    if(query.isValid())
    {
        fromTime = query.value(0).toTime();
        toTime = query.value(1).toTime();
        description = query.value(2).toString();

        taskSeekingTimer->stop();
        emit updated();
    }
    else if(toTime != QTime(0, 0, 0, 0))
    {
        resetTask();
        emit updated();
    }
}

void TaskManager::updateTaskLive(QTime fromT, QTime toT, QString descript)
{
    if(toT != QTime(0, 0, 0, 0))
    {
        fromTime = fromT;
        toTime = toT;
        description = descript;
        emit updated();
    }
    else
    {
        resetTask();
        emit updated();
    }
}

void TaskManager::startSeekingForTask()
{
    taskSeekingTimer->start(60000);
    updateTask();
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

    if(toTime == QTime(0, 0, 0))
        return QTime(0, 0, 0);
    else
    {
        int msecTillEndOfTask = QTime::currentTime().msecsTo(toTime);
        return QTime(0, 0).addMSecs(msecTillEndOfTask);
    }
}
