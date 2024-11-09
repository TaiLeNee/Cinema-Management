//thống kê số lượng vé

#include "../Header/menu.h"


struct BookingDataSold {
    int totalChairBooked;
    int numChairInitial;
};


bool fileExists2(const string& filename) {
    struct stat buffer;
    return (stat(filename.c_str(), &buffer) == 0);
}



void exportXLSX(const vector<vector<wstring>>& table) {
    //lấy thời gian hiện tại
    time_t now = time(0);
    tm *ltm = localtime(&now);
     // Định dạng thời gian thành chuỗi
    string filename = "../OUTPUT/ThongKeVe.csv" +
                           to_string(1900 + ltm->tm_year) + "_" +
                           to_string(1 + ltm->tm_mon) + "_" +
                           to_string(ltm->tm_mday) + "_" +
                           to_string(ltm->tm_hour) + "_" +
                           to_string(ltm->tm_min) + "_" +
                           to_string(ltm->tm_sec) + ".csv";

    wofstream file(filename);
    file.imbue(locale(locale(), new codecvt_utf8<wchar_t>));

    if (!file.is_open()) {
        wcout << L"Không thể mở file " << filename.c_str() << endl;
        return;
    }

    for (auto row : table) {
        for (auto cell : row) {
            file << cell << L",";
        }
        file << L"\n";
    }

    file.close();

    // Mở file bằng ứng dụng mặc định
    string command = "exportPDF.exe " + string(filename.begin(), filename.end());

    //kiểm tra xem có tồn tại file không
    if(fileExists2("exportPDF.exe")){
        if(system(string(command.begin(), command.end()).c_str()))
            green(L"Xuất file thành công\n");
        else
            red(L"Không thể xuất file\n");
    }
    else{
        red(L"Không tìm thấy file exportPDF.exe\n");
    }

}


