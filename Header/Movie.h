#ifndef MOVIE_H
#define MOVIE_H
#include <string>
#include "Showtime.h"
#include <iostream>
#include <io.h>
#include <fcntl.h>
#include <iomanip> // for setw
#include <string>
#include <vector>
#include "drawTable.h"
#include <ctime>
#include <algorithm>

using namespace std;    
class Movie {
public:
    Movie();
    Movie(int id, const wstring& name, int duration, const wstring& subTitle, const wstring& country, int limitAge, const wstring& description);

    Movie(const wstring& name, int duration, const wstring& subTitle, const wstring& country, int limitAge, const wstring& description);
    

    virtual void inputMovieInfo();

    virtual void displayInfo() const;  // hiển thị thông tin phim

    void setId(int id);
    int getId() const;

    void setName(const wstring& name);
    wstring getName() const;
   
    void setDuration(int duration);
    int getDuration() const;

    void setSubTitle(const wstring& subTitle);
    wstring getSubTitle() const;

    void setCountry(const wstring& country);
    wstring getCountry() const;

    void setLimitAge(int limitAge);
    int getLimitAge() const;

    void setDescription(const wstring& description);
    wstring getDescription() const;

    void addShowtime(const Showtime& showtime);
    void displayShowtimes() const;
    vector<Showtime> getShowtimes() const;

    virtual void deleteInfo();
    virtual void editInfo();


private:
    int id;
    wstring name;
    int duration; // thời lượng
    wstring subTitle; // phụ đề
    wstring country; // quốc gia    
    int limitAge; // giới hạn tuổi
    wstring description; 
    vector<Showtime> showtimes; // Danh sách khung giờ chiếu
};

#endif // MOVIE_H
