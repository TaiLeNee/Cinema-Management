#include "../Header/MovieList.h"

using namespace std;


MovieList::MovieList() {
    loadFromCSV("../DATA/movies.csv");
}

void MovieList::loadShowtimesofMovie(vector<Showtime>& showtimes) {
    for(auto &movie : movies){
        vector<Showtime> result;
        for (auto& showtime : showtimes) {
            if (showtime.getMovieID() == movie->getId()) {
                result.push_back(showtime);
                movie->addShowtime(showtime);
            }
        }
    }
}

void MovieList::resetShowtimesofMovie() {
    for(auto &movie : movies){
        movie->resetShowtimes();
    }
}

vector<Movie*>& MovieList::getMovies(){
    return movies;
}


// Movie* MovieList::createMovie(int id, const wstring& name, const wstring& typeMovie, int duration, const wstring& subtitle, const wstring& country, int limitAge, const wstring& description, const wstring& genre) {
//     if (typeMovie == L"Tình cảm") {
//         return new LoveMovie(id, name, duration, subtitle, country, limitAge, description, genre);
//     } else if (typeMovie == L"Hoạt hình") {
//         return new AnimatedMovie(id, name, duration, subtitle, country, limitAge, description, genre);
//     } else if (typeMovie == L"Hành động") {
//         return new ActionMovie(id, name, duration, subtitle, country, limitAge, description, genre);
//     } else if (typeMovie == L"Kinh dị") {
//         return new HorrorMovie(id, name, duration, subtitle, country, limitAge, description, genre);
//     } else {
//         return new Movie(id, name, duration, subtitle, country, limitAge, description);
//     }
// }


void MovieList::addMovie(const wstring& name, const wstring& typeMovie, int duration, const wstring& subtitle, const wstring& country, int limitAge, const wstring& description, const wstring& genre) {
    Movie *movie = NULL;
    if (typeMovie == L"Tình cảm") {
        movie = new LoveMovie( name, duration, subtitle, country, limitAge, description, genre);
    } else if (typeMovie == L"Hoạt hình") {
        movie = new AnimatedMovie( name, duration, subtitle, country, limitAge, description, genre);
    } else if (typeMovie == L"Hành động") {
        movie = new ActionMovie( name, duration, subtitle, country, limitAge, description, genre);
    } else if (typeMovie == L"Kinh dị") {
        movie = new HorrorMovie( name, duration, subtitle, country, limitAge, description, genre);
    } else {
        movie = new Movie( name, duration, subtitle, country, limitAge, description);
    }
    movies.push_back(movie);
}

void MovieList::deleteMovie(int id) {
    movies.erase(remove_if(movies.begin(), movies.end(), [id](Movie* movie) {
        return movie->getId() == id;
    }), movies.end());
}


void MovieList::displayMovieInfo(int id) const {
    auto it = find_if(movies.begin(), movies.end(), [id](Movie* movie) {
        return movie->getId() == id;
    });

    if (it == movies.end()) {
        wcout << L"\033[92m[Phim không tồn tại] \033[0m" << endl;
        return;
    }

    vector<vector<wstring>> table;
    table.push_back({L"          Thông Tin Phim         "});
    table.push_back({L"ID: " + to_wstring((*it)->getId())});
    table.push_back({L"Tên: " + (*it)->getName()});
    table.push_back({L"Thời lượng: " + to_wstring((*it)->getDuration())});
    table.push_back({L"Phụ đề: " + (*it)->getSubTitle()});
    table.push_back({L"Quốc gia: " + (*it)->getCountry()});
    table.push_back({L"Độ tuổi: " + to_wstring((*it)->getLimitAge())});
    table.push_back({L"Mô tả: " + (*it)->getDescription()});
    drawTable(table);
}

void MovieList::displayMovies() const {
    vector<vector<wstring>> table;
    // table.push_back({L"ID", L"Tên phim", L"Thời lượng", L"Thể loại", L"Phụ đề", L"Quốc gia",L"Độ tuổi", L"Mô tả"});
    table.push_back({L"ID", L"Tên phim", L"Thời lượng", L"Phụ đề", L"Quốc gia",L"Độ tuổi", L"Đặc điểm riêng", L"Mô tả"});
    for (const auto& movie : movies) {
        vector<wstring> row;
        row.push_back(to_wstring(movie->getId()));
        row.push_back(movie->getName());
        row.push_back(to_wstring(movie->getDuration()));
        // row.push_back(movie->);
        row.push_back(movie->getSubTitle());
        row.push_back(movie->getCountry());
        row.push_back(to_wstring(movie->getLimitAge()));


        if (dynamic_cast<LoveMovie*>(movie)) {
            row.push_back(dynamic_cast<LoveMovie*>(movie)->getRomantic());
        } else if (dynamic_cast<AnimatedMovie*>(movie)) {
            row.push_back(dynamic_cast<AnimatedMovie*>(movie)->getAnimation());
        } else if (dynamic_cast<ActionMovie*>(movie)) {
            row.push_back(dynamic_cast<ActionMovie*>(movie)->getActionLevel());
        } else if (dynamic_cast<HorrorMovie*>(movie)) {
            row.push_back(dynamic_cast<HorrorMovie*>(movie)->getHorrorLevel());
        } else {
            row.push_back(L"");
        }

        row.push_back(movie->getDescription());
        table.push_back(row);
    }
    wcout << L"\n\n";
    drawTable(table);
}



