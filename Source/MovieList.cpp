#include "../Header/MovieList.h"


using namespace std;


MovieList::MovieList() {
    // loadFromCSV("../DATA/movies.csv");
}

void MovieList::loadShowtimesofMovie(vector<Showtime>& showtimes) {
    for(auto &movie : movies){
        for (auto& showtime : showtimes) {
            if (showtime.getMovieID() == movie->getId()) {
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


void MovieList::addMovie(){
    wstring name, typeMovie, subtitle, country, description, genre;
    int duration, limitAge;
    vector<vector<wstring>> table;
    table.push_back({L"  Chọn Thể Loại Phim"});
    table.push_back({L"1. Tình cảm"});
    table.push_back({L"2. Hoạt hình"});
    table.push_back({L"3. Hành động"});
    table.push_back({L"4. Kinh dị"});
    table.push_back({L"0. Quay lại"});
    drawTable(table);
    wcout << L"\033[92m[Lựa chọn của bạn]  ";
    int choice;
    checkInput(L"Nhập lựa chọn", choice);
    wcin.ignore();

    switch (choice) {
        case 1: {
            typeMovie = L"Tình cảm";
            LoveMovie* lmovie = new LoveMovie();
            lmovie->inputMovieInfo();
            system("cls");
            lmovie->displayInfo();
            green(L"══[Xác nhận thêm phim (Y/N) / (y/n)?]==> ");
            wchar_t c;
            wcin >> c;
            c = towlower(c);
            if (c == 'y') {
                movies.push_back(lmovie);
            }
            break;
            // movies.push_back(lmovie);
            break;
        }
        case 2: {
            typeMovie = L"Hoạt hình";
            AnimatedMovie* amovie = new AnimatedMovie();
            amovie->inputMovieInfo();
            system("cls");
            amovie->displayInfo();
            green(L"══[Xác nhận thêm phim (Y/N) / (y/n)?]==> ");
            wchar_t c;
            wcin >> c;
            c = towlower(c);
            if (c == 'y') {
                movies.push_back(amovie);
            }
            break;
        }

        case 3: {
            typeMovie = L"Hành động";
            ActionMovie* amovie = new ActionMovie();
            amovie->inputMovieInfo();
            system("cls");
            amovie->displayInfo();
            green(L"══[Xác nhận thêm phim (Y/N) / (y/n)?]==> ");
            wchar_t c;
            wcin >> c;
            c = towlower(c);
            if (c == 'y') {
                movies.push_back(amovie);
            }
            break;
        }

        case 4: {
            typeMovie = L"Kinh dị";
            HorrorMovie* hmovie = new HorrorMovie();
            hmovie->inputMovieInfo();
            system("cls");
            hmovie->displayInfo();
            green(L"══[Xác nhận thêm phim (Y/N) / (y/n)?]==> ");
            wchar_t c;
            wcin >> c;
            c = towlower(c);
            if (c == 'y') {
                movies.push_back(hmovie);
            }
            break;
        }


        case 0:
            system("cls"); 
            break;
        default:
            red(L"Lựa chọn không hợp lệ. Vui lòng thử lại.");
            break;
    }
}

void MovieList::deleteMovie(int id) {

    green(L"═════[Xác nhận xóa phim? (Y/N) hoặc (y/n)]==> ");    
    wchar_t c;
    wcin >> c;
    c = towlower(c);
    if (c != 'y') {
        wcout << L"\033[92m[Đã hủy xóa phim]\033[0m" << endl;
        Sleep(1000);
        return;
    }

    
    wcout << L"\033[92m[Đang xóa phim...]\033[0m" << endl;

    movies.erase(remove_if(movies.begin(), movies.end(), [id](Movie* movie) {
        return movie->getId() == id;
    }), movies.end());

    green(L"══[Đã xóa phim thành công]══.\n");
    Sleep(1000);
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

vector<vector<wstring>> MovieList::displayMovies() const {
    vector<vector<wstring>> table;
    drawTable({
        {L"                                   DANH SÁCH PHIM                                "}
    });
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

    return table;
}

vector<vector<wstring>> MovieList::displayMoviesByGenre() const
{
    drawTable({
        {L"  THỂ LOẠI PHIM  "},
        {L"1. Tình cảm"},
        {L"2. Hoạt hình"},
        {L"3. Hành động"},
        {L"4. Kinh dị"},
        {L"0. Quay lại"}
    });

    int choice;

    checkInput(L"Nhập lựa chọn", choice);
    if(choice == 0){
        system("cls");
        return {};
    }
    vector<vector<wstring>> table;
    drawTable({
        {L"                                   DANH SÁCH PHIM                                "}
    });

    table.push_back({L"ID", L"Tên phim", L"Thời lượng", L"Phụ đề", L"Quốc gia",L"Độ tuổi", L"Đặc điểm riêng", L"Mô tả"});

    
    
    for (const auto& movie : movies) {

        if (choice == 1 && dynamic_cast<LoveMovie*>(movie)) {
            vector<wstring> row;    
            row.push_back(to_wstring(movie->getId()));
            row.push_back(movie->getName());
            row.push_back(to_wstring(movie->getDuration()));
            row.push_back(movie->getSubTitle());
            row.push_back(movie->getCountry());
            row.push_back(to_wstring(movie->getLimitAge()));
            row.push_back(dynamic_cast<LoveMovie*>(movie)->getRomantic());
            row.push_back(movie->getDescription());
            table.push_back(row);
        } else if (choice == 2 && dynamic_cast<AnimatedMovie*>(movie)) {
            vector<wstring> row;    
            row.push_back(to_wstring(movie->getId()));
            row.push_back(movie->getName());
            row.push_back(to_wstring(movie->getDuration()));
            row.push_back(movie->getSubTitle());
            row.push_back(movie->getCountry());
            row.push_back(to_wstring(movie->getLimitAge()));
            row.push_back(dynamic_cast<AnimatedMovie*>(movie)->getAnimation());
                row.push_back(movie->getDescription());
            table.push_back(row);
        } else if (choice == 3 && dynamic_cast<ActionMovie*>(movie)) {
            vector<wstring> row;    
            row.push_back(to_wstring(movie->getId()));
            row.push_back(movie->getName());
            row.push_back(to_wstring(movie->getDuration()));
            row.push_back(movie->getSubTitle());
            row.push_back(movie->getCountry());
            row.push_back(to_wstring(movie->getLimitAge()));
            row.push_back(dynamic_cast<ActionMovie*>(movie)->getActionLevel());
                row.push_back(movie->getDescription());
            table.push_back(row);
        } else if (choice == 4 && dynamic_cast<HorrorMovie*>(movie)) {
            vector<wstring> row;    
            row.push_back(to_wstring(movie->getId()));
            row.push_back(movie->getName());
            row.push_back(to_wstring(movie->getDuration()));
            row.push_back(movie->getSubTitle());
            row.push_back(movie->getCountry());
            row.push_back(to_wstring(movie->getLimitAge()));
            row.push_back(dynamic_cast<HorrorMovie*>(movie)->getHorrorLevel());
            row.push_back(movie->getDescription());
            table.push_back(row);
        }

    }

    wcout << L"\n\n";
    drawTable(table);

    return table;
}

vector<vector<wstring>> MovieList::displayMoviesByCountry() const
{   
    auto toLower = [](const wstring &str) -> wstring {
        wstring result;
        for (wchar_t ch : str) {
            result += std::towlower(ch);
        }
        return result;
    };


    wcin.ignore();
    wstring country;
    // checkInput(L"Nhập quốc gia", country);
    red(L"Nhập 0: để quay lại\n");

inputCountry:
    wcout << L"\033[92mNhập quốc gia: \033[0m";

    getline(wcin, country);

    if(country == L"0"){
        system("cls");
        return {};
    }

    else if(country == L"\n"){
        goto inputCountry;
    }

    


    vector<vector<wstring>> table;
     drawTable({
        {L"                                   DANH SÁCH PHIM                                "}
    });
    table.push_back({L"ID", L"Tên phim", L"Thời lượng", L"Phụ đề", L"Quốc gia",L"Độ tuổi", L"Đặc điểm riêng", L"Mô tả"});

    for (const auto& movie : movies) {
        if (toLower(movie->getCountry()) == toLower(country)) {
            vector<wstring> row;
            row.push_back(to_wstring(movie->getId()));
            row.push_back(movie->getName());
            row.push_back(to_wstring(movie->getDuration()));
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
    }

    wcout << L"\n\n";
    drawTable(table);

    return table;
}

vector<vector<wstring>> MovieList::displayMoviesByLimitAge() const
{
    int age;
    red(L"Nhập 0: để quay lại\n");
    checkInput(L"Nhập độ tuổi bắt đầu", age);

    if(age == 0){
        system("cls");
        return {};
    }

    vector<vector<wstring>> table;
     drawTable({
        {L"                                   DANH SÁCH PHIM                                "}
    });
    table.push_back({L"ID", L"Tên phim", L"Thời lượng", L"Phụ đề", L"Quốc gia",L"Độ tuổi", L"Đặc điểm riêng", L"Mô tả"});

    for (const auto& movie : movies) {
        if (movie->getLimitAge() >= age) {
            vector<wstring> row;
            row.push_back(to_wstring(movie->getId()));
            row.push_back(movie->getName());
            row.push_back(to_wstring(movie->getDuration()));
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
    }

    wcout << L"\n\n";
    drawTable(table);

    return table;
}

void MovieList::searchMovie(const wstring& name) {
    vector<vector<wstring>> table;
     // Hàm lambda để chuyển đổi chuỗi sang chữ thường
    auto toLower = [](const wstring &str) -> wstring {
        wstring result;
        for (wchar_t ch : str) {
            result += std::towlower(ch);
        }
        return result;
    };



    drawTable({
        {L"                                   KẾT QUẢ TÌM KIẾM                                "}
    });
    table.push_back({L"ID", L"Tên phim", L"Thời lượng", L"Phụ đề", L"Quốc gia",L"Độ tuổi", L"Đặc điểm riêng", L"Mô tả"});
    for (const auto& movie : movies) {
        if (toLower(movie->getName()).find(toLower(name)) != wstring::npos) {
            vector<wstring> row;
            row.push_back(to_wstring(movie->getId()));
            row.push_back(movie->getName());
            row.push_back(to_wstring(movie->getDuration()));
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
    }
    wcout << L"\n\n";
    drawTable(table);
}


Movie* MovieList::findMovieByName(const wstring& name){
     // Hàm lambda để chuyển đổi chuỗi sang chữ thường
    auto toLower = [](const wstring &str) -> wstring {
        wstring result;
        for (wchar_t ch : str) {
            result += std::towlower(ch);
        }
        return result;
    };

    auto it = find_if(movies.begin(), movies.end(), [toLower, name](Movie* movie) {
        return toLower(movie->getName()).find(toLower(name)) != std::wstring::npos;
    });
    if (it != movies.end()) {
        return *it;
    }

    return nullptr;
}

Movie* MovieList::findMovieByID(int id){
    auto it = find_if(movies.begin(), movies.end(), [id](Movie* movie) {
        return movie->getId() == id;
    });
    if (it != movies.end()) {
        return *it;
    }
    return nullptr;
}

Movie *MovieList::findMovieAll(const wstring &search, int &start)
{       
    auto toLower = [](const wstring &str) -> wstring {
        wstring result;
        for (wchar_t ch : str) {
            result += std::towlower(ch);
        }
        return result;
    };

    auto it = find_if(movies.begin() + start, movies.end(), [search, toLower](Movie *movie) {
        return toLower(movie->getName()).find(toLower(search)) != wstring::npos || to_wstring(movie->getId()) == search;
    });
    if (it != movies.end())
    {   
        start = distance(movies.begin(), it);
        return *it;
    }

    return nullptr;
}
void MovieList::searchMovieByID(int id) {
    auto it = find_if(movies.begin(), movies.end(), [id](Movie* movie) {
        return movie->getId() == id;
    });

    if (it == movies.end()) {
        wcout << L"\033[92m[Phim không tồn tại] \033[0m" << endl;
        return;
    }

    vector<vector<wstring>> table;
    drawTable({
        {L"                                   KẾT QUẢ TÌM KIẾM                                "}
    });
    table.push_back({L"ID", L"Tên phim", L"Thời lượng", L"Phụ đề", L"Quốc gia",L"Độ tuổi", L"Đặc điểm riêng", L"Mô tả"});
    vector<wstring> row;
    row.push_back(to_wstring((*it)->getId()));
    row.push_back((*it)->getName());
    row.push_back(to_wstring((*it)->getDuration()));
    row.push_back((*it)->getSubTitle());
    row.push_back((*it)->getCountry());
    row.push_back(to_wstring((*it)->getLimitAge()));

    if (dynamic_cast<LoveMovie*>(*it)) {
        row.push_back(dynamic_cast<LoveMovie*>(*it)->getRomantic());
    } else if (dynamic_cast<AnimatedMovie*>(*it)) {
        row.push_back(dynamic_cast<AnimatedMovie*>(*it)->getAnimation());
    } else if (dynamic_cast<ActionMovie*>(*it)) {
        row.push_back(dynamic_cast<ActionMovie*>(*it)->getActionLevel());
    } else if (dynamic_cast<HorrorMovie*>(*it)) {
        row.push_back(dynamic_cast<HorrorMovie*>(*it)->getHorrorLevel());
    } else {
        row.push_back(L"");
    }

    row.push_back((*it)->getDescription());
    table.push_back(row);
    wcout << L"\n\n";
    drawTable(table);
}

void MovieList::interactWithMovie(int id){
    int choice;
    do {
        system("cls");
        displayMovieInfo(id);
        vector<vector<wstring>> table;
        wcout << L"\033[0m";
        table.push_back({L"1. Đổi thông tin phim"});
        table.push_back({L"2. Xóa phim"});
        table.push_back({L"0. Quay lại"});
        drawTable(table);
        checkInput(L"Lựa chọn của bạn", choice);
        wcin.ignore();
        system("cls");
        switch (choice) {
            case 1:
                system("cls");
                updateMovie(id);
                break;
            case 2:
                system("cls");
                deleteMovie(id);
                green(L"Xóa phim thành công.\n");
                break;
            case 0:
                system("cls");
                break;
            default:
                red(L"Lựa chọn không hợp lệ, vui lòng thử lại.");
                wcout << endl;
        }
    } while (choice != 0 && choice !=2);
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
        file << L"ID,Tên,Loại, Thời lượng, Phụ đề, Quốc gia, Độ tuổi, Đặc điểm riêng, Mô tả\n";
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

void MovieList::loadFromCSV(const string& filename = "../DATA/movies.csv") {
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