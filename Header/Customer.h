#ifndef CUSTOMER_H
#define CUSTOMER_H
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <locale>
#include <codecvt>
#include "drawTable.h"
#include "Ticket.h"
#include "checkInput.h"
#include <regex>

using namespace std;    
class Customer {
public:   

    static int currentID;

    Customer();
    Customer(int customerID, const wstring& name,const wstring& phoneNumber, int point);
    Customer(const wstring& name, const wstring& phoneNumber, int point);

    int getCustomerID() const;
    void setCustomerID(int customerID);

    void setPoint(int amount);
    int getPoint() const;

    void setPhoneNumber(const wstring& phoneNumber);
    wstring getPhoneNumber() const;

    void displayInfo() const;
    // void deleteCustomer();
    void editCustomer();

    wstring getName() const;
    void setName(const wstring& name);


    static void loadCustomerfromCSV(const string& filename);

private:
    int customerID;
    wstring name;
    wstring phoneNumber;
    int point;
};

#endif // CUSTOMER_H
