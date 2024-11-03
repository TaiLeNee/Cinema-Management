#include <iostream>
#include <vector>
#include <iomanip>
#include <ctime>
#include <locale>
#include <codecvt>
#include "../Header/drawTable.h"
#include "../Header/Datetime.h"


using namespace std;


void drawTable(const vector<vector<wstring>> &table);

Datetime drawCalendar(int month, int year) {

    
    // Lấy ngày hiện tại
    time_t now = time(0);
    tm *ltm = localtime(&now);
    int currentDay = ltm->tm_mday;


    // Lấy thông tin về tháng hiện tại
    tm time_in = { 0, 0, 0, 1, month - 1, year - 1900 };
    time_t time_temp = mktime(&time_in);

    const tm *time_out = localtime(&time_temp);

    int daysInMonth = 31;
    switch (month) {
        case 4: case 6: case 9: case 11: daysInMonth = 30; break;
        case 2: daysInMonth = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) ? 29 : 28; break;
    }

    int startDay = (time_out->tm_wday + 6) % 7; // Đặt chủ nhật ở cuối

    // Tạo bảng lịch
    vector<vector<wstring>> table;
    vector<wstring> header = {L"Mon", L"Tue", L"Wed", L"Thu", L"Fri", L"Sat", L"Sun"};
    table.push_back(header);

    vector<wstring> week(7, L"");
    int day = 1;

    for (int i = 0; i < startDay; ++i) {
        week[i] = L"";
    }

    for (int i = startDay; day <= daysInMonth; ++i) {
        if (i == 7) {
            table.push_back(week);
            week = vector<wstring>(7, L"");
            i = 0;
        }
        week[i] = to_wstring(day++);
    }
    if (!week.empty()) {
        table.push_back(week);
    }

    // Vẽ bảng lịch
    drawTable(table);

    // Nhập ngày
    int choiceDay;
    switch (month) {
        case 4: case 6: case 9: case 11: daysInMonth = 30; break;
        case 2: daysInMonth = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) ? 29 : 28; break;
    }

    while (true) {
        green(L"═════[Nhập ngày]==> ");
        wcin >> day;

        if (day > currentDay && day <= daysInMonth) {
            break;
        } else {
            red(L"[Ngày không hợp lệ. Vui lòng chọn lại.\n]");
        }
    }

    Datetime daySelected(to_wstring(day), to_wstring(month), to_wstring(year));
    green(L"[Ngày đã chọn: " + to_wstring(day) + L"/" + to_wstring(month) + L"/" + to_wstring(year) + L"]\n");

    return daySelected;
}
