#include "../Header/Showtime.h"
#include <iostream>
#include "drawTableChair.cpp"
#include "../Header/drawTable.h"

#include <algorithm>



using namespace std;    

static int curentIDBooked = 0; // ID của vé đã đặt
int maxIDBooked = 0; // ID lớn nhất của vé đã đặt

//hàm đọc các ghế đã đọc để set showtime
void loadChairbooked_auto(int IDshowtime, vector<vector<Chair>>& chairs) {
    

    wifstream file(L"../DATA/chairbooked.csv");
    file.imbue(locale(locale(), new codecvt_utf8<wchar_t>));

    if (!file.is_open()) {
        wcerr << L"Không thể mở file chairbooked.csv!" << endl;
        return;
    }

    wstring line;
    getline(file, line); // bỏ qua tiêu đề
    while (getline(file, line)) {
        wstringstream ss; ss.str(line);
        wstring showtimeID, chairName, isBooked, ticketID, tmpID;
        getline(ss, tmpID, L',');
        getline(ss, ticketID, L',');
        getline(ss, showtimeID, L',');

        if (stoi(showtimeID) != IDshowtime) {
            ss.clear();
            continue;
        }

        if(stoi(tmpID) > maxIDBooked) {
            maxIDBooked = stoi(tmpID);
        }



        //Xử lý đọc tên ghế từ file
        vector<wstring> chairNames;
        wstring tmpName;
        wstringstream ss1;
        getline(ss, tmpName);
        ss1.str(tmpName);

        getline(ss1, chairName, L'"');
        while (getline(ss1, chairName, L',')) {
            // Loại bỏ khoảng trắng đầu và cuối chuỗi
            chairName.erase(0, chairName.find_first_not_of(L"\" \t"));
            chairName.erase(chairName.find_last_not_of(L" \t\"") + 1);
            chairNames.push_back(chairName);
        }
        
    
        for(auto& chairname: chairNames) {

            for (auto& row : chairs) {
                auto it = find_if(row.begin(), row.end(), [chairname](const Chair& chair) {
                    return chair.getName() == chairname;
                });

                if (it != row.end()) {
                    it->setIsBooked(1);
                    break;
                }
            }   
        }
        ss1.clear();
        ss.clear();
    }

    curentIDBooked = maxIDBooked;
    file.close();

}

int Showtime::currentID = 0;
Showtime::Showtime() {}

Showtime::Showtime(int showtimeID, int movieID, int roomID, const Datetime& startTime):
    showtimeID(showtimeID), movieID(movieID), roomID(roomID), startTime(startTime) {
        currentID = max(currentID, this->showtimeID);
    }

Showtime::Showtime(int movieID, int roomID, const Datetime& startTime, vector<vector<Chair>> chairs):
    showtimeID(++currentID), movieID(movieID), roomID(roomID), startTime(startTime), chairs(chairs) {}

Showtime::Showtime(int movieID, int roomID, const Datetime& startTime ):
    showtimeID(++currentID), movieID(movieID), roomID(roomID), startTime(startTime) {}

Showtime::Showtime(int showtimeID, int movieID, int roomID, const Datetime& startTime, vector<vector<Chair>> chairs):
    showtimeID(showtimeID), movieID(movieID), roomID(roomID), startTime(startTime), chairs(chairs) {
        currentID = max(currentID, this->showtimeID);
    }

int Showtime::getMovieID() {
    return movieID;
}

int Showtime::getRoomID() {
    return roomID;
}

Datetime Showtime::getStartTime() const {
    return startTime;
}

Datetime Showtime::getEndTime() const {
    return endTime;
}

void Showtime::setMovieID(int movieID) {
    this->movieID = movieID;
}


void Showtime::setStartTime(const Datetime& startTime) {
    this->startTime = startTime;
}

void Showtime::setShowtimeID(int showtimeID) {
    this->showtimeID = showtimeID;
}

void Showtime::setChairs(vector<vector<Chair>> chairs) {

    this->chairs = chairs;
    loadChairbooked_auto(showtimeID, this->chairs);
}


void Showtime::inputShowtimeInfo()
{   
    // system("cls");
    // drawTable({
    //     {L"         THÊM KHUNG GIỜ CHIẾU         "}});
    // drawTable({
    //     {L"Nhập ID phim: ", L" "},
    //     {L"Nhập ID phòng: ", L" "}
    // }); 

    // gotoXY(17, 3);
    // wcin >> movieID;

    // gotoXY(18, 5);
    // wcin >> roomID;


}


void Showtime::displayChairs(int typeTicket) const
{
    drawTableChair(chairs, typeTicket);
}

bool Showtime::checkChairExist(int showtimeID, const wstring &chairName)
{
    for (auto &row : chairs) {
        auto it = find_if(row.begin(), row.end(), [chairName](const Chair &chair) {
            return chair.getName() == chairName;
        });

        if (it != row.end()) {
            if(it->getIsBooked())
                return true;
        }
    }
    return false;
}

void Showtime::changeStatusChair(int chairId, int isBooked) {
    for (auto& row : this->chairs) {
        auto it = find_if(row.begin(), row.end(), [chairId](const Chair& chair) {
            return chair.getId() == chairId;
        });

        if (it != row.end()) {
            it->setIsBooked(isBooked);       // Set chair status to booked or not booked
            return;
        }
    }
}

void Showtime::bookTickets(int ticketID, vector<wstring> chairNames, int statusBooking) {
     for(auto& chairname: chairNames) {

        for (auto& row : this->chairs) {
            auto it = find_if(row.begin(), row.end(), [chairname](const Chair& chair) {
                return chair.getName() == chairname;
            });

            if (it != row.end()) {
                it->setIsBooked(statusBooking);
                break;
            }
        }   
    }
}


void Showtime::saveChairbooked(int ticketID, vector<wstring> chairNames){

    wofstream file(L"../DATA/chairbooked.csv", ios::app);
    file.imbue(locale(locale(), new codecvt_utf8<wchar_t>));

    if (!file.is_open()) {
        wcerr << L"Không thể mở file chairbooked.csv!" << endl;
        return;
    }

    file << ++curentIDBooked << L"," << ticketID << L"," << this->showtimeID << L","<< L"\"";
    for(auto& chairname: chairNames) {
        file << chairname ;
        if(chairname != chairNames.back()) {
            file << L",";
        }
    }
    file << L"\"\n";

    file.close();
}

void Showtime::loadChairbooked() {
   loadChairbooked_auto(this->showtimeID, this->chairs);
}