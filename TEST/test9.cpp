#include <iostream>
#include <string>
int main() {
    std::string filename = "../DATA/chairbooked.csv";

    // Tìm vị trí của phần mở rộng .csv
    size_t pos = filename.rfind(".csv");
    if (pos != std::string::npos) {
        // Thay thế phần mở rộng .csv bằng .xlsx
        filename.replace(pos, 4, ".xlsx");
    }

    std::cout << "New filename: " << filename << std::endl;

    return 0;
}
