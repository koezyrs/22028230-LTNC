#include <iostream>
using namespace std;

struct Point
{
    float x, y;
    Point() : x(0), y(0) {}
    Point(float _x, float _y) : x(_x), y(_y) {}
};

void print(Point a)
{
    cout << "(" << a.x << "," << a.y << ")" << endl;
}

int main()
{
    Point test(7,5);
    print(test);
    return 0;
}
