#include "../Header/LoveMovie.h"
using namespace std;

LoveMovie::LoveMovie() {}

LoveMovie::LoveMovie(int id, const wstring& name, int duration, const wstring& subTitle, const wstring& country, int limitAge, const wstring& description, wstring romantic)
    : Movie(id, name, duration, subTitle, country, limitAge, description), romantic(romantic) {}

LoveMovie::LoveMovie(const wstring& name, int duration, const wstring& subTitle, const wstring& country, int limitAge, const wstring& description, wstring romantic):
    Movie(name, duration, subTitle, country, limitAge, description), romantic(romantic) {}

LoveMovie::LoveMovie(const Movie& movie): Movie(movie.getId(), movie.getName(), movie.getDuration(), movie.getSubTitle(), movie.getCountry(), movie.getLimitAge(), movie.getDescription()), romantic(L"") {}

void LoveMovie::inputMovieInfo() {
    Movie::inputMovieInfo();
    yellow(L"Nhập thể loại tình cảm: ");
    wcin.ignore();
    getline(wcin, romantic);
}

void LoveMovie::displayInfo() {
    //Movie::displayInfo();
    drawTable({
        {L"ID", L"Tên phim", L"Thời lượng", L"Phụ đề", L"Quốc gia", L"Độ tuổi", L"Đặc điểm riêng", L"Mô tả"},
        {to_wstring(getId()), getName(), to_wstring(getDuration()), getSubTitle(), getCountry(), to_wstring(getLimitAge()), romantic, getDescription()}
    });
}

void LoveMovie::deleteInfo() {
    Movie::deleteInfo();
    romantic = L"";
}


void LoveMovie::setRomantic(const wstring& romantic) {
    this->romantic = romantic;
}

wstring LoveMovie::getRomantic() const {
    return romantic;
}   

