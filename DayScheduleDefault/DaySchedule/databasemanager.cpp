#include "databasemanager.h"

DatabaseManager & DatabaseManager::getInstance()
{
    static DatabaseManager instance;

    return instance;
}

DatabaseManager::~DatabaseManager()
{
    database.close();
}

void DatabaseManager::resetDatabaseToDefault()
{
    QSqlQuery query(database);

    query.prepare("DELETE FROM activity");
    execQuery(query);
    query.prepare("DELETE FROM day");
    execQuery(query);
    query.prepare("DELETE FROM month");
    execQuery(query);
    query.prepare("DELETE FROM year");
    execQuery(query);
    query.prepare("DELETE FROM years");
    execQuery(query);

    vacuumDatabase();
    dbAddress = "";
}

void DatabaseManager::vacuumDatabase()
{
    QSqlQuery query(database);
    query.prepare("VACUUM");
    execQuery(query);
}

bool DatabaseManager::connect(QString databaseAddress)
{
    if(!alreadyConnected())
    {
        if(QFile::exists(databaseAddress))
        {
            dbAddress = databaseAddress;

            database = QSqlDatabase::addDatabase("QSQLITE", "defaultConnection");
            database.setDatabaseName(dbAddress);

            if(database.open())
                return true;
        }
    }
    return false;
}

bool DatabaseManager::alreadyConnected()
{
    if(database.isOpen())
    {
        QSqlQuery query(database);
        query.prepare("SELECT 1 FROM years");

        if(query.exec())
            return true;
    }
    return false;
}

void DatabaseManager::closeDatabase()
{
    if(alreadyConnected())
    {
        database.close();
        database = QSqlDatabase();
        database.removeDatabase("defaultConnection");
    }
}

QString DatabaseManager::getDatabaseAdress() const
{
    return dbAddress;
}

QString DatabaseManager::getDefaultDbAddress() const
{
    return defaultDbAddress;
}

void DatabaseManager::setDefaultDbAddress(const QString & defaultAddress)
{
    defaultDbAddress = defaultAddress;
}

QString DatabaseManager::lastError()
{
    return database.lastError().databaseText();
}

bool DatabaseManager::execQuery(QSqlQuery & query)
{
    if(alreadyConnected())
    {
        if(query.exec())
            return true;
    }
    return false;
}

bool DatabaseManager::recordAlreadyExists(QSqlQuery & query)
{
    execQuery(query);

    return query.next();
}

QSqlQuery DatabaseManager::yearsCheckIfExistsQuery(int id)
{
    QSqlQuery query(database);
    query.prepare("SELECT 1 FROM years WHERE years_id=:id LIMIT 1");
    query.bindValue(":id", id);
    return query;
}

QSqlQuery DatabaseManager::yearsUpdateQuery(int id, QString description)
{
    QSqlQuery query(database);
    query.prepare("UPDATE years SET description = :description WHERE years_id=:id");
    query.bindValue(":description", description);
    query.bindValue(":id", id);
    return query;
}

QSqlQuery DatabaseManager::yearsInsertQuery(int id, QString description)
{
    QSqlQuery query(database);
    query.prepare("INSERT INTO years (years_id, description)"
                   "VALUES (:id, :description)");
    query.bindValue(":id", id);
    query.bindValue(":description", description);
    return query;
}

QSqlQuery DatabaseManager::yearsSelectDescriptionQuery(int id)
{
    QSqlQuery query(database);
    query.prepare("SELECT description FROM years WHERE years_id=:id");
    query.bindValue(":id", id);
    return query;
}

QSqlQuery DatabaseManager::yearCheckIfExistsQuery(int id)
{
    QSqlQuery query(database);
    query.prepare("SELECT 1 FROM year WHERE year_id=:id LIMIT 1");
    query.bindValue(":id", id);
    return query;
}

QSqlQuery DatabaseManager::yearUpdateQuery(int id, QString description)
{
    QSqlQuery query(database);
    query.prepare("UPDATE year SET description=:description WHERE year_id=:id");
    query.bindValue(":description", description);
    query.bindValue(":id", id);
    return query;
}

QSqlQuery DatabaseManager::yearInsertQuery(int id, QString description)
{
    QSqlQuery query(database);
    query.prepare("INSERT INTO year (year_id, description)"
                   "VALUES (:id, :description)");
    query.bindValue(":id", id);
    query.bindValue(":description", description);
    return query;
}

QSqlQuery DatabaseManager::yearSelectDescriptionQuery(int id)
{
    QSqlQuery query(database);
    query.prepare("SELECT description FROM year WHERE year_id=:id");
    query.bindValue(":id", id);
    return query;
}

