#ifndef SCIENTIST_H
#define SCIENTIST_H

#include <string>
using namespace std;

class Scientist
{
private:
    int id;
    string name;
    string gender;
    int YOB;
    int YOD;
public:
    Scientist();
    Scientist(int id, string name, string gender, int yob, int yod);
    int currentYear() const;
    void setID(int i);
    bool setName(string n);
    bool setGender(char s);
    bool setYOB(int y);
    bool setYOD(int y);
    int getID() const;
    string getName() const;
    string getGender() const;
    int getYOB() const;
    int getYOD() const;

    friend ostream& operator << (ostream& out, const Scientist S);
};

#endif // SCIENTIST_H
