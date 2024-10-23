#include <iostream>
#include <vector>
#include <string>
#include <sstream>
    #include <iomanip>
#include <ctime>
#include <algorithm>
using namespace std;

// Hàm chuyển chuỗi "HH:MM DD/MM/YYYY" sang đối tượng time_t
time_t stringToTime(const string& dateTimeStr) {
    struct tm tm {};
    istringstream ss(dateTimeStr);
    ss >> get_time(&tm, "%H:%M %d/%m/%Y");
    cout << mktime(&tm) << endl;
    return mktime(&tm); // Chuyển sang time_t
}

int main() {
    // Danh sách các chuỗi ngày giờ
    vector<string> dateTimes = {
        "20:25 20/3/2025", 
        "10:15 15/4/2023", 
        "08:30 5/6/2024", 
        "22:10 10/1/2022"
    };

    // Sắp xếp danh sách chuỗi theo thứ tự tăng dần
    sort(dateTimes.begin(), dateTimes.end(), [](const string& a, const string& b) {
        return stringToTime(a) < stringToTime(b);
    });

    // In ra các giá trị sau khi sắp xếp
    for (const string& dateTime : dateTimes) {
        cout << dateTime << endl;
    }

    return 0;
}
