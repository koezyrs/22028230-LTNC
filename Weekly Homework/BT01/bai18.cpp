#include <bits/stdc++.h>
using namespace std;

void bai18(){
    int x1, y1, x2, y2;
    cout << "Moi nhap vao toa do x1: "; cin >> x1;
    cout << "Moi nhap vao toa do y1: "; cin >> y1;
    cout << "Moi nhap vao toa do x2: "; cin >> x2;
    cout << "Moi nhap vao toa do y2: "; cin >> y2;
    cout << "Khoang cach giua 2 diem (x1,y2) va (x2,y2):  " << sqrt((x1-x2)*(x1-x2) + (y1-y2)*((y1-y2))) << endl;
    return;
}
