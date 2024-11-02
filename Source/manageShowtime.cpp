#include "../Header/Menu.h"
#include "drawCalendar.cpp"
#include "../Header/gotoXY.h"
#include "../Header/getXY.h"
#include "../Header/checkInput.h"


using namespace std;

Datetime getDatetime(){

    Datetime startTime;
    Position pos; int x, y;

    //Lấy tháng hiện tại, ngày hiện tại
    // Get current time
    time_t now = time(0);
    tm *ltm = localtime(&now);

    // Get current month and day
    int monthNow = 1 + ltm->tm_mon; // tm_mon is months since January (0-11)
    int dayNow = ltm->tm_mday;


    getTime:
    drawTable({{L"Nhập tháng: ", L"          "}});
    pos = getXY();
     y = pos.Y;
     x = pos.X;

    gotoXY(17, y-2);
    int month; wcin>>month;

    //Kiểm tra tháng
    if(month < 1 || month > 12 || month < monthNow){
        red(L"══[Tháng không hợp lệ, Vui lòng nhập lại]══\n");
        goto getTime;
    }
    
    gotoXY(0, y+1);
    startTime = drawCalendar(month, 2024);

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
    return startTime;

   
}

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
    
    inputTime:
    Datetime startTime = getDatetime();

    
    Showtime showtime(movieID, roomID, startTime);

    //Kiểm tra showtime đã tồn tại chưa
    for(auto &room: rooms){
        for(auto &showtime: room.getShowtimes()){
            if(showtime.getStartTime() == startTime){
                red(L"══[Khung giờ đã tồn tại, Vui lòng nhập lại]══\n");
                goto inputTime;
            }
        }
    }

    green(L"══[Tạo khung giờ chiếu thành công]══\n");
    green(L"═══[Có muốn lưu thay đổi không? (Y/N) hoặc (y/n)]==> ");
    wchar_t c;
    wcin>>c;
    c = towlower(c);
    if(c != 'y'){
        return;
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
        red(L"Không thể mở file showtime.csv!\n");
        return;
    }

    file << showtime.showtimeID << L"," << showtime.movieID << L"," << showtime.roomID << L"," << showtime.getStartTime().getFulltime() << L"\n";


    green(L"══[Lưu khung giờ chiếu thành công]══\n");
    wcin.get();

    
    return;

            
}

