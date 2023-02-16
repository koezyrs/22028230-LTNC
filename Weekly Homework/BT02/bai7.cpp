#include <iostream>
#include <cmath>

using namespace std;

int main(){
    int last; cin >> last;
    cout << last << " ";
    int n;
    while(cin >> n){
        if(n < 0){
            cout << n;
            break;
        }
        if(n != last){
            cout << n << " ";
            last = n;
        }
    }
    return 0;
}
