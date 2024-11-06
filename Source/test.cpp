#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <fstream>
#include <fcntl.h>
#include <io.h>
#include <locale>
#include <codecvt>

bool exportPDF(const std::vector<std::vector<std::wstring>>& table) {
    // std::wofstream tempFile("temp_table.txt");
    // for (const auto& row : table) {
    //     for (const auto& cell : row) {
    //         tempFile << cell << L"\t";
    //     }
    //     tempFile << L"\n";
    // }
    // tempFile.close();

    std::wstring command = L"exportPDF.exe ../DATA/chairbooked.csv";
    return std::system(std::string(command.begin(), command.end()).c_str());
}

int main() {

    std::vector<std::vector<std::wstring>> table = {
        {L"ID", L"Tên phim", L"Tháng", L"Số lượng vé", L"Doanh thu"},
        {L"1", L"Phim A", L"01/2024", L"100", L"1000000"}
    };
    if(!exportPDF(table))
        std::cout << "Export PDF successfully\n";
    else
        std::cout << "Export PDF failed\n";
    return 0;
}