#include "../Header/Menu.h"
#include "../Header/drawTable.h"

using namespace std;



void SellTicketInWeek() {
    
    vector<vector<wstring>> table;

    // Lấy thời gian hiện tại
    time_t now = time(0);
    tm *ltm = localtime(&now);

    table.push_back({L"Chọn ngày chiếu phim"}); 
    table.push_back({L"[1]. Hôm nay: " + to_wstring(ltm->tm_mday) + L"/" + to_wstring(1 + ltm->tm_mon) + L"/" + to_wstring(1900 + ltm->tm_year)});
    table.push_back({L"[2]. Ngày mai: " + to_wstring(ltm->tm_mday + 1) + L"/" + to_wstring(1 + ltm->tm_mon) + L"/" + to_wstring(1900 + ltm->tm_year)});
    
    //Các ngày trong tuần 1 tuần

    for(int i = 2; i < 7; i++){
        now += 24 * 60 * 60;
        tm *ltm = localtime(&now);
        table.push_back({ L"["+to_wstring(i+1)+L"]" + L". " + to_wstring(ltm->tm_mday) + L"/" + to_wstring(1 + ltm->tm_mon) + L"/" + to_wstring(1900 + ltm->tm_year)});
    }

    drawTable(table);
}


void sellTicketMenu(){
    SellTicketInWeek();
    

    vector<vector<wstring>> table;
    table.push_back({L"        1. Danh sách tất cả các phim hiện tại            "});
    table.push_back({L"        2. Danh sách phim theo thể loại            "});   
    table.push_back({L"        3. Danh sách phim theo quốc gia            "});
    table.push_back({L"        4. Danh sách phim theo độ tuổi            "});

}

void manageMenu() {
    system("cls");
    wcout<<L"\n\n";
    wcout<< L"\033[92m      ██╗    ██╗███████╗██╗      ██████╗ ██████╗ ███╗   ███╗███████╗██╗\n"
          <<L"\033[92m      ██║    ██║██╔════╝██║     ██╔════╝██╔═══██╗████╗ ████║██╔════╝██║\n"
          <<L"\033[92m      ██║ █╗ ██║█████╗  ██║     ██║     ██║   ██║██╔████╔██║█████╗  ██║\n"
          <<L"\033[92m      ██║███╗██║██╔══╝  ██║     ██║     ██║   ██║██║╚██╔╝██║██╔══╝  ╚═╝\n"
          <<L"\033[92m      ╚███╔███╔╝███████╗███████╗╚██████╗╚██████╔╝██║ ╚═╝ ██║███████╗██╗\n"
          <<L"\033[92m     ╚══╝╚══╝ ╚══════╝╚══════╝ ╚═════╝ ╚═════╝ ╚═╝     ╚═╝╚══════╝╚═╝ \n";
    wcout<<L"\033[m";      
                                                                 
    wcout << L"╔════════════════════════════════════════════╗" << endl;
    wcout << L"║     ";yellow(L"HỆ THỐNG QUẢN LÝ RẠP CHIẾU PHIM");wcout<<L"        ║" << endl;
    wcout << L"╠════════════════════════════════════════════╣" << endl;
    wcout << L"║        ";yellow(L"1. Quản lý Phim");wcout<<L"                     ║" << endl;
    wcout << L"║        ";yellow(L"2. Quản lý Phòng Chiếu");wcout<<L"              ║" << endl;
    wcout << L"║        ";yellow(L"3. Quản lý Lịch Chiếu");wcout<<L"               ║" << endl;
    wcout << L"║        ";yellow(L"4. Quản lý Ghế Ngồi");wcout<<L"                 ║" << endl;
    wcout << L"║        ";yellow(L"5. Quản lý Nhân Viên");wcout<<L"                ║" << endl;  
    wcout << L"║        ";yellow(L"6. Báo Cáo và Thống Kê");wcout<<L"              ║" << endl;  
    wcout << L"║        ";yellow(L"7. Cài Đặt Hệ Thống");wcout<<L"                 ║" << endl;  
    wcout << L"║        ";yellow(L"8. Trợ Giúp và Hỗ Trợ");wcout<<L"               ║" << endl;  
    wcout << L"╚════════════════════════════════════════════╝" << endl;
    wcout << L"══════════[Nhập lựa chọn]==> ";
}

void mainMenu(){
    vector<vector<wstring>> table;
    table.push_back({L"        HỆ THỐNG QUẢN LÝ RẠP CHIẾU PHIM            "});
    table.push_back({L"        1. Bán vé            "});
    table.push_back({L"        2. Quản lý            "});

    drawTable(table);

    int choice;
    wcout << L"════════[Nhập lựa chọn]==> ";
    wcin >> choice;
    switch (choice)
    {
    case 1:
        sellTicketMenu();
        break;
    case 2:
        manageMenu();
        break;
    default:
        break;
    }

}