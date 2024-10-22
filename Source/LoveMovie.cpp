#include "../Header/LoveMovie.h"
using namespace std;

LoveMovie::LoveMovie() {}

LoveMovie::LoveMovie(int id, const wstring& name, int duration, const wstring& subTitle, const wstring& country, int limitAge, const wstring& description, wstring romantic)
    : Movie(id, name, duration, subTitle, country, limitAge, description), romantic(romantic) {}

LoveMovie::LoveMovie(const wstring& name, int duration, const wstring& subTitle, const wstring& country, int limitAge, const wstring& description, wstring romantic):
    Movie(name, duration, subTitle, country, limitAge, description), romantic(romantic) {}

void LoveMovie::inputMovieInfo() {
    Movie::inputMovieInfo();
    wcout << L"Nhập loại hoạt hình: ";
    wcin.ignore();
    getline(wcin, romantic);
}

void LoveMovie::displayInfo() const {
    Movie::displayInfo();
    wcout << L"Loại hoạt hình: " << romantic << endl;
}

void LoveMovie::deleteInfo() {
    Movie::deleteInfo();
    romantic = L"";
}

void LoveMovie::editInfo() {
    Movie::editInfo();
    wcout << L"Nhập loại hoạt hình mới: ";
    wcin.ignore();
    getline(wcin, romantic);
}   

void LoveMovie::setRomantic(const wstring& romantic) {
    this->romantic = romantic;
}

wstring LoveMovie::getRomantic() const {
    return romantic;
}   

