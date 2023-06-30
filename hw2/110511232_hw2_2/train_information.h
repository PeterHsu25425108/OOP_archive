#ifndef TRAIN_INFORMATION_H
#define TRAIN_INFORMATION_H
#include <iostream>
#include <string>
using namespace std;

class train_information
{
private:
    int train_no;
    int drive;
    string date;
    string travel;
    string from, to;

public:
    train_information();
    train_information(int, int, string, string, string, string);
    virtual void print_information();
};

#endif