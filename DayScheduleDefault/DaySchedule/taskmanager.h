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
    QTimer * taskSeekingTimer;

    void resetTask();

public:
    TaskManager();
    ~TaskManager() {}

    QTime getFromTime() const;
    QTime getToTime() const;
    QString getDescription() const;

    QTime getTimeTillEndOfTask();

public slots:
    void updateTask();
    void updateTaskLive(QTime fromT, QTime toT, QString descript);
    void startSeekingForTask();

signals:
    void updated();
};

#endif // TASKMANAGER_H
