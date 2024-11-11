#include "../Header/Payment.h"

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
        wcout << L"Thanh toán qua ngâng hàng thành công" << endl;
    else if(getPaymentStatus() == 0){
        wcout << L"Thanh toán qua ngân hàng thất bại" << endl;
    }
    else{
        wcout << L"Thanh toán qua ngân hàng đang chờ xử lý" << endl;
    }
}

void Cash::checkPaymentStatus(){
    if(getPaymentStatus() == 1)
        wcout << L"Đã nhận tiền mặt" << endl;
    else if(getPaymentStatus() == 0){
        wcout << L"Hủy thanh toán bằng tiền mặt" << endl;
    }else{
        wcout << L"Đang chờ xử lý" << endl;
    }
}

void Pay::setPaymentAmount(long long paymentAmount) {
    this->paymentAmount = paymentAmount;
}