#ifndef TIMERANGESYSTEM_H
#define TIMERANGESYSTEM_H

#include <QTime>
#include <QList>

class TimeRangeSystem
{
private:

    struct Interval
    {
        QTime fromTime;
        QTime toTime;
    };

    QList<Interval> intervals;

    int findInterval(const Interval interval);

public:
    TimeRangeSystem();
    ~TimeRangeSystem() {}

    void addInterval(const QTime from, const QTime to);
    bool removeInterval(const QTime from, const QTime to);

    int getNumberOfIntervals() const;
    void clear();
};

#endif // TIMERANGESYSTEM_H
