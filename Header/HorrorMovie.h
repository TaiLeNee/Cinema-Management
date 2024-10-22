#ifndef HORRORMOVIE_H
#define HORRORMOVIE_H
#include <string>
#include "Movie.h"

using namespace std;

class HorrorMovie : public Movie {
    public:
        HorrorMovie();
        HorrorMovie(int id, const wstring& name, int duration, const wstring& subTitle, const wstring& country, int limitAge, const wstring& description, int actionLevel);  // khởi tạo
        HorrorMovie(const wstring& name, int duration, const wstring& subTitle, const wstring& country, int limitAge, const wstring& description, int actionLevel);

        int getHorrorLevel();   // lấy mức độ hành động
        void setHorrorLevel(int horrorLevel);
        void inputMovieInfo();  // in thông tin (hàm ảo)
        void displayInfo();     
        
        void editHorrorLevel();
    
    private:
        int horrorLevel;    // mức độ hành động
};

#endif  // end HORRORMovie_H

