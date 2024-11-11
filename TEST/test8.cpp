
#include <nlohmann/json.hpp>
#include "base64.hpp"
#include <cpr/cpr.h>
#include <fstream>
#include <iostream>


using namespace std;
int main() {
    // Đọc tệp với mã hóa UTF-8
    ifstream file("../DATA/payments.csv", ios::binary);

    // Mã hóa dữ liệu thành Base64
    string file_content_utf8;
    getline(file, file_content_utf8, '\0');
    file.close();

    auto file_content_base64 = base64::to_base64(file_content_utf8);
  
    nlohmann::json data = {
        {"Parameters", {
            {
                {"Name", "File"},
                {"FileValue", {
                    {"Name", "payments.csv"},
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

    cout << r.text << endl;

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
    cpr::Response r2 = cpr::Get(cpr::Url{url});
    ofstream file2("../DATA/hairbooked.xlsx", ios::binary);
    file2 << r2.text;
    file2.close();

    return 0;
}