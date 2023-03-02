// Game dò mìn đơn giản
#include <bits/stdc++.h>
using namespace std;

int moveRow[8] = {-1, -1, -1, 0 , 0, 1, 1, 1};
int moveColumn[8] ={-1, 0, 1, -1, 1, -1, 0, 1};

void generateSpike(int width, int height, int spikes, char** &Map)
{
    int row, column;
    for(int i = 0; i < spikes; i++)
    {
        GenerateSpike:
        row = rand() % height;
        column = rand() % width;
        if(Map[row][column] == '*') goto GenerateSpike;
        Map[row][column] = '*';
        for(int i = 0; i < 8; i++)
        {
            int next_row = row + moveRow[i];
            int next_column = column + moveColumn[i];
            if(next_row < 0 || next_column < 0 || next_row >= height || next_column >= width) continue;
            if(Map[next_row][next_column] == '*') continue;
            Map[next_row][next_column] = (char)(Map[next_row][next_column] + 1);
        }
    }
    return;
}

void gameOver(int width, int height, char** &Map, char** &playingMap, bool success)
{
    system("CLS");
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            if(Map[i][j] == '*') cout << Map[i][j] << " ";
            else cout << playingMap[i][j] << " ";
        }
        cout << endl;
    }

    if(success) cout << "YOU WIN!";
    else cout << "YOU ARE DEAD!";
}

void spreadBoard(int width, int height, int currentRow, int currentColumn, char** &Map, char** &playingMap, int &score)
{
    for(int i = 0; i < 8; i++)
    {
        int next_row = currentRow + moveRow[i];
        int next_column = currentColumn + moveColumn[i];
        if(next_row < 0 || next_column < 0 || next_row >= height || next_column >= width) continue;
        if(playingMap[next_row][next_column] != '-') continue;
        score++;
        playingMap[next_row][next_column] = Map[next_row][next_column];
        if(Map[next_row][next_column] == '0') spreadBoard(width, height, next_row, next_column, Map, playingMap, score);
    }
}

void gameLoop(int width, int height, int spikes, char** &Map, char** &playingMap)
{
    int score = 0;
    int currentRow, currentColumn;
    bool success = true;
    GameLoop:
    // Xoá màn hình và in ra bản đồ của người chơi
    system("CLS");
    for(int i = 0; i < height; i++)
    {
        for(int j = 0 ; j < width; j++)
        {
            cout << playingMap[i][j] << " ";
        }
        cout << endl;
    }

    // In ra điểm của người chơi hiện tại và lấy dữ liệu đầu vào
    cout << "Your score = " << score << endl;
    cout << "Hay chon mot o [Row][Column]: "; cin >> currentRow >> currentColumn;
    while(currentRow < 0 || currentRow >= height || currentColumn < 0 || currentColumn >= width || playingMap[currentRow][currentColumn] != '-')
    {
        cout << "O khong hop le, hay nhap lai: "; cin >> currentRow >> currentColumn;
    }

    // Kiểm tra điều kiện xem ô đó có mìn hay không
    if(Map[currentRow][currentColumn] != '*')
    {
        if(Map[currentRow][currentColumn] == '0')
        {
            score = score + 1;
            playingMap[currentRow][currentColumn] = Map[currentRow][currentColumn];
            spreadBoard(width, height, currentRow, currentColumn, Map, playingMap, score);
        }else{
            score = score + 1;
            playingMap[currentRow][currentColumn] = Map[currentRow][currentColumn];
        }
        if(score == width * height - spikes) {gameOver(width, height, Map, playingMap, success); return;}
        goto GameLoop;
    }else{
        success = false;
        gameOver(width, height, Map, playingMap, success);
    }
    return;
}

int main(int argv, char* args[])
{
    srand(time(0));
    int width, height, spikes;

    PlayAgain:
    // Xoá màn hình
    system("CLS");
    cout << "Nhap so hang cua ban do: "; cin >> height;
    cout << "Nhap so cot rong cua ban do: "; cin >> width;
    cout << "Nhap so qua min: "; cin >> spikes;

    // Tạo hai mảng: 1 mảng đánh dấu vị trí của mìn + chỉ số các ô, 1 mảng để hiển thị cho người chơi
    char** Map = new char*[height];
    char** playingMap = new char*[height];
    for(int i = 0 ; i < height; i++){Map[i] = new char[width]; playingMap[i] = new char[width];}

    for(int i = 0 ; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            Map[i][j] = '0';
            playingMap[i][j] = '-';
        }
    }

    // Tạo mìn ở các ô ngẫu nhiên trên bản đồ
    generateSpike(width,height,spikes, Map);

    // Bắt đầu chơi game
    gameLoop(width, height, spikes, Map, playingMap);
    for(int i = 0; i < height; i++) {delete[] Map[i]; delete[] playingMap[i];}
    delete[] Map;
    delete[] playingMap;

    // Chơi lại
    cout << endl;
    cout << "Ban co muon choi lai? An [Y] de choi lai hoac phim khac de thoat: ";
    char c; cin >> c;
    switch(c)
    {
    case 'Y':
        goto PlayAgain;
        break;
    case 'y':
        goto PlayAgain;
        break;
    default:
        break;
    }
    return 0;
}
