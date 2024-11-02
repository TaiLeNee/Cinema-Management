#ifndef EMPLOYEELIST_H
#define EMPLOYEELIST_H
#include "../Header/Employee.h"
#include "../Header/drawTable.h"
#include<string>
#include<vector>
#include<iostream>
#include<vector>
#include<algorithm>
#include<fstream>
#include<codecvt>
#include<sstream>
#include<regex>

using namespace std;

class ListOfEmployee{
    private:
        vector<Employee> employee_list;
        static int nextID;
    public: 
        
        //Thêm một nhân viên vào danh sách
        void addEmployee();

        //Xóa một nhân viên khỏi danh sách
        void deleteEmployee(int id);

        //Chỉnh sửa thông tin nhân viên bằng ID
        void editEmployeeInfo(int id);

        //Hiển thị thông tin nhân viên bằng ID
        void showEmployeeInfo(int id) ;

        //Hiển thị danh sách nhân viên
        void showEmployeeList() const;
        
        //Lưu nhân viên vào danh sách 
        void saveEmployee(const string& filename) const;

        //Đọc danh sách từ tệp
        void loadEmployees(const string& filename);
        
        //Kiểm tra đăng nhập
        Employee *signIn(const wstring &userName, const wstring &passWord);

        // Tạo ID mới mỗi khi nhân viên mới đến
        static int createID();
};

#endif