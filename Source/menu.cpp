#include "../Header/Menu.h"

using namespace std;

// wstring YELLOW = L"\033[93m";

void managementMenu(ListOfEmployee &employeeList, MovieList &movieList, CustomerList &customerList, RoomList &roomList, BookedList &bookedList)
{
    int choice;
    do
    {
        vector<vector<wstring>> table;
        table.push_back({L"   Menu Quản lý hệ thống   "});
        table.push_back({L"1. Quản lý phòng chiếu"});
        table.push_back({L"2. Quản lý phim"});
        table.push_back({L"3. Quản lý khung giờ"});
        table.push_back({L"4. Quản lý nhân viên"});
        table.push_back({L"5. Quản lý khách hàng"});
        table.push_back({L"6. Thống kê"});
        table.push_back({L"0. Quay lại"});
        drawTable(table);
        checkInput(L"Lựa chọn của bạn", choice);
        wcin.ignore();
        system("cls");
        switch (choice)
        {
        case 1:
            // roomMenu();
            break;
        case 2:
            movieMenu(movieList);
            break;
        case 3:
            manageShowtimes(roomList, movieList);
            break;
        case 4:
            employeeMenu(employeeList);
            break;
        case 5:
            customerMenu(customerList);
            break;
        case 6:
            statisticMenu(movieList, roomList, customerList, employeeList, bookedList);
            break;
        case 0:
            break;
        }
    } while (choice != 0);
}

void employeeMenu(ListOfEmployee &employeeList)
{
    int choice, id;
    wstring name;
    do
    {
        wcout << L"\033[0m";
        vector<vector<wstring>> table;
        table.push_back({L"    Menu Quản lý Nhân viên "});
        table.push_back({L"1. Hiện danh sách nhân viên"});
        table.push_back({L"2. Tìm nhân viên"});
        table.push_back({L"3. Thêm nhân viên"});
        table.push_back({L"4. Xóa nhân viên"});
        table.push_back({L"5. Đổi thông tin nhân viên"});
        table.push_back({L"6. Lưu danh sách vào hệ thống"});
        table.push_back({L"0. Quay lại"});
        drawTable(table);
        checkInput(L"Lựa chọn của bạn", choice);
        system("cls");
        wcin.ignore();

        switch (choice)
        {
        case 1:
        {
            employeeList.showEmployeeList();

            break;
        }
        case 2:
        {
            wcout << L"\033[92mNhập tên nhân viên cần tìm: \033[0m";
            getline(wcin, name);
            employeeList.findEmployee(name);
            wcout<< L"\033[92mNhập ID nhân viên cần tương tác: \033[0m";
            wcin >> id;
            employeeList.interactWithEmployee(id);
            break;
        }
        case 3:
        {
            employeeList.addEmployee();
            system("cls");
            wcout << L"\033[92m[Đã thêm nhân viên mới.] \033[0m" << endl;
            break;
        }
        case 4:
        {
            wcout << L"\033[92mNhập tên nhân viên cần xóa: \033[0m";
            getline(wcin, name);
            employeeList.findEmployee(name);
            wcout << L"\033[92mNhập ID của nhân viên cần xóa: \033[0m";
            wcin >> id;
            system("cls");
            employeeList.deleteEmployee(id);
            break;
        }
        case 5:
        {
            wcout << L"\033[92mNhập tên nhân viên cần chỉnh sửa: \033[0m";
            getline(wcin, name);
            employeeList.findEmployee(name);
            wcout << L"\033[92mNhập ID của nhân viên cần chỉnh sửa: \033[0m";
            wcin >> id;
            wcin.ignore();
            system("cls");
            if (id == 0)
            {
                wcout << L"\033[92m[Không thể chỉnh sửa tài khoản OWNER]\033[0m" << endl;
                break;
            }
            system("cls");
            employeeList.editEmployeeInfo(id);
            system("cls");
            wcout << L"\033[92m[Đã chỉnh sửa thông tin nhân viên.] \033[0m" << endl;
            break;
        }
        case 6:
            employeeList.saveEmployee("../DATA/employee.csv");
            wcout << L"\033[92m[Đã lưu danh sách nhân viên vào hệ thống.] \033[0m" << endl;
            break;
        case 0:
            break;
        default:
            wcout << L"\033[92m[Lựa chọn không hợp lệ, vui lòng thử lại.\033[0m" << endl;
        }
    } while (choice != 0);
}

