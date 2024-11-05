#include "../Header/Menu.h"

void statisticRevenue(MovieList &movieList, ListOfEmployee &employeeList, BookedList &bookedList){
    drawTable({{L"       THỐNG KÊ DOANH THU        "},
            {L"1. Doanh thu theo ngày"},
            {L"2. Doanh thu theo tháng"},
            {L"3. Doanh thu theo nhân viên"},
            {L"0. Quay lại"}});

    int choice; 
    checkInput(L"Lựa chọn của bạn", choice);
    system("cls");
    switch (choice)
    {
    case 1:{
        //Lấy than giờ hiện tại
        time_t now = time(0);
        tm *ltm = localtime(&now);
        // int day = ltm->tm_mday;
        int month = 1 + ltm->tm_mon;
        Datetime date = drawCalendar(month, 2024, 1);

        bookedList.loadChairbookedFromCSV("../DATA/chairbooked.csv");

        //Lấy thông tin vé đẫ bán, tên phim, số lượng vé, doanh thu
        vector<vector<wstring>> tableBooked;
        tableBooked.push_back({L"ID", L"Tên phim", L"Ngày bán vé", L"Số lượng vé", L"Doanh thu"});
        for(auto &movie: movieList.getMovies()){
            int totalChairBooked = 0;
            long long totalRevenue = 0;
            for(auto &showtime: movie->getShowtimes()){
                for(auto &booked: bookedList.getBooked()){
                    if(date.getDate() == booked.getDate() && 
                    booked.getShowtimeID() == showtime.showtimeID){
                        totalChairBooked += booked.getChairNames().size();
                        totalRevenue += stoll(booked.getTotalMoney());
                    }
                }
            }
            tableBooked.push_back({to_wstring(movie->getId()), movie->getName(), date.getDate(), to_wstring(totalChairBooked), to_wstring(totalRevenue)});
        }
        system("cls");
        drawTable(tableBooked);

        break;
    }
        

    case 2:
        break;

    default:
        break;
    
    }
}