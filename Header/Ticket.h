#ifndef TICKET_H
#define TICKET_H
#include <string>

using namespace std;    
class Ticket {
public:   
    int showtimeID; // khhoas ngoại liên kết với showtime
    Ticket();
    Ticket(int ticketID, float price);
    Ticket(float price);

    int getTicketID();
    void setTicketID(int ticketID);

    void setPrice(float price);
    float getPrice() const;

    void displayInfo();
    void deleteTicket();
    void editTicket();

private:
    int ticketID;
    float price;
};

#endif // TICKET_H
