#include <iostream>
#include <unistd.h>
#include <limits.h>
#include <string>

std::string getFullPath(const std::string& filename) {
    char temp[PATH_MAX];
    if (getcwd(temp, sizeof(temp)) != NULL) {
        std::string fullPath = std::string(temp) + "/" + filename;
        return fullPath;
    } else {
        std::cerr << "Error getting current directory" << std::endl;
        return "";
    }
}

int main(int argc, char* argv[]) {
    // if (argc < 2) {
    //     std::cerr << "Usage: exportPDF <input_file>" << std::endl;
    //     return 1;
    // }

    std::string filename = "../DATA/chairbooked.csv";
    std::string fullPath = getFullPath(filename);
    std::cout << "Full path: " << fullPath << std::endl;

    // Gọi hàm exportToXLSX với đường dẫn đầy đủ
    // return exportToXLSX(fullPath);
    return 0;
}