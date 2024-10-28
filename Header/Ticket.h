#ifndef TICKET_H
#define TICKET_H
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <locale>
#include <codecvt>
#include "drawTable.h"

using namespace std;    
class Ticket {
public:   
    // int showtimeID; // khóa ngoại liên kết với showtime

    static int currentID;

    Ticket();
    // Ticket(int ticketID, int showtimeID, int price);
    // Ticket(int showtimeID, int price);

    Ticket(int tiketID, const wstring& typeTicket, int price);
    Ticket(const wstring& typeTicket, int price);

    Ticket(int price);

    int getTicketID();
    void setTicketID(int ticketID);

    void setPrice(int price);
    int getPrice() const;

    void displayInfo();
    void deleteTicket();
    void editTicket();

    wstring getTypeTicket();


    static void loadTicketfromCSV(const string& filename);

private:
    int ticketID;
    wstring typeTicket;
    int price;
};

#endif // TICKET_H
