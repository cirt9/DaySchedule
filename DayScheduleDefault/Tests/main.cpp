#include <QtTest>
#include <testtimerangesystem.h>

int main(int argc, char** argv)
{
    TestTimeRangeSystem testTimeSystem;

    return QTest::qExec(&testTimeSystem, argc, argv);
}
