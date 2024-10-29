#include "../Header/drawTable.h"
#include "../Header/splitStringByWords.h"


wstring GREEN = L"\033[92m";
wstring RED = L"\033[91m";
wstring END = L"\033[0m";
wstring YELLOW = L"\033[93m";


using namespace std;

void drawTable(const vector<vector<wstring>> &table);

void drawTable(const vector<vector<wstring>>& table) {
    size_t descriptionLimit = 60;

    int numRows = table.size();
    if (numRows == 0) return; // Trường hợp bảng rỗng
    int numCols = table[0].size();

    // Độ rộng của mỗi cột
    vector<int> colWidths(numCols, 0);
    
    // Tính toán độ rộng lớn nhất cho mỗi cột
    for (int i = 0; i < numCols; ++i) {
        for (int j = 0; j < numRows; ++j) {
            // Nếu cột là cột mô tả (description), kiểm tra với giới hạn
            if (i == numCols - 1 && table[j][i].size() > descriptionLimit) {
                auto wrappedLines = splitStringByWords(table[j][i]);
                for (const auto& line : wrappedLines) {
                    if (line.size() > colWidths[i]) {
                        colWidths[i] = line.size();
                    }
                }
            } else {
                if (table[j][i].size() > colWidths[i]) {
                    colWidths[i] = table[j][i].size();
                }
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
        // Tìm số dòng lớn nhất trong hàng hiện tại
        int maxLines = 1;
        for (int col = 0; col < numCols; ++col) {
            if (col == numCols - 1 && table[row][col].size() > descriptionLimit) {
                auto wrappedLines = splitStringByWords(table[row][col]);
                if (wrappedLines.size() > maxLines) {
                    maxLines = wrappedLines.size();
                }
            }
        }

        // Vẽ từng dòng của hàng
        for (int line = 0; line < maxLines; ++line) {
            wcout << L"║";
            for (int col = 0; col < numCols; ++col) {
                wcout << YELLOW << L" ";
                
                if (col == numCols - 1 && table[row][col].size() > descriptionLimit) {
                    // Xử lý mô tả có nhiều dòng
                    auto wrappedLines = splitStringByWords(table[row][col]);
                    if (line < wrappedLines.size()) {
                        wcout << left << setw(colWidths[col]) << wrappedLines[line];
                    } else {
                        wcout << left << setw(colWidths[col]) << L"";
                    }
                } else {
                    // Các ô khác
                    if (line == 0) {
                        wcout << left << setw(colWidths[col]) << table[row][col];
                    } else {
                        wcout << left << setw(colWidths[col]) << L"";
                    }
                }
                wcout << END << L" ║";
            }
            wcout << endl;
        }

        // Nếu không phải hàng cuối, vẽ đường phân cách giữa các hàng
        if (row < numRows - 1) {
            drawSeparator(L'╠', L'╬', L'╣', L'═');
        }
    }
    
    // Vẽ phần cuối của bảng
    drawSeparator(L'╚', L'╩', L'╝', L'═');
}

