// #include "checkInput.cpp"
// #include "Color.cpp"
#include <nlohmann/json.hpp>
#include "../Header/base64.hpp"
#include <cpr/cpr.h>
#include <fstream>
#include <iostream>
#include <fcntl.h>
#include <io.h>
#include <unistd.h>
#include <limits.h>

using namespace std;


string getFullPath(const string& filename) {
    char temp[PATH_MAX];
    if (getcwd(temp, sizeof(temp)) != NULL) {
        string fullPath = string(temp) + "/" + filename;
        return fullPath;
    } else {
        cerr << "Error getting current directory" << endl;
        return "";
    }
}


int exportToXLSX(string filename) {
    // Đọc tệp với mã hóa UTF-8
    ifstream file(filename, ios::binary);

    // Đọc tệp với mã hóa UTF-8
    // ifstream file("../DATA/movies.csv", ios::binary);

    // Mã hóa dữ liệu thành Base64
    string file_content_utf8;
    getline(file, file_content_utf8, '\0');
    file.close();
    remove(filename.c_str());

    auto file_content_base64 = base64::to_base64(file_content_utf8);
  
    nlohmann::json data = {
        {"Parameters", {
            {
                {"Name", "File"},
                {"FileValue", {
                    {"Name", "ouput.csv"},
                    {"Data", file_content_base64}
                }}
            },
            {
                {"Name", "StoreFile"},
                {"Value", "true"}
            },
            {
                {"Name", "Delimiter"},
                {"Value", ","}
            }
        }}
    };

    cpr::Response r = cpr::Post(cpr::Url{"https://v2.convertapi.com/convert/csv/to/xls"},
                                cpr::Header{{"Content-Type", "application/json"},
                                            {"Authorization", "Bearer secret_iBJfWaNhPSIdDruQ"}},
                                cpr::Body{data.dump()});

    // cout << r.text << endl;

    //lấy url từ json
    nlohmann::json j = nlohmann::json::parse(r.text);
    
    //kiểm tra xem có lấy được url không (nếu không h=thì sẽ trả về code 4000, ngược lại thì không có trường code){"Code":4000,

    if(j.find("Code") != j.end()){
        if(j["Code"] == 4000){
            cout << "Error: " << j["Message"] << endl;
            return 0;
        }
    }

    string url = j["Files"][0]["Url"];
    //tải file từ url
    size_t pos = filename.rfind(".csv");
    if (pos != string::npos) {
        // Thay thế phần mở rộng .csv bằng .xlsx
        filename.replace(pos, 4, ".xls");
    }

    cpr::Response r2 = cpr::Get(cpr::Url{url});
    ofstream file2(filename, ios::binary);
    file2 << r2.text;
    file2.close();

    string command = "start EXCEL.EXE " + getFullPath(filename);
    system(command.c_str());

    //delete file csv
    

    return 1;
}


int main(int argc, char* argv[]) {

    if (argc < 2) {
        cerr << L"Usage: exportPDF <input_file>" << endl;
        return 1;
    }

    string filename = argv[1];
    return exportToXLSX(filename);
}