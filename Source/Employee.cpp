#include "../Header/Employee.h"
using namespace std;

Employee::Employee() : id(0), name(L""), age(0), phoneNumber(L""), userName(L""), passWord(L"") {}

Employee::Employee(int id, const wstring &name, int age, const wstring &phoneNumber, const wstring &userName, const wstring &passWord, int level)
    : id(id), name(name), age(age), phoneNumber(phoneNumber), userName(userName), passWord(passWord) , level(level){}

Employee::Employee(const wstring &name, int age, const wstring &phoneNumber, const wstring &userName, const wstring &passWord, int level)
    : name(name), age(age), phoneNumber(phoneNumber), userName(userName), passWord(passWord) , level(level){}

int Employee::getId() const
{
    return id;
}

wstring Employee::getName() const
{
    return name;
}

int Employee::getAge() const
{
    return age;
}

wstring Employee::getPhoneNumber() const
{
    return phoneNumber;
}

int Employee::getLevel() const
{
    return level;
}

wstring Employee::getUserName() const
{
    return userName;
}

wstring Employee::getPassWord() const
{
    return passWord;
}

void Employee::setId(int newID)
{
    id = newID;
}

void Employee::setName(const wstring &newName)
{
    name = newName;
}

void Employee::setAge(int newAge)
{
    age = newAge;
}

void Employee::setPhoneNumber(const wstring &newPhoneNumber)
{
    phoneNumber = newPhoneNumber;
}

void Employee::setLevel(int newLevel)
{
    level = newLevel;
}

void Employee::setUserName(const wstring &newUserName)
{
    userName = newUserName;
}

void Employee::setPassWord(const wstring &newPassWord)
{
    passWord = newPassWord;
}

bool Employee::isSignIn(const wstring &inputUserName, const wstring &inputPassword) const
{
    return (userName == inputUserName && passWord == inputPassword);
}   

void Employee::displayInfo() const {
    vector<vector<wstring>> table;
    table.push_back({L"          Thông Tin Nhân Viên         "});
    table.push_back({L"ID: " + to_wstring(id)});
    table.push_back({L"Tên: " + name});
    table.push_back({L"Tuổi: " + to_wstring(age)});
    table.push_back({L"Số Điện Thoại: " + phoneNumber});
    table.push_back({L"Username: " + userName});
    table.push_back({L"Password: " + passWord});
    if (level == 1) {
        table.push_back({L"Cấp bậc: Admin"});
    } 
    else if (level == 2) {
        table.push_back({L"Cấp Bậc: Nhân viên"});
    }
    else if (level == 0) {
        table.push_back({L"Cấp Bậc: OWNER"});
    }
    drawTable(table);
}