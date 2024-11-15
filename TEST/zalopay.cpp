#include <iostream>
#include <string>
#include <ctime>
#include <nlohmann/json.hpp>
#include <openssl/hmac.h>
#include <openssl/sha.h>
#include <cpr/cpr.h>
#include <rpc.h>
#include <sstream>
#include <iomanip>
#include <vector>

using json = nlohmann::json;

std::string generateUUID() {
    UUID uuid;
    UuidCreate(&uuid);

    RPC_CSTR szUuid = nullptr;
    UuidToStringA(&uuid, &szUuid);

    std::string uuidStr(reinterpret_cast<char*>(szUuid));
    RpcStringFreeA(&szUuid);

    return uuidStr;
}

std::string hmac_sha256(const std::string &key, const std::string &data) {
    unsigned char* digest;
    digest = HMAC(EVP_sha256(), key.c_str(), key.length(), (unsigned char*)data.c_str(), data.length(), NULL, NULL);
    char mdString[SHA256_DIGEST_LENGTH*2+1];
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++)
         sprintf(&mdString[i*2], "%02x", (unsigned int)digest[i]);
    return std::string(mdString);
}

std::string url_encode(const std::string &value) {
    std::ostringstream escaped;
    escaped.fill('0');
    escaped << std::hex;

    for (char c : value) {
        if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
            escaped << c;
        } else {
            escaped << '%' << std::setw(2) << int((unsigned char) c);
        }
    }

    return escaped.str();
}

int main() {
    // Cấu hình
    const int appid = 2554;
    const std::string key1 = "sdngKKJmqEMzvh5QQcdD2A9XBSKUNaYn";
    const std::string key2 = "trMrHtvjo6myautxDUiAcYsVtaeQ8nhf";
    const std::string endpoint = "https://sandbox.zalopay.com.vn/v001/tpe/createorder";

    // Tạo apptransid
    time_t now = time(0);
    struct tm tstruct;
    localtime_s(&tstruct, &now);
    char date[7];
    strftime(date, sizeof(date), "%y%m%d", &tstruct);

    std::string apptransid = std::string(date) + "_" + generateUUID();

    // Tạo JSON order
    json order;
    order["appid"] = appid;
    order["apptransid"] = apptransid;
    order["appuser"] = "demo";
    order["apptime"] = (long long)(std::chrono::system_clock::now().time_since_epoch() / std::chrono::milliseconds(1));
    order["embeddata"] = json::object({ {"merchantinfo", "embeddata123"} }).dump();
    order["item"] = json::array({ { {"itemid", "knb"}, {"itemname", "kim nguyen bao"}, {"itemprice", 198400}, {"itemquantity", 1} } }).dump();
    order["amount"] = 50000;
    order["description"] = "ZaloPay Integration Demo";
    order["bankcode"] = "zalopayapp";

    // Xây dựng chuỗi dữ liệu để ký
    std::ostringstream oss;
    oss << order["appid"].get<int>() << "|"
        << order["apptransid"].get<std::string>() << "|"
        << order["appuser"].get<std::string>() << "|"
        << order["amount"].get<int>() << "|"
        << order["apptime"].get<long long>() << "|"
        << order["embeddata"].get<std::string>() << "|"
        << order["item"].get<std::string>();

    std::string data = oss.str();

    // Tính toán HMAC SHA256
    unsigned char* key = (unsigned char*)key1.c_str();
    unsigned int len = SHA256_DIGEST_LENGTH;
    unsigned char hash[SHA256_DIGEST_LENGTH];

    HMAC_CTX* ctx = HMAC_CTX_new();
    HMAC_Init_ex(ctx, key, key1.length(), EVP_sha256(), NULL);
    HMAC_Update(ctx, (unsigned char*)data.c_str(), data.length());
    HMAC_Final(ctx, hash, &len);
    HMAC_CTX_free(ctx);

    // Chuyển đổi hash thành chuỗi hex
    std::ostringstream mac_oss;
    for (unsigned int i = 0; i < len; i++)
        mac_oss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];

    std::string mac = mac_oss.str();

    // Thêm mac vào order
    order["mac"] = mac;

    // Chuẩn bị payload
    std::ostringstream payload_oss;
    for (auto& el : order.items()) {
        payload_oss << el.key() << "=" << url_encode(el.value().dump()) << "&";
    }
    std::string payload = payload_oss.str();
    payload.pop_back(); // Remove the trailing '&'

    // Gửi yêu cầu POST
    auto response = cpr::Post(cpr::Url{ endpoint },
                              cpr::Body{ payload },
                              cpr::Header{{"Content-Type", "application/x-www-form-urlencoded"}});

    // Kiểm tra phản hồi
    if (response.error) {
        std::cerr << "Error: " << response.error.message << std::endl;
        return 1;
    }

    // Phân tích kết quả JSON
    json result = json::parse(response.text);

    // Hiển thị kết quả
    for (auto& el : result.items()) {
        std::cout << el.key() << ": " << el.value() << std::endl;
    }

    return 0;
}