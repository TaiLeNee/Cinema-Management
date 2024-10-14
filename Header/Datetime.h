#ifndef DATETIME_H
#define DATETIME_H
#include <string>

using namespace std;    
class Datetime {
public:
    Datetime(const wstring& hour, const wstring& minute, int day, const wstring& month, const wstring& year);
    void displayInfo() const;  // hiển thị thông tin thời gian
    void setHour(wstring hour);
    int getHour() const;

    void setMinute(wstring minute);
    wstring getMinute() const;

    void setDay(wstring day);
    wstring getDay() const;

    void setMonth(wstring month);
    wstring getMonth() const;

    void setYear(wstring year);
    wstring getYear() const;

    void deleteDatetime();
    void editDatetime();


private:
    wstring hour;
    wstring minute;
    wstring day;
    wstring month;
    wstring year;
};

#endif // DATETIME_H
