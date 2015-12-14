#include "scientist.h"
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <ctime>
using namespace std;

Scientist::Scientist(){}

Scientist::Scientist(int id, string name, string gender, int yob, int yod){
    setID(id);
    setName(name);
    setGender(gender[0]);
    setYOB(yob);
    setYOD(yod);
}

int Scientist::currentYear() const{
    time_t t = time(0);
    struct tm * now = localtime(&t);
    int year = now->tm_year + 1900;
    return year;
}

void Scientist::setID(int i){
    id = i;
}

//Name validation and fixes
bool Scientist::setName(string n){
    for(size_t i = 0; i < n.length(); i++){
        if((islower(n[i]) && i == 0) || (islower(n[i]) && n[i-1] == ' ')) {
            n[i] = toupper(n[i]);
        }
        else if(n[i] == ' ' && n[i+1] == ' '){
            n.erase(n.begin()+i); i--;
        }
        else if(!islower(n[i])){
            if((isupper(n[i]) && i == 0) || (isupper(n[i]) && n[i-1] == ' ')){}
            else if((n[i] == '-' && islower(n[i-1])) || n[i] == ',' || n[i] == '.' || n[i] == ' '){}
            else if(isalpha(n[i])){
                n[i] = tolower(n[i]);
            }
            else {
                cout << "Invalid characther '" << n[i] << "'" << endl;
                return false;
            }
        }
    }
    name = n;
    return true;
}

bool Scientist::setGender(char s){
    if(s == 'F' || s == 'f'){
        gender = "Female";
        return true;
    } else if(s == 'M' || s == 'm'){
        gender = "Male";
        return true;
    }
    cout << "Invalid gender '" << s << "' only (F)emale or (M)ale valid" << endl;
    return false;
}

bool Scientist::setYOB(int y){
    if( y > currentYear()){
        cout << "Invalid Year of Birth '" << y << "'" << endl;
        return false;
    }
    YOB = y;
    return true;
}

bool Scientist::setYOD(int y){
    if(y != 0 && ( y <= getYOB() || y > currentYear() )){
        cout << "Invalid Year of Death '" << y << "'" << endl;
        cout << "Input '0' if '" << getName() << "' is still alive." << endl;
        return false;
    }
    YOD = y;
    return true;
}

int Scientist::getID() const{
    return id;
}

string Scientist::getName() const{
    return name;
}

string Scientist::getGender() const{
    return gender;
}

int Scientist::getYOB() const{
    return YOB;
}

int Scientist::getYOD() const{
    return YOD;
}

ostream& operator << (ostream& out, const Scientist s){
    out << "|"   << setw(4)  << right << s.getID();
    out << " | " << setw(45) << left  << s.getName();
    out << " | " << setw(7)  << left  << s.getGender();
    out << " | " << setw(5)  << right << s.getYOB();
    if(s.getYOD() == 0){
        out << " |       |";
    }
    else{
        out << " | " << setw(5) << s.getYOD() << " |";
    }
    return out;
}

