#include "../Header/RoomList.h"
#include "../Header/gotoXY.h"
#include "../Header/getXY.h"
#include <regex>

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
        wstring ID, name, numRows, numChairsPerRow, screen, status;
        wstringstream ss;
        ss.str(line);
        getline(ss, ID, L',');
        getline(ss, name, L',');
        getline(ss, numRows, L',');
        getline(ss, numChairsPerRow, L',');
        getline(ss, screen, L',');
        getline(ss, status);

        ss.clear();
        rooms.push_back(Room(stoi(ID), name, stoi(numRows), stoi(numChairsPerRow), screen, stoi(status)));
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
    table.push_back({L" ID ", L" Tên phòng ", L" Số lượng ghế ", L"Màn hình ", L" Trạng thái "});
    for(auto &room: rooms){
        table.push_back({to_wstring(room.getId()), room.getName(), to_wstring(room.getNumRows() * room.getNumChairsPerRow()), room.getScreen(), room.getStatus() == 1 ? L"Đang hoạt động" : L"Không hoạt động"});
    }
    drawTable(table);
}

void RoomList::addRoom(){
    wstring name, numRows, numChairsPerRow;
    wstring screen, status;
    Position pos;
    int x, y;

    system("cls");
    // wcin.ignore();
    red(L"[Nhập 0 để quay lại]\n");
    drawTable({{L"           THÊM PHÒNG CHIẾU           "}});
    drawTable({{L"Nhập tên phòng: ", L"                         "},
                {L"Số hàng ghế: ", L"                         "},
                {L"Số ghế mỗi hàng: ", L"                         "},
                {L"Màn hình: ", L"                         "},
                {L"Trạng thái (1. Hoạt động, 0. Bảo trì): ", L"                         "}});
    pos = getXY();
    x = pos.X;
    y = pos.Y;

inputName:
    gotoXY(44, y-10);
    wcout << L"                     ";
    gotoXY(44, y-10);
    getline(wcin, name);    
    if(name == L"0"){
        system("cls");
        return;
    }

    wregex pattern(L"^[^\\n]([a-zA-ZÀÁÂÃÈÉÊÌÍÒÓÔÕÙÚĂĐĨŨƠàáâãèéêìíòóôõùúăđĩũơƯĂẠẢẤẦẨẪẬẮẰẲẴẶẸẺẼỀỀỂưăạảấầẩẫậắằẳẵặẹẻẽềềểỄỆỈỊỌỎỐỒỔỖỘỚỜỞỠỢỤỦỨỪễệỉịọỏốồổỗộớờởỡợụủứừỬỮỰỲỴÝỶỸửữựỳỵỷỹ0-9 0-9]+)$");

    if(!regex_match(name, pattern)){
        gotoXY(x, y+1);
        red(L"Tên phòng không hợp lệ. Vui lòng nhập lại.\n");
        name.clear();
        goto inputName;
    }

    gotoXY(x, y+1);
    wcout << L"                                             ";

inputNumrow:
    gotoXY(44, y-8);
    wcout << L"                     ";
    gotoXY(44, y-8);
    wcin >> numRows;
    if(!regex_match(numRows, wregex(L"^[0-9]+$"))){
        gotoXY(x, y+1);
        red(L"Số hàng ghế không hợp lệ. Vui lòng nhập lại.\n");
        numRows.clear();
        goto inputNumrow;
    }

    gotoXY(x, y+1);
    wcout << L"                                            ";

inputNumChairsPerRow:
    gotoXY(44, y-6);
    wcout << L"                     ";
    gotoXY(44, y-6);
    wcin >> numChairsPerRow;
    if(!regex_match(numChairsPerRow, wregex(L"^[0-9]+$"))){
        gotoXY(x, y+1);
        red(L"Số ghế mỗi hàng không hợp lệ. Vui lòng nhập lại.\n");
        numChairsPerRow.clear();
        goto inputNumChairsPerRow;
    }

    gotoXY(x, y+1);
    wcout << L"                                            ";

inputScreen:
    gotoXY(44, y-4);
    wcout << L"                     ";
    gotoXY(44, y-4);
    getline(wcin, screen);
    if(!regex_match(screen, wregex(L"^[a-zA-Z0-9 ]+$"))){
        gotoXY(x, y+1);
        red(L"Màn hình không hợp lệ. Vui lòng nhập lại.\n");
        screen.clear();
        goto inputScreen;
    }
    gotoXY(x, y+1);
    wcout << L"                                            ";

inputStatus:
    gotoXY(44, y-2);
    wcout << L"                     ";
    gotoXY(44, y-2);
    wcin >> status;
    if(status != L"1" && status != L"0"){
        gotoXY(x, y+1);
        red(L"Trạng thái không hợp lệ. Vui lòng nhập lại.\n");
        status.clear();
        goto inputStatus;
    }

    gotoXY(x, y+1);
    wcout << L"                                            ";


    rooms.push_back(Room(rooms.size() + 1, name, stoi(numRows), stoi(numChairsPerRow), screen, stoi(status)));

    wofstream file("../DATA/rooms.csv", ios::app);
    file.imbue(locale(locale(), new codecvt_utf8<wchar_t>));
    file << rooms.size() << L"," << name << L"," << numRows << L"," << numChairsPerRow << L"," << screen << L"," << status << endl;
    file.close();
    system("cls");
    green(L"[Phòng chiếu đã được thêm vào hệ thống.]\n");
}


void RoomList::editRoom(){
    
}
     
