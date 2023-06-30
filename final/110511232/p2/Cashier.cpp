#include"Cashier.h"
#include<iostream>
#include<vector>
#include<map>
using namespace std;

int maxCustomer;
string title;
vector<Customer> customers;

Cashier::Cashier() : Person()
{

}

Cashier::Cashier(const Cashier& csh)
{
    while(customers.size()>0)
    {
        customers.pop_back();
    }

    this->Person::operator=((Person&)csh);
    maxCustomer=csh.maxCustomer;
    title=csh.title;

    for(int i=0;i<csh.customers.size();i++)
    {
        customers.push_back(csh.customers[i]);
    }
}

Cashier::Cashier(string name,int age,char gender,string title) : Person(name,gender,age)
{
    this->title=title;
    if(title=="junior")
    {
        maxCustomer=2;
    }
    else if(title=="senior")
    {
        maxCustomer=3;
    }
    /*else
    {
        cout<<"Invalid title "<<title<<endl;
    }*/
}

Cashier::~Cashier()
{

}

void Cashier::deleteCustomer(int idx)
{
    //cout<<"idx = "<<idx<<endl;
    vector<Customer>::iterator deleted = this->customers.begin();
    for(int i=0;i<idx;i++)
        deleted++;
    
    //cout<<"erase start "<<deleted->getName()<<endl;
    this->customers.erase(deleted);
    //cout<<"erase complete"<<endl;
}

void Cashier::pushCustomer(vector<Customer>& quene_vec)
{
    if(quene_vec.size()>0)
    {
        customers.push_back(quene_vec[0]);
        quene_vec.erase(quene_vec.begin());
    }
}

bool Cashier::reachMaxCustomer()const
{
    return (maxCustomer <= customers.size());
}

void Cashier::operator=(const Cashier& csh)
{
    while(customers.size()>0)
    {
        customers.pop_back();
    }

    this->Person::operator=((Person&)csh);
    maxCustomer=csh.maxCustomer;
    title=csh.title;

    for(int i=0;i<csh.customers.size();i++)
    {
        customers.push_back(csh.customers[i]);
    }
}

void Cashier::match_customer(vector<Customer>& quene_vec)
{

    if(customers.size()>=maxCustomer)
    {
        //cout<<"$: match didn't change anything"<<endl;
        return;
    }

    int quene_len = quene_vec.size();

    int insert_num = min(quene_len, (int)(maxCustomer-customers.size()));
    
    /*for(int i=0;i<quene_vec.size();i++)
    {
        cout<<"$: basket size of "<<quene_vec[i].getName()<<" in quene_vec after insert_num: "<<quene_vec[i].getBasket().size()<<endl;
    }*/
    
    //cout<<endl<<"$: insert_num in match_func: "<<insert_num<<endl<<endl;

    for(int i=0;i<insert_num;i++)
    {
        //cout<<"filling in quene customer "<<quene_vec[0].getName()<<endl;
        //exception happened!!!
        Customer element(quene_vec[0]);
        //cout<<"$: basket size of "<<element.getName()<<" of the element insert: "<<element.getBasket().size()<<endl;
        customers.push_back(element);
        //cout<<"$: basket size of "<<customers[customers.size()-1].getName()<<" after push into customers: "<<customers[customers.size()-1].getBasket().size()<<endl;
        quene_vec.erase(quene_vec.begin());

       /* if(quene_vec.size()==0 && i!=insert_num-1)
        {
            cout<<"!!: insert_num ERROR"<<endl;
        }*/
    }
}

void Cashier::printCustomer(int cus_idx)
{
    //cout<<"$$: Basket size: "<<customers[cus_idx].getBasket().size()<<endl;
    cout<<customers[cus_idx];
}