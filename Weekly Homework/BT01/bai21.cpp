#include <bits/stdc++.h>
using namespace std;

void bai21(){
    double a, b, c;
    cout << "Nhap vao do dai canh a: "; cin >> a;
    cout << "Nhap vao do dai canh b: "; cin >> b;
    cout << "Nhap vao do dai canh c: "; cin >> c;

    double s = (a+b+c)/2;

    cout << "Dien tich tam giac la: " << sqrt(s*(s-a)*(s-b)*(s-c)) << endl;
    return;
}


