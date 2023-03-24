#include <iostream>
using namespace std;

/*
    Địa chỉ hai biến x,y giống nhau vì cả 2 biến đều là biến địa phương, biến đầu tiên của hàm
    khả năng chương trình xếp x và y ở ở cùng địa chỉ trong stack
*/

void f(int xval)
{
   int x;
   x = xval;
   cout << &x << endl;
}
void g(int yval)
{
   int y;
   cout << &y << endl;
}
int main()
{
   f(7);
   g(11);
   return 0;
}

