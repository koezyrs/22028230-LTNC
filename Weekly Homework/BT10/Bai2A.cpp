#include <iostream>
using namespace std;

struct Point
{
    float x, y;
    Point() : x(0), y(0) {}
    Point(float _x, float _y) : x(_x), y(_y) {}
};

void f(Point a)
{
    cout << "Pass by value: " << &a << endl;
}

void g(Point& a)
{
    cout << "Pass by reference: " << &a << endl;
}
int main()
{
    Point test(7,5);
    cout << "Root address: " << &test << endl;
    f(test);
    g(test);
    return 0;
}
