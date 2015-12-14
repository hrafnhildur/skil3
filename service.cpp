#include "service.h"
#include "database.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <ctime>
using namespace std;

Service::Service(){
    database.createTables();
}

void Service::addScientist(Scientist s){
    database.writeToDatabase(s);
    getScientistTable();
}

void Service::addComputer(Computer c){
    database.writeToDatabase(c);
    getComputerTable();
}

void Service::removeScientistAtId(int id){
    database.removeScientistById(id);
    getScientistTable();
}

void Service::removeComputerAtId(int id){
    database.removeComputerById(id);
    getComputerTable();
}

void Service::createRelation(int sId, int cId){
    database.joinTablesWhere(sId, cId);
}

void Service::getScientistTable(){
    scientists.clear();
    database.getScientistTableBy('a', "", scientists);
}

void Service::getComputerTable(){
    computers.clear();
    database.getComputerTableBy('a', "", computers);
}

Service Service::searchString(bool scientistMenu, string search){
    Service ss;
    if(scientistMenu){database.getScientistTableBy('s', search, ss.scientists);}
    else {database.getComputerTableBy('s', search, ss.computers);}
    return ss;
}

Service Service::searchName(bool scientistMenu, string search){
    Service ss;
    if(scientistMenu){database.getScientistTableBy('n', search, ss.scientists);}
    else {database.getComputerTableBy('n', search, ss.computers);}
    return ss;
}

Service Service::searchScientistsByComputer(int id){
    Service ss;
    database.getScientistsWhereComputer(id, ss.scientists);
    return ss;
}

Service Service::searchComputersByScientist(int id){
    Service ss;
    database.getComputersWhereScientist(id, ss.computers);
    return ss;
}

Service Service::searchScientistEra(int begin, int end) const{
    Service ss;
    if(end < begin){
        int t = begin;
        begin = end;
        end = t;
    }

    for(size_t i = 0; i < scientists.size(); i++){
        int yod = scientists.at(i).getYOD();
        if(yod == 0){ yod = currentYear(); }

        for(int j = begin; j <= end; j++){
            if(scientists.at(i).getYOB() <= j && j <= yod){
                ss.scientists.push_back(scientists.at(i));
                j = end;
            }
            else if(j > yod){j = end;}
            else if(j < scientists.at(i).getYOB()){
                j = scientists.at(i).getYOB();
            }
        }
    }
    return ss;
}

Service Service::searchComputerEra(int begin, int end) const{
    Service ss;
    if(end < begin){
        int t = begin;
        begin = end;
        end = t;
    }
    int year;
    for(size_t i = 0; i < computers.size(); i++){
        year = computers.at(i).getYear();
        if(year >= begin && year <= end){
            ss.computers.push_back(computers.at(i));
        }
    }
    return ss;
}

bool Service::scientistValidId(int id){
    getScientistTable();
    for(size_t i = 0; i < scientists.size(); ++i){
        if(scientists.at(i).getID() == id){
            return true;
        }
    }
    return false;
}

Scientist Service::getScientistById(int id){
    Scientist s = database.getScientistById(id);
    return s;
}

bool Service::computerValidId(int id){
    getComputerTable();
    for(size_t i = 0; i < computers.size(); ++i){
        if(computers.at(i).getID() == id){
            return true;
        }
    }
    return false;
}

Computer Service::getComputerById(int id){
    Computer c = database.getComputerById(id);
    return c;
}

