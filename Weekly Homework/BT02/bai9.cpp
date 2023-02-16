#include <bits/stdc++.h>
using namespace std;

long  a, b, c;
long temp;

int main(){
    cin >> c;
    cin >> a >> b;

    for(int i = 1; i < c; i++){
        cin >> temp; a = min(a, temp);
        cin >> temp; b = min(b, temp);
    }

    cout << a * b;
    return 0;
}

