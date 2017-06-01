#include <testtimerangesystem.h>

TestTimeRangeSystem::TestTimeRangeSystem()
{

}

void TestTimeRangeSystem::initTestCase()
{
    timeSystem = TimeRangeSystem();
}

void TestTimeRangeSystem::cleanupTestCase()
{
    timeSystem.clear();

    QCOMPARE(timeSystem.getNumberOfIntervals(), 0);
}

void TestTimeRangeSystem::testNumberOfIntervalsReturnsZero()
{
    int zeroIntervals = timeSystem.getNumberOfIntervals();

    QCOMPARE(zeroIntervals, 0);
}

void TestTimeRangeSystem::testIntervalAddingWorksProperly()
{
    QTime fromTimeFirst(0, 0, 0, 0);
    QTime toTimeFirst(1, 0, 0, 0);
    timeSystem.addInterval(fromTimeFirst, toTimeFirst);

    QTime fromTimeSecond(1, 1, 0, 0);
    QTime toTimeSecond(12, 3, 0, 0);
    timeSystem.addInterval(fromTimeSecond, toTimeSecond);

    QCOMPARE(timeSystem.getNumberOfIntervals(), 2);
}

void TestTimeRangeSystem::testIntervalAddingThrowsException()
{
    QString exception = "Exception not thrown";

    try
    {
        QTime fromTimeFirst(1, 0, 0, 0);
        QTime toTimeFirst(2, 0, 0, 0);
        timeSystem.addInterval(fromTimeFirst, toTimeFirst);

        QTime fromTimeSecond(1, 4, 0, 0);
        QTime toTimeSecond(2, 5, 0, 0);
        timeSystem.addInterval(fromTimeSecond, toTimeSecond);
    }
    catch(QString e)
    {
        exception = e;
    }

    QCOMPARE(exception, QString("This time interval collides with other time intervals!"));
}
