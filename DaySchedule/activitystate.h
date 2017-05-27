#ifndef ACTIVITYSTATE_H
#define ACTIVITYSTATE_H

#include <QString>

class ActivityState
{
private:
    QString state;

public:
    ActivityState();
    ActivityState(const QString State);
    ~ActivityState() {}

    setState(const QString State);
    QString getState() const;

    static const QString INACTIVE;
    static const QString ACTIVE;
    static const QString SUCCESS;
    static const QString FAIL;
};

#endif // ACTIVITYSTATE_H