void editShowtime(vector<Showtime*>& showtimeList,  vector<vector<wstring>> table, RoomList &roomList, MovieList &movieList){
    
    bool checkShowtime = 0;

    int choiceShowtime;

    editShowtime:
    // green(L"══[Nhập ID khung giờ chiếu cần sửa]==> ");
    // wcin>>choiceShowtime;
    checkInput(L"Nhập ID khung giờ chiếu cần sửa", choiceShowtime);

    Showtime *getShowtime = nullptr;
    for(Showtime *showtime: showtimeList){
     
        if(showtime->showtimeID == choiceShowtime){
            checkShowtime = 1;            
            getShowtime = showtime;
            break;
        }
    }
    
    if(!checkShowtime){
        red(L"══[Khung giờ chiếu không tồn tại]══\n");
        goto editShowtime;
        
    }


    system("cls");
    
    table.erase(
        remove_if(table.begin()+1, table.end(), [choiceShowtime](const vector<wstring>& row) {
            return row[0] != L"ID Khung giờ" && stoi(row[0]) != choiceShowtime;
        }),
        table.end()
    );
    choiceEdit:
    drawTable(table);

    drawTable({
        {L"         SỬA KHUNG GIỜ CHIẾU         "},
        {L"1. Sửa thời gian chiếu"},
        {L"2. Sửa phòng chiếu"},
        {L"3. Sửa phim chiếu"},
        {L"0. Quay lại"}
        });
    int choice;
    checkInput(L"Nhập lựa chọn", choice);

    if(!choice){
        system("cls");
        return;
    }
    switch (choice){
        case 1:
            //Sửa thời gian chiếu
            getShowtime->setStartTime(getDatetime());
            break;
        case 2:{
            //Sửa phòng chiếu
            vector<vector<wstring>> tableRoom;
            tableRoom.push_back({L" ID Phòng ", L" Tên phòng "});
            for(auto &room: roomList.getRooms()){
                tableRoom.push_back({to_wstring(room.getId()), room.getName()});
            }
            drawTable(tableRoom);
            red(L"Nhập 0: quay lại\n");
            int roomID;
            checkInput(L"Nhập ID phòng chiếu mới", roomID);
            if(!roomID){
                system("cls");
                goto choiceEdit;
            }
            bool checkRoomID = 0;
            for(auto &room: roomList.getRooms()){
                if(room.getId() == roomID){
                    getShowtime->roomID = roomID;
                    checkRoomID = 1;
                    break;
                }
            }
            if(!checkRoomID){
                red(L"══[ID phòng không hợp lệ, Vui lòng nhập lại]══\n");
                goto choiceEdit;
            }
            wcout<<L"ID phòng: "<<getShowtime->roomID<<endl;
            break;

        }

        case 3:{
            //Sửa phim chiếu
            vector<vector<wstring>> tableMovie;
            tableMovie.push_back({L" ID Movie ", L" Tên phim "});
            for(auto &movie: movieList.getMovies()){
                tableMovie.push_back({to_wstring(movie->getId()), movie->getName()});
            }
            drawTable(tableMovie);
            int movieID;
            red(L"Nhập 0: quay lại\n");

            checkInput(L"Nhập ID phim chiếu mới", movieID);
            if(!movieID){
                system("cls");
                goto choiceEdit;
            }
            bool checkMovieID = 0;
            for(auto &movie: movieList.getMovies()){
                if(movie->getId() == movieID){
                    getShowtime->movieID = movieID;
                    checkMovieID = 1;
                    break;
                }
            }
            if(!checkMovieID){
                red(L"══[ID phim không hợp lệ, Vui lòng nhập lại]══\n");
                goto choiceEdit;
            }
        }
            break;
        default:
            system("cls");
            red(L"══[Lựa chọn không hợp lệ, Vui lòng chọn lại]══\n");
            goto choiceEdit;
            break;
    }


    green(L"══[Xác nhận lưu chỉnh sửa? (Y/N) hoặc (y/n)]==> ");
    wstring lineEdit = to_wstring(getShowtime->showtimeID) + L"," + to_wstring(getShowtime->movieID) + L"," + to_wstring(getShowtime->roomID) + L"," + getShowtime->getStartTime().getFulltime();
    

    wchar_t c;
    wcin >> c;
    c = towlower(c);
    if(c != 'y'){
        return;
    }

    //Lưu chỉnh sửa ở file
    wifstream fileIn(L"../DATA/showtimes.csv");
    wofstream fileOut(L"../DATA/temp_showtimes.csv");
    fileIn.imbue(locale(locale(), new codecvt_utf8<wchar_t>));
    fileOut.imbue(locale(locale(), new codecvt_utf8<wchar_t>));
    if (!fileIn.is_open() || !fileOut.is_open()) {
        red(L"Không thể mở file showtimes.csv!\n");
        return;
    }

    wstring line;
    getline(fileIn, line); // Skip the header
    fileOut << line << L"\n";
    while (getline(fileIn, line)) {
        wstringstream ss(line);
        wstring id;
        getline(ss, id, L',');
    
        if (getShowtime->showtimeID == stoi(id)) {
            fileOut << lineEdit << L"\n";
        }else
            fileOut << line << L"\n";
    }


    fileIn.close();
    fileOut.close();

    remove("../DATA/showtimes.csv");
    rename("../DATA/temp_showtimes.csv", "../DATA/showtimes.csv");
    green(L"══[Cập nhật file 'showtimes.csv' thành công]══\n");
    green(L"══[Nhấn Enter để tiếp tục...]══\n");
    wcin.get();
    wcin.get();


    //Lưu chỉnh sửa
    green(L"══[Lưu chỉnh sửa thành công]══\n");
    //Reset lại danh sách showtime
    roomList.resetShowtimesofRoom();
    movieList.resetShowtimesofMovie();
    //Load lại danh sách showtime
    roomList.loadRoom();
    for(auto &room: roomList.getRooms()){
        movieList.loadShowtimesofMovie(room.getShowtimes());
    }

    return;

}

