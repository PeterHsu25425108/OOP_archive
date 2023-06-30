#include"Customer.h"
#include"Cashier.h"
#include"Grocery.h"
#include<iostream>
#include<iomanip>
#include<vector>
#include<map>
#include<cmath>
#include<fstream>
#include<sstream>
using namespace std;

void parse_grocery(ifstream& in_file,map<string,Grocery> &g_map)
{
    string input;
    while(getline(in_file,input))
    {
        string label;
        stringstream ss(input);
        ss>>label;
        string type;
        int price,weight;
        ss>>type>>price>>weight;

        //Grocery(string name,string type,int price,int weight);
        g_map[label]=Grocery(label,type,price,weight);
    }
}

//pass buying by reference 
void enter(stringstream& ss,map<string,Customer> &buying)
{
    string name;
    int age;
    char gender;
    ss>>name>>age>>gender;
    //Customer(string name,char gender,int age)
    buying[name]=Customer(name,gender,age);
}

//pass buying by reference
void buy_func(stringstream& ss,map<string,Customer> &buying,map<string,Grocery> g_map)
{
    string buyer_name,item;
    ss>>buyer_name>>item;

    map<string,Customer>::iterator buyer_iter = buying.find(buyer_name);

    //exception
    /*if(buyer_iter==buying.end())
    {
        cout<<"Error: Buyer"<<buyer_name<<" of "<<item<<" not found in buy_func!!!"<<endl;
    }*/
    

    if(!(buyer_iter->second.basketFull()))
    {
        //int prev_size = buyer_iter->second.getBasket().size();
        //put the grocery into basket
        
        buyer_iter->second.buy(g_map.find(item)->second);

        /*Customer temp(buyer_iter->second);
        temp.buy(g_map.find(item)->second);
        buying[buyer_name] = temp;*/

        /*cout<<"Grocery of "<<buying.find(buyer_name)->second.getName()<<":";
        for(int i=0;i<buying.find(buyer_name)->second.getBasket().size();i++)
        {
            cout<<" "<<buying.find(buyer_name)->second.getBasket()[i].getName();
        }
        cout<<endl;*/

        /*if(prev_size==buying.find(buyer_name)->second.getBasket().size())
            cout<<"!!: Grocery not insert in buy_func"<<endl;*/
    }
    else
    {
        //Basket warning
        cout<<buyer_iter->second.getName()<<" can't buy anymore!"<<endl;
    }
}

void quene_func(stringstream& ss,map<string,Customer> & buying,vector<Customer> & quene_vec,vector<Cashier> &cashiers)
{
    string person;
    ss>>person;

    //int prev_size = quene_vec.size();

    //cout<<"$: basket size of "<<buying.find(person)->second.getName()<<" before push into quene: "<<buying.find(person)->second.getBasket().size()<<endl;

    /*for(int i=0;i<quene_vec.size();i++)
    {
        cout<<"$: basket size of "<<quene_vec[i].getName()<<" before push in quene_func: "<<quene_vec[i].getBasket().size()<<endl;
    }*/

    //customer transfer
    quene_vec.push_back((buying.find(person)->second));

    /*for(int i=0;i<quene_vec.size();i++)
    {
        cout<<"$: basket size of "<<quene_vec[i].getName()<<" after push in quene_func: "<<quene_vec[i].getBasket().size()<<endl;
    }*/
    
    //cout<<"$: basket size of "<<buying.find(person)->second.getName()<<" after push into quene: "<<quene_vec[quene_vec.size()-1].getBasket().size()<<endl;

    //exception
    /*if(prev_size==quene_vec.size())
    {
        cout<<endl<<"Error: "<<person<<" wasn't insert!!"<<endl;
        cout<<"The Customer to be insert: "<<endl;
        cout<<buying.find(person)->second<<endl;
    }*/

    /*for(int i=0;i<quene_vec.size();i++)
    {
        cout<<"$: basket size of "<<quene_vec[i].getName()<<" before erase in quene_func: "<<quene_vec[i].getBasket().size()<<endl;
    }*/

    buying.erase(person);

    /*for(int i=0;i<quene_vec.size();i++)
    {
        cout<<"$: basket size of "<<quene_vec[i].getName()<<" after erase in quene_func: "<<quene_vec[i].getBasket().size()<<endl;
    }*/

    //exception
    /*if(buying.find(person)!=buying.end())
    {
        cout<<"Error: "<<person<<" wasn't deleted!!"<<endl;
    }*/

    for(vector<Cashier>::iterator it = cashiers.begin();it!=cashiers.end();it++)
    {
        if(!(it->reachMaxCustomer()))
        {
            //customer transfer
            //cout<<"$: basket size before match_customer in quene: "<<endl;
            /*for(int i=0;i<quene_vec.size();i++)
            {
                cout<<"$: basket size of "<<quene_vec[i].getName()<<" after erase in quene_func: "<<quene_vec[i].getBasket().size()<<endl;
            }*/

            //cout<<"$: basket size after match_customer in quene: "<<endl;
            it->match_customer(quene_vec);
        }
    }
}

