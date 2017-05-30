#ifndef TESTTIMERANGESYSTEM_H
#define TESTTIMERANGESYSTEM_H

#include <QString>
#include <QtTest>
#include "../DaySchedule/timerangesystem.h"

class TestTimeRangeSystem : public QObject
{
    Q_OBJECT

public:
    TestTimeRangeSystem();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testCase1();
};

#endif // TESTTIMERANGESYSTEM_H
