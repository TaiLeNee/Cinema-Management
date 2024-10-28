#ifndef TICKETLIST_H
#define TICKETLIST_H

#include "Ticket.h"
#include <sstream>
#include <locale>
#include <codecvt>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <vector>

using namespace std;

class TicketList {
    private:
        vector<Ticket> tickets;
    public:
        TicketList();
        void displayTickets();
        void addTicket();
        vector<Ticket> getTickets();
};

#endif // TICKETLIST_H