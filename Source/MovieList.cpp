#include "Movie.cpp"
#include "Color.cpp"
#include "../Header/MovieList.h"
#include <vector>
#include <algorithm> // std::remove_if
#include <sstream>
#include <fstream>
#include <locale>
#include <codecvt>


using namespace std;

vector<Movie> movies;


vector<wstring> splitStringByWords(const wstring& str, size_t width) {
    vector<wstring> result;
    wistringstream words(str);
    wstring word;
    wstring line;

    while (words >> word) {
        if (line.length() + word.length() + 1 > width) {
            result.push_back(line);
            line = word;
        } else {
            if (!line.empty()) {
                line += L" ";
            }
            line += word;
        }
    }
    if (!line.empty()) {
        result.push_back(line);
    }

    return result;
}



void MovieList::addMovie(const Movie& movie) {
    movies.push_back(movie);
}

void MovieList::deleteMovie(int id) {
    movies.erase(remove_if(movies.begin(), movies.end(), [id](const Movie& movie) {
        return movie.getId() == id;
    }), movies.end());
}

void MovieList::displayMovies() const {
    wstringstream output;


    wcout << L"+----+--------------------------------+--------------------+-------------+--------------------------------------+" << endl;
       green(L"| ID |           Name                 |       Genre        |   Duration  |              Description             |\n");
    wcout << L"+----+--------------------------------+--------------------+-------------+--------------------------------------+" << endl;

    for (const auto& movie : movies) {
        std::vector<std::wstring> descriptionLines = splitStringByWords(movie.getDescription(), 35);
        output << L"| " << setw(2) << movie.getId() << L" | "
            << setw(30) << movie.getName().c_str() << L" | "
            << setw(18) << movie.getGenre().c_str() << L" | "
            << setw(6) << movie.getDuration() << L" phút | "
            << setw(36) << descriptionLines[0].c_str() << L" |" << endl;
        yellow(output.str());
        output.str(L""); // Clear the output
        

        for (size_t i = 1; i < descriptionLines.size(); ++i) {
            output << L"| " <<setw(5) << L" | "
            << setw(33) << L" | "
            << setw(21)  << L" | "
            << setw(14) << L" | "
            << setw(36)  << descriptionLines[i].c_str() << L" |" << endl;
            yellow(output.str());
            output.str(L""); // Clear the output
        }
        wcout << L"+----+--------------------------------+--------------------+-------------+--------------------------------------+" << endl;

    }
        wcout << L"+----+--------------------------------+--------------------+-------------+--------------------------------------+" << endl;

}

void MovieList::saveToCSV(const std::string &filename) const
{   
    locale  loc(locale(), new codecvt_utf8<wchar_t>);   //UTF-8

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
    locale  loc(locale(), new codecvt_utf8<wchar_t>);   //UTF-8
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