//pass all vectors by reference
void open_func(stringstream& ss,vector<Cashier> &cashiers,vector<Customer> &quene_vec)
{
    string name,title;
    int age;
    char gender;
    ss>>name>>age>>gender>>title;

    //Insert new Cashier
    //Cashier(string name,int age,char gender,string title)
    Cashier element = Cashier(name,age,gender,title);
    
    //Match Cashier and Customers
    //Pass vector by reference
    int prev_size = quene_vec.size();

    /*for(int i=0;i<quene_vec.size();i++)
    {
        cout<<"$: basket size of "<<quene_vec[i].getName()<<" in quene_vec before match_customer in open_func: "<<quene_vec[i].getBasket().size()<<endl;
    }*/

    //cout<<"$: match_customer in open_func"<<endl;
    element.match_customer(quene_vec);

    /*if(prev_size==quene_vec.size())
    {
        cout<<endl<<"match_func did not remove customer"<<endl<<endl;
    }*/

    cashiers.push_back(element);

    //check baskets in customers
    Cashier temp = cashiers[cashiers.size()-1];
    //cout<<"$: check baskets in customers of "<<temp.getName()<<endl;
    /*for(int i=0;i<temp.getCustomers().size();i++)
    {
        cout<<temp.getCustomers()[i].getName()<<"'s basket size after push_back to cashiers in open_func: "<<temp.getCustomers()[i].getBasket().size()<<endl;
    }*/
}

void close_func(stringstream& ss,vector<Cashier> &cashiers,vector<Customer> &quene_vec)
{
    string cashier_name;
    ss>>cashier_name;

    vector<Cashier>::iterator it = cashiers.begin();

    bool found=false;
    while(it!=cashiers.end())
    {
        if(it->getName()==cashier_name)
        {
            found=true;
            break;
        }
        it++;
    }

    if(found)
    {
        vector<Customer> cus_vec = it->getCustomers();
        quene_vec.insert(quene_vec.begin(),cus_vec.begin(),cus_vec.end());

        //cout<<"$: check customers insert into quene_vec after close_func"<<endl;
        /*for(int i=0;i<cus_vec.size();i++)
        {
            cout<<"$: basket size of "<<quene_vec[i].getName()<<" after close_func: "<<quene_vec[i].getBasket().size()<<endl;
        }*/
    }
    /*else
        cout<<"Error: "<<cashier_name<<" not found in cashiers"<<endl;*/

    cashiers.erase(it);
}

void display_func(vector<Customer> quene_vec,vector<Cashier> cashiers);

void checkout_func(stringstream& ss,vector<Cashier> &cashiers,vector<Customer> &quene_vec,map<string,Grocery> grocery_database)
{
    string cashier_name,customer_name;
    ss>>cashier_name>>customer_name;

    //find the iter of the cashier
    bool found=false;
    vector<Cashier>::iterator cash_it=cashiers.begin();

    while(cash_it!=cashiers.end())
    {
        //cout<<cash_it->getName()<<endl;
        if(cash_it->getName()==cashier_name)
        {
            found=true;
            break;
        }
        cash_it++;
    }

    /*if(!found)
    {
        cout<<"Invalid cashier_name in checkout_func: "<<cashier_name<<endl;
    }*/
    /*else
    {
        cout<<"found "<<cashier_name<<endl;
    }*/

    //find the iter of the customer
    bool found_customer = false;
    //vector<Customer>::iterator cus_it=cash_it->getCustomers().begin();
    //while(cus_it!=cash_it->getCustomers().end())
    int cus_idx = 0;
    while(cus_idx<cash_it->getCustomers().size())
    {
        //cout<<"$$: "<<cash_it->getCustomers()[cus_idx].getName()<<endl;
        if(cash_it->getCustomers()[cus_idx].getName()==customer_name)
        {
            found_customer = true;
            break;
        }
        cus_idx++;
    }

    if(!found_customer)
    {
        //Warning
        cout<<customer_name<<" isn't at "<<cashier_name<<"'s counter!"<<endl;
        return;
    }
    /*else
    {
        cout<<"found customer "<<cash_it->getCustomers()[cus_idx].getName()<<endl;
    }*/

    //cout<<"$$: "<<"cash_it->getCustomers()[cus_idx].getBasket().size() = "<<cash_it->getCustomers()[cus_idx].getBasket().size()<<endl;
    //cout<<"$$: "<<"cus_idx = "<<cus_idx<<endl;

    cout<<"+-------------------------------------------+"<<endl;
    //operator<<(ostream,Customer&)
    //operator<<(ostream,Grocery&)
    cash_it->printCustomer(cus_idx);
    //cout<<"+-------------------------------------------+"<<endl;

    //display_func(quene_vec,cashiers);

    //cout<<"delete start"<<endl;
    cash_it->deleteCustomer(cus_idx);
    //cout<<"delete complete"<<endl;

    /*for(int i=0;i<cash_it->getCustomers().size();i++)
    {
        cout<<"#"<<cash_it->getCustomers()[i].getName()<<endl;
    }*/

    //call by reference
    //cout<<"$: check basket size after match_customer in checkout_func"<<endl;
    cash_it->match_customer(quene_vec);

    /*for(int i=0;i<cash_it->getCustomers().size();i++)
    {
        cout<<"$"<<cash_it->getCustomers()[i].getName()<<endl;
    }*/

    //cout<<"refill customer complete"<<endl;

    //display_func(quene_vec,cashiers);
}

