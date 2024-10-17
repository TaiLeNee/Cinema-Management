#include "Movie.cpp"
#include "../Header/MovieList.h"
#include <vector>
#include <algorithm> // std::remove_if
#include <sstream>
#include <fstream>
#include <locale>
#include <codecvt>
#include "drawTable.cpp"


using namespace std;

vector<Movie> movies;

void MovieList::addMovie(const Movie& movie) {
    movies.push_back(movie);
}

void MovieList::deleteMovie(int id) {
    movies.erase(remove_if(movies.begin(), movies.end(), [id](const Movie& movie) {
        return movie.getId() == id;
    }), movies.end());
}

void MovieList::displayMovies() const {

    vector<vector<wstring>> table;
    table.push_back({L"ID", L"Tên phim", L"Thể loại", L"Thời lượng", L"Mô tả"});
    for (const auto& movie : movies) {
        vector<wstring> row;
        row.push_back(to_wstring(movie.getId()));
        row.push_back(movie.getName());
        row.push_back(movie.getGenre());
        row.push_back(to_wstring(movie.getDuration()));
        row.push_back(movie.getDescription());
        table.push_back(row);
    }
    wcout<<L"\n\n";
    drawTable(table);

}

void MovieList::saveToCSV(const std::string &filename) const
{   
    locale  loc(locale(), new codecvt_utf8<wchar_t>);   //UTF═8

    wofstream file(filename);
    

    if (file.is_open()) {
        file.imbue(loc);
        // file << L"ID,Name,Genre,Duration,Description\n";
        for (const auto& movie : movies) {
            file << movie.getId() << L","
                 << movie.getName() << L","
                 << movie.getGenre() << L","
                 << movie.getDuration() << L","
                 << movie.getDescription() << L"\n";
        }
        file.close();
    } else {
        red(L"Không thể mở tập tin để viết\n");
    }
}

void MovieList::loadFromCSV(const string& filename) {
    
    movies.clear();
    wifstream file(filename);
    locale  loc(locale(), new codecvt_utf8<wchar_t>);   //UTF═8
    file.imbue(loc);

    wstring line;   
    getline(file, line); // Bỏ qua dòng tiêu đề
    while (getline(file, line)) {
        wstringstream ss(line);
        wstring id, name, genre, duration, description;

        getline(ss, id, L',');
        getline(ss, name, L',');
        getline(ss, genre, L',');
        getline(ss, duration, L',');
        getline(ss, description);

        Movie movie(stoi(id), name, genre, stoi(duration), description);
        movies.push_back(movie);
    }
    file.close();
    
}