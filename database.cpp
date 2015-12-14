#include "database.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <QtSql>
using namespace std;

Database::Database(){}

void Database::openConnection(){
    QSqlDatabase sqldb;
    sqldb = QSqlDatabase::addDatabase("QSQLITE");
    sqldb.setDatabaseName("cshistory.sqlite");
    if(!sqldb.open()){
        qFatal("Failed to connect to the database");
    }
}

void Database::createTables(){
    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS Scientists("
               "id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, "
               "name VARCHAR NOT NULL, "
               "gender VARCHAR NOT NULL, "
               "year_of_birth INT NOT NULL, "
               "year_of_death INT NOT NULL)");
    query.exec("CREATE TABLE IF NOT EXISTS Computers("
               "id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, "
               "name VARCHAR NOT NULL, "
               "year INT NOT NULL, "
               "type VARCHAR, "
               "built VARCHAR(3))");
    query.exec("CREATE TABLE IF NOT EXISTS ComputerCreators("
               "scientist_id INT, "
               "computer_id INT, "
               "FOREIGN KEY(scientist_id) REFERENCES Scientists(id) ON DELETE CASCADE, "
               "FOREIGN KEY(computer_id) REFERENCES Computers(rowid) ON DELETE CASCADE, "
               "PRIMARY KEY(scientist_id, computer_id))");
}

void Database::writeToDatabase(Scientist s){
    QSqlQuery query;
    QString qName = QString::fromStdString(s.getName());
    QString qGender = QString::fromStdString(s.getGender());
    QString qYOB = QString::number(s.getYOB());
    QString qYOD = QString::number(s.getYOD());
    query.exec("INSERT INTO Scientists(name, gender, year_of_birth, year_of_death)"
               "VALUES ('" + qName + "', '" + qGender + "', " + qYOB + ", " + qYOD + ")");
}

void Database::writeToDatabase(Computer c){
    QSqlQuery query;
    QString qName = QString::fromStdString(c.getName());
    QString qYear = QString::number(c.getYear());
    QString qType = QString::fromStdString(c.getType());
    QString qBuilt = QString::fromStdString(c.getBuilt());
    query.exec("INSERT INTO Computers(name, year, type, built)"
               "VALUES ('" + qName + "', " + qYear + ", '" + qType + "', '" + qBuilt + "')");
}

void Database::getScientistTableBy(char choice, string s, vector<Scientist>& ss){
    QSqlQuery query;
    QString search = QString::fromStdString(s);
    switch(choice){
    case 's':
        query.prepare("SELECT * FROM Scientists WHERE id = :search OR name = :search OR gender = :search OR year_of_birth = :search OR year_of_death = :search");
        query.bindValue(":search", search);
        query.exec();
        break;
    case 'a':
        query.exec("SELECT * FROM Scientists");
        break;
    case 'n':
        query.prepare("SELECT * FROM Scientists WHERE name LIKE '%' || :name || '%'");
        query.bindValue(":name", search);
        query.exec();
        break;
    }
    while(query.next()){
        int id = query.value("id").toInt();
        string name = query.value("name").toString().toStdString();
        string gender = query.value("gender").toString().toStdString();
        int yob = query.value("year_of_birth").toInt();
        int yod = query.value("year_of_death").toInt();
        Scientist s(id, name, gender, yob, yod);
        ss.push_back(s);
    }
}

void Database::getComputerTableBy(char choice, string s, vector<Computer>& cc){
    QSqlQuery query;
    QString search = QString::fromStdString(s);
    switch(choice){
    case 'a':
        query.exec("SELECT * FROM Computers");
        break;
    case 's':
        query.prepare("SELECT * FROM Computers WHERE id = :search OR name = :search OR year = :search OR built = :search");
        query.bindValue(":search", search);
        query.exec();
        break;
    case 'n':
        query.prepare("SELECT * FROM Computers WHERE name LIKE '%' || :name || '%'");
        query.bindValue(":name", search);
        query.exec();
        break;
    case 't':
        query.prepare("SELECT * FROM Computers WHERE type LIKE '%' || :type || '%'");
        query.bindValue(":type", search);
        query.exec();
        break;
    }
    while(query.next()){
        int id = query.value("id").toInt();
        string name = query.value("name").toString().toStdString();
        int year = query.value("year").toInt();
        string type = query.value("type").toString().toStdString();
        string built = query.value("built").toString().toStdString();
        Computer c(id, name, year, type, built);
        cc.push_back(c);
    }
}

Scientist Database::getScientistById(int i){
    QSqlQuery query;
    query.prepare("SELECT * FROM Scientists WHERE id = :id");
    query.bindValue(":id", i);
    query.exec();
    query.next();
    int id = query.value("id").toInt();
    string name = query.value("name").toString().toStdString();
    string gender = query.value("gender").toString().toStdString();
    int yob = query.value("year_of_birth").toInt();
    int yod = query.value("year_of_death").toInt();
    Scientist s(id, name, gender, yob, yod);
    return s;
}

Computer Database::getComputerById(int i){
    QSqlQuery query;
    query.prepare("SELECT * FROM Computers WHERE id = :id");
    query.bindValue(":id", i);
    query.exec();
    query.next();
    int id = query.value("id").toInt();
    string name = query.value("name").toString().toStdString();
    int year = query.value("year").toInt();
    string type = query.value("type").toString().toStdString();
    string built = query.value("built").toString().toStdString();
    Computer c(id, name, year, type, built);
    return c;
}

void Database::removeScientistById(int id){
    QSqlQuery query;
    query.prepare("DELETE FROM Scientists WHERE id = :id");
    query.bindValue(":id", id);
    query.exec();
}

void Database::removeComputerById(int id){
    QSqlQuery query;
    query.prepare("DELETE FROM Computers WHERE id = :id");
    query.bindValue(":id", id);
    query.exec();
}

void Database::joinTablesWhere(int sId, int cId){
    QSqlQuery query;
    QString qSid = QString::number(sId);
    QString qCid = QString::number(cId);
    query.exec("INSERT INTO ComputerCreators(scientist_id, computer_id)"
               "VALUES (" + qSid + ", " + qCid + ")");
}

void Database::getScientistsWhereComputer(int id, vector<Scientist>& ss){
    QSqlQuery query;
    query.prepare("SELECT scientist_id FROM ComputerCreators WHERE computer_id = :id");
    query.bindValue(":id", id);
    query.exec();
    while(query.next()){
        int sId = query.value("scientist_id").toInt();
        ss.push_back(getScientistById(sId));
    }
}

void Database::getComputersWhereScientist(int id, vector<Computer>& cc){
    QSqlQuery query;
    query.prepare("SELECT computer_id FROM ComputerCreators WHERE scientist_id = :id");
    query.bindValue(":id", id);
    query.exec();
    while(query.next()){
        int cId = query.value("computer_id").toInt();
        cc.push_back(getComputerById(cId));
    }
}
