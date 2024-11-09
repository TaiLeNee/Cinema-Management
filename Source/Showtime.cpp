#include "../Header/Showtime.h"
#include <iostream>
#include "drawTableChair.cpp"
#include <fstream>
#include <algorithm>





using namespace std;    

static int curentIDBooked = 0; // ID của vé đã đặt


int Showtime::currentID = 0;
Showtime::Showtime() {}

Showtime::Showtime(int showtimeID, int movieID, int roomID, const Datetime& startTime):
    showtimeID(showtimeID), movieID(movieID), roomID(roomID), startTime(startTime) {
        currentID = max(currentID, this->showtimeID);
        // loadChairbooked();
    }

Showtime::Showtime(int movieID, int roomID, const Datetime& startTime, vector<vector<Chair>> chairs):
    showtimeID(++currentID), movieID(movieID), roomID(roomID), startTime(startTime), chairs(chairs) {}

Showtime::Showtime(int movieID, int roomID, const Datetime& startTime ):
    showtimeID(++currentID), movieID(movieID), roomID(roomID), startTime(startTime) {}

Showtime::Showtime(int showtimeID, int movieID, int roomID, const Datetime& startTime, vector<vector<Chair>> chairs):
    showtimeID(showtimeID), movieID(movieID), roomID(roomID), startTime(startTime), chairs(chairs) {
        currentID = max(currentID, this->showtimeID);
        // loadChairbooked();

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
    // loadChairbooked_auto(showtimeID, this->chairs);
}

int Showtime::getNumChair() const
{
    int numChairs = 0;
    for (auto &row : chairs) {
        numChairs += row.size();
    }
    return numChairs;
}

void Showtime::inputShowtimeInfo()
{   
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
            if(it->getIsBooked()){
                return true;
            }
            return false;
        }
        else{
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
        // wcout << L"==[DEBUG]==> " << chairname << endl;

        for (auto& row : this->chairs) {
            auto it = find_if(row.begin(), row.end(), [chairname](const Chair& chair) {
                return chair.getName() == chairname;
            });

            if (it != row.end()) {
                // wcout << L"==[DEBUG_setStatus]==> " << it->getName() << endl;
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

void Showtime::loadChairbooked(BookedList &bookedList) {
    for(auto& booked: bookedList.getBooked()){
        if(booked.getShowtimeID() == showtimeID){
            bookTickets(booked.getTicketID(), booked.getChairNames(), 1);
        }
    }
}