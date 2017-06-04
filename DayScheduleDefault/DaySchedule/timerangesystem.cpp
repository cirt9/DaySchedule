#include "timerangesystem.h"

TimeRangeSystem::TimeRangeSystem()
{
    setMinimalTimeInterval();
    setMaximalTimeInterval();
}

void TimeRangeSystem::setMinimalTimeInterval()
{
    QTime minimumIntervalFrom(0, 0, 0, 0);
    QTime minimumIntervalTo(0, 0, 0, 0);
    Interval minimumIntervalRange;
    minimumIntervalRange.fromTime = minimumIntervalFrom;
    minimumIntervalRange.toTime = minimumIntervalTo;

    intervals.push_back(minimumIntervalRange);
}

void TimeRangeSystem::setMaximalTimeInterval()
{
    QTime maximumIntervalFrom(23, 59, 59, 999);
    QTime maximumIntervalTo(23, 59, 59, 999);
    Interval maximumIntervalRange;
    maximumIntervalRange.fromTime = maximumIntervalFrom;
    maximumIntervalRange.toTime = maximumIntervalTo;

    intervals.push_back(maximumIntervalRange);
}

void TimeRangeSystem::addInterval(const QTime from, const QTime to)
{
    Interval interval;

    interval.fromTime = from;
    interval.toTime = to;

    bool intervalAddedProperly = false;

    for(int i=0; i<intervals.size(); i++)
    {
        if(intervals[i].toTime <= interval.fromTime && interval.toTime <= intervals[i+1].fromTime)
        {
            intervals.insert(i+1, interval);
            intervalAddedProperly = true;
            break;
        }
    }

    if(intervalAddedProperly == false)
        throw QString("This time interval collides with other time intervals!");
}

int TimeRangeSystem::getNumberOfIntervals() const
{
    int minMaxIntervals = 2;
    return intervals.size() - minMaxIntervals;
}

void TimeRangeSystem::clear()
{
    auto itBegin = intervals.begin();
    itBegin++;
    auto itEnd = intervals.end();
    itEnd--;

    while(itBegin != itEnd)
        itBegin = intervals.erase(itBegin);
}

bool TimeRangeSystem::removeInterval(const QTime from, const QTime to)
{
    Interval toRemove;
    toRemove.fromTime = from;
    toRemove.toTime = to;

    int position = findIntervalIndex(toRemove);

    if(position != -1)
    {
        intervals.removeAt(position);
        return true;
    }
    else
        return false;
}

int TimeRangeSystem::findIntervalIndex(const Interval interval)
{
    for(int i=1; i<intervals.size()-1; i++)
    {
        if(intervals[i].fromTime == interval.fromTime && intervals[i].toTime == interval.toTime)
            return i;
    }

    return -1;
}