void movieMenu(MovieList &movieList)
{
    auto &movies = movieList.getMovies();
    int choice;
    do
    {
        vector<vector<wstring>> table;
        wcout << L"\033[0m";
        table.push_back({L"    Menu Quản lý Phim "});
        table.push_back({L"1. Hiện danh sách phim"});
        table.push_back({L"2. Thêm phim"});
        table.push_back({L"3. Xóa phim"});
        table.push_back({L"4. Đổi thông tin phim"});
        table.push_back({L"5. Lưu danh sách vào hệ thống"});
        table.push_back({L"0. Quay lại"});
        drawTable(table);
        checkInput(L"Lựa chọn của bạn", choice);
        wcin.ignore();
        system("cls");
        switch (choice)
        {
        case 1:
            system("cls");
            movieList.displayMovies();
            break;
        case 2:
        {
            int duration, limitAge, choice;
            wstring name, typeMovie, subtitle, country, description, genre;
            vector<vector<wstring>> table;
            table.push_back({L"  Chọn Thể Loại Phim"});
            table.push_back({L"1. Tình cảm"});
            table.push_back({L"2. Hoạt hình"});
            table.push_back({L"3. Hành động"});
            table.push_back({L"4. Kinh dị"});
            table.push_back({L"0. Quay lại"});
            drawTable(table);
            red(L"LƯU Ý: KHÔNG THỂ THAY ĐỔI SAO KHI CHỌN.\n");
            checkInput(L"Lựa chọn của bạn", choice);
            wcin.ignore();
            wcout << "\033[93m";
            switch (choice)
            {
            case 1:
            {
                typeMovie = L"Tình cảm";
                Movie *lmovie = new LoveMovie();
                lmovie->inputMovieInfo();
                movies.push_back(lmovie);
                break;
            }
            case 2:
            {
                typeMovie = L"Hoạt hình";
                Movie *amovie = new AnimatedMovie();
                amovie->inputMovieInfo();
                movies.push_back(amovie);
                break;
            }
            case 3:
            {
                typeMovie = L"Hành động";
                Movie *amovie = new ActionMovie();
                amovie->inputMovieInfo();
                movies.push_back(amovie);
                break;
            }
            case 4:
            {
                typeMovie = L"Kinh dị";
                Movie *hmovie = new HorrorMovie();
                hmovie->inputMovieInfo();
                movies.push_back(hmovie);
                break;
            }
            case 0:
                system("cls");
                break;
            default:
                red(L"[Lựa chọn không hợp lệ. Vui lòng chọn lại.]\n");
                break;
            }
            wcout << "\033[0m";
            system("cls");
            green(L"Thêm phim thành công.\n");
            break;
        }
        case 3:
        {
            int id;
            movieList.displayMovies();
            yellow(L"Nhập ID của phim cần xóa: ");
            wcin >> id;
            system("cls");
            movieList.deleteMovie(id);
            green(L"Xóa phim thành công.\n");
            break;
        }
        case 4:
        {
            int id;
            movieList.displayMovies();
            yellow(L"Nhập ID của phim cần sửa: ");
            wcin >> id;
            system("cls");
            movieList.updateMovie(id);
            break;
        }
        case 5:
            movieList.saveToCSV("../DATA/movies.csv");
            wcout << L"\033[92m[Đã lưu danh sách phim vào hệ thống.] \033[0m" << endl;
            break;
        case 0:
            break;
        default:
            red(L"Lựa chọn không hợp lệ, vui lòng thử lại.");
            wcout << endl;
        }
    } while (choice != 0);
}

