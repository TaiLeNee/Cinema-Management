#include <cstdlib>
#include <iostream>
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