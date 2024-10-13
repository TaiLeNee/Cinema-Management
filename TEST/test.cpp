#include <iostream>
#include <fstream>
#include <locale>
#include <codecvt>
#include <string>
#include <fcntl.h> // for O_RDONLY , _O_U16TEXT
#include <io.h> // for _setmode

using namespace std;

int main() {
    locale  loc(locale(), new codecvt_utf8<wchar_t>);   //UTF-8

    _setmode(_fileno(stdout), _O_U8TEXT);
    _setmode(_fileno(stdin), _O_U8TEXT);

    wcout<<L"Xin chào mọi người nhé"<<endl;
    wstring text;

    //read file

    wifstream file(L"output.txt");
    file.imbue(loc);
    getline(file, text);
    wcout<<text<<endl;
    file.close();

    //write file
    wofstream fileout(L"output.txt", ios_base::app);
    fileout.imbue(loc);
    fileout<<L"Đây là dòng thứ 2 nè nha"<<endl;
    fileout.close();

    return 0;
}