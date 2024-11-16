#ifndef ROOMLIST_H
#define ROOMLIST_H
#include "Room.h"
#include "drawTable.h"
#include "Color.h"
#include "checkInput.h"

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
        void addRoom();
        void editRoom();
        void deleteRoom();
};

#endif // ROOMLIST_H