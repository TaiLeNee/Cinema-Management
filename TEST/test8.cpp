#include <iostream>
#include <ctime>
#include <iomanip>

using namespace std;

void printCurrentTimeAndNextWeek() {
    // Lấy thời gian hiện tại
    time_t now = time(0);
    tm *ltm = localtime(&now);

    // In thời gian hiện tại
    cout << "Thời gian hiện tại: ";
    cout << ltm->tm_mday << "/"
         << setfill('0') << setw(2) << 1 + ltm->tm_mon << "/"
         << setfill('0') << setw(2) << 1900 + ltm->tm_year  << " "<<endl;

    //Các ngày trong tuần 1 tuần

    for(int i = 0; i < 7; i++){
        now += 24 * 60 * 60;
        tm *ltm = localtime(&now);
        cout << ltm->tm_mday << "/"
         << setfill('0') << setw(2) << 1 + ltm->tm_mon << "/"
         << setfill('0') << setw(2) << 1900 + ltm->tm_year  << " ";
         cout << endl;
    }
}

int main() {
    printCurrentTimeAndNextWeek();
    return 0;
}