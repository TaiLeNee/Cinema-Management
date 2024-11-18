#include "../Header/Menu.h"

void menuEdit(MovieList &movieList, Movie* &movie)
{
    int choice;
    do
    {
        system("cls");
        vector<vector<wstring>> table;

        
        movie->displayInfo();

        table.push_back({L"    MENU CHỈNH SỬA PHIM    "});
        table.push_back({L"1. Chỉnh sửa thông tin phim"});
        table.push_back({L"2. Xóa phim"});
        table.push_back({L"0. Quay lại"});
        drawTable(table);
        checkInput(L"Lựa chọn của bạn", choice);
        system("cls");
        switch (choice)
        {
        case 1:
            movie->editInfo();
            break;
        case 2:
            movie->displayInfo();
            movieList.deleteMovie(movie->getId());
            movieList.saveToCSV("../DATA/movies.csv");
            return;
        case 0:
            break;
        default:
            red(L"Lựa chọn không hợp lệ, vui lòng thử lại.");
            break;
        }
        movieList.saveToCSV("../DATA/movies.csv");
    } while (choice != 0);
}


Movie* selectMovie(MovieList &movieList, vector<vector<wstring>> &tableMovie)
{
    int choiceMovie;
    red(L"Nhập 0: quay lại.\n");
    checkInput(L"Nhập ID phim cần tương tác", choiceMovie);
    
    if (!choiceMovie)
    {
        system("cls");
        return nullptr;
    }

    auto it = find_if(tableMovie.begin()+1, tableMovie.end(), [choiceMovie](vector<wstring> movie){
        return stoi(movie[0]) == choiceMovie;
    });

    if(it == tableMovie.end()){
        red(L"Không tìm thấy phim có ID = " + to_wstring(choiceMovie) + L"\n");
        return nullptr;
    }

    Movie* movie = movieList.findMovieByID(choiceMovie);

    return movie;

}

void manageMovie(MovieList &movieList)
{
    vector<vector<wstring>> table;
    table.push_back({L"        QUẢN LÝ PHIM            "});
    table.push_back({L"        1. Hiển thị danh sách phim            "});
    table.push_back({L"        2. Tìm kiếm phim            "});
    table.push_back({L"        3. Thêm Phim            "});
    table.push_back({L"        0. Thoát            "});

menuMovie:
    system("cls");
    drawTable(table);

    int choice;
    checkInput(L"Nhập lựa chọn", choice);

    if (!choice)
    {
        system("cls");
        return;
    }

    vector<vector<wstring>> tableMovie;

    switch (choice)
    {
    case 1:{
    displayMovie:
        system("cls");
        drawTable({
            {L"1. Hiển thị tất cả phim"},
            {L"2. Hiển thị phim theo thể loại"},
            {L"3. Hiển thị phim theo quốc gia"},
            {L"4. Hiển thị phim theo độ tuổi"},
            {L"0. Quay lại"}
        });

        int choiceMovie;
        checkInput(L"Nhập lựa chọn", choiceMovie);
        system("cls");

        switch (choiceMovie)
        {
            case 1:{
                tableMovie = movieList.displayMovies();
                Movie* movie = selectMovie(movieList, tableMovie);
                if(movie){
                    menuEdit(movieList, movie);
                }

                goto displayMovie;
            }
            case 2:{
                tableMovie = movieList.displayMoviesByGenre();
                Movie* movie = selectMovie(movieList, tableMovie);
                if(movie){
                    menuEdit(movieList, movie);
                }

                goto displayMovie;
            }
            case 3:{
                tableMovie = movieList.displayMoviesByCountry();
                Movie* movie = selectMovie(movieList, tableMovie);
                if(movie){
                    menuEdit(movieList, movie);
                }

                goto displayMovie;
            }
            case 4:{
                tableMovie = movieList.displayMoviesByLimitAge();
                Movie* movie = selectMovie(movieList, tableMovie);
                if(movie){
                    menuEdit(movieList, movie);
                }

                goto displayMovie;

            }
            case 0:
                break;
            default:
                red(L"Lựa chọn không hợp lệ. Vui lòng thử lại.");
                goto displayMovie;
        }
        break;
    }

    case 2:
    {   vector<vector<wstring>> tableMovieSearch;
        tableMovieSearch.push_back({L"ID", L"Tên phim", L"Thời lượng", L"Phụ đề", L"Quốc gia",L"Độ tuổi", L"Đặc điểm riêng", L"Mô tả"});

        wstring search;
        green(L"═══[Nhập tên phim/ID cần tìm]==> ");
        wcin.ignore();
        getline(wcin, search);
        int start = 0;

        while(1){
            Movie* movie = movieList.findMovieAll(search, start);
            start++;
            if(movie == nullptr){
                break;
            }
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
            tableMovieSearch.push_back(row);
        
        }
        drawTable(tableMovieSearch);
        Movie* movie = selectMovie(movieList, tableMovieSearch);
        if(movie){
            menuEdit(movieList, movie);
        }
        break;
    }

    case 3:
        movieList.addMovie();
        break;
    case 0:
        break;
    default:
        red(L"Lựa chọn không hợp lệ. Vui lòng thử lại.");
    }

    goto menuMovie;
    
}