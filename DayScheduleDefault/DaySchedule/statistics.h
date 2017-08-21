#ifndef STATISTICS_H
#define STATISTICS_H

#include <databasemanager.h>
#include <QString>

class Statistics
{
private:
    int numberOfSucceededActivities;
    int numberOfFailedActivities;
    int numberOfBlankActivities;
    int numberOfProductiveDays;
    QString bestYear;

public:
    Statistics();
    ~Statistics() {}

    void update();

    int getNumberOfSucceededActivities() const;
    int getNumberOfFailedActivities() const;
    int getNumberOfBlankActivities() const;
    int getNumberOfProductiveDays() const;
    QString getBestYear() const;
    int getSuccessRate();
};

#endif // STATISTICS_H
