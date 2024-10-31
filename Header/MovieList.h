#ifndef MOVIELIST_H
#define MOVIELIST_H
#include "Movie.h"
#include <vector>
#include <string>
#include <algorithm> // std::remove_if
#include <sstream>
#include <fstream>
#include <locale>
#include <codecvt>


class MovieList {
private:
    std::vector<Movie*> movies;

public:
    MovieList();
    ~MovieList();
    vector<Movie*>& getMovies();

    // Tạo một bộ phim mới
    // Movie* createMovie(int id, const wstring& name, const wstring& typeMovie, int duration, const wstring& subtitle, const wstring& country, int limitAge, const wstring& description, const wstring& genre);
    // Thêm một bộ phim vào danh sách
    void addMovie(int id, const wstring& name, const wstring& typeMovie, int duration, const wstring& subtitle, const wstring& country, int limitAge, const wstring& description, const wstring& genre);

    // Sửa thông tin một bộ phim trong danh sách
    void updateMovie(int id, const Movie& updatedMovie);

    // Xóa một bộ phim khỏi danh sách
    void deleteMovie(int id);
    
    // Hiển thị tất cả các bộ phim trong danh sách
    void displayMovies() const;

    // Lưu danh sách phim vào tệp CSV
    void saveToCSV(string filename) const;

    // Đọc danh sách phim từ tệp CSV
    void loadFromCSV(const std::string& filename);

    void loadShowtimesofMovie(vector<Showtime>& showtimes);
};

#endif // MOVIELIST_H