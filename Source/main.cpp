#include "../Header/Menu.h"
#include "../Header/RoomList.h"
#include "../Header/MovieList.h"
#include "../Header/globals.h"
#include <fcntl.h>
#include <io.h>

#include <regex>


using namespace std;



void loading(int duration) {
    const int numDots = 3;
    for (int i = 0; i < duration; ++i) {
        system("cls");
        green(L"\rLoading");
        for (int j = 0; j < i % (numDots + 1); ++j) {
            green(L".");
        }
        wcout<<flush;
        Sleep(500);
    }
    green(L"\rLoading complete!\n" );
    Sleep(500);
}


void loginMenu(ListOfEmployee &employeeList , MovieList &movieList, CustomerList &customerList, RoomList &roomList){
    vector<vector<wstring>> table;
    wstring userName, passWord;
    Employee *loggedInUser = nullptr;
    wcout << "\033[0m";
    table.push_back({L"         Đăng nhập "});
    table.push_back({L"Username:                  "});
    table.push_back({L"Password:                  "});

    login:
        drawTable(table);

        gotoXY(13, 3);
        wcin >> userName;
        gotoXY(13, 5);
        wcin >> passWord;
        loggedInUser = employeeList.signIn(userName, passWord);
        if (!loggedInUser) {
            wcout << L"\n\033[92mĐăng nhập thất bại. Vui lòng kiểm tra lại thông tin đăng nhập...\033[0m" << endl;
            Sleep(2000);
            system("cls");
            goto login;
        }
        else{
            system("cls");
            loading(4);
            wcout << L"\n\033[92m[Đăng nhập thành công!]\033[0m" << endl;
            
        }
    

    wstring name;
    name = loggedInUser->getName();
    if (loggedInUser->getLevel() == 0) {
        employeeIDLogin = loggedInUser->getId();
        wcout << L"\033[92m[Xin chào OWNER "<< name <<"]\033[0m"<< endl;
        Sleep(2000);
        mainMenu(employeeList, movieList, customerList, roomList, loggedInUser);
    }
    else if (loggedInUser->getLevel() == 1) {
        employeeIDLogin = loggedInUser->getId();
        wcout << L"\033[92m[Xin chào ADMIN " << name <<"]\033[0m"<< endl;
        Sleep(2000);
        mainMenu(employeeList, movieList, customerList, roomList, loggedInUser);

    } 
    else {
        employeeIDLogin = loggedInUser->getId();
        wcout << L"\033[92m[Xin chào Nhân Viên " << name <<"]\033[0m"<< endl;
        Sleep(2000);
        mainMenu(employeeList, movieList, customerList, roomList, loggedInUser);
    }
}


int main() {
    //thiết lập chế độ Unicode cho console
    system("cls");
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);

    //Khởi tạo
    RoomList roomList;
    MovieList movieList;
    roomList.loadRoom();
    movieList.loadFromCSV("../DATA/movies.csv");
    
    //Load lại danh sách showtime
    for(auto room: roomList.getRooms()){
        movieList.loadShowtimesofMovie(room.getShowtimes());
    }

    // BookedList bookedList;
    // bookedList.loadChairbookedFromCSV("../DATA/chairbooked.csv");
    
    ListOfEmployee employeeList;
    CustomerList customerList;
    employeeList.loadEmployees("../DATA/employee.csv");
    /*======================================*/


    loginMenu(employeeList, movieList, customerList, roomList);
    
   
    return 0;
}