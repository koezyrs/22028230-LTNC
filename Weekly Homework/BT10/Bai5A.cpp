#include <iostream>
using namespace std;

struct Point
{
    float x, y;
    int* arr;
    Point() : x(0), y(0) {}
    Point(float _x, float _y) : x(_x), y(_y)
    {
        arr = new int[5];
    }
};

int main()
{
    Point a(7,5);
    Point b = a;
    cout << a.arr << endl;
    cout << b.arr << endl;
    return 0;
}


