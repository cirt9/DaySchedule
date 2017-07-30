#include "taskmanager.h"

TaskManager::TaskManager()
{

}

void TaskManager::getCurrentTask(QTime & fromTime, QTime & toTime, QString & description)
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
    {
        qDebug() << "Not valid";
    }
}
