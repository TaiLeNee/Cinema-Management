#include "../Header/EmployeeList.h"
#include <algorithm>
#include <windows.h>
#include "../Header/gotoXY.h"
int ListOfEmployee::nextID = 1;

void ListOfEmployee::addEmployee() {
    vector<vector<wstring>> table;
    wstring name, phoneNumber, userName, passWord;
    int age, level;
    table.push_back({L"          Nhập Thông Tin Của Nhân Viên Mới         "});
    table.push_back({L"Nhập tên của nhân viên:  "});
    table.push_back({L"Nhập tuổi của nhân viên: "});
    table.push_back({L"Nhập SĐT của nhân viên: "});
    table.push_back({L"Nhập quyền của nhân viên (1. Admin, 2. Nhân viên):  "});
    drawTable(table);

    gotoXY(27, 3);
    getline(wcin, name);

    gotoXY(27, 5);
    wcin >> age;
    wcin.ignore();

    gotoXY(27, 7);
    getline(wcin, phoneNumber);

    gotoXY(53, 9); 
    wcin >> level;
    wcin.ignore();

    int newID = 1; // Khởi tạo ID mới
    if (!employee_list.empty()) {
        newID = max_element(employee_list.begin(), employee_list.end(), [](const Employee &a, const Employee &b) {
            return a.getId() < b.getId();
        })->getId() + 1;
    }

    if(level == 2){
        userName = L"Nv_" + to_wstring(newID);
        passWord = L"123456";
    }
    else if (level == 1){
        userName = L"Admin_" + to_wstring(newID);
        passWord = L"123456";
    }

    Employee newE(name, age, phoneNumber, userName, passWord, level);
    newE.setId(newID); // Sử dụng ID mới
    employee_list.push_back(newE);
}

void ListOfEmployee::deleteEmployee(int id){
    auto it = find_if(employee_list.begin(), employee_list.end(), [id](Employee &e){
        return e.getId() == id;
    });
    if (it->getLevel() == 0) {
        wcout << L"\033[92m[Không thể xóa tài khoản OWNER]\033[0m" << endl;
        return;
    }
    if(it != employee_list.end()){
        employee_list.erase(it);
        wcout << L"\033[92m[Đã xóa nhân viên " << it->getName() <<"]\033[0m"<< endl;
    }
}

void ListOfEmployee::showEmployeeInfo(int id) {
    auto it = find_if(employee_list.begin(), employee_list.end(), [id]( Employee &e) {
        return e.getId() == id;
    });

    if (it == employee_list.end()) {
        wcout << L"\033[92m[Nhân viên không tồn tại] \033[0m" << endl;
        return;
    }

    vector<vector<wstring>> table;
    table.push_back({L"          Thông Tin Nhân Viên         "});
    table.push_back({L"ID: " + to_wstring(it->getId())});
    table.push_back({L"Tên: " + it->getName()});
    table.push_back({L"Tuổi: " + to_wstring(it->getAge())});
    table.push_back({L"Số Điện Thoại: " + it->getPhoneNumber()});
    table.push_back({L"Username: " + it->getUserName()});
    table.push_back({L"Password: " + it->getPassWord()});
    table.push_back({L"Level: " + to_wstring(it->getLevel())});
    drawTable(table);
}

void ListOfEmployee::showEmployeeList() const{
    vector<vector<wstring>> table2;
    wcout << L"╔═══════════════════════════════════════════════════════════════════════╗" << endl;
    wcout << L"║\033[93m                          Danh Sách Nhân Viên                          \033[0m║" << endl;
    wcout << L"╚═══════════════════════════════════════════════════════════════════════╝" << endl;
    table2.push_back({L"ID", L"Tên", L"Tuổi", L"Số Điện Thoại", L"Username", L"Password", L"Level"});
    for(const auto &e : employee_list){
        table2.push_back({to_wstring(e.getId()), e.getName(), to_wstring(e.getAge()), e.getPhoneNumber(), e.getUserName(), e.getPassWord(), to_wstring(e.getLevel())});
    }
    drawTable(table2);
}


