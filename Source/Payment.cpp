#include "../Header/Payment.h"
#include "../Header/Color.h"
#include <sys/stat.h>
using namespace std;

Pay::Pay() {}


Pay::Pay(int paymentStatus, long long paymentAmount) : paymentStatus(paymentStatus), paymentAmount(paymentAmount) {}

Banking::Banking() {}
Banking::Banking(int paymentStatus, long long paymentAmount) : Pay(paymentStatus, paymentAmount) {}

Cash::Cash() {}
Cash::Cash(int paymentStatus, long long paymentAmount) : Pay(paymentStatus, paymentAmount) {}

void Pay::setPaymentStatus(int paymentStatus) {
    this->paymentStatus = paymentStatus;
}

int Pay::getPaymentStatus() const {
    return paymentStatus;
}


wstring Banking::processPayment() {
    return L"Chuyển khoản ngân hàng";
}

wstring Cash::processPayment() {
    return L"Tiền mặt";
}

void Banking::checkPaymentStatus(){
    if(getPaymentStatus() == 1)
        green(L"\n════[Đã nhận chuyển khoản]══════\n");
    else if(getPaymentStatus() == 0){
        red(L"Hủy chuyển khoản\n");
    }else{
        green(L"\nĐang chờ xử lý\n");
    }
    
}

void Banking::createOrder(string filename) {
    //viết hàm lamda
    auto fileExists = [](const string& filename) {
        struct stat buffer;
        return (stat(filename.c_str(), &buffer) == 0);
    };

    if(fileExists("zalopay.exe")){
        string command = "zalopay.exe " + string(filename.begin(), filename.end());
        
        int status = system(string(command).c_str());
        // wcout << L"Status: " << status << endl;
        setPaymentStatus(status);
    }
    else{
        red(L"[Không tìm thấy zalopay.exe]");
        setPaymentStatus(0);
        // wcout << L"Không thể tạo đơn hàng" << endl;
    }
}

void Cash::checkPaymentStatus(){
    if(getPaymentStatus() == 1)
        green(L"\n════[Đã nhận tiền mặt]══════\n");
    else if(getPaymentStatus() == 0){
        red(L"Hủy thanh toán tiền mặt\n");
    }else{
        green(L"\nĐang chờ xử lý\n");
    }
}


void Cash::createOrder(string filename) {
   
}

void Pay::setPaymentAmount(long long paymentAmount) {
    this->paymentAmount = paymentAmount;
}