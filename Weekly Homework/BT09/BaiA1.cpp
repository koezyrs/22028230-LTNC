#include <iostream>
using namespace std;

char* concat(const char* a, const char* b)
{
    int length_a = 0; while( *(a + length_a) != '\0') length_a++;
    int length_b = 0; while( *(b + length_b) != '\0') length_b++;
    char* res = new char[length_a + length_b];
    for(int i = 0; i < length_a; i++) *(res + i) = *(a + i);
    for(int i = length_a, j = 0; i < length_a + length_b; i++, j++) *(res + i) = *(b + j);
    *(res + length_a + length_b) = '\0';
    return res;
}

int main()
{
    char* k = concat("Hello", " Kitty");
    cout << k;
    return 0;
}