void statisticBooked(MovieList &movieList, RoomList &roomList, BookedList &bookedList){

   

    bookedList.loadChairbookedFromCSV("../DATA/chairbooked.csv");
    drawTable({{L"       THỐNG KÊ SỐ LƯỢNG VÉ        "},
            {L"1. Thống kê theo phim"},
            {L"2. Thống kê theo phòng chiếu"},
            {L"3. Thống kê theo ngày"},
            {L"0. Quay lại"}});


    int choice;
    checkInput(L"Nhập lựa chọn ", choice);

    switch (choice){

        case 1:{
             //Lấy than giờ hiện tại
            long long total = 0;
            time_t now = time(0);
            tm *ltm = localtime(&now);
        getMonth:
            Position pos; int x, y;
            system("cls");
            red(L"Nhập 0: quay lại\n");
            drawTable({{L"Nhập tháng: ", L"          "}});
            pos = getXY();
            y = pos.Y;
            x = pos.X;

            gotoXY(17, y-2);
            wstring month; wcin>>month;
            int monthINT = stoi(month);
            //Kiểm tra tháng
            if(!monthINT){
                system("cls");
                break;
            }
            if(monthINT < 1 || monthINT > 12){
                red(L"══[Tháng không hợp lệ, Vui lòng nhập lại]══\n");
                goto getMonth;
            }
            
            gotoXY(0, y+1);
            int year = 1900 + ltm->tm_year;
            Datetime date(L"0", month, to_wstring(year));

            //Lấy thông tin vé đẫ bán, tên phim, số lượng vé, doanh thu
            vector<vector<wstring>> tableBooked;
            tableBooked.push_back({L"ID", L"Tên phim", L"Tháng", L"Số lượng vé đã bán", L"Số lượng vé ban đầu"});
            // Bản đồ để lưu trữ dữ liệu đặt vé theo phim và tháng
            unordered_map<int, unordered_map<wstring, BookingDataSold>> bookingDataMap;

            // Điền dữ liệu vào bản đồ
            // wstring month = date.getMonth();
            int checkBooked = 0;
            int totalChairInitial = 0;
            int totalChair = 0;
            int numChairInitial = 0;
            for (auto &booked : bookedList.getBooked()) {
                int showtimeID = booked.getShowtimeID();
                wstring monthB = booked.getMonth();
                int chairsBooked = booked.getChairNames().size();

                for (auto &movie : movieList.getMovies()) {
                    for (auto &showtime : movie->getShowtimes()) {
                        int movieID = movie->getId();
                        if (showtime.showtimeID == showtimeID) {
                            bookingDataMap[movieID][monthB].totalChairBooked += chairsBooked;
                            break;
                        }
                    }   
                }
            }
            for(auto &movie: movieList.getMovies()){
                for(auto &showtime: movie->getShowtimes()){
                    if(showtime.getStartTime().getMonth() == month){
                        bookingDataMap[showtime.movieID][month].numChairInitial += showtime.getNumChair();
                        // wcout << showtime.movieID << " " << month << " " << showtime.getNumChair() << endl;
                    }
                }
            }
            

            //thống kê số lượng vé đã bán, số lượng vé ban đầu
            
            for (auto &movie : movieList.getMovies()) {
                int movieID = movie->getId();
                if (bookingDataMap.find(movieID) != bookingDataMap.end() &&
                    bookingDataMap[movieID].find(month) != bookingDataMap[movieID].end()) {
                    BookingDataSold &data = bookingDataMap[movieID][month];
                    tableBooked.push_back({ 
                        to_wstring(movieID),
                        movie->getName(),
                        month,
                        to_wstring(data.totalChairBooked),
                        to_wstring(data.numChairInitial)
                    });
                    totalChair += data.totalChairBooked;
                    totalChairInitial += data.numChairInitial;
                }
            }
            
            
            tableBooked.push_back({L" ", L" ", L" ", L" ", L" "});
            tableBooked.push_back({L"", L"", L"Tổng: ", to_wstring(totalChair), to_wstring(totalChairInitial)}); 

        displayStatisticBooked:
            system("cls");
            drawTable({{L"       THỐNG KÊ  SỐ LƯỢNG VÉ        "}});
            drawTable(tableBooked);
            green(L"=================================================\n");
            drawTable({{L"1. Sắp xếp theo số lượng vé đã bán"},
                        {L"2. Sắp xếp theo số lượng vé ban đầu"},
                        {L"3. Xuất file Excel"},
                        {L"0. Quay lại"}});
            int choiceSort;
            checkInput(L"Nhập lựa chọn ", choiceSort);
            switch (choiceSort)
            {
                case 1:{
    
                    drawTable({{L"SẮP XẾP THEO SỐ LƯỢNG VÉ ĐÃ BÁN"},
                        {L"1. Tăng dần"},
                        {L"2. Giảm dần"},
                        {L"0. Quay lại"}
                    });
                    int choiceSortType;
                    checkInput(L"Nhập lựa chọn ", choiceSortType);
                    switch (choiceSortType)
                    {
                        case 1:{
                            sort(tableBooked.begin() + 1, tableBooked.end()-2, [](vector<wstring> &a, vector<wstring> &b) {
                                return stoi(a[3]) < stoi(b[3]);
                            });
                            goto displayStatisticBooked;
                            break;
                        }
                        case 2:{
                            sort(tableBooked.begin() + 1, tableBooked.end()-2, [](vector<wstring> &a, vector<wstring> &b) {
                                return stoi(a[3]) > stoi(b[3]);
                            });
                            goto displayStatisticBooked;
                            break;
                        }
                        case 0:
                            return;
                    }
                    
                }
                case 2:{
                  
                    drawTable({{L"SẮP XẾP THEO SỐ LƯỢNG VÉ BAN ĐẦU"},
                        {L"1. Tăng dần"},
                        {L"2. Giảm dần"},
                        {L"0. Quay lại"}
                    });
                    int choiceSortType;
                    checkInput(L"Nhập lựa chọn ", choiceSortType);
                    switch (choiceSortType)
                    {
                        case 1:{
                            sort(tableBooked.begin() + 1, tableBooked.end()-2, [](vector<wstring> &a, vector<wstring> &b) {
                                return stoi(a[4]) < stoi(b[4]);
                            });
                            goto displayStatisticBooked;
                            break;
                        }
                        case 2:{
                            sort(tableBooked.begin() + 1, tableBooked.end()-2, [](vector<wstring> &a, vector<wstring> &b) {
                                return stoi(a[4]) > stoi(b[4]);
                            });
                            goto displayStatisticBooked;
                            break;
                        }
                        case 0:
                            return;
                    }
                }
                case 3:{
                    
                    exportXLSX(tableBooked);
                    break;
                }
            }
        }
        case 0:
            return;
    }
        
}