#ifndef ROOMLIST_H
#define ROOMLIST_H
#include "../Header/Room.h"
#include <fstream>
#include <sstream>

class RoomList{
    private:
        vector<Room> rooms;

    public:
        RoomList();
        void loadRoom();
        vector<Room>& getRooms();

};

#endif // ROOMLIST_H