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

    QSqlQuery dayCheckIfExistsQuery(QDate id);
    QSqlQuery dayUpdateQuery(QDate id, int progress, bool alarmsEnabled);
    QSqlQuery dayInsertQuery(QDate id, int progress, bool alarmsEnabled);
    QSqlQuery daySelectDataQuery(QDate id);
    QSqlQuery dayCountActivities(QDate id);

    QSqlQuery actvCheckIfExistsQuery(QDate dayId, QTime fromTime, QTime toTime);

    QSqlQuery actvSelectDataQuery(QDate dayId, QTime fromTime, QTime toTime);
};

#endif // DATABASEMANAGER_H
