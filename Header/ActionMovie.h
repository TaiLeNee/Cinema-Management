#ifndef ACTIONMOVIE_H
#define ACTIONMOVIE_H
#include <string>
#include "Movie.h"

using namespace std;

class ActionMovie : public Movie {
    public:
        ActionMovie();
        ActionMovie(int id, const wstring& name, int duration, const wstring& subTitle, const wstring& country, int limitAge, const wstring& description, const wstring& actionLevel);  // khởi tạo
        ActionMovie(const wstring& name, int duration, const wstring& subTitle, const wstring& country, int limitAge, const wstring& description, const wstring& actionLevel);
        ActionMovie(const Movie& movie);
        wstring getActionLevel();   // lấy mức độ hành động
        void setActionLevel(const wstring& actionLevel);
        void inputMovieInfo();  // in thông tin (hàm ảo)
        void displayInfo();     
        
        void editActionLevel();
    
    private:
        wstring actionLevel;    // mức độ hành động
};

#endif  // end ACTIONMOVIE_H

