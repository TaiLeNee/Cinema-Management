#include <iostream>
#include <windows.h>
#include <io.h>
#include <fcntl.h>
using namespace std;
void countdown(int duration) {

    for (int i = 1; i <= duration; i++) {
        wcout << L"\rĐang xác nhận: " << i << L" giây";
        wcout<<flush;
        Sleep(1000);
    }
    Sleep(1000);
}


int main() {
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);
    int seconds;
   
    countdown(3);
    return 0;
}