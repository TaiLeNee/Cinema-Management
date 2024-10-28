#ifndef CHAIR_H 
#define CHAIR_H
#include <string>

using namespace std;

class Chair {  
    private:
        int id; //Id ghê
        wstring name; //Tên ghế
        float price; //Giá ghế
        int isBooked; //Trạng thái đặt ghế 0: không đặt, 1: đã đặt,  2: đang chọn

    public:
        Chair();
        Chair(int id, const wstring& name, int isBooked);
        int getId() const;
        wstring getName() const;

        void setPrice(float price);
        float getPrice() const;

        int getIsBooked() const;
        void setIsBooked(int isBooked);
        void setName(wstring name);
};

#endif // CHAIR_H