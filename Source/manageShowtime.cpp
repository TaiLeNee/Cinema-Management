#include "../Header/Menu.h"
#include "drawCalendar.cpp"
#include "../Header/gotoXY.h"
#include "../Header/getXY.h"
#include "../Header/checkInput.h"

using namespace std;



void addShowtime(RoomList &roomList, MovieList& movieList){
    Position pos;
    int x,y;


    vector<vector<wstring>> table;
    table.push_back({L" ID Movie ", L" Tên phim ", L" ", L" ID Phòng ", L" Tên phòng "});

    vector<Movie*>& movies = movieList.getMovies();
    vector<Room>& rooms = roomList.getRooms();

    
    vector<wstring> row;
    for(int i = 0; i< movies.size(); i++){
        row.push_back(to_wstring(movies[i]->getId()));
        row.push_back(movies[i]->getName());
        row.push_back(L" ");
        if(i < rooms.size()){
            row.push_back(to_wstring(rooms[i].getId()));
            row.push_back(rooms[i].getName());
        }else{
            row.push_back(L" ");
            row.push_back(L" ");
        }
        table.push_back(row);
        row.clear();
    }
    system("cls");

    addShowtime:
    drawTable(table);
    int movieID, roomID;
    drawTable({
        {L"         THÊM KHUNG GIỜ CHIẾU         "}});
    drawTable({
        {L"Nhập ID phim: ", L" "},
        {L"Nhập ID phòng: ", L" "}
    }); 

    pos = getXY();
    x = pos.X;
    y = pos.Y;

    gotoXY(20, y - 4);

    wcin >> movieID;

    int checkMovieID = 0;
    for(auto &movie: movies){
        if(movie->getId() == movieID){
            checkMovieID = 1;
            break;
        }
    }

    if(!checkMovieID){
        system("cls");
        red(L"══[ID Movie không hợp lệ, Vui lòng nhập lại]══\n");
        goto addShowtime;
    }


    gotoXY(20, y - 2);
    wcin >> roomID;
    gotoXY(0, y+1);

    bool checkRoomID = 0;
    for(auto &room: rooms){
        if(room.getId() == roomID){
            checkRoomID = 1;
            break;
        }
    }

    if(!checkRoomID){
        system("cls");
        red(L"══[ID Room không hợp lệ, Vui lòng nhập lại]══\n");
        goto addShowtime;
    }

   
    choiceDate:
    drawTable({
        {L"         Nhập Thời gian bắt đầu         "}});
    
    

    drawTable({{L"Nhập tháng: ", L"          "}});
    pos = getXY();
     y = pos.Y;
     x = pos.X;

    gotoXY(17, y-2);
    int month; wcin>>month;
    
    gotoXY(0, y+1);
    Datetime startTime = drawCalendar(month, 2024);

    inputTime:

    drawTable({{L"Giờ: ", L"    ", L"Phút: ", L"    "}});
    int hour, minute;
     pos = getXY();
     y = pos.Y;
     x = pos.X;
    gotoXY(10, y-2);
    wcin>>hour;
    

    if(hour < 0 || hour > 23){
        red(L"══[Giờ không hợp lệ, Vui lòng nhập lại]══\n");
        goto inputTime;
    }

    gotoXY(26, y-2);
    wcin>>minute;

    if(minute < 0 || minute > 59){
        red(L"══[Phút không hợp lệ, Vui lòng nhập lại]══\n");
        goto inputTime;
    }

    gotoXY(0, y+1);

    startTime.setHour(to_wstring(hour));
    startTime.setMinute(to_wstring(minute));

    green(L"══[Lưu khung giờ chiếu thành công]══\n");
    green(L"═══[Có muốn lưu thay đổi không? (Y/N) hoặc (y/n)]==> ");
    wchar_t c;
    wcin>>c;
    c = towlower(c);
    if(c != 'y'){
        return;
    }


    Showtime showtime( movieID, roomID, startTime);

    //Kiểm tra showtime đã tồn tại chưa
    for(auto &room: rooms){
        for(auto &showtime: room.getShowtimes()){
            if(showtime.getStartTime() == startTime){
                red(L"══[Khung giờ đã tồn tại, Vui lòng nhập lại]══\n");
                goto inputTime;
            }
        }
    }

    bool checkInRoom=0;
    for(auto &room: rooms){
        if(room.getId() == roomID){
            showtime.setChairs(room.getChairs());
            room.addShowtime(showtime);
            checkInRoom = 1;
            break;
        }
    }

    bool checkInMovie=0;
    for(auto &movie: movies){
        if(movie->getId() == movieID){
            movie->addShowtime(showtime);
            checkInMovie = 1;
            break;
        }
    }
    
    if(!checkInRoom || !checkInMovie){
        red(L"══[Thêm khung giờ chiếu không thành công]══\n");
        wcin.get();
        return;
    }

    wofstream file("../Data/showtimes.csv", ios::app);
    file.imbue(locale(locale(), new codecvt_utf8<wchar_t>));
    if (!file.is_open()) {
        wcerr << L"Không thể mở file showtime.csv!" << endl;
        return;
    }

    file << showtime.showtimeID << L"," << showtime.movieID << L"," << showtime.roomID << L"," << showtime.getStartTime().getFulltime() << L"\n";


    green(L"══[Lưu khung giờ chiếu thành công]══\n");
    wcin.get();

    
    return;

            
}



