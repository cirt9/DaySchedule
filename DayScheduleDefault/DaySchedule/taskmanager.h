#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include <databasemanager.h>
#include <QDate>

class TaskManager
{    
public:
    TaskManager();

    void getCurrentTask(QTime & fromTime, QTime & toTime, QString & description);
};

#endif // TASKMANAGER_H
