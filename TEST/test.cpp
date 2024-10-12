#include <iostream>
#include <iomanip>
#include <string>

int main() {
    std::string text = "Hello";

    int width = 20; // Độ rộng của cột
    int padding = (width - text.size()) / 2; // Tính toán khoảng trống hai bên

    // Căn giữa text trong cột rộng 20
    std::cout << std::setw(padding + text.size()) << text << std::setw(padding) << std::endl;

    return 0;
}
