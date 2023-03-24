#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

void count_even(int* arr, int n)
{
    int res = 0;
    for(int i = 0 ; i < 5; i++)
    {
        if(*(arr + i) % 2 == 0) res++;
    }

    for(int i = n - 1; i >= n - 6; i--)
    {
        if(*(arr + i) % 2 == 0) res++;
    }
    cout << res;
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

    for(int i = 0; i < n; i++)
    {
        cout << *(arr + i) << " ";
    }
    cout << endl;
    count_even(arr, n);
    return 0;
}
