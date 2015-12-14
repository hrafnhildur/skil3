#ifndef COMPUTER_H
#define COMPUTER_H

#include <string>
using namespace std;

class Computer
{
private:
    int id;
    string name;
    int year;
    string type;
    string built;
public:
    Computer();
    Computer(int id, string name, int year, string type, string built);
    int currentYear() const;
    void setID(int i);
    bool setName(string n);
    bool setYear(int y);
    bool setType(char c);
    bool setBuilt(char c);
    int getID() const;
    string getName() const;
    int getYear() const;
    string getType() const;
    string getBuilt() const;

    friend ostream& operator << (ostream& out, const Computer c);
};

#endif // COMPUTER_H
