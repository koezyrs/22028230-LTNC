#include <iostream>
using namespace std;
void solve(char** world, int currentRow, int currentColumn, const int &H, const int &W, bool &success)
{
    if(currentRow < 0 ||  currentColumn < 0 || currentRow >= H || currentColumn >= W) return;
    if(world[currentRow][currentColumn] == 'R') return;
    if(currentRow == H - 1) {success = true; return;}
    if(!success) solve(world, currentRow + 1, currentColumn, H, W, success);
    if(!success && world[currentRow][currentColumn + 1] == 'E') solve(world, currentRow + 1, currentColumn + 1, H, W, success);
    if(!success && world[currentRow][currentColumn - 1] == 'E') solve(world, currentRow + 1, currentColumn - 1, H, W, success);
}

int main(int argv, char* args[])
{
    int H, W; cin >> H >> W;
    char** world = new char*[H];
    for(int i = 0; i < H; i++) world[i] = new char[W];

    int startRow, startColumn;
    for(int i = 0; i < H; i++){
        for(int j = 0; j < W; j++){
            cin >> world[i][j];
            if(world[i][j] == 'Y'){startRow = i; startColumn = j;}
        }
    }

    bool success = false;
    solve(world, startRow, startColumn, H, W, success);

    if(success) cout << "YES";
    else cout << "NO";

    // Deallocates Memories
    for(int i = 0; i < H; i++) delete[] world[i];
    delete[] world;
    return 0;
}
