#include "../Header/Showtime.h"
#include <iostream>
#include "drawTableChair.cpp"
#include <algorithm>
using namespace std;    

Showtime::Showtime() {}

Showtime::Showtime(int showtimeID, int movieID, int roomID, const Datetime& startTime):
    showtimeID(showtimeID), movieID(movieID), roomID(roomID), startTime(startTime) {}

Showtime::Showtime(int movieID, int roomID, const Datetime& startTime, vector<vector<Chair>> chairs):
    movieID(movieID), roomID(roomID), startTime(startTime), chairs(chairs) {}

Showtime::Showtime(int showtimeID, int movieID, int roomID, const Datetime& startTime, vector<vector<Chair>> chairs):
    showtimeID(showtimeID), movieID(movieID), roomID(roomID), startTime(startTime), chairs(chairs) {}

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


void Showtime::displayChairs() const
{
    drawTableChair(chairs);
}



void Showtime::changeStatusChair(int chairId, bool isBooked) {
    for (auto& row : chairs) {
        auto it = find_if(row.begin(), row.end(), [chairId](const Chair& chair) {
            return chair.getId() == chairId;
        });

        if (it != row.end()) {
            it->setIsBooked(isBooked);       // Set chair status to booked or not booked
            return;
        }
    }
}

