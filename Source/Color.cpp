#include "../Header/Color.h"


// wstring GREEN = L"\033[92m";
// wstring RED = L"\033[91m";
// wstring L"\033[0m" = END;
// wstring YELLOW = L"\033[93m";

void green(const wstring& text) {
    wcout << L"\033[92m" << text << L"\033[0m";
}

void red(const wstring& text) {
    wcout << L"\033[91m" << text << L"\033[0m";
}

void yellow(const wstring& text) {
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