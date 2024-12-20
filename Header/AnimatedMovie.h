#ifndef ANIMATEDMOVIE_H
#define ANIMATEDMOVIE_H
#include "Movie.h"
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

class AnimatedMovie : public Movie {
    public:
        AnimatedMovie();

        AnimatedMovie(int id, const wstring& name, int duration, const wstring& subTitle, const wstring& country, int limitAge, const wstring& description, wstring animation);

        AnimatedMovie(const wstring& name, int duration, const wstring& subTitle, const wstring& country, int limitAge, const wstring& description, wstring animation);
       
        AnimatedMovie(const Movie& movie);
        
        //Hàm ảo từ lớp cha
        void inputMovieInfo();
        void displayInfo();
        void deleteInfo();
        void editAnimatedInfo();    

        void setAnimation(const wstring& animation);
        wstring getAnimation() const;

    private:
        wstring animation; // Loại hoạt hình
};
#endif  // end ANIMATEDMOVIE_H