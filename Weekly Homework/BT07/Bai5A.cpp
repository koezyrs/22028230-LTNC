#include <iostream>
using namespace std;

char* weird_string() {
   char* c = new char[6];
   c = "123345";
   return c;
}

int main()
{
    char* text = weird_string();
    cout << text;
    delete text;
    return 0;
}
