#ifndef THSR_H
#define THSR_H
#include "train_information.h"

class THSR : public train_information
{
private:
    string Class;
    int car;
    string seat;

public:
    THSR();
    THSR(int, int, string, string, string, string, string, int, string);
    void print_information();
};

#endif