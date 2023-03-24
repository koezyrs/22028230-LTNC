#include <iostream>
using namespace std;

struct Point
{
    float x, y;
    Point() : x(0), y(0) {}
    Point(float _x, float _y) : x(_x), y(_y) {}
};

int main()
{
    Point test(7,5);
    cout << "Point address: " << &test << endl;
    cout << "X Field Address: " << &(test.x) << endl;
    cout << "Y Field Address: " << &(test.y) << endl;
    // Nhận xét: Địa chỉ cấu trúc Point trùng với địa chỉ trường đầu tiên của cấu trúc
    return 0;
}

