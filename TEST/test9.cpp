#include <iostream>
#include <string>
#include <locale>
#include <cwctype>
#include <fcntl.h>
#include <io.h>

using namespace std;

wstring toLower(const wstring& str) {
    wstring result;
    for (wchar_t ch : str) {
        result += std::towlower(ch);
    }
    return result;
}

int main() {
    // Đặt chế độ đầu ra và đầu vào của terminal thành UTF-16
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);

    wstring str = L"Xin ChÀo";
    wcout << toLower(str) << endl;

    return 0;
}