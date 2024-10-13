#include "MovieList.cpp"
#include "Room.cpp"
using namespace std;

string filename = "../DATA/movies.csv";


int main() {
    //thiết lập chế độ Unicode cho console
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);

    MovieList movieList;

    movieList.loadFromCSV(filename);

    movieList.displayMovies();

    const int numRows = 4;           // Số hàng ghế
    const int numChairsPerRow = 10;  // Số ghế trong mỗi hàng
    

    Room room;
    room.addChairs(numRows, numChairsPerRow);
    room.changeStatusChair(105, true);
    room.changeStatusChair(110, true);
    room.changeStatusChair(403, true);

    printChairs(room.getChairs(), numRows, numChairsPerRow);

    return 0;
}