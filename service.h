#ifndef SERVICE_H
#define SERVICE_H

#include "scientist.h"
#include "computer.h"
#include "database.h"
#include <vector>
using namespace std;

class Service
{
private:
    vector<Scientist> scientists;
    vector<Computer> computers;
    Database database;
public:
    Service();

    void addScientist(Scientist s);
    void addComputer(Computer c);
    void removeScientistAtId(int id);
    void removeComputerAtId(int id);
    void createRelation(int sId, int cId);

    void getScientistTable();
    void getComputerTable();

    Service searchString(bool menu, string search);
    Service searchName(bool menu, string search);
    Service searchScientistEra(int begin, int end) const;
    Service searchComputerEra(int begin, int end) const;
    Service searchScientistsByComputer(int id);
    Service searchComputersByScientist(int id);
    bool scientistValidId(int id);
    bool computerValidId(int id);
    Scientist getScientistById(int id);
    Computer getComputerById(int id);
    void sortByName();
    void sortByYear();
    void sortByGender();
    void sortByType();

    void printScientists() const;
    void printComputers() const;
    int currentYear() const;
};

#endif // SERVICE_H
