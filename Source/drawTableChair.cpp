#include <iostream>
#include <vector>
#include <iomanip>
#include <sstream>
#include <fcntl.h>
#include <io.h>
#include "../Header/Chair.h"

// wstring YELLOW = L"\033[93m";
const wstring WHITE_BG = L"\033[47m";   // Nền trắng
const wstring PINK_BG = L"\033[45m";    // Nền hồng
const wstring RED_BG = L"\033[41m";     // Nền đỏ
const wstring BLUE_BG = L"\033[44m";    // Nền xanh dương
const wstring YELLOW_BG = L"\033[43m";  // Nền vàng
const wstring RESET = L"\033[0m";       // Khôi phục mặc định

using namespace std;

void drawTableChair(const vector<vector<Chair>>& chairs, int typeTicket) {
    const wstring GREEN = L"\033[92m"; // Màu xanh lá cây

    wcout << L"\n\n════════════════════════════════════════════════════" << endl; 
    wcout << L"                     MÀN HÌNH       \n";
    wcout << L"════════════════════════════════════════════════════" << endl; 

    vector<vector<wstring>> table;  
    for(auto &row: chairs){
        vector<wstring> rowTable;
        for(auto &chair: row){
            rowTable.push_back(chair.getName());
        }

        table.push_back(rowTable);
    }

    int numRows = table.size();
    if (numRows == 0) return; // Trường hợp bảng rỗng
    int numCols = table[0].size();

    // Độ rộng của mỗi cột
    vector<int> colWidths(numCols, 0);
    
    // Tính toán độ rộng lớn nhất cho mỗi cột
    for (int i = 0; i < numCols; ++i) {
        for (int j = 0; j < numRows; ++j) {
            if (table[j][i].size() > colWidths[i]) {
                colWidths[i] = table[j][i].size();
            }
            
        }
    }

    // Hàm tạo dòng phân cách   
    auto drawSeparator = [&](wchar_t left, wchar_t middle, wchar_t right, wchar_t fill) {
        wcout << left;
        for (int i = 0; i < numCols; ++i) {
            wcout << wstring(colWidths[i] + 2, fill);
            if (i < numCols - 1) wcout << middle;
        }
        wcout << right << endl;
    };

    // Vẽ phần đầu của bảng
    drawSeparator(L'╔', L'╦', L'╗', L'═');
    
    // Vẽ các hàng dữ liệu
    for (int row = 0; row < numRows; ++row) {
        // Màu nền cho hàng
        wstring background;
        if(typeTicket == 1){
            background = (row < 2) ? WHITE_BG : RESET;
        }
        else if(typeTicket == 2){
            background = (row < 2) ? RESET : PINK_BG;
        }
        else if (typeTicket == 3){
            background = YELLOW_BG;
        }else{
            background = BLUE_BG;
        }

        // Vẽ từng dòng của hàng
        for (int col = 0; col < numCols; ++col) {
            wcout << L"║" << RESET ;
            if(!(chairs[row][col].getIsBooked())){
                wcout << background << GREEN << " " << setw(colWidths[col]) << table[row][col];
            }
            else if (chairs[row][col].getIsBooked() == 1)
                wcout << GREEN << " " << setw(colWidths[col]) << table[row][col];
            else 
                wcout << RED_BG << GREEN << " " << setw(colWidths[col]) << table[row][col];
            
            wcout << L" "  << RESET;
        }
        wcout << RESET<<  L"║" <<endl;
        // Nếu không phải hàng cuối, vẽ đường phân cách giữa các hàng
        if (row < numRows - 1) {
            drawSeparator(L'╠', L'╬', L'╣', L'═');
        }
    }
    
    // Vẽ phần cuối của bảng
    drawSeparator(L'╚', L'╩', L'╝', L'═');
}

