#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QString>
#include <QtSql>
#include <QFile>
#include <QDate>

class DatabaseManager
{
private:
    DatabaseManager() {}

    QSqlDatabase database;
    QString dbAddress;

    bool alreadyConnected();

public:
    DatabaseManager(DatabaseManager const &) = delete;
    void operator=(DatabaseManager const &) = delete;

    static DatabaseManager & getInstance();
    ~DatabaseManager();

    void connect(QString databaseAddress);
    void closeDatabase();

    void execQuery(QSqlQuery & query);
    bool recordAlreadyExists(QSqlQuery & query);

    QSqlQuery yearsCheckIfExistsQuery(int id);
    QSqlQuery yearsUpdateQuery(int id, QString description);
    QSqlQuery yearsInsertQuery(int id, QString description);
    QSqlQuery yearsSelectDescriptionQuery(int id);

    QSqlQuery yearCheckIfExistsQuery(int id);
    QSqlQuery yearUpdateQuery(int id, QString description);
    QSqlQuery yearInsertQuery(int id, QString description);
    QSqlQuery yearSelectDescriptionQuery(int id);

    QSqlQuery monthCheckIfExistsQuery(int monthId, int yearId);
    QSqlQuery monthUpdateQuery(int monthId, int yearId, QString description);
    QSqlQuery monthInsertQuery(int monthId, int yearId, QString description);
    QSqlQuery monthSelectDescriptionQuery(int monthId, int yearId);

    QSqlQuery dayCheckIfExistsQuery(const QDate & id);
    QSqlQuery dayUpdateQuery(const QDate & id, int progress, bool alarmsEnabled);
    QSqlQuery dayInsertQuery(const QDate & id, int progress, bool alarmsEnabled);
    QSqlQuery daySelectDataQuery(const QDate & id);
    QSqlQuery daySelectActivityIntervals(const QDate & id);

    QSqlQuery actvCheckIfExistsQuery(const QDate &dayId, const QTime &fromTime, const QTime &toTime);
    QSqlQuery actvInsertQuery(const QDate & dayId, QString state, QString description,
                              const QTime & fromTime, const QTime & toTime);
    QSqlQuery actvUpdateQuery(const QDate & dayId, const QTime & fromTime,
                              const QTime & toTime, QString state);
    QSqlQuery actvSelectDataQuery(const QDate &dayId, const QTime &fromTime, const QTime &toTime);
    QSqlQuery actvSelectStateQuery(const QDate &dayId, const QTime &fromTime, const QTime &toTime);
    QSqlQuery actvDeleteQuery(const QDate &dayId, const QTime &fromTime, const QTime &toTime);

    QSqlQuery taskSelectCurrentActivity();

    QSqlQuery settingsCheckIfExistsQuery();
    QSqlQuery settingsSelectDataQuery();
    QSqlQuery settingsUpdateQuery(bool alarmsEnabled);

    bool getAlarmsStateForToday();
};

#endif // DATABASEMANAGER_H
