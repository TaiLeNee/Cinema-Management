#ifndef DATETIME_H
#define DATETIME_H
#include <string>

using namespace std;    
class Datetime {
public:
    Datetime();
    Datetime(wstring fullTime);
    Datetime(wstring hour, wstring minute, wstring day, wstring month, wstring year);
    void setDatetime();
    void setHour(wstring hour);
    wstring getHour() const;

    void setMinute(wstring minute);
    wstring getMinute() const;

    void setDay(wstring day);
    wstring getDay() const;

    void setMonth(wstring month);
    wstring getMonth() const;

    void setYear(wstring year);
    wstring getYear() const;

    void displayInfo();
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
