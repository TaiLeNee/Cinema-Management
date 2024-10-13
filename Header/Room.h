#ifndef ROOM_H
#define ROOM_H
#include "Chair.h"
#include <vector>

class Room {
    private:
        int id; // Id phòng
        wstring name; // Tên phòng
        vector<Chair> chairs; // Danh sách ghế trong phòng

    public:
        Room();
        Room(int id, const wstring& name, const vector<Chair>& chairs);

        // Getters and setters
        int getId() const;
        wstring getName() const;
        vector<Chair>& getChairs();
        void displayChairs() const;
        void addChairs(int numRows, int numChairsPerRow);
        void changeStatusChair(int chairId, bool isBooked);
};

#endif // ROOM_H