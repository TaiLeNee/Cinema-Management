#include "../Header/Color.h"


// wstring GREEN = L"\033[92m";
// wstring RED = L"\033[91m";
// wstring L"\033[0m" = END;
// wstring YELLOW = L"\033[93m";

template <typename T>
void green(T text) {
    wcout << L"\033[92m" << text << L"\033[0m";
}

template <typename T>
void red(T text) {
    wcout << L"\033[91m" << text << L"\033[0m";
}

template <typename T>
void yellow(T text) {
    wcout << L"\033[93m" << text << L"\033[0m";
}


// int main() {
//     wstringstream output;
//     output << L"Hello World!";
//     green(output.str());
//     green(123);
//     red(L"Error message");
//     yellow(456);
// }