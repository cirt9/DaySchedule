#include "databasemanager.h"

#include <QDebug>

DatabaseManager & DatabaseManager::getInstance()
{
    static DatabaseManager instance;

    return instance;
}

DatabaseManager::~DatabaseManager()
{
    database.close();
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

void DatabaseManager::connect(QString databaseAddress)
{
    if(!alreadyConnected())
    {
        if(QFile::exists(databaseAddress))
        {
            dbAddress = databaseAddress;

            database = QSqlDatabase::addDatabase("QSQLITE");
            database.setDatabaseName(dbAddress);

            if(!database.open())
                qDebug() << "Failed to open database.";
            else
                qDebug() << "Database opened.";
        }
        else
            qDebug() << "Database does not exsists";
    }
    else
        qDebug() << "Already connected";
}

void DatabaseManager::closeDatabase()
{
    database.close();
}

void DatabaseManager::execQuery(QSqlQuery & query)
{
    if(alreadyConnected())
    {
        if(query.exec())
            qDebug() << "query success";

        else
        {
            qDebug() << query.lastError();
            qDebug() << query.executedQuery();
        }
    }
}

bool DatabaseManager::recordAlreadyExists(QSqlQuery & query)
{
    execQuery(query);

    return query.next();
}

QSqlQuery DatabaseManager::yearsCheckIfExistsQuery(int id)
{
    QSqlQuery query;
    query.prepare("SELECT 1 FROM years WHERE years_id=:id LIMIT 1");
    query.bindValue(":id", id);
    return query;
}

QSqlQuery DatabaseManager::yearsUpdateQuery(int id, QString description)
{
    QSqlQuery query;
    query.prepare("UPDATE years SET description = :description WHERE years_id=:id");
    query.bindValue(":description", description);
    query.bindValue(":id", id);
    return query;
}

QSqlQuery DatabaseManager::yearsInsertQuery(int id, QString description)
{
    QSqlQuery query;
    query.prepare("INSERT INTO years (years_id, description)"
                   "VALUES (:id, :description)");
    query.bindValue(":id", id);
    query.bindValue(":description", description);
    return query;
}

QSqlQuery DatabaseManager::yearsSelectDescriptionQuery(int id)
{
    QSqlQuery query;
    query.prepare("SELECT description FROM years WHERE years_id=:id");
    query.bindValue(":id", id);
    return query;
}

QSqlQuery DatabaseManager::yearCheckIfExistsQuery(int id)
{
    QSqlQuery query;
    query.prepare("SELECT 1 FROM year WHERE year_id=:id LIMIT 1");
    query.bindValue(":id", id);
    return query;
}

QSqlQuery DatabaseManager::yearUpdateQuery(int id, QString description)
{
    QSqlQuery query;
    query.prepare("UPDATE year SET description=:description WHERE year_id=:id");
    query.bindValue(":description", description);
    query.bindValue(":id", id);
    return query;
}

QSqlQuery DatabaseManager::yearInsertQuery(int id, QString description)
{
    QSqlQuery query;
    query.prepare("INSERT INTO year (year_id, description)"
                   "VALUES (:id, :description)");
    query.bindValue(":id", id);
    query.bindValue(":description", description);
    return query;
}

QSqlQuery DatabaseManager::yearSelectDescriptionQuery(int id)
{
    QSqlQuery query;
    query.prepare("SELECT description FROM year WHERE year_id=:id");
    query.bindValue(":id", id);
    return query;
}

QSqlQuery DatabaseManager::monthCheckIfExists(int m_id, int y_id)
{
    QSqlQuery query;
    query.prepare("SELECT 1 FROM month "
                  "WHERE month_id=:mid AND year_id=:yid LIMIT 1");
    query.bindValue(":mid", m_id);
    query.bindValue(":yid", y_id);
    return query;
}

QSqlQuery DatabaseManager::monthUpdateQuery(int m_id, int y_id, QString description)
{
    QSqlQuery query;
    query.prepare("UPDATE month SET description = :description "
                  "WHERE month_id=:mid AND year_id=:yid");
    query.bindValue(":description", description);
    query.bindValue(":mid", m_id);
    query.bindValue(":yid", y_id);
    return query;
}

QSqlQuery DatabaseManager::monthInsertQuery(int m_id, int y_id, QString description)
{
    QSqlQuery query;
    query.prepare("INSERT INTO month (month_id, year_id, description)"
                   "VALUES (:mid, :yid, :description)");
    query.bindValue(":mid", m_id);
    query.bindValue(":yid", y_id);
    query.bindValue(":description", description);
    return query;
}

QSqlQuery DatabaseManager::monthSelectDescriptionQuery(int m_id, int y_id)
{
    QSqlQuery query;
    query.prepare("SELECT description FROM month "
                  "WHERE month_id=:mid AND year_id=:yid");
    query.bindValue(":mid", m_id);
    query.bindValue(":yid", y_id);
    return query;
}
