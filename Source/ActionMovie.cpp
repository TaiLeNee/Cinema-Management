#include "../Header/ActionMovie.h"
#include "../Header/Movie.h"
#include <iostream>
#include <io.h>
#include <fcntl.h>
#include <iomanip> // for setw
#include <string>


using namespace std;

// Thiết lập chế độ Unicode cho console

ActionMovie::ActionMovie() {}

ActionMovie::ActionMovie(int id, const wstring& name, int duration, const wstring& subTitle, const wstring& country, int limitAge, const wstring& description, const wstring& actionLevel) 
    : Movie(id, name, duration, subTitle, country, limitAge, description), actionLevel(actionLevel) {}

ActionMovie::ActionMovie(const wstring& name, int duration, const wstring& subTitle, const wstring& country, int limitAge, const wstring& description, const wstring& actionLevel) 
    : Movie(name, duration, subTitle, country, limitAge, description), actionLevel(actionLevel) {}

ActionMovie::ActionMovie(const Movie& movie)
    : Movie(movie.getId(), movie.getName(), movie.getDuration(), movie.getSubTitle(), movie.getCountry(), movie.getLimitAge(), movie.getDescription()), actionLevel(L"") {}

wstring ActionMovie::getActionLevel() {
    return this->actionLevel;
}

void ActionMovie::setActionLevel(const wstring& actionLevel) {
    this->actionLevel = actionLevel;
}

void ActionMovie::inputMovieInfo() {
    Movie::inputMovieInfo();
     //nhấn esc để thoát
    if(GetAsyncKeyState(VK_ESCAPE)){
        return;
    }
    yellow(L"Nhập mức độ hành động (1-4): ");
    wcin.ignore();
    getline(wcin, actionLevel);
    actionLevel =L"Hành Động " + actionLevel;
}

void ActionMovie::displayInfo() {
    //Movie::displayInfo();
    drawTable({
        {L"ID", L"Tên phim", L"Thời lượng", L"Phụ đề", L"Quốc gia", L"Độ tuổi", L"Đặc điểm riêng", L"Mô tả"},
        {to_wstring(getId()), getName(), to_wstring(getDuration()), getSubTitle(), getCountry(), to_wstring(getLimitAge()), actionLevel, getDescription()}
    });
}


  


