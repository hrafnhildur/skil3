#ifndef DATABASE_H
#define DATABASE_H

#include "scientist.h"
#include "computer.h"
#include <vector>

class Database
{
private:
public:
    Database();
    void openConnection();
    void createTables();
    void writeToDatabase(Scientist s);
    void writeToDatabase(Computer c);
    void getScientistTableBy(char choice, string s, vector<Scientist>& ss);
    void getComputerTableBy(char choice, string s, vector<Computer>& cc);
    Scientist getScientistById(int i);
    Computer getComputerById(int i);
    void removeScientistById(int id);
    void removeComputerById(int id);
    void joinTablesWhere(int sId, int cId);
    void getScientistsWhereComputer(int id, vector<Scientist>& ss);
    void getComputersWhereScientist(int id, vector<Computer>& cc);
};

#endif // DATABASE_H
