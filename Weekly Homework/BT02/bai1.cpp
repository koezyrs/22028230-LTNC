#include <iostream>
#include <cmath>

using namespace std;

int main(){
    int n; cin >> n;
    bool prime = (n > 1) ? true: false;
    for(int i = 2; i*i <= n; i++){
        if(n%i == 0) prime = false;
    }
    if(prime) cout << "yes";
    else cout << "no";

    return 0;
}
