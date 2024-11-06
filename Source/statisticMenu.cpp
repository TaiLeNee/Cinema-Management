#include "../Header/Menu.h"
// #include "ExportToXLSX.cpp"


struct BookingData {
    int totalChairBooked;
    long long totalRevenue;
};

bool fileExists(const string& filename) {
    struct stat buffer;
    return (stat(filename.c_str(), &buffer) == 0);
}



void exportPDF(const vector<vector<wstring>>& table) {
    //lấy thời gian hiện tại
    time_t now = time(0);
    tm *ltm = localtime(&now);
     // Định dạng thời gian thành chuỗi
     string filename = "../OUTPUT/ThongKeDoanhThu.csv";
    //                        to_string(1900 + ltm->tm_year) + "_" +
    //                        to_string(1 + ltm->tm_mon) + "_" +
    //                        to_string(ltm->tm_mday) + "_" +
    //                        to_string(ltm->tm_hour) + "_" +
    //                        to_string(ltm->tm_min) + "_" +
    //                        to_string(ltm->tm_sec) + ".csv";

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
    if(fileExists("exportPDF.exe")){
        if(!system(string(command.begin(), command.end()).c_str()))
            green(L"Xuất file thành công\n");
        else
            red(L"Không thể xuất file\n");
    }
    else{
        red(L"Không tìm thấy file exportPDF.exe\n");
    }

}



