#include "../Header/Customer.h"
#include <algorithm>
#include "../Header/drawTable.h"
#include "../Header/gotoXY.h"
using namespace std;

int Customer::currentID = 0;

Customer::Customer() {}

Customer::Customer(int customerID,const wstring& name,const wstring& phoneNumber, int point)
    : customerID(customerID), name(name), phoneNumber(phoneNumber), point(point) {
        currentID = max(currentID, this->customerID);
    }

Customer::Customer(const wstring& name,const wstring& phoneNumber, int point)
    : customerID(++currentID),  name(name), phoneNumber(phoneNumber), point(point) {}

void Customer::displayInfo() const {
    drawTable({
        {L"ID", L"Họ và tên", L"Số điện thoại", L"Điểm tích luỹ" },
        {to_wstring(customerID),name,phoneNumber,to_wstring(point)}
    });
}

// void Customer::deleteCustomer() {
//     customerID = 0;
//     name = L"";
//     phoneNumber = 0;
//     point = 0;
// }

void Customer::editCustomer() {
    vector<vector<wstring>> table;
    wstring newName,newPhoneNumber;
    int newPoint;
    table.push_back({L"SỬA THÔNG TIN"});
    table.push_back({L"1. Họ tên."});
    table.push_back({L"2. Số điện thoại."});
    table.push_back({L"0. Quay lại."});

    edit:
    drawTable(table);
    int choice;
    checkInput(L"Chọn thông tin cần sửa", choice);
    if(!choice) {
        return;
    }
    switch(choice) {
         case 1: {
            wcout << L"Nhập họ và tên mới: ";
            wcin.ignore();
            getline(wcin, newName);
            wregex pattern(L"^[\\p{L}\\s]+$");
            if (regex_match(newName, pattern)) {
                name = newName;
            } else {
                red(L"Tên không hợp lệ. Vui lòng nhập lại.\n");
            }
            goto edit;
        }
        case 2: {
            wcout << L"Nhập số điện thoại mới: ";
            wcin.ignore();
            getline(wcin, newPhoneNumber);
            wregex phonePattern(L"^(84|0)[0-9]{8,13}$");
            if (regex_match(newPhoneNumber, phonePattern)) {
                phoneNumber = newPhoneNumber;
            } else {
                red(L"Số điện thoại không hợp lệ. Vui lòng nhập lại.\n");
            }
            goto edit;
        }
        default:
            red(L"Chọn không hợp lệ. Vui lòng chọn lại.\n");
            goto edit;
    }
}

void Customer::setCustomerID(int id) {
    this->customerID = id;
}   

int Customer::getCustomerID() const {
    return customerID;
}

void Customer::setName(const wstring& name) {
    this->name = name;
}

wstring Customer::getName() const {
    return name;
}

void Customer::setPhoneNumber(const wstring& phoneNumber) {
    this->phoneNumber = phoneNumber;
}

wstring Customer::getPhoneNumber() const {
    return phoneNumber;
}

void Customer::setPoint(int amount) {
    this->point += amount * 0.1;
}

void Customer::resetPoint() {
    this->point = 0;
}

int Customer::getPoint() const {
    return point;
}

void loadCustomerfromCSV(const string& filename) {
    
}

