#include "../Header/Room.h"
#include <algorithm>
#include "displayChairs.cpp"
#include "Chair.cpp"


// Room class implementation
Room::Room() : id(0), name(L"") {}

Room::Room(int id, const wstring& name, const vector<Chair>& chairs) : id(id), name(name), chairs(chairs) {}

int Room::getId() const {
    return id;
}

wstring Room::getName() const {
    return name;
}

vector<Chair>& Room::getChairs() {
    return chairs;  
}

void Room::displayChairs() const
{

}

void Room::addChairs(int numRows, int numChairsPerRow) {
    char rowLabel = 'A';
    int chairId = 1;

    for (int i = 0; i < numRows; ++i) {
        for (int j = 1; j <= numChairsPerRow; ++j) {
            int chairId = (i + 1) * 100 + j; // Tạo ID ghế theo định dạng {số hàng}{số ghế}
            wstring chairName = wstring(1, rowLabel) + to_wstring(j);
            chairs.push_back(Chair(chairId, chairName, false));
        }
        rowLabel++;
    }
}

void Room::changeStatusChair(int chairId, bool isBooked) {
    auto it = find_if(chairs.begin(), chairs.end(), [chairId](const Chair& chair) {
        return chair.getId() == chairId;
    });

    if (it != chairs.end()) {
        it->setIsBooked(isBooked); // Đặt trạng thái ghế thành không được đặt
    }
}
