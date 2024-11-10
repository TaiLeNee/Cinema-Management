#include "../Header/Room.h"
#include "../Header/Showtime.h"
#include "../Header/Chair.h"
#include "loadShowtimeFromCSV.cpp"


using namespace std;


// void Room::loadShowtimes(const string& filename);
    

// Room class implementation
Room::Room() : id(0), name(L"") {}

Room::Room(int id, const wstring& name, int numRows, int numChairsPerRow)
    : id(id), name(name), numRows(numRows), numChairsPerRow(numChairsPerRow) {

    char rowLabel = 'A';
    int chairId = 1;

    for (int i = 0; i < numRows; ++i) {
        vector<Chair> row;
        for (int j = 1; j <= numChairsPerRow; ++j) {
            int chairId = (i + 1) * 100 + j; // Create chair ID in the format {row number}{chair number}
            wstring chairName = wstring(1, rowLabel) + to_wstring(j);
            row.push_back(Chair(chairId, chairName, false));
        }
        chairs.push_back(row);
        rowLabel++;
    }

    loadShowtimeFromCSV(showtimes, id);


    for(auto &showtime: showtimes){
        showtime.setChairs(chairs);
    }

}

int Room::getId() const {
    return id;
}

wstring Room::getName() const {
    return name;
}

void Room::addShowtime(const Showtime &showtime)
{
    showtimes.push_back(showtime);
}

vector<Showtime>& Room::getShowtimes() { 
    return showtimes; 
}

void Room::resetShowtimes() {
    showtimes.clear();
}

vector<vector<Chair>> Room::getChairs() {
    return chairs;  
}

void Room::deleteShowtime(int showtimeID) {
    auto it = find_if(showtimes.begin(), showtimes.end(), [showtimeID](const Showtime& showtime) {
        return showtime.showtimeID == showtimeID;
    });

    if (it != showtimes.end()) {
        showtimes.erase(it);
    }
}

int Room::getNumRows() {
    return numRows;
}

int Room::getNumChairsPerRow() {
    return numChairsPerRow;
}
