#include <iostream>
#include <sstream>

using namespace std;

wstring GREEN = L"\033[92m";
wstring RED = L"\033[91m";
wstring END = L"\033[0m";
wstring YELLOW = L"\033[93m";

template <typename T>
void green(T text) {
    wcout << GREEN << text << END;
}

template <typename T>
void red(T text) {
    wcout << RED << text << END;
}

template <typename T>
void yellow(T text) {
    wcout << YELLOW << text << END;
}


// int main() {
//     wstringstream output;
//     output << L"Hello World!";
//     green(output.str());
//     green(123);
//     red(L"Error message");
//     yellow(456);
// }