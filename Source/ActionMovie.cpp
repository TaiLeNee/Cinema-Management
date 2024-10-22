#include "../Header/ActionMovie.h"
#include "../Header/Movie.h"
#include <iostream>
#include <io.h>
#include <fcntl.h>
#include <iomanip> // for setw
#include <string>


using namespace std;

// Thiết lập chế độ Unicode cho console



ActionMovie::ActionMovie(int id, const wstring& name, int duration, const wstring& subTitle, const wstring& country, int limitAge, const wstring& description, int actionLevel) 
    : Movie(id, name, duration, subTitle, country, limitAge, description), actionLevel(actionLevel) {}

ActionMovie::ActionMovie(const wstring& name, int duration, const wstring& subTitle, const wstring& country, int limitAge, const wstring& description, int actionLevel) 
    : Movie(name, duration, subTitle, country, limitAge, description), actionLevel(actionLevel) {}

int ActionMovie::getActionLevel() {
    return this->actionLevel;
}

void ActionMovie::setActionLevel(int actionLevel) {
    this->actionLevel = actionLevel;
}

void ActionMovie::inputMovieInfo() {
    Movie::inputMovieInfo();
    wcout << L"Nhập mức độ hành động (1-4): ";
    wcin >> actionLevel;
}

void ActionMovie::displayInfo() {
    Movie::displayInfo();
    wcout << L"Mức độ hành động: " << actionLevel <<endl;
}

void ActionMovie::editActionLevel() {
    int newActionLevel;
    wcout << L"Nhập mức độ hành động (1-4): ";
    wcin >> newActionLevel;
    this->actionLevel = newActionLevel;
    wcout << L"Nhập thành công!!";
}


  