QSqlQuery DatabaseManager::monthCheckIfExistsQuery(int monthId, int yearId)
{
    QSqlQuery query(database);
    query.prepare("SELECT 1 FROM month "
                  "WHERE month_id=:mid AND year_id=:yid LIMIT 1");
    query.bindValue(":mid", monthId);
    query.bindValue(":yid", yearId);
    return query;
}

QSqlQuery DatabaseManager::monthUpdateQuery(int m_id, int yearId, QString description)
{
    QSqlQuery query(database);
    query.prepare("UPDATE month SET description = :description "
                  "WHERE month_id=:mid AND year_id=:yid");
    query.bindValue(":description", description);
    query.bindValue(":mid", m_id);
    query.bindValue(":yid", yearId);
    return query;
}

QSqlQuery DatabaseManager::monthInsertQuery(int m_id, int yearId, QString description)
{
    QSqlQuery query(database);
    query.prepare("INSERT INTO month (month_id, year_id, description)"
                  "VALUES (:mid, :yid, :description)");
    query.bindValue(":mid", m_id);
    query.bindValue(":yid", yearId);
    query.bindValue(":description", description);
    return query;
}

QSqlQuery DatabaseManager::monthSelectDescriptionQuery(int m_id, int yearId)
{
    QSqlQuery query(database);
    query.prepare("SELECT description FROM month "
                  "WHERE month_id=:mid AND year_id=:yid");
    query.bindValue(":mid", m_id);
    query.bindValue(":yid", yearId);
    return query;
}

QSqlQuery DatabaseManager::dayCheckIfExistsQuery(const QDate & id)
{
    QSqlQuery query(database);
    query.prepare("SELECT 1 FROM day WHERE day_id=:id LIMIT 1");
    query.bindValue(":id", id);
    return query;
}

QSqlQuery DatabaseManager::dayUpdateQuery(const QDate & id, int progress, bool alarmsEnabled)
{
    QSqlQuery query(database);
    query.prepare("UPDATE day SET progress=:progress, alarms_enabled=:alarmsEnabled "
                  "WHERE day_id=:id");
    query.bindValue(":progress", progress);
    query.bindValue(":alarmsEnabled", alarmsEnabled);
    query.bindValue(":id", id);
    return query;
}

QSqlQuery DatabaseManager::dayInsertQuery(const QDate & id, int progress, bool alarmsEnabled)
{
    QSqlQuery query(database);
    query.prepare("INSERT INTO day (day_id, progress, alarms_enabled)"
                  "VALUES (:id, :progress, :alarmsEnabled)");
    query.bindValue(":id", id);
    query.bindValue(":progress", progress);
    query.bindValue(":alarmsEnabled", alarmsEnabled);
    return query;
}

QSqlQuery DatabaseManager::daySelectDataQuery(const QDate & id)
{
    QSqlQuery query(database);
    query.prepare("SELECT progress, alarms_enabled FROM day "
                  "WHERE day_id=:id");
    query.bindValue(":id", id);
    return query;
}

QSqlQuery DatabaseManager::dayUpdateAlarmsStateQuery(const QDate & id, bool alarmsEnabled)
{
    QSqlQuery query(database);
    query.prepare("UPDATE day SET alarms_enabled=:alarmsEnabled "
                  "WHERE day_id=:id");
    query.bindValue(":alarmsEnabled", alarmsEnabled);
    query.bindValue(":id", id);
    return query;
}

QSqlQuery DatabaseManager::daySelectActivityIntervals(const QDate & id)
{
    QSqlQuery query(database);
    query.prepare("SELECT from_time, to_time FROM activity WHERE day_id=:id");
    query.bindValue(":id", id);
    return query;
}

void DatabaseManager::dayDeleteActivitesFromDay(const QDate & id)
{
    QSqlQuery query(database);
    query.prepare("DELETE FROM activity WHERE day_id=:id");
    query.bindValue(":id", id);
    execQuery(query);
}

QSqlQuery DatabaseManager::actvCheckIfExistsQuery(const QDate & dayId,
                          const QTime & fromTime, const QTime & toTime)
{
    QSqlQuery query(database);
    query.prepare("SELECT 1 FROM activity WHERE day_id=:id "
                  "AND from_time=:from AND to_time=:to");
    query.bindValue(":id", dayId);
    query.bindValue(":from", fromTime);
    query.bindValue(":to", toTime);
    return query;
}

