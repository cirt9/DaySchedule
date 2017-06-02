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
    void cleanup();

    void testNumberOfIntervalsReturnsZero();
    void testIntervalAddingWorksProperly();
    void testIntervalAddingThrowsException();
    void testIntervalRemovingReturnsTrue();
    void testIntervalRemovingReturnsFalse();
};

#endif // TESTTIMERANGESYSTEM_H
