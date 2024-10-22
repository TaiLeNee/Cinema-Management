#include "../Header/RoomList.h"
#include <fstream>

using namespace std;

vector<Room> rooms;

void loadRoom(){
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
