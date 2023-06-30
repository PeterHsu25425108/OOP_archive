#ifndef TRA_H
#define TRA_H
#include "train_information.h"

class TRA : public train_information
{
private:
    string train_type;
    int car;
    string seat;

public:
    TRA();
    TRA(int, int, string, string, string, string, string, int, string);
    void print_information();
};

#endif