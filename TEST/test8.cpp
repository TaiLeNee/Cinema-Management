#include <iostream>
#include <string>

std::wstring getDate(const std::wstring& datetime) {
    size_t pos = datetime.find(L" ");
    if (pos != std::wstring::npos) {
        return datetime.substr(pos + 1);
    }
    return L""; // Trả về chuỗi rỗng nếu không tìm thấy dấu cách
}

int main() {
    std::wstring datetime = L"23:45:1 4/11/2024";
    std::wstring date = getDate(datetime);
    std::wcout << L"Date: " << date << std::endl;
    return 0;
}