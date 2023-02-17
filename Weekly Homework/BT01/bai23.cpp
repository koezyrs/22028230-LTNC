#include <bits/stdc++.h>
using namespace std;

void bai23(){
    int a, b;
    cout << "Nhap vao so a: "; cin >> a;
    cout << "Nhap vao so b: "; cin >> b;

    int c = a - b;
    int k = (c >> 31) & 1;
    cout << "So lon hon la: " << a - k * c << endl;
    return;
}



