#include <iostream>
using namespace std;

class A {
    public:
   
    virtual void print()  {}
};

class B: public A{
    public:
    void print(){
        cout << "B" << endl;
    }
};

int main(){
    A *a = new B();
    a->print();

    A* b = a;
    b->print();
    delete a;
    return 0;
}