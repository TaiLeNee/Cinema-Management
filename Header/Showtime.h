#ifndef SHOWTIME_H
#define SHOWTIME_H
#include <vector>
#include <string>
#include "Datetime.h"
#include "Chair.h"
#include "gotoXY.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <locale>
#include <codecvt>


using namespace std;
class Showtime {
    public:
        static int currentID;
        vector<vector<Chair>> chairs; // Danh sách ghế trong phòng

        int showtimeID; 
        int movieID;  // Khóa ngoại liên kết với Movie
        int roomID;   // Khóa ngoại liên kết với Room
        Showtime();
        Showtime(int showtimeID, int movieID, int roomID, const Datetime& startTime);
        Showtime(int movieID, int roomID, const Datetime& startTime, vector<vector<Chair>> chairs);
        Showtime(int movieID, int roomID, const Datetime& startTime);
        Showtime(int showtimeID, int movieID, int roomID, const Datetime& startTime, vector<vector<Chair>> chairs);

        int getMovieID();
        int getRoomID();
        
        Datetime getStartTime() const;
        Datetime getEndTime() const;

        void setMovieID(int movieID);
        void setShowtimeID(int showtimeID);
        void setStartTime(const Datetime& startTime);

        void inputShowtimeInfo();
        void setChairs(vector<vector<Chair>> chairs);
        void displayChairs(int typeTicket) const;
        bool checkChairExist(int showtimeID, const wstring& chairName);

        void changeStatusChair(int chairId, int isBooked);
        void bookTickets(int ticketID, vector<wstring> chairNames, int statusBooking);

        void loadChairbooked();
        void saveChairbooked(int ticketID, vector<wstring> chairNames);



    private:
        
        Datetime startTime;
        Datetime endTime;
};

#endif // SHOWTIME_H