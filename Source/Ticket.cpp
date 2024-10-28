#include "../Header/Ticket.h"
#include <sstream>

using namespace std;

int Ticket::currentID = 0;  

Ticket::Ticket() : ticketID(++currentID), typeTicket(L""), price(0) {}

Ticket::Ticket(int ticketID, const wstring& typeTicket, int price)
    : ticketID(ticketID), typeTicket(typeTicket), price(price) {
    if (ticketID > currentID) {
        currentID = ticketID;
    }
}

Ticket::Ticket(const wstring& typeTicket, int price)
    : ticketID(++currentID), typeTicket(typeTicket), price(price) {}

// Ticket::Ticket(int price)

wstring Ticket::getTypeTicket() {
    return typeTicket;
}

int Ticket::getTicketID() {
    return ticketID;
}

void Ticket::setTicketID(int ticketID) {
    this->ticketID = ticketID;
}

void Ticket::setPrice(int price) {
    this->price = price;
}

int Ticket::getPrice() const {
    return price;
}

void Ticket::displayInfo() {
    drawTable({
        {L"ID", L"Loại vé", L"Giá vé"},
        {to_wstring(ticketID), typeTicket, to_wstring(price)}
    });
}

void Ticket::deleteTicket() {
    ticketID = 0;
    typeTicket = L"";
    price = 0;
}

void Ticket::editTicket() {
    wcout << L"Nhập loại vé mới: ";
    wcin.ignore();
    getline(wcin, typeTicket);
    wcout << L"Nhập giá vé mới: ";
    wcin >> price;
}

// void Ticket::loadTicketfromCSV(const string& filename) {





