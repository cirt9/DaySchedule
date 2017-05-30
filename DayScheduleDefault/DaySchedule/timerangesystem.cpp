#include "timerangesystem.h"

TimeRangeSystem::TimeRangeSystem()
{

}

void TimeRangeSystem::addInterval(const QTime from, const QTime to)
{
    Interval interval;

    interval.fromTime = from;
    interval.toTime = to;

    for(int i=0; i<intervals.size(); i++)
    {
        if(intervals[i].toTime < interval.fromTime && interval.toTime < intervals[i+1].fromTime)
        {
            //insert
            break;
        }
    }
}
