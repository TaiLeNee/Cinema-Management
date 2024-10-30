#include "CustomerList.cpp"
#include "Customer.cpp"
#include <fcntl.h>
#include <io.h>
#include <regex>
#include "drawTable.cpp"
#include "splitStringByWords.cpp"
#include <iostream>

using namespace std;

void CustomerMenu(CustomerList &customerList) {
    int choice;
    do {
        vector<vector<wstring>> table;
        table.push_back({L"    Menu Quản lý Khách hàng "});
        table.push_back({L"1. Hiện danh sách khách hàng"});
        table.push_back({L"2. Thêm khách hàng"});
        table.push_back({L"3. Xóa khách hàng"});
        table.push_back({L"4. Sửa thông tin khách hàng"});
        table.push_back({L"5. Lưu danh sách vào customer.csv"});
        table.push_back({L"6. Tải danh sách từ customer.csv"});
        table.push_back({L"0. Thoát"});
        drawTable(table);
        green(L"================[Lựa chọn của bạn]══>");
        // wcout << L"\033[92m════════[Lựa chọn của bạn]══> ";
        wcin >> choice;
        wcout << L"\033[0m";
        system("cls");
        wcin.ignore();

        switch (choice) {
            case 1: {
                customerList.displayCustomers();
                break;
            }
            case 2: {
                wstring name, phoneNumber;
                int point;
                wcout << L"Nhập tên khách hàng: ";
                wcin.ignore();
                getline(wcin, name);
                wcout << L"Nhập số điện thoại: ";
                wcin >> phoneNumber;
                wcout << L"Nhập số điểm: ";
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
                customerList.editCustomer(id, updatedCustomer);
                break;
            }
            case 5:
                customerList.saveToCSV("../DATA/customers.csv");
                break;
            case 6:
                customerList.loadFromCSV("../DATA/customers.csv");
                break;
            case 0:
                wcout << L"Đăng xuất..." << endl;
                break;
            default:
                wcout << L"Lựa chọn không hợp lệ, vui lòng thử lại." << endl;
        }
    } while (choice != 0);
}

int main() {
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);
    CustomerList customerList;
    CustomerMenu(customerList);
    return 0;
}



