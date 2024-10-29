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

bool Employee::isSignIn(const wstring &inputUserName, const wstring &inputPassword) const
{
    return (userName == inputUserName && passWord == inputPassword);
}