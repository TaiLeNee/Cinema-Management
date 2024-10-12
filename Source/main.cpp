#include "MovieList.cpp"
using namespace std;


int main() {
    //thiết lập chế độ Unicode cho console
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);

    Movie movie1(L"Inception", L"Sci-Fi", 148, L"A mind-bending thriller");
    movie1.setId(1);    
    addMovie(movie1);

    Movie movie2(L"Lật mặt", L"Sci-Fi", 136, L"A computer hacker learns about the true nature of reality");
    movie2.setId(2);
    addMovie(movie2);

    displayMovies();

    return 0;
}