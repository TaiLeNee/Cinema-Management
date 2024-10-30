#include "../Header/EmployeeList.h"
#include "../Header/drawTable.h"
#include "../Header/gotoXY.h"
#include <fcntl.h>
#include <io.h>
void loginMenu(ListOfEmployee &employeeList);
void adminMenu(ListOfEmployee &employeeList){
    int choice;
    do{
    vector<vector<wstring>> table;
    table.push_back({L"    Menu Quản lý Nhân viên "});
    table.push_back({L"1. Hiện danh sách nhân viên"});
    table.push_back({L"2. Thêm nhân viên"});
    table.push_back({L"3. Xóa nhân viên"});
    table.push_back({L"4. Lưu danh sách vào hệ thống"});
    table.push_back({L"5. Đổi thông tin nhân viên"});
    table.push_back({L"0. Đăng xuất hoặc Thoát"});
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
                employeeList.saveEmployee("../DATA/employee.csv");
                break;
            case 5:
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
            case 0:
                int choice1;
                drawTable({
                    {L"1.Đăng xuất"},
                    {L"2.Thoát"}
                });
                wcout << L"\033[92m════════[Lựa chọn của bạn]══> ";
                wcin >> choice1;
                wcout<<L"\033[0m";
                wcin.ignore();
                switch (choice1){
                    case 1:
                        system("cls");
                        loginMenu(employeeList);
                        break;
                    case 2:
                        wcout << L"\033[92m[Đã thoát khỏi chương trình.] \033[0m" << endl;
                        exit(0);
                        break;
                    default:
                        wcout << L"\033[92m[Lựa chọn không hợp lệ, vui lòng thử lại.] \033[0m" << endl;
                    }
                break;
            default:
                wcout << L"\033[92m[Lựa chọn không hợp lệ, vui lòng thử lại.\033[0m" << endl;
        }
    }while (choice != 0);
}

void loginMenu(ListOfEmployee &employeeList){
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
            wcout << L"\nĐăng nhập thất bại. Vui lòng kiểm tra lại thông tin đăng nhập." << endl;
        }
        else{
            system("cls");
            wcout << L"\nĐăng nhập thành công!" << endl;
            break;
        }
    }while(!loggedInUser);

    wstring name;
    name = loggedInUser->getName();
    if (loggedInUser->getLevel() == 0) {
        wcout << L"Xin chào OWNER "<< name << endl;
        adminMenu(employeeList);
    }
    else if (loggedInUser->getLevel() == 1) {
        wcout << L"Xin chào ADMIN " << name << endl;
        adminMenu(employeeList);
    } 
    else {
        wcout << L"Xin chào Nhân Viên " << name << endl;
    }
}

int main(){
    system("cls");
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);


    ListOfEmployee employeeList;
    employeeList.loadEmployees("../DATA/employee.csv");

    loginMenu(employeeList);
    
    return 0;
}
