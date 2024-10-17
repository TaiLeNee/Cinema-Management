#include "../Header/EmployeeList.h"
#include<iostream>
#include<vector>
#include<algorithm>
#include<fstream>
int ListOfEmployee::nextID = 1;

void ListOfEmployee::addEmployee(){
    wstring name, phoneNumber, userName, passWord;
    int age;

    wcout<< L"Nhập tên của nhân viên : ";
    getline(wcin, name);
    
    wcout<< L"Nhập tuổi của nhân viên : ";
    wcin >> age;
    wcin.ignore();  

    wcout<< L"Nhập số điện thoại của nhân viên : ";
    getline(wcin,phoneNumber);

    wcout<< L"Hãy tạo tài khoản vào hệ thống của bạn" <<endl;
    wcout<< L"Nhập tên đăng nhập : ";
    getline(wcin,userName);

    wcout<< L"Nhập mật khẩu : ";
    getline(wcin,passWord);

    Employee newE(name, age, phoneNumber, userName, passWord);
    newE.setId(createID());
    employee_list.push_back(newE);
}

void ListOfEmployee::deleteEmployee(int id){
    auto it = find_if(employee_list.begin(), employee_list.end(), [id](Employee &e){
        return e.getId() == id;
    });

    if(it != employee_list.end()){
        employee_list.erase(it);
    }
}

void ListOfEmployee::saveEmployee(const string& filename ) const{
    wofstream file(filename);
    if(file.is_open()){
        for(const auto &e : employee_list){
            file << e.getId() << endl;
            file << e.getName() << endl;
            file << e.getAge() << endl;
            file << e.getPhoneNumber() << endl;
            file << e.getUserName() << endl;
            file << e.getPassWord() << endl;
        }
    }
    else{
        wcerr<< L"Không thể mở file để lưu trữ thông tin nhân viên" <<endl;
    }
}

void ListOfEmployee::loadEmployees(const string& filename) {
    wifstream file(filename);

    if (file.is_open()) {
        while (true) {
            int id, age;
            wstring name, phoneNumber, userName, passWord;

            if (!(file >> id)) break;
            file.ignore();
            if (!getline(file, name)) break;
            if (!(file >> age)) break;
            file.ignore();
            if (!getline(file, phoneNumber)) break;
            if (!getline(file, userName)) break;
            if (!getline(file, passWord)) break;

            Employee e(name, age, phoneNumber, userName, passWord);
            e.setId(id);
            employee_list.push_back(e);
        }
    } else {
        wcerr << L"Không thể mở file để tải thông tin nhân viên" << endl;
    }
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

