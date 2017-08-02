#include "taskmanager.h"

void TaskManager::resetTask()
{
    fromTime = QTime(0, 0, 0);
    toTime = QTime(0, 0, 0);
    description = QString("No task");
}

TaskManager::TaskManager()
{
    resetTask();
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
    }
    else
        resetTask();

    emit updated();
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
