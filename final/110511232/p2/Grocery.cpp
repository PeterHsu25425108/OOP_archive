#include"Grocery.h"
#include<iostream>
#include<iomanip>
using namespace std;

Grocery::Grocery(string name,string type,int price,int weight)
{
    this->name=name;
    this->type=type;
    this->price=price;
    this->weight=weight;
    quantity=1;
}

Grocery::Grocery(const Grocery& g)
{
    name=g.name;
    type=g.type;
    price=g.price;
    weight=g.weight;
    quantity=g.quantity;
}

ostream& operator<<(ostream& out,const Grocery& g)
{
	out<<left<<'|'<<right<<setw(10)<<g.name;
	out<<left<<'|'<<right<<setw(10)<<g.quantity;
	out<<left<<'|'<<right<<setw(10)<<g.price;
	out<<left<<'|'<<right<<setw(10)<<g.getTotal();
	out<<left<<'|'<<endl;
    return out;
}

void Grocery::operator=(const Grocery& g)
{
    name=g.name;
    type=g.type;
    price=g.price;
    weight=g.weight;
    quantity=g.quantity;
}

bool Grocery::operator<(const Grocery& big)
{
    if(type=="bread" && big.type!="bread")
        return true;
    else if(type=="fruit" && big.type=="drink")
        return true;
    else if(type==big.type && weight<big.weight)
        return true;
    else
        return false;
}

Grocery Grocery::operator++(int a)
{
    quantity++;
    return *this;
}