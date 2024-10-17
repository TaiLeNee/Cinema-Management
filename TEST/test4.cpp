#include <iostream>
#include "../Source/EmployeeList.cpp"
#include <io.h>
#include <fcntl.h>
using namespace std;

int main() {
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);
    ListOfEmployee list;
    
    // Adding employees
    int numEmployees;
    wcout << L"Nhập số lượng nhân viên muốn thêm: ";
    wcin >> numEmployees;
    wcin.ignore(); // Clear the newline character

    for (int i = 0; i < numEmployees; ++i) {
        list.addEmployee();
    }

    // Saving employees to a file
    list.saveEmployee("employee.txt");
    wcout << L"Thông tin nhân viên đã được lưu vào file employee.txt." << endl;

    // Loading employees from a file
    list.loadEmployees("employee.txt");
    wcout << L"Thông tin nhân viên đã được tải từ file employee.txt." << endl;

    // Signing in
    wstring userName, passWord;
    wcout << L"Nhập tên đăng nhập: ";
    getline(wcin, userName);
    wcout << L"Nhập mật khẩu: ";
    getline(wcin, passWord);

    Employee* employee = list.signIn(userName, passWord);
    if (employee) {
        wcout << L"Đăng nhập thành công! Chào mừng " << employee->getName() << L"." << endl;
    } else {
        wcout << L"Đăng nhập thất bại. Tên đăng nhập hoặc mật khẩu không đúng." << endl;
    }

    return 0;
}