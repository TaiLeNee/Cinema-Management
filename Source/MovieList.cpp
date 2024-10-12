#include <vector>
#include "Movie.cpp"
#include <algorithm> // std::remove_if
#include <sstream>

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

void addMovie(const Movie& movie) {
    movies.push_back(movie);
}

void removeMovie(int id) {
    movies.erase(remove_if(movies.begin(), movies.end(), [id](const Movie& movie) {
        return movie.getId() == id;
    }), movies.end());
}

void displayMovies() {
    wcout << L"+----+----------------------+----------+-------------+--------------------------------+" << endl;
    wcout << L"| ID | Name                 | Genre    |   Duration  |           Description          |" << endl;
    wcout << L"+----+----------------------+----------+-------------+--------------------------------+" << endl;

    for (const auto& movie : movies) {
        std::vector<std::wstring> descriptionLines = splitStringByWords(movie.getDescription(), 30);
        wcout << L"| " << setw(2) << movie.getId() << L" | "
             << setw(20) << movie.getName() << L" | "
             << setw(8) << movie.getGenre() << L" | "
             << setw(6) << movie.getDuration() << L" phút | "
             << setw(30) << descriptionLines[0] << L" |" << endl;
        

        for (size_t i = 1; i < descriptionLines.size(); ++i) {
            wcout << L"| " <<setw(5) << L" | "
             << setw(23) << L" | "
             << setw(11)  << L" | "
             << setw(14) << L" | "
             << setw(30)  << descriptionLines[i] << L" |" << endl;
        }
        wcout << L"+----+----------------------+----------+-------------+--------------------------------+" << endl;

    }
        wcout << L"+----+----------------------+----------+-------------+--------------------------------+" << endl;

}