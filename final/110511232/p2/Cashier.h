#ifndef CAS_H
#define CAS_H
#include<iostream>
#include"Customer.h"
#include"Grocery.h"
#include"Person.h"
#include<vector>
#include<map>
using namespace std;

class Cashier : public Person
{
protected:
    int maxCustomer;
    string title;
    vector<Customer> customers;
public:
    int getMaxCustomer()const{return maxCustomer;}
    string getTitle()const{return title;}
    vector<Customer> getCustomers()const
    {
        return customers;
    }

    Cashier();
    Cashier(string name,int age,char gender,string title);
    ~Cashier();
    Cashier(const Cashier&);
    void deleteCustomer(int idx);
    void pushCustomer(vector<Customer>& quene_vec);
    void match_customer(vector<Customer>& quene_vec);
    bool reachMaxCustomer()const;
    void operator=(const Cashier&);
    void printCustomer(int cus_idx);
};

#endif