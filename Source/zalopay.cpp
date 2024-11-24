#include <Poco/UUIDGenerator.h>
#include <Poco/UUID.h>
#include <Poco/JSON/Object.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Dynamic/Var.h>
#include <Poco/HMACEngine.h>
#include <Poco/SHA2Engine.h>

#include <Poco/Thread.h>
#include <Poco/Util/Application.h>
#include <Poco/Util/Option.h>
#include <Poco/Util/OptionSet.h>
#include <Poco/Util/HelpFormatter.h>
#include <cpr/cpr.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <ctime>
#include <iomanip>
#include <fcntl.h>
#include <io.h>
#include <windows.h>
#include <conio.h>

using namespace Poco;
using namespace Poco::JSON;
using namespace Poco::Util;
using namespace std;

const wstring GREEN = L"\033[92m";
const wstring RED = L"\033[91m";
const wstring RESET = L"\033[0m";
const wstring YELLOW = L"\033[93m";

struct Config {
    int appid = 2554;
    string key1 = "sdngKKJmqEMzvh5QQcdD2A9XBSKUNaYn";
    string key2 = "trMrHtvjo6myautxDUiAcYsVtaeQ8nhf";
};


typedef struct {
    string apptransid;
    string orderurl;
} OrderResponse;

Config config;

vector<string> readFile(const string& file) {
    vector<string> lines;
    ifstream infile(file);
    if (!infile) {
        wcout << RED << L"Không tìm thấy file " << file.c_str() << RESET << endl;
        return lines;
    }
    string line;
    while (getline(infile, line)) {
        lines.push_back(line);
    }
    return lines;
}

string urlEncode(const string &value) {
    ostringstream escaped;
    escaped.fill('0');
    escaped << hex;
    for (char c : value) {
        if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
            escaped << c;
        } else {
            escaped << '%' << setw(2) << int((unsigned char) c);
        }
    }
    return escaped.str();
}

OrderResponse createOrder(const vector<string>& lines) {
    OrderResponse OR;

    if (lines.size() < 14) {
        wcout << RED << L"File không hợp lệ" << RESET << endl;
        OR;
    }

    string id = lines[0], movie = lines[2], chairs = lines[6], totalMoney = lines[9], room = lines[5], typeticket = lines[7];

    UUIDGenerator uuidGen;
    Poco::UUID uuid = uuidGen.create();

    Object order;
    order.set("appid", config.appid);
    order.set("apptransid", DateTimeFormatter::format(LocalDateTime(), "%y%m%d") + "_" + uuid.toString());
    order.set("appuser", "demo");
    order.set("apptime", Timestamp().epochMicroseconds() / 1000);
    order.set("embeddata", "{\"merchantinfo\":\"embeddata123\",\"redirecturl\":\"https://avancer-z.online\"}");
    order.set("item", "[{\"itemid\":\"" + id + "\",\"itemname\":\"" + movie + chairs + "\",\"itemprice\":" + totalMoney + ",\"itemquantity\":1}]");
    order.set("amount", stoi(totalMoney));
    order.set("description", "Thanh toán vé xem phim " + movie + ", " + room + " " + chairs + " " + typeticket);
    order.set("bankcode", "zalopayapp");

    string data = to_string(config.appid) + "|" + order.getValue<string>("apptransid") + "|demo|" + to_string(order.getValue<int>("amount")) + "|" + to_string(order.getValue<int64_t>("apptime")) + "|" + order.getValue<string>("embeddata") + "|" + order.getValue<string>("item");

    HMACEngine<SHA2Engine256> hmac(config.key1);
    hmac.update(data);
    order.set("mac", DigestEngine::digestToHex(hmac.digest()));

    // Construct URL-encoded string
    stringstream ss;
    ss << "appid=" << urlEncode(to_string(config.appid))
       << "&apptransid=" << urlEncode(order.getValue<string>("apptransid"))
       << "&appuser=" << urlEncode(order.getValue<string>("appuser"))
       << "&apptime=" << urlEncode(to_string(order.getValue<int64_t>("apptime")))
       << "&embeddata=" << urlEncode(order.getValue<string>("embeddata"))
       << "&item=" << urlEncode(order.getValue<string>("item"))
       << "&amount=" << urlEncode(to_string(order.getValue<int>("amount")))
       << "&description=" << urlEncode(order.getValue<string>("description"))
       << "&bankcode=" << urlEncode(order.getValue<string>("bankcode"))
       << "&mac=" << urlEncode(order.getValue<string>("mac"));
    string orderUrlEncoded = ss.str();
    // wcout << orderUrlEncoded.c_str() << endl;

    // Thực hiện yêu cầu HTTP POST bằng cpr
    auto response = cpr::Post(cpr::Url{"https://sandbox.zalopay.com.vn/v001/tpe/createorder"},
                              cpr::Body{orderUrlEncoded},
                              cpr::Header{{"Content-Type", "application/x-www-form-urlencoded"}});

    string responseBody = response.text;

   
    // Phân tích phản hồi JSON
    try {
        Parser parser;
        Dynamic::Var result = parser.parse(responseBody);
        Object::Ptr resultObj = result.extract<Object::Ptr>();

        if (resultObj->getValue<int>("returncode") == 1) {
            wcout << GREEN << L"Tạo đơn hàng thành công" << RESET << endl;
            wcout << L"Mã đơn hàng: " << order.getValue<string>("apptransid").c_str() << endl;
            
            
            OR.orderurl =  resultObj->getValue<string>("orderurl");
            OR.apptransid = order.getValue<string>("apptransid");
            return OR;
        } else {
            wcout << RED << L"Tạo đơn hàng thất bại" << RESET << endl;
            return OR;
        }
    } catch (Poco::JSON::JSONException& e) {
        wcout << RED << L"Lỗi phân tích JSON: " << e.what() << RESET << endl;
        wcout << L"Nội dung phản hồi: " << responseBody.c_str() << endl;
        return OR;
    }
}

