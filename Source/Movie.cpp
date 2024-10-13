#include "../Header/Movie.h"
#include <iostream>
#include <io.h>
#include <fcntl.h>
#include <iomanip> // for setw
#include <string>

using namespace std;

// Thiết lập chế độ Unicode cho console


Movie::Movie( const wstring& name, const wstring& genre, int duration, const wstring& description)
    : name(name), genre(genre), duration(duration), description(description) {}

Movie::Movie(int id, const wstring& name, const wstring& genre, int duration, const wstring& description)
    : id(id), name(name), genre(genre), duration(duration), description(description) {}


void Movie::displayInfo() const {


    wcout << L"+--------------------------------------------------+" << endl;
    wcout << L"|                    Thông Tin Phim                |" << endl;
    wcout << L"+-----------------+--------------------------------+" << endl;
    wcout << L"| Tên             | " << setw(30) << name.c_str() << L" |" << endl;
    wcout << L"+-----------------+--------------------------------+" << endl;
    wcout << L"| Thể loại        | " << setw(30) << genre.c_str() << L" |" << endl;
    wcout << L"+-----------------+--------------------------------+" << endl;
    wcout << L"| Thời lượng      | " << setw(25) << duration << L" phút |" << endl;
    wcout << L"+-----------------+--------------------------------+" << endl;
    wcout << L"| Mô tả           | " << setw(30) << description.c_str() << L" |" << endl;
    wcout << L"+--------------------------------------------------+" << endl;
}

void Movie::deleteInfo() {
    name = L"";
    genre = L"";
    duration = 0;
    description = L"";
}



void Movie::editInfo() {
    int choice;
    wstring newName, newGenre, newDescription;
    int newDuration;

    do {
        // Hiển thị thông tin phim trước khi chỉnh sửa
        displayInfo();

        // Hiển thị menu chỉnh sửa
        wcout << L"+----------------------------------------+" << endl;
        wcout << L"|           Chọn thông tin chỉnh sửa     |" << endl;
        wcout << L"+-----------------+----------------------+" << endl;
        wcout << L"| 1. Tên                                 |" << endl;
        wcout << L"| 2. Thể loại                            |" << endl;
        wcout << L"| 3. Thời lượng                          |" << endl;
        wcout << L"| 4. Mô tả                               |" << endl;
        wcout << L"| 5. Thoát                               |" << endl;
        wcout << L"+-----------------+----------------------+" << endl;
        wcout << L"Lựa chọn của bạn: ";
        // Kiểm tra đầu vào của người dùng
        bool validInput = false;
        while (!validInput) {
            wcout << L"Lựa chọn của bạn: ";
            wcin >> choice;

            if (wcin.fail()) {
                wcin.clear(); // Xóa trạng thái lỗi
                wcin.ignore(1e4, '\n'); // Xóa bộ nhớ đệm
                wcout << L"Lựa chọn không hợp lệ. Vui lòng nhập lại." << endl;
            } else {
                validInput = true;
                wcin.ignore();
            }
        }

        switch (choice) {
            case 1:
                wcout << L"Nhập tên mới: ";
                wcin.ignore();
                getline(wcin, newName);
                name = newName;
                break;
            case 2:
                wcout << L"Nhập thể loại mới: ";
                wcin.ignore();
                getline(wcin, newGenre);
                genre = newGenre;
                break;
            case 3:
                wcout << L"Nhập thời lượng mới: ";
                wcin >> newDuration;
                duration = newDuration;
                break;
            case 4:
                wcout << L"Nhập mô tả mới: ";
                wcin.ignore();
                getline(wcin, newDescription);
                description = newDescription;
                break;
            case 5:
                wcout << L"Thoát chỉnh sửa." << endl;
                break;
            default:
                wcout << L"Lựa chọn không hợp lệ. Vui lòng chọn lại." << endl;
        }
    } while (choice != 5);
}

void Movie::setId(int id) {
    this->id = id;
}   

int Movie::getId() const {
    return id;
}

wstring Movie::getName() const {
    return name;
}

wstring Movie::getGenre() const {
    return genre;
}

int Movie::getDuration() const {
    return duration;
}

wstring Movie::getDescription() const {
    return description;
}