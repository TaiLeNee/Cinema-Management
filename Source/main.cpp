#include "Color.cpp"
#include "MovieList.cpp"
#include "Room.cpp"
#include <cstdlib>
#include <vector>

using namespace std;

string filename = "../DATA/movies.csv";




void displayMenu() {
    system("cls");
    wcout<<L"\n\n";
    wcout<< L"\033[92m      ██╗    ██╗███████╗██╗      ██████╗ ██████╗ ███╗   ███╗███████╗██╗\n"
          <<L"\033[92m      ██║    ██║██╔════╝██║     ██╔════╝██╔═══██╗████╗ ████║██╔════╝██║\n"
          <<L"\033[92m      ██║ █╗ ██║█████╗  ██║     ██║     ██║   ██║██╔████╔██║█████╗  ██║\n"
          <<L"\033[92m      ██║███╗██║██╔══╝  ██║     ██║     ██║   ██║██║╚██╔╝██║██╔══╝  ╚═╝\n"
          <<L"\033[92m      ╚███╔███╔╝███████╗███████╗╚██████╗╚██████╔╝██║ ╚═╝ ██║███████╗██╗\n"
          <<L"\033[92m     ╚══╝╚══╝ ╚══════╝╚══════╝ ╚═════╝ ╚═════╝ ╚═╝     ╚═╝╚══════╝╚═╝ \n";
    wcout<<L"\033[m";      
                                                                 
    wcout << L"╔════════════════════════════════════════════╗" << endl;
    wcout << L"║                  MENU                      ║" << endl;
    wcout << L"╠════════════════════════════════════════════╣" << endl;
    wcout << L"║ 1. Hiện thị danh sách Movie                ║" << endl;
    wcout << L"║ 2. Add Chairs                              ║" << endl;
    wcout << L"║ 3. Change Chair Status                     ║" << endl;
    wcout << L"║ 4. Display Chairs                          ║" << endl;
    wcout << L"║ 5. Exit                                    ║" << endl;
    wcout << L"╚════════════════════════════════════════════╝" << endl;
    wcout << L"Enter your choice: ";
}

int main() {
    //thiết lập chế độ Unicode cho console
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);

    MovieList movieList;

    movieList.loadFromCSV(filename);

    displayMenu();
    movieList.displayMovies();

    const int numRows = 4;           // Số hàng ghế
    const int numChairsPerRow = 10;  // Số ghế trong mỗi hàng
    

    Room room(1, L"Phòng 1", numRows, numChairsPerRow);
    room.addShowtime(Showtime(1, 1, Datetime(L"2021", L"5", L"20", L"10", L"30"), room.getChairs()));
    // room.addShowtime(Showtime(2, 1, Datetime(2021, 5, 20, 14, 30)));
    
    vector<Showtime>& showtimes = room.getShowtimes();
    for (auto& showtime : showtimes) {
        showtime.displayChairs();
    }
    

    return 0;
}