void display_func(vector<Customer> quene_vec,vector<Cashier> cashiers)
{
    //quene
    cout<<"queue: ";
    for(vector<Customer>::iterator qit=quene_vec.begin();qit!=quene_vec.end();qit++)
    {
        cout<<qit->getName();

        vector<Customer>::iterator next=qit;
        next++;
        if(next!=quene_vec.end())
        {
            cout<<" <- ";
        }
    }
    cout<<endl;

    //counters
    //cout<<"cashier size: "<<cashiers.size()<<endl;
    for(int j=0;j<cashiers.size();j++)
    {
        //cout<<"size of customers: "<<cashiers[j].getCustomers().size()<<endl;
        cout<<cashiers[j].getName()<<"'s counter:";
        
        for(int i=0;i<cashiers[j].getCustomers().size();i++)
        {
            cout<<" ";
            cout<<cashiers[j].getCustomers()[i].getName();
            //p++;
            //cout<<"next++"<<endl;
        }
        cout<<endl;
        //cout<<cashiers[j].getName()<<" done"<<endl;
    }
    //cout<<"all csh done"<<endl;
}

int main(int argc,char** argv)
{
    ifstream grocery_file(argv[1]);
    ifstream scenario_file(argv[2]);

    //stores grocery for initialization, used when buying grocery
    map<string,Grocery> grocery_database;
    //Customer that are still buying
    map<string,Customer> buying;
    //Customers that are quening
    vector<Customer> quene_vec;
    //Cashiers
    vector<Cashier> cashiers;


    //parse grocery file
    parse_grocery(grocery_file,grocery_database);

    string input;
    while(getline(scenario_file,input))
    {
        //cout<<endl<<"$: Next input: "<<input<<endl;
        stringstream ss(input);
        string mode;
        ss>>mode;
        if(mode=="enter")
        {
                //add new Customer to buying
                //cout<<"enter start"<<endl;
                enter(ss,buying);
                //cout<<"enter pass"<<endl;
        }
        else if(mode == "buy")
        {
            //add new Grocery to the mentioned Customer in buying
            //cout warning if Customer.getCapacity() <= basket.size()

            //for debug
            int prev_size = buying.size();
            vector<Customer> temp;
            for(map<string,Customer>::iterator it=buying.begin();it!=buying.end();it++)
            {
                temp.push_back(it->second);
            }

            //put the grocery into basket
            buy_func(ss,buying,grocery_database);

            //checking if buying is changed after buy_func
            /*bool a = (buying.size()==prev_size);
            int idx=0;
            for(map<string,Customer>::iterator it=buying.begin();it!=buying.end();it++)
            {
                for(int i=0;i<temp[idx].getBasket().size();i++)
                {
                    if(a || (temp[idx].getBasket()[i].getQuantity()==it->second.getBasket()[i].getQuantity()))
                    {
                        //cout<<"!!: buy_func doesn't work in main"<<endl;
                        break;
                    }
                }
                idx++;
            }*/
        }
        else if(mode=="queue"){
                //quene_vec.push_back(mentioned Customer)
                //buying.pop(mentioned Customer)
                quene_func(ss,buying,quene_vec,cashiers);
        }
        else if(mode=="open"){
                open_func(ss,cashiers,quene_vec);
        }
        else if(mode=="close"){
                close_func(ss,cashiers,quene_vec);
        }
        else if(mode=="checkout"){
                checkout_func(ss,cashiers,quene_vec,grocery_database);
        }
        else if(mode=="display"){
                display_func(quene_vec,cashiers);
                //cout<<"display_func end"<<endl;
        }
        /*else
        {
                cout<<"Invalid mode "<<mode<<endl;
        }*/
    }

    grocery_file.close();
    scenario_file.close();
    return 0;
}
