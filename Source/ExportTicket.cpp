#include <nlohmann/json.hpp>
#include <cpr/cpr.h>
#include <fstream>
#include <iostream>
#include <unistd.h>
#include <limits.h>
#include <locale>
#include <codecvt>
using namespace std;
using json = nlohmann::json;

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


// Hàm chuyển đổi wstring sang string với mã hóa UTF-8
string wstring_to_utf8(const wstring& str) {
    wstring_convert<codecvt_utf8<wchar_t>> conv;
    return conv.to_bytes(str);
}


int exportToPDF(string filename) {
    // Đọc tệp với mã hóa UTF-8
    wifstream file(filename);
    file.imbue(locale(locale(), new codecvt_utf8<wchar_t>));
    if (!file.is_open()) {
        cerr << "Can't open file " << filename << endl;
        return 0;
    }

    // Đọc nội dung tệp
   wstring employee, movie , age, date, room, chair, ticket ,point, amount ,price, payment, timebook, line, customer;

    getline(file, line);
    
    getline(file, employee);
    getline(file, movie);
    getline(file, age);
    getline(file, date);
    getline(file, room);
    getline(file, chair);
    getline(file, ticket);
    getline(file, point);
    getline(file, amount);
    getline(file, price);
    getline(file, payment);
    getline(file, timebook);
    getline(file, customer);


    file.close();


     // Chuyển đổi wstring sang string
    string employee_utf8 = wstring_to_utf8(employee);
    string movie_utf8 = wstring_to_utf8(movie);
    string age_utf8 = wstring_to_utf8(age);
    string date_utf8 = wstring_to_utf8(date);
    string room_utf8 = wstring_to_utf8(room);
    string chair_utf8 = wstring_to_utf8(chair);
    string ticket_utf8 = wstring_to_utf8(ticket);
    string point_utf8 = wstring_to_utf8(point);
    string amount_utf8 = wstring_to_utf8(amount);
    string price_utf8 = wstring_to_utf8(price);
    string payment_utf8 = wstring_to_utf8(payment);
    string timebook_utf8 = wstring_to_utf8(timebook);
    string customer_utf8 = wstring_to_utf8(customer);


    // Tạo JSON
    nlohmann::json data = {
        {"document", "MU3EbsRkiKWJDs1Zse8Z"},
          {"apiKey", "VXXWB3A-5JVUSLI-QKB6H3Y-CXJIKTQ"},
          {"format", "pdf"},
          {"data", {
              {"date", date_utf8},
              {"employee", employee_utf8},
              {"movie", movie_utf8},
              {"age", age_utf8},
              {"room", room_utf8},
              {"chair", chair_utf8},
              {"ticket", ticket_utf8},
              {"point", point_utf8},
              {"amount", amount_utf8},
              {"price", price_utf8},
              {"payment", payment_utf8},
              {"timebook", timebook_utf8},
              {"customer", customer_utf8}
          }}};

    cpr::Response r = cpr::Post(cpr::Url{"https://app.documentero.com/api"}, cpr::Body{data.dump()}, cpr::Header{{"Content-Type", "application/json"}});

    nlohmann::json j = nlohmann::json::parse(r.text);
    if(j.find("status") != j.end()){
        if(j["status"] != 200){
            cout << "Error: " << j["message"] << endl;
            return 0;
        }
    }

    string url = j["data"];
    
    cpr::Response r2 = cpr::Get(cpr::Url{url});
    
    //tải file từ url
    size_t pos = filename.rfind(".txt");
    if (pos != string::npos) {
        // Thay thế phần mở rộng .csv bằng .xlsx
        filename.replace(pos, 4, ".pdf");
    }

    ofstream file2(filename, ios::binary);
    file2 << r2.text;
    file2.close();

    string commant = "start " + getFullPath(filename);
    system(commant.c_str());    
    // cout << "File PDF đã được tạo tại " << fullPath << endl;



    // //delete file txt

    

    return 1;
}


int main(int argc, char* argv[]) {
    
    if (argc < 2) {
        cerr << L"Usage: exportPDF <input_file>" << endl;
        return 1;
    }

    string filename = argv[1];
    return exportToPDF(filename);
}