void statisticRevenue(MovieList &movieList, ListOfEmployee &employeeList, BookedList &bookedList){

menuStatistic:
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
        long long total = 0;
        //Lấy than giờ hiện tại
        time_t now = time(0);
        tm *ltm = localtime(&now);
        // int day = ltm->tm_mday;
        int month = 1 + ltm->tm_mon;
        Datetime date = drawCalendar(month, 2024, 1);
        if(date.getDay() == L"0"){
            system("cls");
            break;
        }

        bookedList.loadChairbookedFromCSV("../DATA/chairbooked.csv");

        //Lấy thông tin vé đẫ bán, tên phim, số lượng vé, doanh thu
        vector<vector<wstring>> tableBooked;
        tableBooked.push_back({L"ID", L"Tên phim", L"Ngày bán vé", L"Số lượng vé", L"Doanh thu"});
       
      // Bản đồ để lưu trữ dữ liệu đặt vé theo phim và tháng
        unordered_map<int, unordered_map<wstring, BookingData>> bookingDataMap;

        // Điền dữ liệu vào bản đồ
        for (auto &booked : bookedList.getBooked()) {
            int showtimeID = booked.getShowtimeID();
            wstring day = booked.getDate();
            int chairsBooked = booked.getChairNames().size();
            long long revenue = stoll(booked.getTotalMoney());

            for (auto &movie : movieList.getMovies()) {
                for (auto &showtime : movie->getShowtimes()) {
                    if (showtime.showtimeID == showtimeID) {
                        int movieID = movie->getId();
                        bookingDataMap[movieID][day].totalChairBooked += chairsBooked;
                        bookingDataMap[movieID][day].totalRevenue += revenue;
                        break;
                    }
                }
            }
        }

        // Duyệt qua các phim và sử dụng bản đồ để lấy dữ liệu đặt vé
        for (auto &movie : movieList.getMovies()) {
            int movieID = movie->getId();
            wstring day = date.getDate();

            if (bookingDataMap.find(movieID) != bookingDataMap.end() &&
                bookingDataMap[movieID].find(day) != bookingDataMap[movieID].end()) {
                
                BookingData &data = bookingDataMap[movieID][day];
                tableBooked.push_back({to_wstring(movieID),movie->getName(), date.getDate(), to_wstring(data.totalChairBooked), to_wstring(data.totalRevenue)
                });
                total += data.totalRevenue;
            }
        }
        system("cls");
        tableBooked.push_back({L" ", L" ", L" ", L" ", L" "});
        tableBooked.push_back({L"", L"", L"", L"Tổng doanh thu: ", to_wstring(total)});
        drawTable({{L"       THỐNG KÊ DOANH THU THEO NGÀY " + date.getDate() + L"       "}});
        drawTable(tableBooked);


        //Xuất file Excel
        int choiceExport;
        checkInput(L"Xuất file Excel? 1. Có | 0. Không", choiceExport);
        if(choiceExport){
            tableBooked.insert(tableBooked.begin(), {L"", L"", L"       THỐNG KÊ DOANH THU NGÀY " + date.getDate() + L"       ", L"", L""});
            exportPDF(tableBooked);
        }


        break;
    }
        

    case 2:{
        Position pos; int x, y;
        //Lấy than giờ hiện tại
        long long total = 0;
        time_t now = time(0);
        tm *ltm = localtime(&now);
    getMonth:
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

        bookedList.loadChairbookedFromCSV("../DATA/chairbooked.csv");

        //Lấy thông tin vé đẫ bán, tên phim, số lượng vé, doanh thu
        vector<vector<wstring>> tableBooked;
        tableBooked.push_back({L"ID", L"Tên phim", L"Tháng", L"Số lượng vé", L"Doanh thu"});


      // Bản đồ để lưu trữ dữ liệu đặt vé theo phim và tháng
        unordered_map<int, unordered_map<wstring, BookingData>> bookingDataMap;

        // Điền dữ liệu vào bản đồ
        for (auto &booked : bookedList.getBooked()) {
            int showtimeID = booked.getShowtimeID();
            wstring month = booked.getMonth();
            int chairsBooked = booked.getChairNames().size();
            long long revenue = stoll(booked.getTotalMoney());

            for (auto &movie : movieList.getMovies()) {
                for (auto &showtime : movie->getShowtimes()) {
                    if (showtime.showtimeID == showtimeID) {
                        int movieID = movie->getId();
                        bookingDataMap[movieID][month].totalChairBooked += chairsBooked;
                        bookingDataMap[movieID][month].totalRevenue += revenue;
                        break;
                    }
                }
            }
        }

        // Duyệt qua các phim và sử dụng bản đồ để lấy dữ liệu đặt vé
        for (auto &movie : movieList.getMovies()) {
            int movieID = movie->getId();
            wstring month = date.getMonth();

            if (bookingDataMap.find(movieID) != bookingDataMap.end() &&
                bookingDataMap[movieID].find(month) != bookingDataMap[movieID].end()) {
                
                BookingData &data = bookingDataMap[movieID][month];
                tableBooked.push_back({to_wstring(movieID),movie->getName(), month + L"/" + date.getYear(), to_wstring(data.totalChairBooked), to_wstring(data.totalRevenue)
                });
                total += data.totalRevenue;
            }
        }
        system("cls");
        tableBooked.push_back({L" ", L" ", L" ", L" ", L" "});
        tableBooked.push_back({L"", L"", L"", L"Tổng doanh thu: ", to_wstring(total)});

        drawTable({{L"       THỐNG KÊ DOANH THU THEO THÁNG " + date.getMonth() + L"/" + to_wstring(year) + L"       "}});
        drawTable(tableBooked);

        //Xuất file Excel
        int choiceExport;
        checkInput(L"Xuất file Excel? 1. Có | 0. Không", choiceExport);
        if(choiceExport){
            tableBooked.insert(tableBooked.begin(), {L"", L"",L"       THỐNG KÊ DOANH THU THEO THÁNG " + date.getMonth() + L"/" + to_wstring(year) + L"       ",L"",L""});
            exportPDF(tableBooked);
        }


        break;
    }

    case 3:{ // Lấy doanh thu nhân viên
        Position pos; int x, y;
        //Lấy than giờ hiện tại
        
        time_t now = time(0);
        tm *ltm = localtime(&now);
    getMonth2:
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
            goto getMonth2;
        }
        
        gotoXY(0, y+1);
        int year = 1900 + ltm->tm_year;
        Datetime date(L"0", month, to_wstring(year));

        bookedList.loadChairbookedFromCSV("../DATA/chairbooked.csv");
       
        //Lấy thông tin vé đẫ bán, tên phim, số lượng vé, doanh thu
        long long total = 0;
        vector<vector<wstring>> tableBooked;
        tableBooked.push_back({L"ID Nhân viên", L"Họ tên", L"Số lượng vé", L"Doanh thu"});
        unordered_map<int, unordered_map<wstring, BookingData>> bookingDataMap;


        // Điền dữ liệu vào các bản đồ
        for (auto &booked : bookedList.getBooked()) {
            int employeeID = booked.getEmployeeID();
            wstring month = booked.getMonth();
            int chairsBooked = booked.getChairNames().size();
            long long revenue = stoll(booked.getTotalMoney());

            bookingDataMap[employeeID][month].totalChairBooked += chairsBooked;
            bookingDataMap[employeeID][month].totalRevenue += revenue;
        }

        // Duyệt qua các nhân viên và sử dụng các bản đồ để lấy dữ liệu đặt vé
        for (auto &employee : employeeList.getEmployees()) {
            int employeeID = employee.getId();
            wstring month = date.getMonth();

            if (bookingDataMap.find(employeeID) != bookingDataMap.end() &&
                bookingDataMap[employeeID].find(month) != bookingDataMap[employeeID].end()) {
                
                BookingData &data = bookingDataMap[employeeID][month];
                tableBooked.push_back({ 
                    to_wstring(employeeID),
                    employee.getName(),
                    to_wstring(data.totalChairBooked),
                    to_wstring(data.totalRevenue)
                });
                total += data.totalRevenue;
            }
        }
        system("cls");
        tableBooked.push_back({L" ", L" ", L" ", L" "});
        tableBooked.push_back({L" ", L" ", L"Tổng doanh thu: ", to_wstring(total)});

        drawTable({{L"       THỐNG KÊ DOANH THU NHÂN VIÊN THÁNG " + date.getMonth() + L"/" + to_wstring(year) + L"       "}});
        drawTable(tableBooked);

        int choiceExport;
        checkInput(L"Xuất file Excel? 1. Có | 0. Không", choiceExport);
        if(choiceExport){
            tableBooked.insert(tableBooked.begin(), {L"", L"",L"       THỐNG KÊ DOANH THU NHÂN VIÊN THÁNG " + date.getMonth() + L"/" + to_wstring(year) + L"       ",L""});
            exportPDF(tableBooked);
        }
        break;     
    }

    case 0:
        return;
    default:
        system("cls");
        red(L"Lựa chọn không hợp lệ, vui lòng chọn lại.\n");
    }
    goto menuStatistic;
}

