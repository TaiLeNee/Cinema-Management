#include "../Header/Menu.h"



using namespace std;

// wstring YELLOW = L"\033[93m";


void managementMenu(ListOfEmployee &employeeList, MovieList &movieList, CustomerList &customerList, RoomList &roomList){
    int choice;
    do{
    vector<vector<wstring>> table;
    table.push_back({L"   Menu Quản lý hệ thống   "});
    table.push_back({L"1. Quản lý phòng chiếu"});
    table.push_back({L"2. Quản lý phim"});
    table.push_back({L"3. Quản lý khung giờ"});
    table.push_back({L"4. Quản lý nhân viên"});
    table.push_back({L"5. Quản lý khách hàng"});
    table.push_back({L"0. Đăng xuất/Thoát"});
    drawTable(table);
    wcout << L"\033[92m════════[Lựa chọn của bạn]══> ";
    wcin >> choice;
    wcout<<L"\033[0m";
    wcin.ignore();
    system("cls");
        switch (choice) {
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
                case 0:
                    int choice1;
                    vector<vector<wstring>> table1;
                    table1.push_back({L"1. Đăng xuất"});
                    table1.push_back({L"2. Thoát"});
                    table1.push_back({L"0. Quay lại"});
                    drawTable(table1);
                    wcout << L"\033[92m[Lựa chọn của bạn:   ] ";
                    gotoXY(19, 7);
                    wcin >> choice1;
                    wcout<<L"\033[0m";
                    wcin.ignore();
                    system("cls");
                    switch (choice1) {
                        case 1:
                            loginMenu(employeeList, movieList, customerList, roomList);
                            break;
                        case 2:
                            break;
                        case 0:
                            managementMenu(employeeList, movieList, customerList, roomList);
                            break;
                default:
                    wcout << L"\033[92m[Lựa chọn không hợp lệ, vui lòng thử lại.\033[0m" << endl;
            }
        }
    }while (choice != 0);
}

void employeeMenu(ListOfEmployee &employeeList){
    int choice;
    do{
    vector<vector<wstring>> table;
    table.push_back({L"    Menu Quản lý Nhân viên "});
    table.push_back({L"1. Hiện danh sách nhân viên"});
    table.push_back({L"2. Thêm nhân viên"});
    table.push_back({L"3. Xóa nhân viên"});
    table.push_back({L"4. Lưu danh sách vào employee.csv"});
    table.push_back({L"5. Tải danh sách từ employee.csv"});
    table.push_back({L"0. Thoát"});
    drawTable(table);
    wcout << L"\033[92m════════[Lựa chọn của bạn]══> ";
    wcin >> choice;
    wcout<<L"\033[0m";
    system("cls");
    wcin.ignore();

    switch (choice) {
            case 1: {
                employeeList.showEmployeeList();
                break;
            }
            case 2: {
                employeeList.addEmployee();
                system("cls");
                wcout << L"\033[92m[Đã thêm nhân viên mới.] \033[0m" << endl;
                break;
            }
            case 3: 
                int id;
                employeeList.showEmployeeList();
                wcout << L"\033[92mNhập ID của nhân viên cần xóa: \033[0m";
                wcin >> id;
                system("cls");
                employeeList.deleteEmployee(id);
                break;
            case 4:
                employeeList.showEmployeeList();
                wcout << L"\033[92mNhập ID của nhân viên cần chỉnh sửa: \033[0m";
                wcin >> id;
                wcin.ignore();
                system("cls");
                if (id == 0){
                    wcout << L"\033[92m[Không thể chỉnh sửa tài khoản OWNER]\033[0m" << endl;
                    break;
                }
                system("cls");
                employeeList.showEmployeeInfo(id);
                employeeList.editEmployeeInfo(id);
                system("cls");
                wcout << L"\033[92m[Đã chỉnh sửa thông tin nhân viên.] \033[0m" << endl;
                break;
            case 5:
                employeeList.saveEmployee("../DATA/employee.csv");
                break;
            case 0:
                break;
            default:
                wcout << L"\033[92m[Lựa chọn không hợp lệ, vui lòng thử lại.\033[0m" << endl;
        }
    }while (choice != 0);
}

