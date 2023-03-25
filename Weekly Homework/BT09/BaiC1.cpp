#include <iostream>
using namespace std;

char* reverse(const char a[])
{
    int length = 0;
    while(a[length] != '\0') length++;
    char b[length];
    char* res = new char[length];
    for(int i = 0; i < length; i++) b[i] = a[i];
    for(int i = 0, j = length - 1; i < length; i++, j--)
    {
        *(res + i) = b[j];
    }
    return res;
}

char* delete_char(const char a[],const char c)
{
    int length = 0;
    while(a[length] != '\0') length++;
    char* res = new char[length];
    for(int i = 0; i < length; i++) *(res + i) = a[i];
    for(int i = 0 ; i < length; i++)
    {
        if(*(res + i) != c) continue;
        for(int j = i; j < length - 1; j++)
        {
            *(res + j) = *(res + j + 1);
        }
        length--;
        i--;
    }
    *(res + length) = '\0';
    return res;
}

char* pad_right(const char a[], const int n)
{
    int length = 0;
    while(a[length] != '\0') length++;
    char* res = new char[length];
    for(int i = 0; i < length; i++) *(res + i) = a[i];
    if(length >= n) return res;

    for(int i = length ; i < n ; i++) *(res + i) = ' ';
    *(res + n) = '\0';

    return res;
}

char* pad_left(const char a[], const int n)
{
    int length = 0;
    while(a[length] != '\0') length++;
    char* res = new char[length];
    for(int i = 0; i < length; i++) *(res + i) = a[i];
    if(length >= n) return res;
    // Copy string a
    char b[length];
    for(int i = 0 ; i < length; i++) b[i] = a[i];

    for(int i = 0; i < n - length; i++) *(res + i) = ' ';
    for(int i = n - length, j = 0; j < length; i++, j++ ) *(res + i) = b[j];
    *(res + n) = '\0';
    return res;
}

char* truncate(const char a[], const int n)
{
    int length = 0;
    while(a[length] != '\0') length++;
    char* res = new char[length];
    for(int i = 0; i < length; i++) *(res + i) = a[i];

    if(length <= n) return res;
    *(res + n) = '\0';
    return res;
}

bool is_palindrome(const char a[])
{
    bool res = true;

    int length = 0;
    while(a[length] != '\0') length++;
    int mid = length / 2;
    for(int i = 0 ; i < mid; i ++)
    {
        if(a[i] != a[length - i - 1]) res = false;
    }

    return res;
}

char* trim_left(const char a[])
{
    int length = 0;
    while(a[length] != '\0') length++;
    char* res = new char[length];
    for(int i = 0; i < length; i++) *(res + i) = a[i];

    int c = 0;
    while(a[c] == ' ') c++;
    for(int i = 0; i < length - c; i++)
    {
        *(res + i) = *(res + i + c);
    }
    *(res + length - c) = '\0';
    return res;
}

char* trim_right(const char a[])
{
    int length = 0;
    while(a[length] != '\0') length++;
    char* res = new char[length];
    for(int i = 0; i < length; i++) *(res + i) = a[i];

    int c = length - 1;
    while(a[c] == ' ' && c >= 0) c--;
    *(res + c + 1) = '\0';
    return res;
}

int main()
{
    char text[] = "The boys are in the way my friend!";
    char palindrome[] = "123321";
    char* test;
    //test = reverse(text);
    //test = delete_char(text, 'e');
    //test = delete_char(text, 't');
    //test = pad_right(text, 50);
    //test = pad_left(text, 50);
    //test = truncate(text, 15);
    //cout << test;
    //cout << is_palindrome(palindrome);


    int length = 0;
    test = trim_left("    123");
    while(test[length] != '\0') length++;
    cout << length << endl;

    test = trim_right("123       ");
    length = 0;
    while(test[length] != '\0') length++;
    cout << length << endl;

}
