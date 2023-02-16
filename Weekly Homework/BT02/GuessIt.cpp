#include <bits/stdc++.h>

using namespace std;

void init(int &n){
    n = rand()%99 + 1;
    return;
}

void gameLoop(const int &randNumber){
    int guessNumber;
    bool correct = false;

    cout << "Moi doan 1 so: "; cin >> guessNumber;
    do{
        if(guessNumber > randNumber) {cout << "So qua lon, moi nhap lai: "; cin >> guessNumber;}
        else if(guessNumber < randNumber) {cout << "So qua be, moi nhap lai: "; cin >> guessNumber;}
        else if(guessNumber == randNumber) correct = true;
    }while(!correct);
    cout << "Doan dung!" << endl;
}

int main(int argc, char* args[]){
    srand(time(0));
    int randNumber = 0;
    Play:
    init(randNumber);
    system("CLS");
    gameLoop(randNumber);
    cout << "Ban co muon choi lai? An 'Y' de choi lai hoac 'N' de thoat: ";
    char c; cin >> c;
    switch(c){
    case 'Y':
        goto Play;
        break;
    case 'y':
        goto Play;
        break;
    default:
        break;
    }
    return 0;
}
