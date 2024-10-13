#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <fcntl.h>
#include <io.h>
#include "../Header/Chair.h"

using namespace std;

// Mã màu nền ANSI
const wstring WHITE_BG = L"\033[47m";   // Nền trắng
const wstring PINK_BG = L"\033[45m";    // Nền hồng
const wstring RESET = L"\033[0m";       // Khôi phục mặc định



bool isHidden(const Chair& chair) {
    return chair.getIsBooked();
}

void drawRowDivider(int numSeats) {
    wcout << L"   ";
    for (int i = 0; i < numSeats; ++i) {
        wcout << L"+-------";
    }
    wcout << L"+" << endl;
}

void drawSeatRow(char rowLabel, const vector<Chair>& chairs, int rowIndex, int numSeats) {
    wcout << L" " << rowLabel << L" ";

    // Xác định màu nền của hàng ghế
    wstring background = (rowIndex < 2) ? WHITE_BG : PINK_BG;

    for (int j = 0; j < numSeats; ++j) {
        const Chair& chair = chairs[rowIndex * numSeats + j];
        if (isHidden(chair)) {
            // Nếu ghế bị ẩn, bỏ qua ghế này
            wcout << L"|       ";  // Ô trống thay vì hiển thị số ghế
        } else {
            // Ghế bình thường với nền theo hàng
            wcout << L"| " << background << L" " << setw(3) << chair.getName() <<  L" " << RESET << L" ";
        }
    }
    wcout << L"|" << endl;
}

void drawTheater(const vector<Chair>& chairs, int numRows, int numChairsPerRow) {
    for (int i = 0; i < numRows; ++i) {
        drawRowDivider(numChairsPerRow);
        char rowLabel = 'A' + i;
        drawSeatRow(rowLabel, chairs, i, numChairsPerRow);
    }
    drawRowDivider(numChairsPerRow);  // Đường chia cuối cùng
}

void drawLegend() {
    // Chú thích về màu nền và trạng thái của ghế
    wcout << endl;
    wcout << WHITE_BG << L"       " << RESET << L" - Ghế thường (85.000đ)" <<"         ";
    wcout << PINK_BG << L"       " << RESET << L" - Ghế VIP (100.000đ)" << "         ";
    wcout << L"       - Ghế đã chọn (không hiển thị)" << endl;
}

void drawScreenFrame() {
    // Vẽ khung bao quanh chữ "Màn hình"
    int width = 50; // Độ rộng của khung bao quanh
    
    // Vẽ viền trên của khung
    wcout << L"   ";
    for (int i = 0; i < width; ++i) {
        wcout << L"-";
    }
    wcout << endl;
    
    // Vẽ nội dung bên trong khung với chữ "Màn hình"
    wcout << L"   |" << setw((width - 8) / 2) << L"" << L"Màn hình" << setw((width - 8) / 2) << L"|" << endl;
    
    // Vẽ viền dưới của khung
    wcout << L"   ";
    for (int i = 0; i < width; ++i) {
        wcout << L"-";
    }
    wcout << endl;
}

void printChairs( const vector<Chair> chairs, int numRows, int numChairsPerRow){
    // Hiển thị màn hình với khung bao quanh
    drawScreenFrame();
    
    // Hiển thị bảng ghế
    drawTheater(chairs, numRows, numChairsPerRow);  // Số hàng và số ghế trong mỗi hàng
    
    // Hiển thị chú thích
    drawLegend();
}

// int main() {
//        //thiết lập chế độ Unicode cho console
//     _setmode(_fileno(stdout), _O_U16TEXT);
//     _setmode(_fileno(stdin), _O_U16TEXT);


//     const int numRows = 4;           // Số hàng ghế
//     const int numChairsPerRow = 10;  // Số ghế trong mỗi hàng
//     vector<Chair> chairs;            // Danh sách ghế

//     char rowLabel = 'A';
//     for (int i = 0; i < numRows; ++i) {
//         for (int j = 1; j <= numChairsPerRow; ++j) {
//             int chairId = (i + 1) * 100 + j; // Tạo ID ghế theo định dạng {số hàng}{số ghế}
//             wstring chairName = wstring(1, rowLabel) + to_wstring(j);
//             chairs.push_back(Chair(chairId, chairName, false)); // Tất cả ghế chưa bị ẩn
//         }
//         rowLabel++;
//     }

//     // // Ví dụ: Ẩn các ghế B5, C7, D10
//     // chairs[5].isBooked = true; // B5
//     // chairs[18].isBooked = true; // C7
//     // chairs[40].isBooked = true; // D10

    

//     return 0;
// }
