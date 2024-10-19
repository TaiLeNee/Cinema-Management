#include "Color.cpp"
#include "MovieList.cpp"
#include "RoomList.cpp" //Có vector<Room> rooms
#include <fcntl.h>
#include <io.h>
#include "menu.cpp"

using namespace std;

string filename = "../DATA/movies.csv";


int main() {
    //thiết lập chế độ Unicode cho console
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);

    // displayMenu();

    loadRoom();

    
    MovieList movieList;

    movieList.displayMovies();

    for(auto& room: rooms){
        vector<Showtime> showtimes = room.getShowtimes();
        movieList.loadShowtimesofMovie(showtimes);

    }
    movieList.getMovies()[0].displayShowtimes();

    
 


    return 0;
}