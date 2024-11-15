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
    virtual void createOrder(std::string filename) = 0;

    void setPaymentAmount(long long paymentAmount);
    void setPaymentStatus(int paymentStatus);
    int getPaymentStatus() const;
};

class Banking : public Pay {
public:
    Banking();
    Banking(int paymentStatus, long long paymentAmount);
    std::wstring processPayment() override;
    void checkPaymentStatus() override;
    void createOrder(std::string filename) override;
};

class Cash : public Pay {
public:
    Cash();
    Cash(int paymentStatus, long long paymentAmount);
    std::wstring processPayment() override;
    void checkPaymentStatus() override;
    void createOrder(std::string filename) override;
};

#endif // PAYMENT_H