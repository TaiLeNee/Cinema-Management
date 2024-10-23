#include <iostream>
#include <io.h>
#include <fcntl.h>
#include "../Header/Datetime.h"
#include <iomanip> // for setw
#include <string>
#include <conio.h>
#include <windows.h>
#include "../Header/drawTable.h"

using namespace std;

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x - 1; // Tọa độ bắt đầu từ 0
    coord.Y = y - 1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

Datetime::Datetime(): hour(L"0"), minute(L"0"), day(L"0"), month(L"0"), year(L"0") {}

Datetime::Datetime(wstring fullTime){
    
}

Datetime::Datetime(wstring hour, wstring minute, wstring day, wstring month, wstring year)
    : hour(hour), minute(minute), day(day), month(month), year(year) {}

void Datetime::setDatetime() 
   {
        wcout << L"+-----------------------------------------------+" << endl;
        wcout << L"|                 Giờ chiếu phim                |" << endl;
        wcout << L"+-----------------+-----------------------------+" << endl;
        wcout << L"| 1. Giờ (giờ : phút)         :                 |" << endl;
        wcout << L"| 2. Ngày (ngày / tháng / năm):                 |" << endl;
        wcout << L"+-----------------+--------------    ---------------+" << endl;
        gotoxy(20,6);   wcin >> hour; wcout << " : ";  wcin >> minute;
        gotoxy(20,6);   wcin >> day; wcout << " / ";  wcin >> month; wcout << " / ";  wcin >> year;
        displayInfo();
    }


void Datetime::displayInfo() {
        
       drawTable({
        {L"Giờ chiếu", L"Ngày chiếu"},
        {hour + L":" + minute, day + L"/" + month + L"/" + year}  
       }
       );
}

void Datetime::editDatetime() {
    int choice;
    wstring newHour, newMinute, newDay, newMonth, newYear;

    do { 
        // Hiển thị menu chỉnh sửa
        wcout << L"+-----------------------------------------------+" << endl;
        wcout << L"|            Thay đổi giờ chiếu phim            |" << endl;
        wcout << L"+-----------------------+-----------------------+" << endl;
        wcout << L"| 1. Giờ (giờ : phút)                           |" << endl;
        wcout << L"| 2. Ngày (ngày / tháng / năm)                  |" << endl;
        wcout << L"| 3. Cả hai                                     |" << endl;
        wcout << L"| 4. Thoát                                      |" << endl;
        wcout << L"+-----------------------+-----------------------+" << endl;
        wcout << L"Lựa chọn của bạn: ";
        // Kiểm tra đầu vào của người dùng
        bool validInput = false;
        while (!validInput) {
            wcout << L"Lựa chọn của bạn: ";
            wcin >> choice;

            if (wcin.fail()) {
                wcin.clear(); // Xóa trạng thái lỗi
                wcin.ignore(1e4, '\n'); // Xóa bộ nhớ đệm
                wcout << L"Lựa chọn không hợp lệ. Vui lòng nhập lại." << endl;
            } else {
                validInput = true;
                wcin.ignore();
            }
        }

        switch (choice) {
            case 1:
                wcout << L"Nhập giờ mới (giờ : phút): ";
                wcin >> newHour ;
                wcout << L" : ";
                wcin >> newMinute;
                this->hour = newHour;
                this->minute = newMinute;
                displayInfo();
                break;
            case 2:
                wcout << L"Nhập ngày mới (ngày / tháng / năm): ";
                wcin >> newDay ;
                wcout << L" / ";
                wcin >> newMonth;
                wcout << L" / ";
                wcin >> newYear;
                this->day = newDay;
                this->month = newMonth;
                this->year = newYear;
                displayInfo();
                break;
            case 3:
                Datetime();
                break;
            case 4:
                wcout << L"Thoát chỉnh sửa." << endl;
                break;
            default:
                wcout << L"Lựa chọn không hợp lệ. Vui lòng chọn lại." << endl;
        }
    } while (choice != 4);
}

void deleteDatetime(){
    Datetime(0,0,0,0,0);
}

void Datetime::setHour(wstring hour) {
    this->hour = hour;
}   

wstring Datetime::getHour() const {
    return hour;
}

void Datetime::setMinute(wstring minute) {
    this->minute = minute;
}   

wstring Datetime::getMinute() const {
    return minute;
}

void Datetime::setDay(wstring day) {
    this->day = day;
}   

wstring Datetime::getDay() const {
    return day;
}

void Datetime::setMonth(wstring month) {
    this->month = month;
}   

wstring Datetime::getMonth() const {
    return month;
}

void Datetime::setYear(wstring year) {
    this->year = year;
}   

wstring Datetime::getYear() const {
    return year;
}

wstring Datetime::getFulltime() {
    return hour + L":" + minute + L" " + day + L"/" + month + L"/" + year;
}