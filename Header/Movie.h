#ifndef MOVIE_H
#define MOVIE_H
#include <string>
#include "Showtime.h"

using namespace std;    
class Movie {
public:
    Movie(const wstring& name, const wstring& genre, int duration, const wstring& description);
    Movie(int id, const wstring& name, const wstring& genre, int duration, const wstring& description);
    void displayInfo() const;  // hiển thị thông tin phim
    void setId(int id);
    int getId() const;
    wstring getName() const;
    wstring getGenre() const;
    int getDuration() const;
    wstring getDescription() const;

    void addShowtime(const Showtime& showtime);
    void deleteInfo();
    void editInfo();


private:
    int id;
    wstring name;
    wstring genre;   // thể loại
    int duration; // thời lượng
    wstring description; 
    vector<Showtime> showtimes; // Danh sách khung giờ chiếu
};

#endif // MOVIE_H
