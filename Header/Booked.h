#ifndef BOOKED_H
#define BOOKED_H
#include "Chair.h"
#include "drawTable.h"
#include "Payment.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <codecvt>
#include <locale>
#include <string>

// void loadChairbooked_auto(int IDshowtime, int &curentIDBooked, vector<vector<Chair>>& chairs);
class Booked{
    private:
        int idBooked;
        int showtimeID;
        int ticketID;
        int employeeID;
        wstring datetime;
        wstring totalMoney;
        vector<wstring> chairNames;


    public:
        static int curentIDBooked; // ID của vé đã đặt
        Booked();
        Booked(int idBooked, int ticketID, int showtimeID, int employeeID, wstring datetime, wstring totalMoney, vector<wstring> chairNames);
        Booked(int ticketID, int showtimeID, int employeeID, wstring datetime, wstring totalMoney, vector<wstring> chairNames);
        
        int getIdBooked() const;

        void saveChairbooked();

        int getTicketID() const;
        void setTicketID(int ticketID);

        int getShowtimeID() const;
        void setShowtimeID(int showtimeID);

        int getEmployeeID() const;
        void setEmployeeID(int employeeID);

        wstring getDatetime() const;
        void setDatetime(wstring datetime);

        wstring getTotalMoney() const;
        void setTotalMoney(wstring totalMoney);

        vector<wstring> getChairNames() const;
        void setChairNames(vector<wstring> chairNames);

        wstring getDate() const;
        wstring getMonth() const;

        void displayInfo() const;
        void pay(Pay* payment);

        


        
};

#endif // BOOKED_H