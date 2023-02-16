#include <iostream>
#include <cmath>

using namespace std;

int main(){
    int n; cin >> n;
    for(int i = 1; i <= n; i++){
        for(int j = i; j <= n + i - 1; j++){
            if(j%n != 0) cout << j%n << " ";
            else cout << j << " ";
        }
        cout << endl;
    }

    return 0;
}

