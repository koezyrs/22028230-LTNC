#include <iostream>
using namespace std;

void f(int* arr)
{
    cout << sizeof(arr) << endl;
}

int main()
{
    int a[100];
    int b[] = {1,2,3,4};
    cout << sizeof(a) << endl;
    cout << sizeof(b) << endl;
    f(a);
    f(b);
    return 0;
}
