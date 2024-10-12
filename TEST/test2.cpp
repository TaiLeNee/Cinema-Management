#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <io.h>
#include <fcntl.h>

using namespace std;

vector<wstring> splitStringByWords(const wstring& str, size_t width) {
    vector<wstring> result;
    wistringstream words(str);
    wstring word;
    wstring line;

    while (words >> word) {
        if (line.length() + word.length() + 1 > width) {
            result.push_back(line);
            line = word;
        } else {
            if (!line.empty()) {
                line += L" ";
            }
            line += word;
        }
    }
    if (!line.empty()) {
        result.push_back(line);
    }

    return result;
}


vector<wstring> splitString(const wstring& str, size_t width) {
    vector<wstring> result;
    size_t start = 0;
    while (start < str.length()) {
        result.push_back(str.substr(start, width));
        start += width;
    }
    return result;
}


int main(){
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);

    wstring str = L"Hello world! This is a test string.";
    vector<wstring> words = splitStringByWords(str, 15);
     wcout << words[1] <<endl;
    wcout << "-------------------" << endl;
    for (const auto& word : words) {
        wcout << word << endl;
    }
    wcout << "-------------------" << endl;

    vector<wstring> words2 = splitString(str, 15);
    wcout << words2[2] <<endl;
    wcout << "-------------------" << endl;
    for (const auto& word : words2) {
        wcout << word << endl;
    }
    return 0;


}