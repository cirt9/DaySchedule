#include "statistics.h"

Statistics::Statistics()
{
    update();
}

void Statistics::update()
{
    DatabaseManager & db = DatabaseManager::getInstance();
    QSqlQuery query = db.statsCountActivitiesStates();
    db.execQuery(query);
    query.first();
    numberOfSucceededActivities = query.value(0).toInt();
    numberOfFailedActivities = query.value(1).toInt();
    numberOfBlankActivities = query.value(2).toInt();

    query = db.statsSelectProductiveDaysNumber();
    db.execQuery(query);
    query.first();
    numberOfProductiveDays = query.value(0).toInt();

    query = db.statsSelectBestYear();
    db.execQuery(query);
    query.first();
    bestYear = query.value(0).toString();
}

int Statistics::getNumberOfSucceededActivities() const
{
    return numberOfSucceededActivities;
}

int Statistics::getNumberOfFailedActivities() const
{
    return numberOfFailedActivities;
}

int Statistics::getNumberOfBlankActivities() const
{
    return numberOfBlankActivities;
}

int Statistics::getNumberOfProductiveDays() const
{
    return numberOfProductiveDays;
}

QString Statistics::getBestYear() const
{
    return bestYear;
}

int Statistics::getSuccessRate()
{
    if(numberOfSucceededActivities + numberOfFailedActivities > 0)
        return numberOfSucceededActivities * 100 / (numberOfSucceededActivities + numberOfFailedActivities);

    else
        return 0;
}