//Non member functions to compare member variables
bool sortNameAscSci(const Scientist &lhs, const Scientist &rhs){
    return lhs.getName() < rhs.getName();
}
bool sortNameAscCmp(const Computer &lhs, const Computer &rhs){
    return lhs.getName() < rhs.getName();
}
bool sortNameDesSci(const Scientist &lhs, const Scientist &rhs){
    return lhs.getName() > rhs.getName();
}
bool sortNameDesCmp(const Computer &lhs, const Computer &rhs){
    return lhs.getName() > rhs.getName();
}
bool sortYearAscSci(const Scientist &lhs, const Scientist &rhs){
    return lhs.getYOB() < rhs.getYOB();
}
bool sortYearAscCmp(const Computer &lhs, const Computer &rhs){
    return lhs.getYear() < rhs.getYear();
}
bool sortYearDesSci(const Scientist &lhs, const Scientist &rhs){
    return lhs.getYOB() > rhs.getYOB();
}
bool sortYearDesCmp(const Computer &lhs, const Computer &rhs){
    return lhs.getYear() > rhs.getYear();
}
bool sortGenderAsc(const Scientist &lhs, const Scientist &rhs){
    return lhs.getGender() < rhs.getGender();
}
bool sortGenderDes(const Scientist &lhs, const Scientist &rhs){
    return lhs.getGender() > rhs.getGender();
}
bool sortTypeAsc(const Computer &lhs, const Computer &rhs){
    return lhs.getType() < rhs.getType();
}
bool sortTypeDes(const Computer &lhs, const Computer &rhs){
    return lhs.getType() > rhs.getType();
}

void Service::sortByName(){
    if(scientists.size() > 1){
        if(scientists.at(0).getName() > scientists.at(scientists.size()-1).getName()){
            sort(scientists.begin(), scientists.end(), sortNameAscSci);
        }
        else{ sort(scientists.begin(), scientists.end(), sortNameDesSci); }
    }
    if(computers.size() > 1){
        if(computers.at(0).getName() > computers.at(computers.size()-1).getName()){
            sort(computers.begin(), computers.end(), sortNameAscCmp);
        }
        else{ sort(computers.begin(), computers.end(), sortNameDesCmp); }
    }
}

void Service::sortByYear(){
    if(scientists.size() > 1){
        if(scientists.at(0).getYOB() > scientists.at(scientists.size()-1).getYOB()){
            sort(scientists.begin(), scientists.end(), sortYearAscSci);
        }
        else{ sort(scientists.begin(), scientists.end(), sortYearDesSci); }
    }
    if(computers.size() > 1){
        if(computers.at(0).getYear() > computers.at(computers.size()-1).getYear()){
            sort(computers.begin(), computers.end(), sortYearAscCmp);
        }
        else{ sort(computers.begin(), computers.end(), sortYearDesCmp); }
    }
}

void Service::sortByGender(){
    if(scientists.size() > 1){
        if(scientists.at(0).getGender() > scientists.at(scientists.size()-1).getGender()){
            sort(scientists.begin(), scientists.end(), sortGenderAsc);
        }
        else{ sort(scientists.begin(), scientists.end(), sortGenderDes); }
    }
}

void Service::sortByType(){
    if(computers.size() > 1){
        if(computers.at(0).getType() > computers.at(computers.size()-1).getType()){
            sort(computers.begin(), computers.end(), sortTypeAsc);
        }
        else{ sort(computers.begin(), computers.end(), sortTypeDes); }
    }
}

int Service::currentYear() const{
    time_t t = time(0);
    struct tm * now = localtime(&t);
    int year = now->tm_year + 1900;
    return year;
}

void Service::printScientists() const{
    cout << "---------------------------------------------------------------------------------" << endl;
    cout << "| ID  | NAME\t\t\t\t\t      | GENDER\t|  BORN |  DEAD |" << endl;
    cout << "---------------------------------------------------------------------------------" << endl;
    for(size_t i = 0; i < scientists.size(); i++){
        cout << scientists[i] << endl;
    }
    cout << "---------------------------------------------------------------------------------" << endl;
    cout << "|     | TOTAL: " << scientists.size() << "\t\t\t\t      | \t| \t| \t|" << endl;
    cout << "---------------------------------------------------------------------------------" << endl;
    cout << endl;
}

void Service::printComputers() const{
    cout << "---------------------------------------------------------------------------------" << endl;
    cout << "| ID  | NAME\t\t\t\t\t      | YEAR | TYPE\t  | BLT |" << endl;
    cout << "---------------------------------------------------------------------------------" << endl;
    for(size_t i = 0; i < computers.size(); i++){
        cout << computers[i] << endl;
    }
    cout << "---------------------------------------------------------------------------------" << endl;
    cout << "|     | TOTAL: " << computers.size() << "\t\t\t\t      |      | \t\t  |     |" << endl;
    cout << "---------------------------------------------------------------------------------" << endl;
    cout << endl;
}
