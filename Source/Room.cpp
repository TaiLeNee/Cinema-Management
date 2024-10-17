#include "../Header/Room.h"

#include "Showtime.cpp"
#include "Chair.cpp"

<<<<<<< HEAD
// Room class implementation
Room::Room() : id(0), name(L"") {}

Room::Room(int id, const wstring &name, const vector<Chair> &chairs) : id(id), name(name), chairs(chairs) {}
=======
using namespace std;

 // Danh sách khung giờ chiếu

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
}
>>>>>>> 6f719d1ff1800254f76089400e7703df50c01151

int Room::getId() const
{
    return id;
}

wstring Room::getName() const
{
    return name;
}

<<<<<<< HEAD
vector<Chair> &Room::getChairs()
{
    return chairs;
}

void Room::displayChairs() const
{
}

void Room::addChairs(int numRows, int numChairsPerRow)
{
    char rowLabel = 'A';
    int chairId = 1;

    for (int i = 0; i < numRows; ++i)
    {
        for (int j = 1; j <= numChairsPerRow; ++j)
        {
            int chairId = (i + 1) * 100 + j; // Tạo ID ghế theo định dạng {số hàng}{số ghế}
            wstring chairName = wstring(1, rowLabel) + to_wstring(j);
            chairs.push_back(Chair(chairId, chairName, false));
        }
        rowLabel++;
    }
}

void Room::changeStatusChair(int chairId, bool isBooked)
{
    auto it = find_if(chairs.begin(), chairs.end(), [chairId](const Chair &chair)
                      { return chair.getId() == chairId; });

    if (it != chairs.end())
    {
        it->setIsBooked(isBooked); // Đặt trạng thái ghế thành không được đặt
    }
}
=======
void Room::addShowtime(const Showtime &showtime)
{
    showtimes.push_back(showtime);
}

vector<Showtime>& Room::getShowtimes() { 
    return showtimes; 
}

vector<vector<Chair>>& Room::getChairs() {
    return chairs;  
}

>>>>>>> 6f719d1ff1800254f76089400e7703df50c01151
