#include "../Header/EmployeeList.h"
#include "../Header/drawTable.h"
#include "../Header/gotoXY.h"
#include <fcntl.h>
#include <io.h>

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
            case 3: {
                int id;
                wcout << L"\033[92m[Nhập ID của nhân viên cần xóa:   ] \033[0m";
                gotoXY(32, 0);
                wcin >> id;
                employeeList.deleteEmployee(id);
                break;
            }
            case 4:
                employeeList.saveEmployee("../DATA/employee.csv");
                break;
            case 5:
                int id;
                wcout << L"\033[92m[Nhập ID của nhân viên cần chỉnh sửa:   ] \033[0m";
                gotoXY(38, 0);
                wcin >> id;
                wcin.ignore();
                employeeList.editEmployeeInfo(id);
                break;
            case 0:
                wcout << L"\033[92m[HẸN GẶP LẠI]\033[0m" << endl;
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
    do{
        // system("cls");
        table.push_back({L"         Đăng nhập "});
        table.push_back({L"Username:                  "});
        table.push_back({L"Password:                  "});
        drawTable(table);
        gotoXY(13, 3);
        getline(wcin, userName);
        gotoXY(13, 5);
        getline(wcin, passWord);
        loggedInUser = employeeList.signIn(userName, passWord);
        if (!loggedInUser) {
            wcout << L"Đăng nhập thất bại. Vui lòng kiểm tra lại thông tin đăng nhập." << endl;
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
