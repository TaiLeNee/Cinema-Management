#include "../Header/TicketList.h"
#include "../Header/drawTable.h"


void loadTicketfromCSV(vector<Ticket>& tickets) {
    wifstream file(L"../DATA/tickets.csv");
    file.imbue(locale(locale(), new codecvt_utf8<wchar_t>));

    if (!file.is_open()) {
        wcerr << L"Could not open the file!" << endl;
        return;
    }

    static int maxID = 0;
    wstring line;
    getline(file, line); // bỏ qua tiêu đề
    while (getline(file, line)) {
        wstringstream ss; ss.str(line);

        wstring typeTicket, price, ticketID;
        
        getline(ss, ticketID, L',');
        getline(ss, typeTicket, L',');
        getline(ss, price);

        tickets.push_back(Ticket(stoi(ticketID), typeTicket, stoi(price)));
    }

    file.close();
}

void saveTickettoCSV(vector<Ticket>& tickets) {
    wofstream file(L"../DATA/tickets.csv");
    file.imbue(locale(locale(), new codecvt_utf8<wchar_t>));

    file << L"ID,Loại vé,Giá vé" << endl;
    for (Ticket& ticket : tickets) {
        file << ticket.getTicketID() << L"," << ticket.getTypeTicket() << L"," << ticket.getPrice() << endl;
    }

    file.close();
}

TicketList::TicketList() {
    loadTicketfromCSV(tickets);
}

void TicketList::displayTickets(){
    vector<vector<wstring>> table;
    table.push_back({L"ID", L"Loại vé", L"Giá vé"});
    for (Ticket& ticket : tickets) {
        table.push_back({to_wstring(ticket.getTicketID()), ticket.getTypeTicket(), to_wstring(ticket.getPrice())});
    }
    drawTable(table);
}

void TicketList::addTicket() {
    wstring typeTicket;
    int price;

    wcout << L"Nhập loại vé: ";
    getline(wcin, typeTicket);
    wcout << L"Nhập giá vé: ";
    wcin >> price;
    tickets.push_back(Ticket(typeTicket, price));

    saveTickettoCSV(tickets);
}

vector<Ticket> TicketList::getTickets() {
    return tickets;
}   