int callback(const string& apptransid) {
    Object params;
    params.set("appid", config.appid);
    params.set("apptransid", apptransid);

    string data = to_string(config.appid) + "|" + apptransid + "|" + config.key1;
    HMACEngine<SHA2Engine256> hmac(config.key1);
    hmac.update(data);
    params.set("mac", DigestEngine::digestToHex(hmac.digest()));

    // Construct URL-encoded string
    stringstream ss;
    ss << "appid=" << urlEncode(to_string(config.appid))
       << "&apptransid=" << urlEncode(apptransid)
       << "&mac=" << urlEncode(params.getValue<string>("mac"));
    string paramsUrlEncoded = ss.str();

    // Thực hiện yêu cầu HTTP POST bằng cpr
    auto response = cpr::Post(cpr::Url{"https://sandbox.zalopay.com.vn/v001/tpe/getstatusbyapptransid"},
                              cpr::Body{paramsUrlEncoded},
                              cpr::Header{{"Content-Type", "application/x-www-form-urlencoded"}});

    string responseBody = response.text;

    // Phân tích phản hồi JSON
    try {
        Parser parser;
        Dynamic::Var result = parser.parse(responseBody);
        Object::Ptr resultObj = result.extract<Object::Ptr>();

        if (resultObj->getValue<int>("returncode") == 1) {
            wcout << GREEN << L"\nThanh toán thành công" << RESET << endl;
            wcout << L"Mã đơn hàng: " << apptransid.c_str() << endl;
            return 1;
        } else {
            wcout << YELLOW << L"\rChờ thanh toán" << RESET;

            // Tạo loading \ | / -
            const char* loadingChars = "\\|/-";
            int cnt = 0;
            while (cnt < 4) {
                wcout << L"\r" << YELLOW << L"Chờ thanh toán " << loadingChars[cnt % 4] << RESET ;
                cnt++;
                if (_kbhit() && _getch() == 27) { // ESC key
                    wcout << RED << L"\nHủy thanh toán thành công" << RESET << endl;
                    return -2;
                }
                this_thread::sleep_for(chrono::milliseconds(800));
            }
            return 0;
        }
    } catch (Poco::JSON::JSONException& e) {
        wcout << RED << L"Lỗi phân tích JSON: " << e.what() << RESET << endl;
        wcout << L"Nội dung phản hồi: " << responseBody.c_str() << endl;
        return -1;
    }
}

int main(int argc, char** argv) {
    if (argc < 2) {
        wcout << RED << L"Sử dụng: zalopay <file>" << RESET << endl;
        return -1;
    }
    // Thiết lập mã hóa UTF-8 cho đầu ra của console
    _setmode(_fileno(stdout), _O_U16TEXT);
    SetConsoleOutputCP(CP_UTF8);

    string filename  = argv[1];
    vector<string> lines = readFile(filename);
    if (!lines.empty()) {
        OrderResponse OR = createOrder(lines);
        string url = OR.orderurl;
        string apptransid = OR.apptransid;
        if (!url.empty()) {
            system(("start " + url).c_str());
            while (true) {
                int cb = callback(apptransid);
                if (cb == -1){
                    wcout << RED << L"Đã xảy ra lỗi" << RESET << endl;
                    return -1;
                }
                else if (cb ==0){
                    continue;
                }
                else if (cb == -2){
                    return 0;
                }
                else if (cb == 1){
                    return 1;
                }
            }
        }
    }
    return 0;
}