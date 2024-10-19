#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <locale>
#include <codecvt>
#include <fstream>
#include <fcntl.h>
#include <io.h>


using namespace std;

void split(const wstring& str, wchar_t delimiter, vector<wstring>& out) {
    wstringstream ss(str);
    wstring item;
    while (getline(ss, item, delimiter)) {
        out.push_back(item);
    }
}

void parseDateTime(const wstring& datetime, wstring& hour, wstring& minute, wstring& day, wstring& month, wstring& year) {
    // Tách phần thời gian và phần ngày tháng
    vector<wstring> parts;
    split(datetime, L' ', parts);

    if (parts.size() != 2) {
        throw invalid_argument("Invalid datetime format");
    }

    wstring timePart = parts[0];
    wstring datePart = parts[1];

    // Tách giờ và phút
    vector<wstring> timeParts;
    split(timePart, L':', timeParts);

    if (timeParts.size() != 2) {
        throw invalid_argument("Invalid time format");
    }

    hour = timeParts[0];
    minute = timeParts[1];

    // Tách ngày, tháng, năm
    vector<wstring> dateParts;
    split(datePart, L'/', dateParts);

    if (dateParts.size() != 3) {
        throw invalid_argument("Format date is not correct");
    }

    day = dateParts[0];
    month = dateParts[1];
    year = dateParts[2];
}

int main() {
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);

    wifstream file(L"../DATA/showtimes.csv");
    file.imbue(locale(locale(), new codecvt_utf8<wchar_t>));

    if (!file.is_open()) {
        wcout << L"Không thể mở file showtimes.csv" << endl;
        return 1;
    }

    wstring line;
    getline(file, line); // Bỏ qua dòng tiêu đề
    while(getline(file, line)){
        wcout << L"===========" <<endl;
         wstring datetime;
        wstring ID, movieID, roomID;
        wstringstream ss;
        ss.str(line);
        getline(ss, ID, L',');
        getline(ss, movieID, L',');
        getline(ss, roomID, L',');
        getline(ss, datetime);
        ss.clear();
        wcout << L"Showtime ID: " << ID << endl;
        wcout << L"Movie ID: " << movieID << endl;
        wcout << L"Room ID: " << roomID << endl;
        wcout << L"DateTime: " << datetime << endl;
        

        wstring hour, minute, day, month, year;

        try {
            parseDateTime(datetime, hour, minute, day, month, year);

            // Hiển thị kết quả
            wcout << L"Hour: " << hour << endl;
            wcout << L"Minute: " << minute << endl;
            wcout << L"Day: " << day << endl;
            wcout << L"Month: " << month << endl;
            wcout << L"Year: " << year << endl;
        } catch (const invalid_argument& e) {
            wcerr << e.what() << endl;
        }
    }
        file.close();
        return 0;
}