#include "../Header/HorrorMovie.h"
#include "../Header/Movie.h"
#include <iostream>
#include <io.h>
#include <fcntl.h>
#include <iomanip> // for setw
#include <string>


using namespace std;

// Thiết lập chế độ Unicode cho console


HorrorMovie::HorrorMovie() {}

HorrorMovie::HorrorMovie(int id, const wstring& name, int duration, const wstring& subTitle, const wstring& country, int limitAge, const wstring& description, const wstring& horrorLevel) 
    : Movie(id, name, duration, subTitle, country, limitAge, description), horrorLevel(horrorLevel) {}

HorrorMovie::HorrorMovie(const wstring& name, int duration, const wstring& subTitle, const wstring& country, int limitAge, const wstring& description, const wstring& horrorLevel) 
    : Movie(name, duration, subTitle, country, limitAge, description), horrorLevel(horrorLevel) {}

HorrorMovie::HorrorMovie(const Movie& movie): Movie(movie.getId(), movie.getName(), movie.getDuration(), movie.getSubTitle(), movie.getCountry(), movie.getLimitAge(), movie.getDescription()), horrorLevel(L"") {}

wstring HorrorMovie::getHorrorLevel() {
    return this->horrorLevel;
}

void HorrorMovie::setHorrorLevel(const wstring& horrorLevel) {
    this->horrorLevel = horrorLevel;
}

void HorrorMovie::inputMovieInfo() {
    Movie::inputMovieInfo();
    wcout << L"Nhập mức độ kinh dị (1-4): ";
    wcin.ignore();
    getline(wcin, horrorLevel);
    horrorLevel = L"Kinh Dị " + horrorLevel; 
}

void HorrorMovie::displayInfo(){
    Movie::displayInfo();
    drawTable({
        {L"Mức độ kinh dị: ",horrorLevel}
    });
    // wcout << L"Mức độ kinh dị: " << horrorLevel <<endl;
}



  


