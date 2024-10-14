#include <iostream>
#include <io.h>
#include <fcntl.h>
#include "../Header/Datetime.h"
#include <iomanip> // for setw
#include <string>
#include <conio.h>

using namespace std;

Datetime::Datetime()
    : hour(0), minute(0), day(0), month(0), year(0) {
        wcout << L"+----------------------------------------+" << endl;
        wcout << L"|             Giờ chiếu phim             |" << endl;
        wcout << L"+-----------------+----------------------+" << endl;
        wcout << L"| Ngày       |"; wcin >> day; wcout << L"            |" << endl;
        wcout << L"| 2. Thể loại                            |" << endl;
        wcout << L"| 3. Thời lượng                          |" << endl;
        wcout << L"| 4. Mô tả                               |" << endl;
        wcout << L"| 5. Thoát                               |" << endl;
        wcout << L"+-----------------+----------------------+" << endl;
    }

Datetime::Datetime(const wstring& hour, const wstring& minute, const wstring& day, const wstring& month, const wstring& year)
    : hour(hour), minute(minute), day(day), month(month), year(year) {}


void Datetime::editDatetime() {
    int choice;
    wstring newName, newGenre, newDescription, newlanguage, newAge;
    Datetime newDuration;
    Datetime newTimeline;

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

Datetime Movie::getDuration() const {
    return duration;
}

wstring Movie::getDescription() const {
    return description;
}