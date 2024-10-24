#include "../Header/Menu.h"
#include "../Header/RoomList.h"
#include "../Header/MovieList.h"
#include <fcntl.h>
#include <io.h>


using namespace std;




int main() {
    //thiết lập chế độ Unicode cho console
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);

    mainMenu();

    RoomList roomList;
    roomList.loadRoom();

    vector<Room> rooms = roomList.getRooms();
    
    MovieList movieList;

    movieList.displayMovies();

    for(auto& room: rooms){
        vector<Showtime> showtimes = room.getShowtimes();
        movieList.loadShowtimesofMovie(showtimes);

    }
    movieList.getMovies()[0]->displayShowtimes();

    
 


    return 0;
}