QSqlQuery DatabaseManager::actvInsertQuery(const QDate & dayId, QString state, QString description,
                                           const QTime & fromTime, const QTime & toTime)
{
    QSqlQuery query(database);
    query.prepare("INSERT INTO activity (day_id, state, description, from_time, to_time)"
                  "VALUES (:id, :state, :description, :from, :to)");
    query.bindValue(":id", dayId);
    query.bindValue(":state", state);
    query.bindValue(":description", description);
    query.bindValue(":from", fromTime);
    query.bindValue(":to", toTime);
    return query;
}

QSqlQuery DatabaseManager::actvUpdateQuery(const QDate & dayId, const QTime & fromTime,
                                           const QTime & toTime, QString state)
{
    QSqlQuery query(database);
    query.prepare("UPDATE activity SET state=:state WHERE day_id=:id "
                  "AND from_time=:from AND to_time=:to");
    query.bindValue(":id", dayId);
    query.bindValue(":state", state);
    query.bindValue(":from", fromTime);
    query.bindValue(":to", toTime);
    return query;
}

QSqlQuery DatabaseManager::actvSelectDataQuery(const QDate & dayId, const QTime & fromTime,
                                               const QTime & toTime)
{
    QSqlQuery query(database);
    query.prepare("SELECT state, from_time, to_time, description "
                  "FROM activity WHERE day_id=:id "
                  "AND from_time=:from AND to_time=:to");
    query.bindValue(":id", dayId);
    query.bindValue(":from", fromTime);
    query.bindValue(":to", toTime);
    return query;
}

QSqlQuery DatabaseManager::actvSelectStateQuery(const QDate &dayId, const QTime &fromTime,
                                                const QTime &toTime)
{
    QSqlQuery query(database);
    query.prepare("SELECT state FROM activity WHERE day_id=:id "
                  "AND from_time=:from AND to_time=:to");
    query.bindValue(":id", dayId);
    query.bindValue(":from", fromTime);
    query.bindValue(":to", toTime);
    return query;
}

QSqlQuery DatabaseManager::actvDeleteQuery(const QDate & dayId, const QTime & fromTime,
                                           const QTime & toTime)
{
    QSqlQuery query(database);
    query.prepare("DELETE FROM activity WHERE day_id=:id AND "
                  "from_time=:from AND to_time=:to");
    query.bindValue(":id", dayId);
    query.bindValue(":from", fromTime);
    query.bindValue(":to", toTime);
    return query;
}

QSqlQuery DatabaseManager::taskSelectCurrentActivity()
{ 
    QSqlQuery query(database);
    query.prepare("SELECT from_time, to_time, description FROM activity "
                  "WHERE :time >= from_time AND :time <= to_time "
                  "AND day_id = :date AND state = 'active'");
    query.bindValue(":time", QTime::currentTime());
    query.bindValue(":date", QDate::currentDate());
    return query;
}

QSqlQuery DatabaseManager::statsSelectProductiveDaysNumber()
{
    QSqlQuery query(database);
    query.prepare("SELECT count(*) FROM "
                  "(SELECT day.day_id FROM day "
                  "INNER JOIN activity ON day.day_id = activity.day_id "
                  "WHERE activity.state = 'success' "
                  "GROUP BY day.day_id "
                  "HAVING count(activity.state) > 0"
                  ") productive_days;");
    return query;
}

QSqlQuery DatabaseManager::statsCountActivitiesStates()
{
    QSqlQuery query(database);
    query.prepare("SELECT "
                  "(SELECT count(*) FROM activity "
                  "WHERE state = 'success') succeeded, "
                  "(SELECT count(*) FROM activity "
                  "WHERE state = 'fail') failed, "
                  "(SELECT count(*) FROM activity "
                  "WHERE state = 'active') blank;");
    return query;
}

QSqlQuery DatabaseManager::statsSelectBestYear()
{
    QSqlQuery query(database);
    query.prepare("SELECT year FROM "
                  "(SELECT strftime('%Y', day_id)year, count(*)succeeded FROM activity "
                  "WHERE year IN (SELECT DISTINCT strftime('%Y', day_id)year  FROM activity) "
                  "AND state = 'success' "
                  "GROUP BY year ORDER BY succeeded desc LIMIT 1)");
    return query;
}

bool DatabaseManager::getAlarmsStateForToday()
{
    QSqlQuery query(database);
    query.prepare("SELECT alarms_enabled FROM day WHERE day_id=:id");
    query.bindValue(":id", QDate::currentDate());
    execQuery(query);

    query.first();

    if(query.isValid())
        return query.value(0).toBool();
    else
        return false;
}
