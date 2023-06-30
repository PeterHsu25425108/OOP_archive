#ifndef G_H
#define G_H
#include<iostream>
using namespace std;

class Grocery
{
protected:
    string name;
    string type;
    int price;
    int weight;
    int quantity;
public:
    string getName()const{return name;}
    string getType()const{return type;}
    int getPrice()const{return price;}
    int getWeight()const{return weight;}
    int getQuantity()const{return quantity;}
    int getTotal()const{return quantity*price;}
    Grocery(){;}
    Grocery(string name,string type,int price,int weight);
    Grocery(const Grocery&);
    friend ostream& operator<<(ostream& out,const Grocery& g);
    void operator=(const Grocery&);
    bool operator<(const Grocery&);
    Grocery operator++(int);
};

#endif