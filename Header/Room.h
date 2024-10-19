#ifndef ROOM_H
#define ROOM_H
#include "Showtime.h"
#include "Chair.h"
#include <vector>
using namespace std;
class Room {
    private:
        int id; // Id phòng
        wstring name; // Tên phòng
        vector<Showtime> showtimes; // Danh sách khung giờ chiếu
        vector<vector<Chair>> chairs; // Danh sách ghế trong phòng
        int numRows; // Số hàng ghế
        int numChairsPerRow; // Số ghế trong mỗi hàng

    public:
        Room();
        Room(int id, const wstring& name, int numRows, int numChairsPerRow); // Constructor

        // Getters and setters
        int getId() const;
        wstring getName() const;
        void addShowtime(const Showtime& showtime);
        vector<Showtime> getShowtimes();
        void addChairs(int numRows, int numChairsPerRow);
        vector<vector<Chair>> getChairs();
        void loadShowtimes(const string& filename);
};  

#endif // ROOM_H