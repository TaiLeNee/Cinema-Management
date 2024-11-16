#include "../Header/Room.h"
#include "../Header/Showtime.h"
#include "../Header/Chair.h"
#include "loadShowtimeFromCSV.cpp"
// #include "Room.h"


using namespace std;


// void Room::loadShowtimes(const string& filename);
    

// Room class implementation
Room::Room() : id(0), name(L"") {}

Room::Room(int id, const wstring& name, int numRows, int numChairsPerRow, wstring screen, int status) : id(id), name(name), numRows(numRows), numChairsPerRow(numChairsPerRow), screen(screen), status(status) {

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

wstring Room::getScreen() {
    return screen;
}

int Room::getStatus() {
    return status;
}

void Room::setName(const wstring &name)
{
    this->name = name;
}

void Room::setNumRows(int numRows)
{
    this->numRows = numRows;
}

void Room::setNumChairsPerRow(int numChairsPerRow)
{
    this->numChairsPerRow = numChairsPerRow;
}

void Room::setScreen(const wstring &screen)
{
    this->screen = screen;
}

void Room::setStatus(int status)
{
    this->status = status;
}

void Room::displayInfo(){
    drawTable({{L"          THÔNG TIN PHÒNG CHIẾU          "}});
    drawTable({{L"ID", L"Tên phòng", L"Số ghế", L"Màn hình", L"Trạng thái"},
                {to_wstring(id), name, to_wstring(numRows * numChairsPerRow), screen, status == 1 ? L"Đang hoạt động" : L"Không hoạt động"}});
                

}