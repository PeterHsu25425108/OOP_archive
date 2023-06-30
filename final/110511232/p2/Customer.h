#ifndef CUS_H
#define CUS_H
#include<iostream>
#include"Person.h"
#include"Grocery.h"
#include<vector>
#include<map>
using namespace std;

class Customer : public Person
{
protected:
    int capacity;
    vector<Grocery> basket;
public:
    int getCapacity()const{return capacity;}
    vector<Grocery> getBasket()const{return basket;}

    Customer():Person(){;}
    ~Customer(){
        //cout<<"destructing "<<name<<endl;
    }
    Customer(const Customer&);
    Customer(string name,char gender,int age);
    friend ostream& operator<<(ostream&,const Customer&);
    bool basketFull()const;
    void buy(Grocery);
    void operator=(const Customer&);
};

#endif