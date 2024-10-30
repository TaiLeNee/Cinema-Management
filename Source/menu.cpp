#include "../Header/Menu.h"
#include "../Header/drawTable.h"
#include "../Header/TicketList.h"


using namespace std;

// wstring YELLOW = L"\033[93m";


void manageMovie(MovieList &movieList){

    system("cls");
    vector<vector<wstring>> table;
    table.push_back({L"        QUẢN LÝ PHIM            "});
    table.push_back({L"        1. Danh sách tất cả các phim hiện tại            "});
    table.push_back({L"        2. Danh sách phim theo thể loại            "});   
    table.push_back({L"        3. Danh sách phim theo quốc gia            "});
    table.push_back({L"        4. Danh sách phim theo độ tuổi            "});

}






void manageMenu(RoomList &roomList, MovieList &movieList) {
     
    system("cls");                                                             
   drawTable({
        {L"         HỆ THỐNG QUẢN LÝ RẠP CHIẾU PHIM            "},
        {L"1. Quản lý Phim            "},
        {L"2. Quản lý Phòng Chiếu            "},
        {L"3. Quản lý Lịch Chiếu            "},
        {L"4. Quản lý Ghế Ngồi            "},
        {L"5. Quản lý Nhân Viên            "},
        {L"6. Báo Cáo và Thống Kê            "},
        {L"7. Cài Đặt Hệ Thống            "},
        {L"8. Trợ Giúp và Hỗ Trợ            "},
        {L"0. Quay lại            "}
    });
   
    wcout << L"══════════[Nhập lựa chọn]==> ";
    int choice;
    wcin >> choice;
    if(!choice)
        return;
    switch (choice)
    {
    case 1:
        break;
    case 2:
        break;
    case 3:
        manageShowtimes(roomList, movieList);
        break;
    }

}

void mainMenu(RoomList &roomList, MovieList &movieList){
    system("cls");
    wcout<<L"\n\n";
    wcout<< L"\033[92m      ██╗    ██╗███████╗██╗      ██████╗ ██████╗ ███╗   ███╗███████╗██╗\n"
          <<L"\033[92m      ██║    ██║██╔════╝██║     ██╔════╝██╔═══██╗████╗ ████║██╔════╝██║\n"
          <<L"\033[92m      ██║ █╗ ██║█████╗  ██║     ██║     ██║   ██║██╔████╔██║█████╗  ██║\n"
          <<L"\033[92m      ██║███╗██║██╔══╝  ██║     ██║     ██║   ██║██║╚██╔╝██║██╔══╝  ╚═╝\n"
          <<L"\033[92m      ╚███╔███╔╝███████╗███████╗╚██████╗╚██████╔╝██║ ╚═╝ ██║███████╗██╗\n"
          <<L"\033[92m     ╚══╝╚══╝ ╚══════╝╚══════╝ ╚═════╝ ╚═════╝ ╚═╝     ╚═╝╚══════╝╚═╝ \n";
    wcout<<L"\033[m";     


    vector<vector<wstring>> table;
    table.push_back({L"        HỆ THỐNG QUẢN LÝ RẠP CHIẾU PHIM            "});
    table.push_back({L"        1. Bán vé            "});
    table.push_back({L"        2. Quản lý            "});

    int choice;
    while (choice!=0)
    {
    
        drawTable(table);

        wcout << L"════════[Nhập lựa chọn]==> ";
        wcin >> choice;
        switch (choice)
        {
        case 1:
            SellTicketInWeek(movieList);
            break;
        case 2:
            manageMenu(roomList, movieList);
            break;
        default:
            break;
        }
    }

}