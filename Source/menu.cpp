#include "../Header/Menu.h"
#include "../Header/drawTable.h"
#include "../Header/TicketList.h"
#include <regex>

using namespace std;

// wstring YELLOW = L"\033[93m";

void SellTicketInWeek(MovieList &movieList) {
    wstring GREEN = L"\033[92m";
    wstring YELLOW = L"\033[93m";
    

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

    
    vector<vector<wstring>> tableMovie;
    tableMovie.push_back({L"Chọn", L"ID", L"Danh sách phim trong ngày: " + date[choice-1], L"Khung giờ chiếu"});

    
    for(const auto& movie: movieList.getMovies()){
        for(const auto& showtime: movie->getShowtimes()){
            if(showtime.getStartTime().getDate() == date[choice-1]){
                tableMovie.push_back({ L"["+to_wstring(showtime.movieID) + L"]" , to_wstring(showtime.showtimeID) , movie->getName(), showtime.getStartTime().getTime()});
                break;
            }
        }
    }

    /// Hiện thị danh sách phim trong ngày
    MovieInDay:
        drawTable(tableMovie);
        wcout<<L"\033[92mNhập 0: Quay lại\n";
        wcout<<L"\033[92m════════[Chọn phim]==> ";
        wcin>>choice;
        wcout<<L"\033[0m";
        if(!choice)
            goto Date;
        
        //Lấy showtimeID
        int showtimeID = -1;
        for(int i=1; i<tableMovie.size(); i++){
            if(tableMovie[i][0] == (L"[" + to_wstring(choice)  + L"]") ){

                showtimeID = stoi(tableMovie[i][1]);
                
                break;
            }
        }

        if (showtimeID == -1) {
            goto MovieInDay;
        }

        if (choice <= 0 || choice > movieList.getMovies().size()) {
            wcerr << L"Chọn sai." << endl;
            return;
        }

        auto movie = movieList.getMovies()[choice - 1];
        if (!movie) {
            wcerr << L"Chọn sai." << endl;
            return;
        }

        //Hiện thị tông tin phim
        system("cls");
        drawTable({{L"     THÔNG TIN PHIM ĐÃ CHỌN   "}});
        movie->displayInfo();
        auto &showtimes = movie->showtimes;


        // Chọn loại vé
        TicketList ticketList;

        choiceTicket:
        ticketList.displayTickets();
        wcout << GREEN << L"══════[ Chọn loại vé ]==> ";
        int ticketID;
        wcin >> ticketID;
        if (ticketID <= 0 || ticketID > ticketList.getTickets().size()) {
            wcerr << L"Chọn sai." << endl;
            goto choiceTicket;
        }

        wcout << GREEN << L"══════[ Nhập số lượng ghế ]==> ";
        int numChairs;
        wcin >> numChairs;

        system("cls");
        //Hiển thị thông tin loại vé và số lượng ghế
        for(auto& ticket: ticketList.getTickets()){
            if(ticket.getTicketID() == ticketID){
                drawTable({{L"     THÔNG TIN VÉ ĐÃ CHỌN   "}});
                drawTable({{L"Loại vé", L"Giá vé", L"Số lượng ghế", L"Tổng tiền vé"},
                           {ticket.getTypeTicket(), to_wstring(ticket.getPrice()), to_wstring(numChairs), to_wstring(ticket.getPrice() * numChairs)}
                    });
                break;
            }
        }

        
        wcout<<GREEN<<L"═══[ Nhấn Enter để chọn ghế hoặc 0 để quay lại ... ]==> ";
        wcin.ignore();
        wcin.get();
        if(wcin.get() == '0')
            goto choiceTicket;



        //Chọn ghế
        choiceChair:
        bool foundShowtime = false;
        Showtime *showtimeCurrent;

        for (auto &showtime : showtimes) {
            if (showtime.showtimeID == showtimeID) {
                showtime.displayChairs(ticketID);
                showtimeCurrent = &showtime;
                foundShowtime = true;
                break;
            }
        }

        if(foundShowtime){
            
            red(L"Nhập 0: quay lại\n");
            wcout << GREEN << L"══════[ Chọn ghế ]══════\n";

            vector<wstring> chairNames;
            for (int i = 0; i < numChairs; ++i) {
                wstring chairName;
                wcout<<GREEN<<L"══╬═══[Nhập tên ghế thứ " << i + 1 << L"]==> ";
                wcin >> chairName;
                if(chairName == L"0")
                    goto choiceTicket;
                

                wregex pattern(L"^[A-Z]\\d{1,2}$"); // Định dạng tên ghế
                if (!regex_match(chairName, pattern)) {
                    red(L"Tên ghế không hợp lệ. Vui lòng nhập lại.\n");
                    --i;
                    continue;
                }

                if(find(chairNames.begin(), chairNames.end(), chairName) != chairNames.end()){
                    red(L"Ghế đã được chọn trước đó. Vui lòng chọn ghế khác.\n");
                    --i;
                    continue;
                }

                if(showtimeCurrent->checkChairExist(showtimeID, chairName)){
                    red(L"Ghế không tồn tại hoặc đã được đặt. Vui lòng chọn ghế khác.\n");
                    --i;
                    continue;
                }
                
                chairNames.push_back(chairName);
            }
            
            // Đặt vé
            showtimeCurrent->bookTickets(ticketID, chairNames, 2);
            showtimeCurrent->displayChairs(ticketID);   
            
            //Xử lý yes no
            wcout<<GREEN<<L"══════[Xác nhận đặt vé]══════\n";
            wcout<<GREEN<<L"══════[Nhập Yes hoặc No để tiếp tục ... Y/N (y/n)]==>";
            wchar_t c;
            wcin>>c;
            c = towlower(c);
            if(c == 'y'){
                showtimeCurrent->bookTickets(ticketID, chairNames, 1);
            }
            else{
                showtimeCurrent->bookTickets(ticketID, chairNames, 0);
                goto choiceChair;
            }


            // Lưu thông tin vé vào file
            showtimeCurrent->saveChairbooked(ticketID, chairNames);

        }
    
        showtimeCurrent->displayChairs(ticketID);

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