void deleteShowtime(RoomList &roomList, MovieList &movieList){


    vector<Room>& rooms = roomList.getRooms();
    vector<Movie*>& movies = movieList.getMovies();

    int choiceShowtime;
    green(L"══[Nhập ID khung giờ chiếu cần xóa]==> ");
    wcin >> choiceShowtime;
    checkInput(choiceShowtime);

    for(auto &room: rooms){
        for(auto &showtime: room.getShowtimes()){
            if(showtime.showtimeID == choiceShowtime){
                room.deleteShowtime(showtime.showtimeID);
                for(auto &movie: movies){
                    if(movie->getId() == showtime.movieID){
                        movie->deleteShowtime(showtime.showtimeID);
                    }
                }
                green(L"══[Xóa khung giờ chiếu thành công]══\n");
                return;
            }
        }
    }
}


void displayListShowtime(RoomList &roomList, MovieList &movieList){
    vector<vector<wstring>> table;
    table.push_back({L" ID Khung giờ ", L" Tên phòng ", L" Tên phim ", L" Giờ chiếu ", L" Ngày chiếu "});
    

    vector<Room>& rooms = roomList.getRooms();
    vector<Movie*>& movies = movieList.getMovies();

    for(auto &room: rooms){
        vector<Showtime> showtimes = room.getShowtimes();
        for(auto &showtime: showtimes){
            for(auto &movie: movies){
                if(showtime.movieID== movie->getId()){
                    Datetime startime = showtime.getStartTime();
                    table.push_back({to_wstring(showtime.showtimeID), room.getName(), movie->getName(), 
                                    startime.getTime(), startime.getDate()});
                }
            }
        }
    }

    sort(table.begin()+1, table.end(), [](const vector<wstring>& a, const vector<wstring>& b){
        return stoi(a[0]) < stoi(b[0]);
    });

    displayShowtime:
    drawTable(table);

    green(L"════════════════════════════════════════════════════════════════════════════════════════════════\n");

    drawTable({
        {L"1. Thêm Khung giờ chiếu"},
        {L"2. Sửa Khung giờ chiếu"},
        {L"3. Xóa Khung giờ chiếu"},
        {L"0. Quay lại"}
    });

    green(L"════════[Nhập lựa chọn]==> ");
    int choice;
    wcin >> choice;
    if(!choice)
        return;
    switch (choice){
        case 1:
            addShowtime(roomList, movieList);
            break;
        case 2:
            break;
        case 3:
            break;
    }

}




void manageShowtimes(RoomList &roomList, MovieList &movieList){
    system("cls");
    vector<vector<wstring>> table;
    table.push_back({L"        QUẢN LÝ LỊCH CHIẾU            "});
    table.push_back({L"        1. Danh sách tất cả các lịch chiếu           "});
    table.push_back({L"        2. Danh sách lịch chiếu theo ngày            "});   
    table.push_back({L"        3. Danh sách lịch chiếu theo phim            "});
    table.push_back({L"        4. Danh sách lịch chiếu theo phòng chiếu            "});

    drawTable(table);

   green(L"════════[Nhập lựa chọn]==> ");
    int choice;
    wcin >> choice;
    if(!choice)
        return;
    switch (choice)
    {
    case 1:
        displayListShowtime(roomList, movieList);
        break;
    case 2:
        break;

    }
}