void customerMenu(CustomerList &customerList)
{
    int choice;
    do
    {
        vector<vector<wstring>> table;
        table.push_back({L"    Menu Quản lý Khách hàng "});
        table.push_back({L"1. Hiện danh sách khách hàng"});
        table.push_back({L"2. Thêm khách hàng"});
        table.push_back({L"3. Xóa khách hàng"});
        table.push_back({L"4. Đổi thông tin khách hàng"});
        table.push_back({L"5. Lưu danh sách vào hệ thống"});
        table.push_back({L"0. Quay lại"});
        drawTable(table);
        checkInput(L"Lựa chọn của bạn", choice);
        wcin.ignore();
        system("cls");
        switch (choice)
        {
        case 1:
            customerList.displayCustomers();
            break;
        case 2:
        {
            wstring name, phoneNumber;
            int point;
            vector<vector<wstring>> table;
            table.push_back({L"           Thêm khách hàng mới              "});
            table.push_back({L"Nhập tên khách hàng: "});
            table.push_back({L"Nhập số điện thoại: "});
            table.push_back({L"Nhập số điểm: "});
            drawTable(table);

            gotoXY(22, 3);
            getline(wcin, name);

            gotoXY(21, 5);
            wcin >> phoneNumber;

            gotoXY(15, 7);
            wcin >> point;
            customerList.addCustomer(name, phoneNumber, point);
            system("cls");
            wcout << L"Đã thêm khách hàng mới." << endl;
            break;
        }
        case 3:
        {
            int id;
            wcout << L"Nhập ID của khách hàng cần xóa: ";
            wcin >> id;
            customerList.deleteCustomer(id);
            break;
        }
        case 4:
        {
            int id;
            wcout << L"Nhập ID của khách hàng cần sửa: ";
            wcin >> id;
            Customer updatedCustomer;
            customerList.editCustomer(id);
            break;
        }
        case 5:
            customerList.saveToCSV("../DATA/customers.csv");
            break;
        case 0:
            break;
        default:
            wcout << L"Lựa chọn không hợp lệ, vui lòng thử lại." << endl;
        }
    } while (choice != 0);
}

void manageMovie(MovieList &movieList)
{
    system("cls");
    vector<vector<wstring>> table;
    table.push_back({L"        QUẢN LÝ PHIM            "});
    table.push_back({L"        1. Danh sách tất cả các phim hiện tại            "});
    table.push_back({L"        2. Danh sách phim theo thể loại            "});
    table.push_back({L"        3. Danh sách phim theo quốc gia            "});
    table.push_back({L"        4. Danh sách phim theo độ tuổi            "});
}

void statisticMenu(MovieList &movieList, RoomList &roomList, CustomerList &customerList, ListOfEmployee &employeeList, BookedList &bookedList)
{

    int choice;
    do
    {
        vector<vector<wstring>> table;
        table.push_back({L"    MENU THỐNG KÊ     "});
        table.push_back({L"1. Thống kê doanh thu"});
        table.push_back({L"2. Thống kê số lượng vé "});
        // table.push_back({L"3.  "});
        // table.push_back({L"4. Thống kê số lượng vé "});
        // table.push_back({L"5. Thống kê số lượng vé "});
        // table.push_back({L"6. Thống kê số lượng vé "});
        // table.push_back({L"7. Thống kê số lượng vé "});
        table.push_back({L"0. Quay lại"});
        drawTable(table);
        checkInput(L"Lựa chọn của bạn", choice);
        system("cls");
        switch (choice)
        {
        case 1:
            statisticRevenue(movieList, employeeList, bookedList);
            break;
        case 2:
            // statisticSoldTicket();
            break;
        case 3:
            // statisticBookedTicket();
            break;
        case 4:
            // statisticCanceledTicket();
            break;
        case 5:
            // statisticBookedTicketByMovie();
            break;
        case 6:
            // statisticBookedTicketByDate();
            break;
        case 7:
            // statisticBookedTicketByMonth();
            break;
        case 0:
            break;
        default:
            wcout << L"Lựa chọn không hợp lệ, vui lòng thử lại." << endl;
        }
    } while (choice != 0);
}

