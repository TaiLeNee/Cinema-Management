#ifndef PAYMENT_H
#define PAYMENT_H
#include <iostream>
#include <string>

class Pay {
private:
    int paymentStatus;  
    long long paymentAmount;
public:
    Pay();
    Pay(int paymentStatus, long long paymentAmount);
    virtual ~Pay() {}
    virtual std::wstring processPayment() = 0;
    virtual void checkPaymentStatus() = 0;

    void setPaymentAmount(long long paymentAmount);
    void setPaymentStatus(int paymentStatus);
    int getPaymentStatus() const;
};

class Banking : public Pay {    //1

public:
    Banking();
    Banking(int paymentStatus, long long paymentAmount);
    std::wstring processPayment() override;
    void checkPaymentStatus() override;
};

class Cash : public Pay {   //2
public:
    Cash();
    Cash(int paymentStatus, long long paymentAmount);
    std::wstring processPayment() override;
    void checkPaymentStatus() override;
};

#endif // PAYMENT_H