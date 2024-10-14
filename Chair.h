#ifndef CHAIR_H 
#define CHAIR_H
#include <string>

using namespace std;

class Chair {  
    private:
        int id; //Id ghê
        wstring name; //Tên ghế
        bool isBooked; //Trạng thái đặt ghế

    public:
        Chair();
        Chair(int id, const wstring& name, bool isBooked);
        int getId() const;
        wstring getName() const;
        bool getIsBooked() const;
        void setIsBooked(bool isBooked);
};

#endif // CHAIR_H