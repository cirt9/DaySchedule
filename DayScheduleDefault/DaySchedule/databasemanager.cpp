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
            qDebug() << query.lastError();
    }
}

bool DatabaseManager::recordAlreadyExists(QSqlQuery & query)
{
    execQuery(query);

    return query.next();
}
