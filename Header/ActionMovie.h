#ifndef ACTIONMOVIE_H
#define ACTIONMOVIE_H
#include <string>
#include "Movie.h"

using namespace std;

class ActionMovie : public Movie {
    public:
        ActionMovie();
        ActionMovie(int id, const wstring& name, int duration, const wstring& subTitle, const wstring& country, int limitAge, const wstring& description, int actionLevel);  // khởi tạo
        ActionMovie(const wstring& name, int duration, const wstring& subTitle, const wstring& country, int limitAge, const wstring& description, int actionLevel);

        int getActionLevel();   // lấy mức độ hành động
        void setActionLevel(int actionLevel);
        void inputMovieInfo();  // in thông tin (hàm ảo)
        void displayInfo();     
        
        void editActionLevel();
    
    private:
        int actionLevel;    // mức độ hành động
};

#endif  // end ACTIONMOVIE_H

