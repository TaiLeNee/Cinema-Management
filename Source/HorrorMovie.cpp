#include "../Header/HorrorMovie.h"
#include "../Header/Movie.h"
#include <iostream>
#include <io.h>
#include <fcntl.h>
#include <iomanip> // for setw
#include <string>


using namespace std;

// Thiết lập chế độ Unicode cho console



HorrorMovie::HorrorMovie(int id, const wstring& name, int duration, const wstring& subTitle, const wstring& country, int limitAge, const wstring& description, int horrorLevel) 
    : Movie(id, name, duration, subTitle, country, limitAge, description), horrorLevel(horrorLevel) {}

HorrorMovie::HorrorMovie(const wstring& name, int duration, const wstring& subTitle, const wstring& country, int limitAge, const wstring& description, int horrorLevel) 
    : Movie(name, duration, subTitle, country, limitAge, description), horrorLevel(horrorLevel) {}

int HorrorMovie::getHorrorLevel() {
    return this->horrorLevel;
}

void HorrorMovie::setHorrorLevel(int horrorLevel) {
    this->horrorLevel = horrorLevel;
}

void HorrorMovie::inputMovieInfo() {
    Movie::inputMovieInfo();
    wcout << L"Nhập mức độ kinh dị (1-4): ";
    wcin >> horrorLevel;
}

void HorrorMovie::displayInfo() {
    Movie::displayInfo();
    wcout << L"Mức độ kinh dị: " << horrorLevel <<endl;
}

void HorrorMovie::editHorrorLevel() {
    int newHorrorLevel;
    wcout << L"Nhập mức độ kinh dị (1-4): ";
    wcin >> newHorrorLevel;
    this->horrorLevel = newHorrorLevel;
    wcout << L"Nhập thành công!!";
}


  


