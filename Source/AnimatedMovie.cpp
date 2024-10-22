#include "../Header/AnimatedMovie.h"
using namespace std;

AnimatedMovie::AnimatedMovie() {}

AnimatedMovie::AnimatedMovie(int id, const wstring& name, int duration, const wstring& subTitle, const wstring& country, int limitAge, const wstring& description, wstring animation)
    : Movie(id, name, duration, subTitle, country, limitAge, description), animation(animation) {}

AnimatedMovie::AnimatedMovie(const wstring& name, int duration, const wstring& subTitle, const wstring& country, int limitAge, const wstring& description, wstring animation):
    Movie(name, duration, subTitle, country, limitAge, description), animation(animation) {}

void AnimatedMovie::inputMovieInfo() {
    Movie::inputMovieInfo();
    wcout << L"Nhập loại hoạt hình: ";
    wcin.ignore();
    getline(wcin, animation);
}

void AnimatedMovie::displayInfo() const {
    Movie::displayInfo();
    wcout << L"Loại hoạt hình: " << animation << endl;
}

void AnimatedMovie::deleteInfo() {
    Movie::deleteInfo();
    animation = L"";
}

void AnimatedMovie::editInfo() {
    Movie::editInfo();
    wcout << L"Nhập loại hoạt hình mới: ";
    wcin.ignore();
    getline(wcin, animation);
}   

void AnimatedMovie::setAnimation(const wstring& animation) {
    this->animation = animation;
}

wstring AnimatedMovie::getAnimation() const {
    return animation;
}   

