#ifndef TESTTIMERANGESYSTEM_H
#define TESTTIMERANGESYSTEM_H

#include <QString>
#include <QtTest>
#include "../DaySchedule/timerangesystem.h"

class TestTimeRangeSystem : public QObject
{
    Q_OBJECT
private:
    TimeRangeSystem timeSystem;

public:
    TestTimeRangeSystem();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();

    void testNumberOfIntervalsReturnsZero();
    void testIntervalAddingWorksProperly();
    void testIntervalAddingThrowsException();
};

#endif // TESTTIMERANGESYSTEM_H
