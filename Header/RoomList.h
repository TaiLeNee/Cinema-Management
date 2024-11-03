#ifndef ROOMLIST_H
#define ROOMLIST_H
#include "Room.h"
#include "drawTable.h"
#include <fstream>
#include <sstream>

class RoomList{
    private:
        vector<Room> rooms;

    public:
        RoomList();
        void loadRoom();
        vector<Room>& getRooms();
        void resetShowtimesofRoom();
        void displayRooms();

};

#endif // ROOMLIST_H