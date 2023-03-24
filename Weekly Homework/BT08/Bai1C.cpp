#include <iostream>
using namespace std;

void reverse(char a[])
{
    int length = 0;
    while(a[length] != '\0') length++;
    char b[length];
    for(int i = 0; i < length; i++) b[i] = a[i];
    for(int i = 0, j = length - 1; i < length; i++, j--)
    {
        a[i] = b[j];
    }
}

void delete_char(char a[], char c)
{
    int length = 0;
    while(a[length] != '\0') length++;
    for(int i = 0 ; i < length; i++)
    {
        if(a[i] != c) continue;
        for(int j = i; j < length - 1; j++)
        {
            a[j] = a[j + 1];
        }
        length--;
        i--;
    }
    a[length] = '\0';
}

void pad_right(char a[], int n)
{
    int length = 0;
    while(a[length] != '\0') length++;
    if(length >= n) return;

    for(int i = length ; i < n ; i++) a[i] = ' ';
    a[n] = '\0';
}

void pad_left(char a[], int n)
{
    int length = 0;
    while(a[length] != '\0') length++;
    if(length >= n) return;
    // Copy string a
    char b[length];
    for(int i = 0 ; i < length; i++) b[i] = a[i];

    for(int i = 0; i < n - length; i++) a[i] = ' ';
    for(int i = n - length, j = 0; j < length; i++, j++ ) a[i] = b[j];
    a[n] = '\0';
}

void truncate(char a[], int n)
{
    int length = 0;
    while(a[length] != '\0') length++;
    if(length <= n) return;
    a[n] = '\0';
}

bool is_palindrome(char a[])
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

void trim_left(char a[])
{
    int length = 0;
    while(a[length] != '\0') length++;
    int c = 0;
    while(a[c] == ' ') c++;
    for(int i = 0; i < length - c; i++)
    {
        a[i] = a[i + c];
    }
    a[length - c] = '\0';
}

void trim_right(char a[])
{
    int length = 0;
    while(a[length] != '\0') length++;

    int c = length - 1;
    while(a[c] == ' ' && c >= 0) c--;
    a[c + 1] = '\0';

}

int main()
{
    char text[] = "The boys are in the way my friend!";
    char palindrome[] = "123321";
    //reverse(text);
    //delete_char(text, 'e');
    //delete_char(text, 't');
    //pad_right(text, 50);
    //pad_left(text, 50);
    //truncate(text, 15);
    //cout << text;
    //cout << is_palindrome(palindrome);

    int length = 0;
    char trimText[] = "     1    ";
    while(trimText[length] != '\0') length++;
    cout << length << endl;

    trim_left(trimText);
    length = 0;
    while(trimText[length] != '\0') length++;
    cout << length << endl;

    trim_right(trimText);
    length = 0;
    while(trimText[length] != '\0') length++;
    cout << length << endl;
}
