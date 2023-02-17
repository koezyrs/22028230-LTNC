#include <bits/stdc++.h>
using namespace std;

void bai19(){
    bool x;
    int a, b, c;
    cout << "Nhap so a: "; cin >> a;
    cout << "Nhap so b: "; cin >> b;
    cout << "Nhap so c: "; cin >> c;
    if((a > b && b > c) || (a < b) && (b < c)) x = true;
    else x = false;
    cout << "Ket qua: " << boolalpha << x << endl;
    return;
}

