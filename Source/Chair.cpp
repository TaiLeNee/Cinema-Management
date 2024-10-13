#include "../Header/Chair.h"
using namespace std;

Chair::Chair()
{
    this->id = 0;
    this->name = L"";
    this->isBooked = false;
}


Chair::Chair(int id, const wstring &name, bool isBooked)
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

bool Chair::getIsBooked() const
{
    return this->isBooked;
}

void Chair::setIsBooked(bool isBooked)
{
    this->isBooked = isBooked;
}
