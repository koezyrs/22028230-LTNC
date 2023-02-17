#include <bits/stdc++.h>
using namespace std;

void bai20(){
    int a, b;
    cout << "Nhap vao so a: "; cin >> a;
    cout << "Nhap vao so b: "; cin >> b;
    cout << "Ket qua: " << boolalpha << ((a % 7 == 0) && (b % 7 == 0)) << endl;
    return;
}

