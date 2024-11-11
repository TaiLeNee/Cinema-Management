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
        cerr << "Không thể mở tệp " << filename << endl;
        return 0;
    }

    // Đọc nội dung tệp
   wstring employee, movie , age, date, room, chair, ticket ,amount ,price, payment, timebook, line;

    getline(file, line);
    
    getline(file, employee);
    getline(file, movie);
    getline(file, age);
    getline(file, date);
    getline(file, room);
    getline(file, chair);
    getline(file, ticket);
    getline(file, amount);
    getline(file, price);
    getline(file, payment);
    getline(file, timebook);

    file.close();


     // Chuyển đổi wstring sang string
    string employee_utf8 = wstring_to_utf8(employee);
    string movie_utf8 = wstring_to_utf8(movie);
    string age_utf8 = wstring_to_utf8(age);
    string date_utf8 = wstring_to_utf8(date);
    string room_utf8 = wstring_to_utf8(room);
    string chair_utf8 = wstring_to_utf8(chair);
    string ticket_utf8 = wstring_to_utf8(ticket);
    string amount_utf8 = wstring_to_utf8(amount);
    string price_utf8 = wstring_to_utf8(price);
    string payment_utf8 = wstring_to_utf8(payment);
    string timebook_utf8 = wstring_to_utf8(timebook);

    // Tạo JSON
    nlohmann::json data = {
        {"document", "XWyOPdAFKogwFCkc4YBV"},
          {"apiKey", "2HNAM3Y-QIMELPA-TY6A2KY-AU6P6AQ"},
          {"format", "pdf"},
          {"data", {
              {"date", date_utf8},
              {"employee", employee_utf8},
              {"movie", movie_utf8},
              {"age", age_utf8},
              {"room", room_utf8},
              {"chair", chair_utf8},
              {"ticket", ticket_utf8},
              {"amount", amount_utf8},
              {"price", price_utf8},
              {"payment", payment_utf8},
              {"timebook", timebook_utf8}
          }}};

    cpr::Response r = cpr::Post(cpr::Url{"https://app.documentero.com/api"}, cpr::Body{data.dump()}, cpr::Header{{"Content-Type", "application/json"}});

    // cout << r.text << endl;
    /*
    reponse:
    {"status":200,"message":"Document Generated Succesfully","data":"https://storage.googleapis.com/doc-generated/beige_and_brown_minimalist_movie_ticket_m3d70exd.pdf?X-Goog-Algorithm=GOOG4-RSA-SHA256&X-Goog-Credential=documentero-65e4d%40appspot.gserviceaccount.com%2F20241111%2Fauto%2Fstorage%2Fgoog4_request&X-Goog-Date=20241111T154318Z&X-Goog-Expires=3600&X-Goog-SignedHeaders=host&response-content-disposition=attachment&X-Goog-Signature=958c2ebd023511b13dba2a3a3e30649948062e12939b9c1f33b225a420fda7035a75f3e20d3c19b53f0603b1668d9170c2efa475add9600b2324a309d6b1b9ee059e8c9a30006c7fb45a26abc3ae134bb3ced4fa836438960362158668fa43410fda42875b3e3d32f1050bf27058b2b4ca5396e2e018e8105c683d5abc2f41e32954c7248ab024ea4e3c2d004bc267047e95f6f804904944a12c0783a93991932f2638a50c0215ebcdc74e12747f7fcbc5ee988c23c7004f0d697c66f0a49f8c0fb5787e25c71818c116e3127b324d671c6243e9b62b45e3f99de62f459031e5feba777459d39efe11ee9ff044554864e597941697df37555311acb55776a7c4"}
    */
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