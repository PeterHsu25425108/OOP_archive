#include<iostream>
#include"Person.h"
#include"Grocery.h"
#include<vector>
#include<map>
#include<iomanip>
#include"Customer.h"
#include<algorithm>
#include<cstdlib>
#include<string>
using namespace std;

Customer::Customer(string name,char gender,int age) : Person(name,gender,age)
{
    if(age<18)
        capacity=3;
    else if(gender=='M')
        capacity=5;
    else if(gender=='F')
        capacity=4;
    /*else
    {
        cout<<"Invalid gender: "<<gender<<endl<<"age: "<<age<<endl;
    }*/
}

Customer::Customer(const Customer& cus)
{
    while(basket.size()>0)
    {
        basket.pop_back();
    }
    this->Person::operator=((Person&)cus);
    capacity=cus.capacity;

    int basket_len=cus.basket.size();
    //cout<<"@: basket size in copy constructor copying "<<cus.name<<basket_len<<endl;
    for(int i=0;i<basket_len;i++)
    {
        basket.push_back(cus.basket[i]);
    }
}

ostream& operator<<(ostream& out,const Customer& cus)
{
    string outstr = "|Name: "+ cus.name;
    out<<outstr<<setw(45-outstr.length())<<right<<"|"<<endl;
    out<<"+-------------------------------------------+"<<endl;
    out<<left<<'|'<<right<<setw(10)<<"item";
	out<<left<<'|'<<right<<setw(10)<<"quantity";
	out<<left<<'|'<<right<<setw(10)<<"unit price";
	out<<left<<'|'<<right<<setw(10)<<"total";
    out<<left<<'|'<<endl;
    
    int total=0;
    //vector<Grocery> basket;
    //cout<<"$: "<<cus.basket.size()<<endl;
    for(vector<Grocery>::const_iterator i=cus.basket.begin();i!=cus.basket.end();i++)
    {
        total+=i->getTotal();
        out<<*i;
    }
    
    string k = "total amount: "+to_string(total)+"|";
    out<<left<<"|"<<setw(44)<<right<<k<<endl;
    out<<"+-------------------------------------------+"<<endl;
    return out;
}

bool Customer::basketFull()const
{
    int vec_len=basket.size();
    int count=0;
    for(int i=0;i<vec_len;i++)
    {
        count+=basket[i].getQuantity();
    }
    /*cout<<endl<<"vec_len: "<<vec_len<<endl;
    cout<<"capacity: "<<capacity<<endl<<endl;*/
    return (capacity<=count);
}

void Customer::buy(Grocery g)
{
    int prev_size = basket.size();
    
    bool found = false;
    int i;
    for(i=0;i<prev_size;i++)
    {
        if(basket[i].getName()==g.getName())
        {
            found = true;
            break;
        }
    }

    if(!found)
        basket.push_back(g);
    else
        basket[i]++;

    /*if(prev_size==basket.size())
        cout<<"!!: Grocery not insert in Customer::buy"<<endl;*/

    sort(basket.begin(),basket.end());
}

void Customer::operator=(const Customer& cus)
{
    while(basket.size()>0)
    {
        basket.pop_back();
    }

    //cout<<"%: this->basket size in operator= begining "<<name<<basket.size()<<endl;
    this->Person::operator=((Person&)cus);
    capacity=cus.capacity;

    int basket_len=cus.basket.size();
    //cout<<"%: basket size in operator= copying "<<cus.name<<basket_len<<endl;
    //cout<<"%: this->basket size in operator= before copy "<<name<<basket.size()<<endl;
    for(int i=0;i<basket_len;i++)
    {
        basket.push_back(cus.basket[i]);
    }
    //cout<<"%: this->basket size in operator= after copy "<<name<<basket.size()<<endl;
}