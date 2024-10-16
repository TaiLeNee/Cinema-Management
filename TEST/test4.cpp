#include <iostream>
#include <vector>
#include <iomanip>
#include <sstream>
#include <fcntl.h>
#include <io.h>
#include "../Source/Color.cpp"
#include "../Source/Room.cpp"

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

void drawTable(const vector<vector<wstring>>& table, size_t descriptionLimit = 35) {
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
                auto wrappedLines = splitStringByWords(table[j][i], descriptionLimit);
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
                auto wrappedLines = splitStringByWords(table[row][col], descriptionLimit);
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
                    auto wrappedLines = splitStringByWords(table[row][col], descriptionLimit);
                    if (line < wrappedLines.size()) {
                        wcout << setw(colWidths[col]) << wrappedLines[line];
                    } else {
                        wcout << setw(colWidths[col]) << L"";
                    }
                } else {
                    // Các ô khác
                    if (line == 0) {
                        wcout << setw(colWidths[col]) << table[row][col];
                    } else {
                        wcout << setw(colWidths[col]) << L"";
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

int main() {
    // Dữ liệu mẫu
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);
 

    const int numRows = 4;           // Số hàng ghế
    const int numChairsPerRow = 10;  // Số ghế trong mỗi hàng
    

    Room room;
    room.addChairs(numRows, numChairsPerRow);
    room.changeStatusChair(105, true);
    room.changeStatusChair(110, true);
    room.changeStatusChair(403, true);

     // Extract chair names
    vector<vector<wstring>> chairNames;
    for (const auto& row : room.getChairs()) {
        vector<wstring> nameRow;
        for (const auto& chair : row) {
            nameRow.push_back(chair.getName());
        }
        chairNames.push_back(nameRow);
    }

    drawTable(chairNames);

    return 0;
}
