#include <bits/stdc++.h>
using namespace std;

void bai22(){
    double weight, height;
    cout << "Nhap vao can nang cua ban (kg): "; cin >> weight;
    cout << "Nhap vao chieu cao cua ban (cm): "; cin >> height;
    cout << "Chi so BMI cua ban la: " << weight/(height*height)*10000 << endl;
    return;
}


