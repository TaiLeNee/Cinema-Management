#include "../Header/Menu.h"
#include "../Header/RoomList.h"
#include "../Header/MovieList.h"
#include "../Header/globals.h"
#include <fcntl.h>
#include <io.h>
#include <conio.h>
#include <regex>

using namespace std;

void loading(int duration)
{
    const int numDots = 3;
    for (int i = 0; i < duration; ++i)
    {
        system("cls");
        green(L"\rLoading");
        for (int j = 0; j < i % (numDots + 1); ++j)
        {
            green(L".");
        }
        wcout << flush;
        Sleep(500);
    }
    green(L"\rLoading complete!\n");
    Sleep(500);
}

void loginMenu(ListOfEmployee &employeeList, MovieList &movieList, CustomerList &customerList, RoomList &roomList, BookedList &bookedList)
{
    vector<vector<wstring>> table;
    wstring userName, passWord;
    char temp;
    Employee *loggedInUser = nullptr;
    wcout << "\033[0m";

    table.push_back({L"           Đăng nhập "});
    table.push_back({L"   Username:                      "});
    table.push_back({L"   Password:                      "});

login:
    wcout << "\033[?25l";
    int currentField = 0; 
    userName.clear();
    passWord.clear();

    while (true)
    {
        system("cls"); 
        drawTable(table);

        gotoXY(11, 3);
        if (currentField == 0){
            gotoXY(1, 3);
            yellow(L" » ");
        }
        gotoXY(16,3);
        wcout << userName;

        gotoXY(11, 5);
        if (currentField == 1){
            gotoXY(1,5);
            yellow(L" » ");
        }

        gotoXY(16,5);
        for (size_t i = 0; i < passWord.size(); ++i)
            wcout << L'*';

        temp = _getch();

        if (temp == '\r')
        { 
            if (currentField == 1)
                break;        
            currentField = 1; 
        }
        else if (temp == -32)
        { 
            temp = _getch();
            if (temp == 72)
            {
                currentField = (currentField == 0) ? 1 : 0;
            }
            else if (temp == 80)
            { 
                currentField = (currentField == 1) ? 0 : 1;
            }
        }
        else if (temp == '\b')
        { 
            if (currentField == 0 && !userName.empty())
            {
                userName.pop_back();
            }
            else if (currentField == 1 && !passWord.empty())
            {
                passWord.pop_back();
            }
        }
        else if (temp >= 32 && temp <= 126)
        {
            if (currentField == 0)
            {
                userName += temp;
            }
            else if (currentField == 1)
            {
                passWord += temp;
            }
        }
    }
    wcout << "\033[?25h";
    loggedInUser = employeeList.signIn(userName, passWord);
    if (!loggedInUser)
    {
        wcout << L"\n\033[92m\nĐăng nhập thất bại. Vui lòng kiểm tra lại thông tin đăng nhập...\033[0m" << endl;
        Sleep(2000);
        system("cls");
        goto login;
    }
    else
    {
        system("cls");
        loading(4);
        wcout << L"\n\033[92m[Đăng nhập thành công!]\033[0m" << endl;
    } 

    wstring name = loggedInUser->getName();
    loggedin_global = loggedInUser;

    if (loggedInUser->getLevel() == 0)
    {
        employeeIDLogin = loggedInUser->getId();
        wcout << L"\033[92m[Xin chào Owner " << name << L"]\033[0m" << endl;
        Sleep(1000);
        mainMenu(employeeList, movieList, customerList, roomList, bookedList, loggedInUser);
    }
    else if (loggedInUser->getLevel() == 1)
    {
        employeeIDLogin = loggedInUser->getId();
        wcout << L"\033[92m[Xin chào Admin " << name << L"]\033[0m" << endl;
        Sleep(1000);
        mainMenu(employeeList, movieList, customerList, roomList, bookedList, loggedInUser);
    }
    else
    {
        employeeIDLogin = loggedInUser->getId();
        wcout << L"\033[92m[Xin chào nhân viên " << name << L"]\033[0m" << endl;
        Sleep(1000);
        mainMenu(employeeList, movieList, customerList, roomList, bookedList, loggedInUser);
    }
}

int main()
{
    // thiết lập chế độ Unicode cho console
    system("cls");
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);

    // Khởi tạo
    RoomList roomList;
    MovieList movieList;
    roomList.loadRoom();
    movieList.loadFromCSV("../DATA/movies.csv");

    // Load lại danh sách showtime
    for (auto room : roomList.getRooms())
    {
        movieList.loadShowtimesofMovie(room.getShowtimes());
    }

    BookedList bookedList;
    // bookedList.loadChairbookedFromCSV("../DATA/payments.csv");

    ListOfEmployee employeeList;
    employeeList.loadEmployees("../DATA/employee.csv");
    CustomerList customerList;
    customerList.loadFromCSV("../DATA/customers.csv");
    customerList_gb = &customerList; // đặt con trỏ global trỏ đến customerList
    /*======================================*/

    loginMenu(employeeList, movieList, customerList, roomList, bookedList);

    return 0;
}