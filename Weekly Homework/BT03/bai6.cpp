// Ma trận kì ảo

#include <bits/stdc++.h>
using namespace std;

void Siamese(int** &arr, int cnt, int i, int j, int n)
{
    if(cnt > n*n) return;
    if(i < 0) i = n - 1;

    if(arr[i][j] != 0) return;
    else arr[i][j] = cnt;

    Siamese(arr, cnt + 1, i - 1, (j + 1)%n, n);
    Siamese(arr, cnt + 1, (i + 1)%n, j%n, n);
    return;
}

int main(int argv, char* args[])
{
    int n; cin >> n;
    int** arr = new int*[n];
    for(int i = 0; i < n; i++) arr[i] = new int[n];
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            arr[i][j] = 0;

    Siamese(arr, 1, 0, n/2, n);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++) cout << arr[i][j] << " ";
        cout << endl;
    }
    for(int i =0 ; i < n; i++) delete[] arr[i];
    delete[] arr;
    return 0;
}
