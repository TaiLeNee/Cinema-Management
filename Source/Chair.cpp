#include "../Header/Chair.h"
using namespace std;

Chair::Chair()
{
    this->id = 0;
    this->name = L"";
    this->isBooked = false;
}


Chair::Chair(int id, const wstring &name, int isBooked)
{
    this->id = id;
    this->name = name;
    this->isBooked = isBooked;
}

int Chair::getId() const
{
    return this->id;
}

wstring Chair::getName() const
{
    return this->name;
}

void Chair::setPrice(float price)
{
    this->price = price;
}

float Chair::getPrice() const
{
    return this->price;
}


int Chair::getIsBooked() const
{
    return this->isBooked;
}

void Chair::setIsBooked(int isBooked)
{
    this->isBooked = isBooked;
}

void Chair::setName(wstring name)
{
    this->name = name;
}
