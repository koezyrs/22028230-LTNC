#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;



void binarySearch(int* arr, int l, int r, int value)
{
    if(l > r) return;
    int mid = (l + r)/2;
    if(*(arr + mid) > value)
    {
        binarySearch(arr, l , mid - 1, value);
    }else if(*(arr + mid) < value)
    {
        binarySearch(arr, mid + 1, r, value);
    }else
    {
        cout << "Found " << value << " at position: " << mid << endl;
    }

}

int main()
{
    srand(time(0));
    int n = rand()%100;
    int* arr = new int[n];
    for(int i = 0; i < n; i++)
    {
        *(arr + i) = rand()%1001;
    }

    sort(arr, arr + n);
    for(int i = 0; i < n; i++)
    {
        cout << *(arr + i) << " ";
    }
    cout << endl;
    int value; cin >> value;
    binarySearch(arr, 0, n, value);
    return 0;
}
