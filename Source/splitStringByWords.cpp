#include "../Header/splitStringByWords.h"

vector<wstring> splitStringByWords(const wstring& str) {
    size_t width = 35;
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