#include "../Header/AnimatedMovie.h"
using namespace std;

AnimatedMovie::AnimatedMovie() {}

AnimatedMovie::AnimatedMovie(int id, const wstring& name, int duration, const wstring& subTitle, const wstring& country, int limitAge, const wstring& description, wstring animation)
    : Movie(id, name, duration, subTitle, country, limitAge, description), animation(animation) {}

AnimatedMovie::AnimatedMovie(const wstring& name, int duration, const wstring& subTitle, const wstring& country, int limitAge, const wstring& description, wstring animation):
    Movie(name, duration, subTitle, country, limitAge, description), animation(animation) {}

AnimatedMovie::AnimatedMovie(const Movie& movie)
    : Movie(movie.getId(), movie.getName(), movie.getDuration(), movie.getSubTitle(), movie.getCountry(), movie.getLimitAge(), movie.getDescription()), animation(L"") {}

void AnimatedMovie::inputMovieInfo() {
    Movie::inputMovieInfo();
    yellow(L"Nhập thể loại hoạt hình: ");
    wcin.ignore();
    getline(wcin, animation);
}

void AnimatedMovie::displayInfo() {
    //Movie::displayInfo();
    drawTable({
        {L"ID", L"Tên phim", L"Thời lượng", L"Phụ đề", L"Quốc gia", L"Độ tuổi", L"Đặc điểm riêng", L"Mô tả"},
        {to_wstring(getId()), getName(), to_wstring(getDuration()), getSubTitle(), getCountry(), to_wstring(getLimitAge()), animation, getDescription()}
    });
}

void AnimatedMovie::deleteInfo() {
    Movie::deleteInfo();
    animation = L"";
}


void AnimatedMovie::setAnimation(const wstring& animation) {
    this->animation = animation;
}

wstring AnimatedMovie::getAnimation() const {
    return animation;
}   

