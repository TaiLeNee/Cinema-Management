#include "../Header/Menu.h"

using namespace std;
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
    wcout << L"║                  ";yellow(L"MENU");wcout<<L"                      ║" << endl;
    wcout << L"╠════════════════════════════════════════════╣" << endl;
    wcout << L"║ ";yellow(L"1. Hiện thị danh sách Movie");wcout<<L"                ║" << endl;
    wcout << L"║ ";yellow(L"2. Hiện thị danh sách Movie");wcout<<L"                ║" << endl;
    wcout << L"║ ";yellow(L"3. Hiện thị danh sách Movie");wcout<<L"                ║" << endl;
    wcout << L"║ ";yellow(L"4. Hiện thị danh sách Movie");wcout<<L"                ║" << endl;
    wcout << L"║ ";yellow(L"5. Hiện thị danh sách Movie");wcout<<L"                ║" << endl;  
    wcout << L"╚════════════════════════════════════════════╝" << endl;
    wcout << L"Enter your choice: ";
}