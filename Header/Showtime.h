#ifndef SHOWTIME_H
#define SHOWTIME_H
#include <vector>
#include <string>
#include "../Source/Datetime.cpp"
#include "Chair.h"

using namespace std;
class Showtime {
    public:
        vector<vector<Chair>> chairs; // Danh sách ghế trong phòng

        int showtimeID; 
        int movieID;  // Khóa ngoại liên kết với Movie
        int roomID;   // Khóa ngoại liên kết với Room
        Showtime();
        Showtime(int showtimeID, int movieID, int roomID, const Datetime& startTime);
        Showtime(int movieID, int roomID, const Datetime& startTime, vector<vector<Chair>> chairs);
        Showtime(int showtimeID, int movieID, int roomID, const Datetime& startTime, vector<vector<Chair>> chairs);

        int getMovieID();
        int getRoomID();
        
        Datetime getStartTime() const;
        Datetime getEndTime() const;

        void setMovieID(int movieID);
        void setShowtimeID(int showtimeID);
        void setStartTime(const Datetime& startTime);


        // void setChairs(vector<vector<Chair>> chairs);
        void displayChairs() const;
        void changeStatusChair(int chairId, bool isBooked);



    private:
        
        Datetime startTime;
        Datetime endTime;
};

#endif // SHOWTIME_H