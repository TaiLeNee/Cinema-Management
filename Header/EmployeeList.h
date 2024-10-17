#ifndef EMPLOYEELIST_H
#define EMPLOYEELIST_H
#include<string>
#include<vector>
#include "Employee.h"

using namespace std;

class ListOfEmployee{
    private:
        vector<Employee> employee_list;
        static int nextID;
    public: 
        //Thêm một nhân viên 
        void addEmployee();

        //Xóa một nhân viên khỏi danh sách
        void deleteEmployee(int id);

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