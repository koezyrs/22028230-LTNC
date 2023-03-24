#include <iostream>
#include <cstring>
using namespace std;
struct String
{
    int n;
    char* str;
    String(const char* _str)
    {
        int length = 0;
        while(_str[length] != '\0') length++;
        n = length;
        str = new char[length + 1];
        strcpy(str, _str);
        str[length] = '\0';
    }

    ~String()
    {
        delete[] str;
    }

    void print()
    {
        for(int i = 0; i < n; i++) cout << str[i];
    }

    void append(const char* _text)
    {
        int textLength = 0;
        while(_text[textLength] != '\0')
        {
            textLength++;
        }
        char* temp = new char[n + textLength + 1];
        for(int i = 0; i < n; i++) temp[i] = str[i];
        for(int i = 0, j = n; i < textLength; i++, j++)
        {
            temp[j] = _text[i];
        }
        temp[n + textLength] = '\0';
        n = n + textLength;
        char* oldStr = str;
        str = temp;
        delete[] oldStr;
    }
};
int main()
{
    String s("Hello");
    s.append(" there!");
    s.print();
    return 0;
}
