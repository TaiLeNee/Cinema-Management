#include "../Header/Menu.h"
#include "../Header/RoomList.h"
#include "../Header/MovieList.h"
#include <fcntl.h>
#include <io.h>

#include <regex>


using namespace std;



void loginMenu(ListOfEmployee &employeeList , MovieList &movieList, CustomerList &customerList, RoomList &roomList){
    vector<vector<wstring>> table;
    wstring userName, passWord;
    Employee *loggedInUser = nullptr;
    do{
        // system("cls");
        table.push_back({L"         Đăng nhập "});
        table.push_back({L"Username:                  "});
        table.push_back({L"Password:                  "});
        drawTable(table);
        gotoXY(13, 3);
        getline(wcin, userName);
        gotoXY(13, 5);
        getline(wcin, passWord);
        loggedInUser = employeeList.signIn(userName, passWord);
        if (!loggedInUser) {
            wcout << L"Đăng nhập thất bại. Vui lòng kiểm tra lại thông tin đăng nhập." << endl;
        }
        else{
            system("cls");
            wcout << L"\nĐăng nhập thành công!" << endl;
            break;
        }
    }while(!loggedInUser);

    wstring name;
    name = loggedInUser->getName();
    if (loggedInUser->getLevel() == 0) {
        wcout << L"\033[92m[Xin chào OWNER "<< name <<"]\033[0m"<< endl;
        mainMenu(employeeList, movieList, customerList, roomList, 0);
    }
    else if (loggedInUser->getLevel() == 1) {
        wcout << L"\033[92m[Xin chào ADMIN " << name <<"]\033[0m"<< endl;
        mainMenu(employeeList, movieList, customerList, roomList, 1);

    } 
    else {
        wcout << L"Xin chào Nhân Viên " << name << endl;
        mainMenu(employeeList, movieList, customerList, roomList, loggedInUser->getLevel());

    }
}


int main() {
    //thiết lập chế độ Unicode cho console
    system("cls");
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);

    //Khởi tạo
    RoomList roomList;
    roomList.loadRoom();

    vector<Room> rooms = roomList.getRooms();
    
    MovieList movieList;

    for(auto& room: rooms){
        vector<Showtime> showtimes = room.getShowtimes();
        movieList.loadShowtimesofMovie(showtimes);

    }
    
    ListOfEmployee employeeList;
    CustomerList customerList;
    employeeList.loadEmployees("../DATA/employee.csv");
    movieList.loadFromCSV("../DATA/movies.csv");
    /*======================================*/


    loginMenu(employeeList, movieList, customerList, roomList);
    
   
    return 0;
}