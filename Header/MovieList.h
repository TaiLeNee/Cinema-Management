#ifndef MOVIELIST_H
#define MOVIELIST_H
#include "Movie.h"
#include <vector>
#include <string>


class MovieList {
private:
    std::vector<Movie> movies;

public:
    // Constructer
    MovieList(Movie movies);

    // Thêm một bộ phim vào danh sách
    void addMovie(const Movie& movie);

    // Sửa thông tin một bộ phim trong danh sách
    void updateMovie(int id, const Movie& updatedMovie);

    // Xóa một bộ phim khỏi danh sách
    void deleteMovie(int id);

    // Hiển thị tất cả các bộ phim trong danh sách
    void displayMovies() const;

    // Lưu danh sách phim vào tệp CSV
    void saveToCSV(const std::string& filename) const;

    // Đọc danh sách phim từ tệp CSV
    void loadFromCSV(const std::string& filename);
};

#endif // MOVIELIST_H