// Lịch khám bệnh

#include <bits/stdc++.h>
using namespace std;

int main(int argv, char* args[])
{
    int n; cin >> n;
    int* arr = new int[n];
    for(int i = 0; i < n; i++){
        cin >> arr[i];
    }

    for(int i = 0; i < n - 1; i++){
        for(int j = 0; j < n - 1 - i; j++){
            if(arr[j] > arr[j + 1])
            {
                int c = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = c;
            }
        }
    }

    int k = n;
    long sum = 0;
    for(int i = 0; i < n; i++) sum = sum + (n - i - 1)*arr[i];
    cout << sum;
    delete[] arr;
    return 0;
}