void ListOfEmployee::editEmployeeInfo(int id) {
    auto it = find_if(employee_list.begin(), employee_list.end(), [id](Employee &e) {
        return e.getId() == id;
    });

    if (it == employee_list.end()) {
        wcout << L"\033[92m[Nhân viên không tồn tại] \033[0m" << endl;
        return;
    }

    vector<vector<wstring>> table;
    wstring name, phoneNumber, userName, passWord;
    int age, level;
    table.push_back({L"Hãy chọn thông tin bạn muốn sửa đổi"});
    table.push_back({L"1. Họ và tên"});
    table.push_back({L"2. Tuổi"});
    table.push_back({L"3. Số điện thoại"});
    table.push_back({L"4. Username"});
    table.push_back({L"5. Password"});
    table.push_back({L"6. Level"});
    table.push_back({L"7. Thoát"});
    drawTable(table);
    wcout << L"\033[92m════════[Lựa chọn của bạn]══> ";
    int choice;
    wcin >> choice;
    wcin.ignore();

    switch (choice){
        case 1: {
            wcout << L"\033[92m[Nhập tên mới] \033[0m";
            std::getline(wcin, name);
            it->setName(name);
            break;
        }
        case 2: {
            wcout << L"\033[92m[Nhập tuổi mới] \033[0m";
            wcin >> age;
            it->setAge(age);
            break;
        }
        case 3: {
            wcout << L"\033[92m[Nhập số điện thoại mới] \033[0m";
            std::getline(wcin, phoneNumber);
            it->setPhoneNumber(phoneNumber);
            break;
        }
        case 4: {
            wcout << L"\033[92m[Nhập username mới] \033[0m";
            std::getline(wcin, userName);
            it->setUserName(userName);
            break;
        }
        case 5: {
            wcout << L"\033[92m[Nhập password mới] \033[0m";
            std::getline(wcin, passWord);
            it->setPassWord(passWord);
            break;
        }
        case 6: {
            wcout << L"\033[92m[Nhập level mới] \033[0m";
            wcin >> level;
            it->setLevel(level);
            break;
        }
        case 7: {
            break;
        }  
        default:{
            wcout << L"\033[92m[Lựa chọn không hợp lệ] \033[0m" << endl;
            break;
        }
    }
}

void ListOfEmployee::saveEmployee(const string& filename) const {
    // Sử dụng wofstream để hỗ trợ ghi tiếng Việt
    wofstream file(filename);
    file.imbue(std::locale(file.getloc(), new std::codecvt_utf8<wchar_t>)); // Thiết lập ghi UTF-8

    if (file.is_open()) {
        // Ghi tiêu đề cột
        file << L"ID,Tên,Tuổi,Số Điện Thoại,Username,Password,Level" << endl;

        // Ghi thông tin từng nhân viên
        for (const auto &e : employee_list) {
            file << e.getId() << L","
                 << e.getName() << L","
                 << e.getAge() << L","
                 << e.getPhoneNumber() << L","
                 << e.getUserName() << L","
                 << e.getPassWord() << L","
                 << e.getLevel() << endl;
        }
        wcout << L"\033[92m[Danh sách nhân viên đã được lưu vào hệ thống] \033[0m" << endl;
    } else {
        wcout << L"\033[92m[Không thể mở file để lưu trữ thông tin nhân viên] \033[0m" << endl;
    }
}

// Hàm tải danh sách nhân viên từ file CSV
void ListOfEmployee::loadEmployees(const string& filename) {
    // Sử dụng wifstream để hỗ trợ đọc tiếng Việt
    wifstream file(filename);
    file.imbue(std::locale(file.getloc(), new std::codecvt_utf8<wchar_t>)); // Thiết lập đọc UTF-8

    if (!file.is_open()) {
        wcerr << L"Không thể mở file: " << filename.c_str() << endl;
        return; 
    }

    wstring line;
    getline(file, line); 

    while (getline(file, line)) {
        wstringstream ss(line);
        wstring token;

        int id, age, level;
        wstring name, phoneNumber, userName, passWord;

        getline(ss, token, L',');
        id = stoi(token);

        getline(ss, name, L',');

        getline(ss, token, L',');
        age = stoi(token);

        getline(ss, phoneNumber, L',');

        getline(ss, userName, L',');

        getline(ss, passWord, L',');

        getline(ss, token, L',');
        level = stoi(token);

        Employee e(name, age, phoneNumber, userName, passWord, level);
        e.setId(id);
        employee_list.push_back(e);
    }
    file.close();
}

Employee *ListOfEmployee::signIn(const wstring &userName, const wstring &passWord) {
    auto it = find_if(employee_list.begin(), employee_list.end(), [userName, passWord](Employee &e) {
        return e.getUserName() == userName && e.getPassWord() == passWord;
    });

    if (it != employee_list.end()) {
        return &(*it);
    }

    return nullptr;
}

int ListOfEmployee::createID(){
    return nextID++;
}


