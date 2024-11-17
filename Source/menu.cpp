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
            roomMenu(roomList);
            break;
        case 2:
            manageMovie(movieList);
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
            red(L"Nhập 0 để quay lại.\n");
            checkInput(L"ID nhân viên cần tương tác:", id);
            if (id == 0)
            {
                system("cls");
                break;
            }
            employeeList.interactWithEmployee(id);
            break;
        }
        case 3:
        {
            employeeList.addEmployee();
            break;
        }
        case 4:
        {
            wcout << L"\033[92mNhập tên nhân viên cần xóa: \033[0m";
            getline(wcin, name);
            employeeList.findEmployee(name);
            red(L"Nhập 0: Quay lại \n");
            checkInput(L"ID nhân viên cần tương tác:", id);
            if (id == 0){
                system("cls");
                break;
            }
            employeeList.deleteEmployee(id);
            break;
        }
        case 5:
        {
            wcout << L"\033[92mNhập tên nhân viên cần chỉnh sửa: \033[0m";
            getline(wcin, name);
            employeeList.findEmployee(name);
            checkInput(L"ID nhân viên cần tương tác:", id);
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





void statisticMenu(MovieList &movieList, RoomList &roomList, CustomerList &customerList, ListOfEmployee &employeeList, BookedList &bookedList)
{

    int choice;
    do
    {
        vector<vector<wstring>> table;
        system("cls");
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
            statisticBooked(movieList, roomList, bookedList);
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
    int cntCLS = 0;
    while (choice != 0)
    {   
        if(cntCLS >= 1)
            system("cls");
        cntCLS++;
        
        wcout << L"\n\n";

        
        wcout << L"\033[92m    █████╗ ██╗   ██╗ █████╗ ███╗   ██╗ ██████╗███████╗██████╗     ███████╗████████╗ █████╗ ██████╗ \n"
              << L"\033[92m   ██╔══██╗██║   ██║██╔══██╗████╗  ██║██╔════╝██╔════╝██╔══██╗    ██╔════╝╚══██╔══╝██╔══██╗██╔══██╗\n"
              << L"\033[92m   ███████║██║   ██║███████║██╔██╗ ██║██║     █████╗  ██████╔╝    ███████╗   ██║   ███████║██████╔╝\n"
              << L"\033[92m   ██╔══██║╚██╗ ██╔╝██╔══██║██║╚██╗██║██║     ██╔══╝  ██╔══██╗    ╚════██║   ██║   ██╔══██║██╔══██╗\n"
              << L"\033[92m   ██║  ██║ ╚████╔╝ ██║  ██║██║ ╚████║╚██████╗███████╗██║  ██║    ███████║   ██║   ██║  ██║██║  ██║\n"
              << L"\033[92m   ╚═╝  ╚═╝  ╚═══╝  ╚═╝  ╚═╝╚═╝  ╚═══╝ ╚═════╝╚══════╝╚═╝  ╚═╝    ╚══════╝   ╚═╝   ╚═╝  ╚═╝╚═╝  ╚═╝\n";
                                                                                        
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
            SellTicketInWeek(movieList, roomList);
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