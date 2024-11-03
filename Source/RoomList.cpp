#include "../Header/RoomList.h"


using namespace std;


RoomList::RoomList(){};

void RoomList::loadRoom(){
    rooms.clear();
    wifstream file("../DATA/rooms.csv");
    file.imbue(locale(locale(), new codecvt_utf8<wchar_t>));
    if (!file.is_open()) {
        wcout << L"Không thể mở file showtimes.csv" << endl;
        return;
    }

    wstring line;
    getline(file, line); // Bỏ qua dòng tiêu đề

    while(getline(file, line)){
        wstring ID, name, numRows, numChairsPerRow;
        wstringstream ss;
        ss.str(line);
        getline(ss, ID, L',');
        getline(ss, name, L',');
        getline(ss, numRows, L',');
        getline(ss, numChairsPerRow);
        ss.clear();
        rooms.push_back(Room(stoi(ID), name, stoi(numRows), stoi(numChairsPerRow)));
    }  
}

vector<Room>& RoomList::getRooms(){
    return rooms;
}   

void RoomList::resetShowtimesofRoom(){
    for(auto &room: rooms){
        room.resetShowtimes();
    }
}

void RoomList::displayRooms(){
    drawTable({{L"          DANH SÁCH PHÒNG CHIẾU          "}});
    vector<vector<wstring>> table;
    table.push_back({L" ID ", L" Tên phòng ", L" Số lượng ghế "});
    for(auto &room: rooms){
        table.push_back({to_wstring(room.getId()), room.getName(), to_wstring(room.getNumRows()*room.getNumChairsPerRow())});
    }
    drawTable(table);
}