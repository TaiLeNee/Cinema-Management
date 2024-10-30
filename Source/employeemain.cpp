#include "../Header/EmployeeList.h"
#include "../Header/MovieList.h"
#include "../Header/drawTable.h"
#include "../Header/gotoXY.h"
#include <fcntl.h>
#include <io.h>

void loginMenu(ListOfEmployee &employeeList, MovieList &movieList);

void employeeMenu(ListOfEmployee &employeeList);

void movieMenu(MovieList &movieList);

void managementMenu(ListOfEmployee &employeeList, MovieList &movieList);

void managementMenu(ListOfEmployee &employeeList, MovieList &movieList){
    int choice;
    do{
    vector<vector<wstring>> table;
    table.push_back({L"   Menu Quản lý hệ thống   "});
    table.push_back({L"1. Quản lý phòng chiếu"});
    table.push_back({L"2. Quản lý phim"});
    table.push_back({L"3. Quản lý nhân viên"});
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
                    employeeMenu(employeeList);
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
                            loginMenu(employeeList, movieList);
                            break;
                        case 2:
                            break;
                        case 0:
                            managementMenu(employeeList, movieList);
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
    table.push_back({L"4. Đổi thông tin nhân viên"});
    table.push_back({L"5. Lưu danh sách vào hệ thống"});
    table.push_back({L"0. Quay lại"});
    drawTable(table);
    wcout << L"\033[92m════════[Lựa chọn của bạn]══> ";
    wcin >> choice;
    wcout<<L"\033[0m";
    wcin.ignore();
    system("cls");
    switch (choice) {
            case 1: 
                employeeList.showEmployeeList();
                break;
            case 2: 
                employeeList.addEmployee();
                system("cls");
                wcout << L"\033[92m[Đã thêm nhân viên mới.] \033[0m" << endl;
                break;
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
                    default:
                        wcout << L"Invalid choice. Please try again." << endl;
                        break;
                }
                break;
            }
            case 3: {
                int id;
                movieList.displayMovies();
                wcout << L"\033[92mNhập ID của phim cần xóa: \033[0m";
                wcin >> id;
                system("cls");
                movieList.deleteMovie(id);
                wcout << L"\033[92m[Đã xóa phim khỏi hệ thống.] \033[0m" << endl;
                break;
            }
            case 4: {
                int id;
                movieList.displayMovies();
                wcout << L"\033[92mNhập ID của phim cần chỉnh sửa: \033[0m";
                wcin >> id;
                wcin.ignore();
                system("cls");
                movieList.updateMovie(id);
                break;
            }
            case 5:
                movieList.saveToCSV("../DATA/movies.csv");
                system("cls");
                wcout << L"\033[92m[Đã lưu danh sách phim vào hệ thống.] \033[0m" << endl;
                break;
            default:
                break;
        }
    }while (choice != 0);
}

void loginMenu(ListOfEmployee &employeeList , MovieList &movieList){
    vector<vector<wstring>> table;
    wstring userName, passWord;
    Employee *loggedInUser = nullptr;
        table.push_back({L"         Đăng nhập "});
        table.push_back({L"Username:                  "});
        table.push_back({L"Password:                  "});
        drawTable(table);
    do{
        // system("cls");
        gotoXY(13, 3);
        getline(wcin, userName);
        gotoXY(13, 5);
        getline(wcin, passWord);
        loggedInUser = employeeList.signIn(userName, passWord);
        if (!loggedInUser) {
            wcout << L"\n\033[92m[Đăng nhập thất bại. Vui lòng kiểm tra lại thông tin đăng nhập.]\033[0m" << endl;
        }
        else{
            system("cls");
            wcout << L"\n\033[92m[Đăng nhập thành công!]\033[0m" << endl;
            break;
        }
    }while(!loggedInUser);

    wstring name;
    name = loggedInUser->getName();
    if (loggedInUser->getLevel() == 0) {
        wcout << L"\033[92m[Xin chào OWNER "<< name <<"]\033[0m"<< endl;
        managementMenu(employeeList, movieList);
    }
    else if (loggedInUser->getLevel() == 1) {
        wcout << L"\033[92m[Xin chào ADMIN " << name <<"]\033[0m"<< endl;
        managementMenu(employeeList, movieList);
    } 
    else {
        wcout << L"\033[92m[Xin chào Nhân Viên " << name <<"]\033[0m"<< endl;
    }
}



int main(){
    system("cls");
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);


    ListOfEmployee employeeList;
    MovieList movieList;
    employeeList.loadEmployees("../DATA/employee.csv");
    movieList.loadFromCSV("../DATA/movies.csv");
    loginMenu(employeeList, movieList);
    
    return 0;
}
