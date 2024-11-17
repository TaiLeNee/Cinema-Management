#ifndef ROOM_H
#define ROOM_H
#include <iostream>
#include "Showtime.h"
#include "Chair.h"
#include <vector>
#include <locale>
#include <codecvt>
#include <algorithm>

using namespace std;
class Room {
    private:
        int id; // Id phòng
        wstring name; // Tên phòng
        vector<Showtime> showtimes; // Danh sách khung giờ chiếu
        vector<vector<Chair>> chairs; // Danh sách ghế trong phòng
        int numRows; // Số hàng ghế
        int numChairsPerRow; // Số ghế trong mỗi hàng
        wstring screen;
        int status;

    public:
        Room();
        Room(int id, const wstring& name, int numRows, int numChairsPerRow, wstring screen, int status); // Constructor

        // Getters and setters
        int getId() const;
        wstring getName() const;
        void addShowtime(const Showtime& showtime);
        vector<Showtime>& getShowtimes();
        void resetShowtimes();
        void addChairs(int numRows, int numChairsPerRow);
        vector<vector<Chair>> getChairs();
        void loadShowtimes(const string& filename);
        void deleteShowtime(int showtimeID);

        int getNumRows();
        int getNumChairsPerRow();

        wstring getScreen();
        int getStatus();

        void setName(const wstring& name);
        void setNumRows(int numRows);
        void setNumChairsPerRow(int numChairsPerRow);
        void setScreen(const wstring& screen);
        void setStatus(int status);

        void displayInfo();

};  

#endif // ROOM_H