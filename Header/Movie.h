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
    vector<Showtime> showtimes; // Danh sách khung giờ chiếu

    Movie();
    Movie(int id, const wstring& name, int duration, const wstring& subTitle, const wstring& country, int limitAge, const wstring& description);

    Movie(const wstring& name, int duration, const wstring& subTitle, const wstring& country, int limitAge, const wstring& description);
    

    virtual void inputMovieInfo();

    virtual void displayInfo();  // hiển thị thông tin phim

    void displayShowtimeInDay(const wstring& date) const;
    void deleteShowtime(int showtimeID);


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
    vector<Showtime>& getShowtimes();
    void resetShowtimes();

    virtual void deleteInfo();
    virtual void editInfo();

    static int currentID;

private:
    int id;
    wstring name;
    int duration; // thời lượng
    wstring subTitle; // phụ đề
    wstring country; // quốc gia    
    int limitAge; // giới hạn tuổi
    wstring description; 
};

#endif // MOVIE_H
