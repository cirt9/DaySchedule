#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QString>
#include <QtSql>
#include <QFile>

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

    QSqlQuery monthCheckIfExists(int m_id, int y_id);
    QSqlQuery monthUpdateQuery(int m_id, int y_id, QString description);
    QSqlQuery monthInsertQuery(int m_id, int y_id, QString description);
    QSqlQuery monthSelectDescriptionQuery(int m_id, int y_id);
};

#endif // DATABASEMANAGER_H
