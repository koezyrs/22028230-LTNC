#include <iostream>
#include <algorithm>
using namespace std;

void SelectionSort(int* &arr, int n)
{
    for(int i = 0; i < n - 1; i++){
        int _min = i;
        for(int j = i + 1; j < n; j++) if(arr[j] < arr[_min]) _min = j;
        int temp = arr[i];
        arr[i] = arr[_min];
        arr[_min] = temp;
    }
    return;
}

int main(int argv, char* args[])
{
    int n; cin >> n;
    int* arrA = new int[n];
    int* arrB = new int[n + 1];
    for(int i = 0; i < n; i++) cin >> arrA[i];
    for(int i = 0; i < n + 1; i++) cin >> arrB[i];
    SelectionSort(arrA, n);
    SelectionSort(arrB, n + 1);
    for(int i = 0; i < n; i++){
        if(arrA[i] == arrB[i]) continue;
        cout << arrB[i];
        goto Deallocates_Memory;
    }
    cout << arrB[n];

    Deallocates_Memory:
    delete[] arrA;
    delete[] arrB;
    return 0;
}