void movieMenu(MovieList &movieList){
    auto &movies = movieList.getMovies();
    int choice;
    do{
    vector<vector<wstring>> table;
    table.push_back({L"    Menu Quản lý Phim "});
    table.push_back({L"1. Hiện danh sách phim"});
    table.push_back({L"2. Thêm phim"});
    table.push_back({L"3. Xóa phim"});
    table.push_back({L"4. Đổi thông tin phim"});
    table.push_back({L"5. Lưu danh sách vào hệ thống"});
    table.push_back({L"0. Quay lại"});
    drawTable(table);
    wcout << L"\033[92m[Lựa chọn của bạn]  ";
    wcin >> choice;
    wcout << L"\033[0m";
    wcin.ignore();
    system("cls");
        switch (choice) {
            case 1:
                movieList.displayMovies();
                break;
            case 2: {
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
                wcout << L"\033[92m[Lựa chọn của bạn]  ";
                wcin >> choice;
                wcin.ignore();

                switch (choice) {
                    case 1: {
                        typeMovie = L"Tình cảm";
                        Movie* lmovie = new LoveMovie();
                        lmovie->inputMovieInfo();
                        movies.push_back(lmovie);
                        break;
                    }
                    case 2: {
                        typeMovie = L"Hoạt hình";
                        Movie* amovie = new AnimatedMovie();
                        amovie->inputMovieInfo();
                        movies.push_back(amovie);
                        break;
                    }
                    case 3: {
                        typeMovie = L"Hành động";
                        Movie* amovie = new ActionMovie();
                        amovie->inputMovieInfo();
                        movies.push_back(amovie);
                        break;
                    }
                    case 4: {
                        typeMovie = L"Kinh dị";
                        Movie* hmovie = new HorrorMovie();
                        hmovie->inputMovieInfo();
                        movies.push_back(hmovie);
                        break;
                    }
                    case 0:
                        system("cls"); 
                        break;
                    default:
                        wcout << L"Invalid choice. Please try again." << endl;
                        break;
                }
                break;
            }
            case 3: {
                int id;
                wcout << L"Nhập ID của phim cần xóa: ";
                wcin >> id;
                movieList.deleteMovie(id);
                break;
            }
            case 4: {
                int id;
                wcout << L"Nhập ID của phim cần sửa: ";
                wcin >> id;
                movieList.updateMovie(id);
                break;
            }
            case 5:
                movieList.saveToCSV("../DATA/movies.csv");
                break;
            case 0:
                break;
            default:
                wcout << L"Lựa chọn không hợp lệ, vui lòng thử lại." << endl;
        }
    }while (choice != 0);
}

void customerMenu(CustomerList &customerList){
    int choice;
    do{
    vector<vector<wstring>> table;
    table.push_back({L"    Menu Quản lý Khách hàng "});
    table.push_back({L"1. Hiện danh sách khách hàng"});
    table.push_back({L"2. Thêm khách hàng"});
    table.push_back({L"3. Xóa khách hàng"});
    table.push_back({L"4. Đổi thông tin khách hàng"});
    table.push_back({L"5. Lưu danh sách vào hệ thống"});
    table.push_back({L"0. Quay lại"});
    drawTable(table);
    wcout << L"\033[92m[Lựa chọn của bạn]  ";
    wcin >> choice;
    wcout << L"\033[0m";
    wcin.ignore();
    system("cls");
        switch (choice) {
            case 1:
                customerList.displayCustomers();
                break;
            case 2: {
                wstring name, phoneNumber;
                int point;
                vector<vector<wstring>> table;
                table.push_back({L"           Thêm khách hàng mới              "});
                table.push_back({L"Nhập tên khách hàng: "});
                table.push_back({L"Nhập số điện thoại: "});
                table.push_back({L"Nhập số điểm: "});
                drawTable(table);

                gotoXY(22,3);
                getline(wcin, name);
                
                gotoXY(21,5);
                wcin >> phoneNumber;

                gotoXY(15,7);
                wcin >> point;
                customerList.addCustomer(name, phoneNumber, point);
                system("cls");
                wcout << L"Đã thêm khách hàng mới." << endl;
                break;
            }
            case 3: {
                int id;
                wcout << L"Nhập ID của khách hàng cần xóa: ";
                wcin >> id;
                customerList.deleteCustomer(id);
                break;
            }
            case 4: {
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


void manageMovie(MovieList &movieList){

    system("cls");
    vector<vector<wstring>> table;
    table.push_back({L"        QUẢN LÝ PHIM            "});
    table.push_back({L"        1. Danh sách tất cả các phim hiện tại            "});
    table.push_back({L"        2. Danh sách phim theo thể loại            "});   
    table.push_back({L"        3. Danh sách phim theo quốc gia            "});
    table.push_back({L"        4. Danh sách phim theo độ tuổi            "});

}


void mainMenu(ListOfEmployee &employeeList, MovieList &movieList, CustomerList &customerList, RoomList &roomList, int typeEmployee){
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

    if(typeEmployee <= 1)
        table.push_back({L"        2. Quản lý hệ thống       "});
    

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
            if(typeEmployee <= 1)
                managementMenu(employeeList, movieList, customerList, roomList);
            break;
        default:
            break;
        }
    }

}