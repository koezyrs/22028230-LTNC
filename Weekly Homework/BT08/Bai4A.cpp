#include <iostream>
using namespace std;

int main()  {
   char** s;
   char* foo = "Hello World";
   s = &foo;
   cout << "s is " << *s << endl;
   *s = foo;
   cout << "s[0] is " << (*s)[0] << endl;
   return 0;
}
