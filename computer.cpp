#include "computer.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <ctime>
using namespace std;

Computer::Computer() {}

Computer::Computer(int id, string name, int year, string type, string built){
    setID(id);
    setName(name);
    setYear(year);
    setType(type[0]);
    setBuilt(built[0]);
}

int Computer::currentYear() const{
    time_t t = time(0);
    struct tm * now = localtime(&t);
    int year = now->tm_year + 1900;
    return year;
}

void Computer::setID(int i){
    id = i;
}

bool Computer::setName(string n){
    if(n.length() < 1 || n.length() > 100){
        cout << "Invalid name '" << n << "'" << endl;
        return false;
    }
    name = n;
    return true;
}

bool Computer::setYear(int y){
    if( y > currentYear()){
        cout << "Invalid Year of Invention '" << y << "'" << endl;
        return false;
    }
    year = y;
    return true;
}

bool Computer::setType(char c){
    c = toupper(c);
    switch(c){
    case 'M':
        type = "Mechanical";
        return true;
    case 'E':
        type = "Electronic";
        return true;
    case 'T':
        type = "Transistor";
        return true;
    }
    cout << "Invalid type! Only (M)echanical, (E)lectronic or (T)ransistor Computers are valid" << endl;
    return false;
}

bool Computer::setBuilt(char c){
    c = toupper(c);
    switch(c){
    case 'Y':
        built = "Yes";
        return true;
    case 'N':
        built = "No";
        return true;
    }
    cout << "invalid input" << endl;
    return false;
}

int Computer::getID() const{
    return id;
}

string Computer::getName() const{
    return name;
}

int Computer::getYear() const{
    return year;
}

string Computer::getType() const{
    return type;
}

string Computer::getBuilt() const{
    return built;
}

ostream& operator << (ostream& out, const Computer c){
    out << "|"   << setw(4)  << right << c.getID();
    out << " | " << setw(45) << left  << c.getName();
    out << " | " << setw(4)  << right  << c.getYear();
    out << " | " << setw(10)  << left  << c.getType();
    out << " | " << setw(3)  << right << c.getBuilt();
    out << " |";
    return out;
}
