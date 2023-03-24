#include <iostream>
using namespace std;

struct Point
{
    float x, y;
    Point() : x(0), y(0) {}
    Point(float _x, float _y) : x(_x), y(_y) {}
};

Point mid_point(Point a, Point b)
{
    Point res((a.x + b.x)/2, (a.y + b.y)/2);
    return res;
}

void print(Point a)
{
    cout << "(" << a.x << "," << a.y << ")" << endl;
}

int main()
{
    Point test = mid_point(Point(2,8), Point(4,10));
    print(test);
    return 0;
}