void MovieList::updateMovie(int id) {
    auto it = find_if(movies.begin(), movies.end(), [id](Movie* movie) {
        return movie->getId() == id;
    });

    if (it == movies.end()) {
        wcout << L"\033[92m[Phim không tồn tại] \033[0m" << endl;
        return;
    }

    (*it)->editInfo();

}


void MovieList::saveToCSV(string filename = "../DATA/movies.csv") const {   
    locale loc(locale(), new codecvt_utf8<wchar_t>);   // UTF-8

    wofstream file(filename);
    if (file.is_open()) {
        file.imbue(loc);
        for (const auto& movie : movies) {
            file << movie->getId() << L","
                 << movie->getName() << L",";
            if (dynamic_cast<LoveMovie*>(movie)) {
                file << L"Tình cảm,";
            } else if (dynamic_cast<AnimatedMovie*>(movie)) {
                file << L"Hoạt hình,";
            } else if (dynamic_cast<ActionMovie*>(movie)) {
                file << L"Hành động,";
            } else if (dynamic_cast<HorrorMovie*>(movie)) {
                file << L"Kinh dị,";
            }
            file << movie->getDuration() << L","
                 << movie->getSubTitle() << L","
                 << movie->getCountry() << L","
                 << movie->getLimitAge() << L",";
            if (dynamic_cast<LoveMovie*>(movie)) {
                file << dynamic_cast<LoveMovie*>(movie)->getRomantic() << L",";
            } else if (dynamic_cast<AnimatedMovie*>(movie)) {
                file << dynamic_cast<AnimatedMovie*>(movie)->getAnimation() << L",";
            } else if (dynamic_cast<ActionMovie*>(movie)) {
                file << dynamic_cast<ActionMovie*>(movie)->getActionLevel() << L",";
            } else if (dynamic_cast<HorrorMovie*>(movie)) {
                file << dynamic_cast<HorrorMovie*>(movie)->getHorrorLevel() << L",";
            }
            
            file << movie->getDescription() << L"\n";
        }
        file.close();
    } else {
        wcerr << L"Không thể mở tập tin để lưu\n";
    }
}

void MovieList::loadFromCSV(const string& filename) {
    movies.clear();
    wifstream file(filename);
    locale loc(locale(), new codecvt_utf8<wchar_t>);   // UTF-8
    file.imbue(loc);

    wstring line;   
    getline(file, line); // Bỏ qua dòng tiêu đề
    while (getline(file, line)) {
        wstringstream ss(line);
        wstring id, name, typeMovie, duration, description, subtitle, country,limitAge, genre;

        getline(ss, id, L',');
        getline(ss, name, L',');
        getline(ss, typeMovie, L',');
        getline(ss, duration, L',');
        getline(ss, subtitle, L',');
        getline(ss, country, L',');
        getline(ss, limitAge, L',');
        getline(ss, genre, L',');
        getline(ss, description);

        if(typeMovie == L"Tình cảm"){
            Movie* movie = new LoveMovie(stoi(id), name, stoi(duration),subtitle, country, stoi(limitAge), description, genre);
            movies.push_back(movie);
        } else if(typeMovie == L"Hoạt hình"){
            Movie* movie = new AnimatedMovie(stoi(id), name, stoi(duration), subtitle, country, stoi(limitAge), description, genre);
            movies.push_back(movie);
        } else if(typeMovie == L"Hành động"){
            Movie* movie = new ActionMovie(stoi(id), name, stoi(duration), subtitle, country, stoi(limitAge), description, genre);
            movies.push_back(movie);
        } else if(typeMovie == L"Kinh dị"){
            Movie* movie = new HorrorMovie(stoi(id), name, stoi(duration), subtitle, country, stoi(limitAge), description, genre);
            movies.push_back(movie);
       
        }
    }
    file.close();
}

MovieList::~MovieList() {
    for (auto& movie : movies) {
        delete movie;
    }
}