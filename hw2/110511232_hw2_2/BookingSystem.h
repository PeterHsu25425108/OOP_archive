#ifndef BOOKINGSYSTEM_H
#define BOOKINGSYSTEM_H
#include "THSR.h"
#include "TRA.h"
#include <map>
#include <sstream>

class BookingSystem
{
private:
    map<string, THSR> THSR_m;
    map<string, TRA> TRA_m;

public:
    BookingSystem();
    void BookingSystemShell();
    void p();
    void b();
    void s();
    void u();
    void parseTicket(string line, int select);
};

#endif