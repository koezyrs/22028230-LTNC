#include <iostream>
using namespace std;
void solve()
{
    int n; cin >> n;
    int* arr = new int[n + 1];
    long* prefixSum = new long[n + 1];
    arr[0] = 0; prefixSum[0] = 0;
    for(int i = 1; i <= n; i++) cin >> arr[i];
    for(int i = 1; i <= n; i++) prefixSum[i] = prefixSum[i - 1] + arr[i];
    for(int i = 1; i <= n; i++){
        if(prefixSum[i - 1] == prefixSum[n] - prefixSum[i]){cout << "YES" << endl; return;}
    }
    cout << "NO" << endl;
    delete[] arr;
    delete[] prefixSum;
    return;
}

int main(int argv, char* args[])
{
    int t; cin >> t;
    while(t){
        solve();
        t--;
    }
    return 0;
}
