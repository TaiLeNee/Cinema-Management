#include "../Header/Booked.h"


int Booked::curentIDBooked = 0;

Booked::Booked() {}

 Booked::Booked(int ticketID, int showtimeID, int employeeID, wstring datetime, wstring totalMoney, vector<wstring> chairNames): ticketID(ticketID), showtimeID(showtimeID), employeeID(employeeID), datetime(datetime), totalMoney(totalMoney), chairNames(chairNames) {
    ++curentIDBooked;
}

Booked::Booked(int idBooked, int ticketID, int showtimeID, int employeeID, wstring datetime, wstring totalMoney, vector<wstring> chairNames): idBooked(idBooked), ticketID(ticketID), showtimeID(showtimeID), employeeID(employeeID), datetime(datetime), totalMoney(totalMoney), chairNames(chairNames) {
    curentIDBooked = max(curentIDBooked, this->idBooked);
}

void Booked::saveChairbooked(){
    wofstream file(L"../DATA/payments.csv", ios::app);
    file.imbue(locale(locale(), new codecvt_utf8<wchar_t>));

    if (!file.is_open()) {
        wcerr << L"Không thể mở file payments.csv!" << endl;
        return;
    }

    file << curentIDBooked << L"," << ticketID << L"," << this->showtimeID << L","<< this->employeeID << L"," << datetime << L"," << totalMoney << L",\"";

    for(auto& chairname: chairNames) {
        file << chairname ;
        if(chairname != chairNames.back()) {
            file << L",";
        }
    }
    file << L"\"\n";

    file.close();
}

int Booked::getTicketID() const {
    return ticketID;
}   

void Booked::setTicketID(int ticketID) {
    this->ticketID = ticketID;
}   

int Booked::getShowtimeID() const {
    return showtimeID;
}   

void Booked::setShowtimeID(int showtimeID) {
    this->showtimeID = showtimeID;
}   

int Booked::getEmployeeID() const {
    return employeeID;
}   

void Booked::setEmployeeID(int employeeID) {
    this->employeeID = employeeID;
}   

wstring Booked::getDatetime() const {
    return datetime;
}   

void Booked::setDatetime(wstring datetime) {
    this->datetime = datetime;
}   

wstring Booked::getTotalMoney() const {
    return totalMoney;
}   

void Booked::setTotalMoney(wstring totalMoney) {
    this->totalMoney = totalMoney;
}   

vector<wstring> Booked::getChairNames() const {
    return chairNames;
}

void Booked::setChairNames(vector<wstring> chairNames) {
    this->chairNames = chairNames;
}

wstring Booked::getDate() const
{
    size_t pos = datetime.find(L" ");
    if (pos != wstring::npos) {
        return datetime.substr(pos + 1);
    }
    return L"";
}   

wstring Booked::getMonth() const
{
    size_t pos = datetime.find(L" ");
    if (pos != std::wstring::npos) {
        size_t monthStart = datetime.find(L"/", pos) + 1;
        size_t monthEnd = datetime.find(L"/", monthStart);
        return datetime.substr(monthStart, monthEnd - monthStart);
    }
    return L"";
}

void Booked::pay(Pay* payment) {
    payment->setPaymentStatus(1);
    saveChairbooked();
}