void deleteShowtime(RoomList &roomList, MovieList &movieList){


    vector<Room>& rooms = roomList.getRooms();
    vector<Movie*>& movies = movieList.getMovies();
    

    
    
    bool checkShowtime = 0;

    Movie* Movieptr = NULL;
    Room *Roomptr = NULL;


    int choiceShowtime;

    deleteShowtime:
    // green(L"══[Nhập ID khung giờ chiếu cần xóa]==> ");
    // wcin>>choiceShowtime;
    red(L"Nhập 0: quay lại\n");
    checkInput(L"Nhập ID khung giờ chiếu cần xóa", choiceShowtime);
    if(!choiceShowtime){
        system("cls");
        return;
    }
    Showtime getShowtime;

    for(auto &room: rooms){
        for(auto &showtime: room.getShowtimes()){
            if(showtime.showtimeID == choiceShowtime){
                checkShowtime = 1;
                for(auto &movie: movies){
                    if(movie->getId() == showtime.movieID){
                        checkShowtime = 1;
                        getShowtime = showtime;    
                        Movieptr = movie;
                        Roomptr = &room;
                    }
                }
                
            }
        }
      
    }

    if(!checkShowtime){
        red(L"══[Khung giờ chiếu không tồn tại]══\n");
        goto deleteShowtime;
        
    }

    system("cls");
    vector<vector<wstring>> table;
    table.push_back({L" ID Khung giờ ", L" Tên phòng ", L" Tên phim ", L" Giờ chiếu ", L" Ngày chiếu "});
    table.push_back({to_wstring(getShowtime.showtimeID), Roomptr->getName(), Movieptr->getName(), 
                    getShowtime.getStartTime().getTime(), getShowtime.getStartTime().getDate()});

    drawTable(table);

    green(L"══[Xác nhận xóa khung giờ chiếu? (Y/N) hoặc (y/n)]==> ");
    wchar_t c;
    wcin >> c;
    c = towlower(c);
    if(c != 'y'){
        return;
    }

    
    Roomptr->deleteShowtime(choiceShowtime);
    Movieptr->deleteShowtime(choiceShowtime);
    green(L"══[Xóa khung giờ chiếu thành công]══\n");

    // Remove showtime from CSV file
    wifstream fileIn(L"../DATA/showtimes.csv");
    wofstream fileOut(L"../DATA/temp_showtimes.csv");
    fileIn.imbue(locale(locale(), new codecvt_utf8<wchar_t>));
    fileOut.imbue(locale(locale(), new codecvt_utf8<wchar_t>));

    if (!fileIn.is_open() || !fileOut.is_open()) {
        red(L"Không thể mở file showtimes.csv!\n");
        return;
    }

    wstring line;
    getline(fileIn, line); // Skip the header
    fileOut << line << L"\n";
    while (getline(fileIn, line)) {
        wstringstream ss(line);
        wstring id;
        getline(ss, id, L',');
        if (stoi(id) != choiceShowtime) {
            fileOut << line << L"\n";
        }
    }

    fileIn.close();
    fileOut.close();

    remove("../DATA/showtimes.csv");
    rename("../DATA/temp_showtimes.csv", "../DATA/showtimes.csv");
    green(L"══[Cập nhật file 'showtimes.csv' thành công]══\n");
    green(L"══[Nhấn Enter để tiếp tục...]══\n");
    wcin.get();
    wcin.get();
    return;

}


void displayListShowtimeAll(RoomList &roomList, MovieList &movieList){
    vector<vector<wstring>> table;
    vector<Room>& rooms = roomList.getRooms();
    vector<Movie*>& movies = movieList.getMovies();

    vector<Showtime*> showtimeList;

    displayShowtime:
    table.clear();
    table.push_back({L" ID Khung giờ ", L" Tên phòng ", L" Tên phim ", L" Giờ chiếu ", L" Ngày chiếu "});
    


    for(auto &room: rooms){
        vector<Showtime>& showtimes = room.getShowtimes();
        for(auto &showtime: showtimes){
            for(auto &movie: movies){
                if(showtime.movieID == movie->getId()){
                    Datetime startime = showtime.getStartTime();
                    table.push_back({to_wstring(showtime.showtimeID), room.getName(), movie->getName(), 
                                    startime.getTime(), startime.getDate()});

                    showtimeList.push_back(&showtime);

                }
            }
        }
    }

    sort(table.begin()+1, table.end(), [](const vector<wstring>& a, const vector<wstring>& b){
        return stoi(a[0]) < stoi(b[0]);
    });

    
    drawTable(table);

    green(L"════════════════════════════════════════════════════════════════════════════════════════════════\n");

    drawTable({
        {L"1. Thêm Khung giờ chiếu"},
        {L"2. Sửa Khung giờ chiếu"},
        {L"3. Xóa Khung giờ chiếu"},
        {L"0. Quay lại"}
    });

    
    int choice;
    checkInput(L"Nhập lựa chọn", choice);

    if(!choice){
        system("cls");
        return;
    }
        
    switch (choice){
        case 1:
            addShowtime(roomList, movieList);
            break;
        case 2:
            editShowtime(showtimeList, table, roomList, movieList);
            break;
        case 3:
            deleteShowtime(roomList, movieList);
            break;
        default:
            system("cls");
            red(L"══[Lựa chọn không hợp lệ, Vui lòng chọn lại]══\n");
            
            break;
    }
    goto displayShowtime;

}




void manageShowtimes(RoomList &roomList, MovieList &movieList){
    system("cls");
    vector<vector<wstring>> table;
    table.push_back({L"        QUẢN LÝ LỊCH CHIẾU            "});
    table.push_back({L"        1. Danh sách tất cả các lịch chiếu           "});
    table.push_back({L"        2. Danh sách lịch chiếu theo ngày            "});   
    table.push_back({L"        3. Danh sách lịch chiếu theo phim            "});
    table.push_back({L"        4. Danh sách lịch chiếu theo phòng chiếu            "});
    table.push_back({L"        0. Quay lại            "});

    manageShowtime:
    drawTable(table);

   green(L"════════[Nhập lựa chọn]==> ");
    int choice;
    wcin >> choice;
    if(!choice){
        system("cls");
        return;
    }
    switch (choice)
    {
        case 1:
            displayListShowtimeAll(roomList, movieList);
            break;
        case 2:
            break;

    }
    goto manageShowtime;
}