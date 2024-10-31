#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include <string>

using namespace std;

class Employee{
    private: 
        int id;
        wstring name;
        int age; 
        wstring phoneNumber;
        int level; 
        wstring userName;
        wstring passWord; 
    public:
        Employee();
        Employee(int id,const wstring &name, int age,const wstring &phoneNumber,const wstring &userName,const wstring &passWord, int level);
        Employee(const wstring &name, int age,const wstring &phoneNumber,const wstring &userName,const wstring &passWord, int level);
        int getId() const;
        wstring getName() const;
        int getAge() const;
        wstring getPhoneNumber() const;
        int getLevel() const;
        wstring getUserName() const;
        wstring getPassWord() const;
        bool isSignIn(const wstring &inputUserName, const wstring &inputPassword) const;
        void setId(int newID);
};

#endif