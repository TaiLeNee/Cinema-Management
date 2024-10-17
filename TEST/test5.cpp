#include <iostream>
#include <iomanip>  // Thư viện cho setw
#include <conio.h>  // Thư viện cho getch
#include <windows.h> // Thư viện cho hàm gotoxy

using namespace std;

// Hàm di chuyển con trỏ đến tọa độ x, y
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Hàm vẽ khung nhập
void veKhung(int x, int y, int width, int height) {
    gotoxy(x, y);
    cout << char(218);  // Góc trên bên trái
    for (int i = 0; i < width; ++i) cout << char(196);  // Đường ngang
    cout << char(191);  // Góc trên bên phải
    
    for (int i = 0; i < height; ++i) {
        gotoxy(x, y + i + 1);
        cout << char(179);  // Đường dọc bên trái
        gotoxy(x + width + 1, y + i + 1);
        cout << char(179);  // Đường dọc bên phải
    }

    gotoxy(x, y + height + 1);
    cout << char(192);  // Góc dưới bên trái
    for (int i = 0; i < width; ++i) cout << char(196);  // Đường ngang dưới
    cout << char(217);  // Góc dưới bên phải
}

// Hàm nhập ngày tháng năm
void nhapNgayThangNam(int x, int y) {
    string ngay, thang, nam;

    gotoxy(x, y);
    cout << "Nhap ngay: ";
    cin >> ngay;

    gotoxy(x, y + 2);
    cout << "Nhap thang: ";
    cin >> thang;

    gotoxy(x, y + 4);
    cout << "Nhap nam: ";
    cin >> nam;

    gotoxy(x, y + 6);
    cout << "Ngay thang nam da nhap la: " << ngay << "/" << thang << "/" << nam;
}

int main() {
    // Vẽ khung nhập dữ liệu
    veKhung(10, 5, 30, 10);

    // Nhập ngày tháng năm
    nhapNgayThangNam(12, 7);

    // Dừng màn hình
    getch();  // Dùng _getch() trong Visual Studio
    return 0;
}
