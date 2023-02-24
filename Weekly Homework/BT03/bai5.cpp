// Bảng xoắn ốc

#include <iostream>
using namespace std;

int x, y;
int moveRows[4]     =    {0,1,0,-1};
int moveColumns[4]  =    {1,0,-1,0};

void Spirall(int** &arr, int i, int j, int cnt, int dir)
{
    if(cnt > x*y) return;
    arr[i][j] = cnt;
    int next_i = i + moveRows[dir];
    int next_j = j + moveColumns[dir];
    if(next_i < 0 || next_i >= x || next_j < 0 || next_j >= y || arr[next_i][next_j] != 0){
        dir = (dir + 1) % 4;
        next_i = i + moveRows[dir];
        next_j = j + moveColumns[dir];
    }
    Spirall(arr, next_i, next_j, cnt + 1, dir);
    return;
}

int main(int argv, char* args[])
{
    cin >> x >> y;
    int** arr = new int*[x];
    for(int i = 0; i < x; i++) arr[i] = new int[y];

    for(int i = 0; i < x; i++){
        for(int j = 0; j < y; j++){
            arr[i][j] = 0;
        }
    }

    Spirall(arr, 0, 0, 1, 0);

    for(int i = 0; i < x; i++){
        for(int j = 0; j < y; j++){
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }

    // Deallocate memory
    for(int i = 0; i < x; i++) delete[] arr[i];
    delete[] arr;

    return 0;
}