void mainMenu(ListOfEmployee &employeeList, MovieList &movieList, CustomerList &customerList, RoomList &roomList, BookedList &bookedList, Employee *loggedin)
{
    int choice = -1;
    while (choice != 0)
    {
        system("cls");
        wcout << L"\n\n";

        wcout << L"\033[92m   ████████╗██╗  ██╗██████╗     ███████╗████████╗ █████╗ ██████╗\n"
              << L"\033[92m   ╚══██╔══╝██║  ██║██╔══██╗    ██╔════╝╚══██╔══╝██╔══██╗██╔══██╗\n"
              << L"\033[92m      ██║   ███████║██║  ██║    ███████╗   ██║   ███████║██████╔╝\n"
              << L"\033[92m      ██║   ██╔══██║██║  ██║    ╚════██║   ██║   ██╔══██║██╔══██╗\n"
              << L"\033[92m      ██║   ██║  ██║██████╔╝    ███████║   ██║   ██║  ██║██║  ██║\n"
              << L"\033[92m      ╚═╝   ╚═╝  ╚═╝╚═════╝     ╚══════╝   ╚═╝   ╚═╝  ╚═╝╚═╝  ╚═╝\n";

        wcout << L"\033[m";

        vector<vector<wstring>> table;
        table.push_back({L"HỆ THỐNG QUẢN LÝ RẠP CHIẾU PHIM            "});
        table.push_back({L"1. Bán vé            "});

        if (loggedin->getId() <= 1)
            table.push_back({L"2. Quản lý hệ thống       "});
        else
            table.push_back({L"2. Đổi mật khẩu       "});
        table.push_back({L"0. Đăng xuất/Thoát            "});

        drawTable(table);
        checkInput(L"Lựa chọn của bạn", choice);
        switch (choice)
        {
        case 1:
            SellTicketInWeek(movieList);
            break;
        case 2:
            system("cls");
            if (loggedin->getId() <= 1)
            {
                system("cls");
                managementMenu(employeeList, movieList, customerList, roomList, bookedList);
            }
            else
            {
                vector<vector<wstring>> table2;
                table2.push_back({L" ĐỔI MẬT KHẨU "});
                table2.push_back({L" Username: " + loggedin->getUserName()});
                table2.push_back({L" Nhập mật khẩu cũ: "});
                table2.push_back({L" Nhập mật khẩu mới:               "});
                table2.push_back({L" Nhập lại mật khẩu mới:"});
                drawTable(table2);
                wstring newPass, oldPass, rePass;
                do
                {
                    oldPass = L"";
                    newPass = L"";
                    gotoXY(21, 3);
                    wcin >> oldPass;
                    gotoXY(22, 5);
                    wcin >> newPass;
                    gotoXY(26, 7);
                    wcin >> rePass;
                    if (oldPass != loggedin->getPassWord())
                    {
                        red(L"\n[Mật khẩu cũ không đúng. Vui lòng nhập lại.]");
                        wcout << L"\nold :" << oldPass << endl;
                        wcout << L"\npass :" << loggedin->getPassWord() << endl;
                        Sleep(2000);
                        system("cls");
                        drawTable(table2);
                    }
                    else if (newPass != rePass)
                    {
                        red(L"\n[Mật khẩu mới không khớp. Vui lòng nhập lại.]");
                        Sleep(2000);
                        system("cls");
                        drawTable(table2);
                    }
                } while (oldPass != loggedin->getPassWord() || newPass != rePass);

                loggedin->setPassWord(newPass);
                employeeList.saveEmployee("../DATA/employee.csv");
                wcout << L"\033[92m\n[Đã đổi mật khẩu thành công.]\033[0m" << endl;
                Sleep(2000);
            }
            break;
        case 0:
            system("cls");
            drawTable({{L"1. Đăng xuất"},
                       {L"2. Thoát chương trình"},
                       {L"0. Quay lại"}});
            int choice1;
            checkInput(L"Lựa chọn của bạn", choice1);
            switch (choice1)
            {
            case 1:
                system("cls");
                loginMenu(employeeList, movieList, customerList, roomList, bookedList);
                break;
            case 2:
                wcout << L"\033[91mĐang đăng xuất khỏi hệ thống...\033[0m" << endl;
                Sleep(2000);
                exit(0);
                break;
            case 0:
                mainMenu(employeeList, movieList, customerList, roomList, bookedList, loggedin);
                break;
            default:
                cout << "Lựa chọn không hợp lệ, vui lòng thử lại." << endl;
            }
        default:
            wcout << L"Lựa chọn không hợp lệ, vui lòng thử lại." << endl;
        }
    }
}