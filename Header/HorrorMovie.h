#ifndef HORRORMOVIE_H
#define HORRORMOVIE_H
#include <string>
#include "Movie.h"

using namespace std;

class HorrorMovie : public Movie {
    public:
        HorrorMovie();
        HorrorMovie(int id, const wstring& name, int duration, const wstring& subTitle, const wstring& country, int limitAge, const wstring& description, const wstring& actionLevel);  // khởi tạo
        HorrorMovie(const wstring& name, int duration, const wstring& subTitle, const wstring& country, int limitAge, const wstring& description, const wstring& actionLevel);

        wstring getHorrorLevel();   // lấy mức độ hành động
        void setHorrorLevel(const wstring& horrorLevel);
        void inputMovieInfo();  // in thông tin (hàm ảo)
        void displayInfo();     
        
        void editHorrorLevel();
    
    private:
        wstring horrorLevel;    // mức độ hành động
};

#endif  // end HORRORMovie_H

