#include<iostream>
#include"Person.h"
using namespace std;

Person::Person()
{

}

Person::Person(const Person&)
{
    this->name=name;
    this->gender=gender;
    this->age=age;
}

Person::Person(string name,char gender,int age)
{
    this->name=name;
    this->gender=gender;
    this->age=age;
}

Person::~Person()
{
    
}

void Person::operator=(const Person& p)
{
    name=p.name;
    gender=p.gender;
    age=p.age;
}

/*bool Person::operator==(const Person& p)
{

}*/