#ifndef P_H
#define P_H
#include<iostream>
using namespace std;

class Person
{
protected:
    string name;
    char gender;
    int age;
public:
    string getName()const{return name;}
    char getGender()const{return gender;}
    int getAge()const{return age;}
    Person();
    Person(const Person&);
    Person(string name,char gender,int age);
    ~Person();
    void operator=(const Person& p);
    //bool operator==(const Person& p);
};

#endif