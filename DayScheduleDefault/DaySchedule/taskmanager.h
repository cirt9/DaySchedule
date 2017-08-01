#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include <databasemanager.h>
#include <QDate>
#include <QSharedPointer>
#include <QObject>

class TaskManager : public QObject
{
    Q_OBJECT
private:
    QTime fromTime;
    QTime toTime;
    QString description;

public:
    TaskManager();
    ~TaskManager() {}

    QTime getFromTime() const;
    QTime getToTime() const;
    QString getDescription() const;

    QTime getTimeTillEndOfTask() const;

public slots:
    void updateTask();

signals:
    void updated();
};

#endif // TASKMANAGER_H
