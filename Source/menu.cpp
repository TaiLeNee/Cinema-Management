#include "../Header/Menu.h"
#include "../Header/drawTable.h"

using namespace std;

// wstring YELLOW = L"\033[93m";

void SellTicketInWeek(MovieList &movieList) {
    

    vector<vector<wstring>> table;
    vector<wstring>date;
    // Lấy thời gian hiện tại
    time_t now = time(0);
    tm *ltm = localtime(&now);

    table.push_back({L"Ngày chiếu phim"}); 
    table.push_back({L"[1]. Hôm nay: " + to_wstring(ltm->tm_mday) + L"/" + to_wstring(1 + ltm->tm_mon) + L"/" + to_wstring(1900 + ltm->tm_year)});
    
    date.push_back(to_wstring(ltm->tm_mday) + L"/" + to_wstring(1 + ltm->tm_mon) + L"/" + to_wstring(1900 + ltm->tm_year));

    now += 24 * 60 * 60;
    ltm = localtime(&now);
    table.push_back({L"[2]. Ngày mai: " + to_wstring(ltm->tm_mday) + L"/" + to_wstring(1 + ltm->tm_mon) + L"/" + to_wstring(1900 + ltm->tm_year)});
    date.push_back(to_wstring(ltm->tm_mday) + L"/" + to_wstring(1 + ltm->tm_mon) + L"/" + to_wstring(1900 + ltm->tm_year));
    
    //Các ngày trong tuần 1 tuần

    for(int i = 2; i < 7; i++){
        now += 24 * 60 * 60;
        tm *ltm = localtime(&now);
        table.push_back({ L"["+to_wstring(i+1)+L"]" + L". " + to_wstring(ltm->tm_mday) + L"/" + to_wstring(1 + ltm->tm_mon) + L"/" + to_wstring(1900 + ltm->tm_year)});
        date.push_back(to_wstring(ltm->tm_mday) + L"/" + to_wstring(1 + ltm->tm_mon) + L"/" + to_wstring(1900 + ltm->tm_year));

    }

    Date:
        system("cls");
        drawTable(table);
        wcout<<L"\033[92mNhập 0: Quay lại\n";
        wcout<<L"\033[92m════════[Chọn ngày]==> ";
        int choice ;
        wcin>>choice;
        wcout<<L"\033[0m";

        if(choice == 0)
            return;

    MovieInDay:
        vector<vector<wstring>> tableMovie;
        tableMovie.push_back({L"ID", L"Danh sách phim trong ngày: " + date[choice-1], L"Khung giờ chiếu"});

        for(const auto& movie: movieList.getMovies()){
            for(const auto& showtime: movie->getShowtimes()){
                if(showtime.getStartTime().getDate() == date[choice-1]){
                    tableMovie.push_back({ to_wstring(movie->getId()) , movie->getName(), showtime.getStartTime().getTime()});
                    break;
                }
            }
        }

    
        drawTable(tableMovie);
        wcout<<L"\033[92mNhập 0: Quay lại\n";
        wcout<<L"\033[92m════════[Chọn phim]==> ";
        wcin>>choice;
        wcout<<L"\033[0m";
        if(!choice)
            goto Date;
    
}




void sellTicketMenu(MovieList &movieList){
    SellTicketInWeek(movieList);
    

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
    }

}

void mainMenu(MovieList &movieList){
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
            sellTicketMenu(movieList);
            break;
        case 2:
            manageMenu();
            break;
        default:
            break;
        }
    }

}