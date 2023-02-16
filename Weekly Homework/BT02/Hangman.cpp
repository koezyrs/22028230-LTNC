#include <bits/stdc++.h>

using namespace std;

const int MAX_WORD = 200;

const string word[MAX_WORD] = {
        "angle", "ant", "apple", "arch", "arm", "army",
        "baby", "bag", "ball", "band", "basin", "basket", "bath", "bed", "bee", "bell", "berry",
        "bird", "blade", "board", "boat", "bone", "book", "boot", "bottle", "box", "boy",
        "brain", "brake", "branch", "brick", "bridge", "brush", "bucket", "bulb", "button",
        "cake", "camera", "card",  "cart", "carriage", "cat", "chain", "cheese", "chest",
        "chin", "church", "circle", "clock", "cloud", "coat", "collar", "comb", "cord",
        "cow", "cup", "curtain", "cushion",
        "dog", "door", "drain", "drawer", "dress", "drop", "ear", "egg", "engine", "eye",
        "face", "farm", "feather", "finger", "fish", "flag", "floor", "fly",
        "foot", "fork", "fowl", "frame", "garden", "girl", "glove", "goat", "gun",
        "hair", "hammer", "hand", "hat", "head", "heart", "hook", "horn", "horse",
        "hospital", "house", "island", "jewel",  "kettle", "key", "knee", "knife", "knot",
        "leaf", "leg", "library", "line", "lip", "lock",
        "map", "match", "monkey", "moon", "mouth", "muscle",
        "nail", "neck", "needle", "nerve", "net", "nose", "nut",
        "office", "orange", "oven", "parcel", "pen", "pencil", "picture", "pig", "pin",
        "pipe", "plane", "plate", "plow", "pocket", "pot", "potato", "prison", "pump",
        "rail", "rat", "receipt", "ring", "rod", "roof", "root",
        "sail", "school", "scissors", "screw", "seed", "sheep", "shelf", "ship", "shirt",
        "shoe", "skin", "skirt", "snake", "sock", "spade", "sponge", "spoon", "spring",
        "square", "stamp", "star", "station", "stem", "stick", "stocking", "stomach",
        "store", "street", "sun", "table", "tail", "thread", "throat", "thumb", "ticket",
        "toe", "tongue", "tooth", "town", "train", "tray", "tree", "trousers", "umbrella",
        "wall", "watch", "wheel", "whip", "whistle", "window", "wire", "wing", "worm"
};

const string FIGURE[8] = {
    "   -------------    \n"
    "   |                \n"
    "   |                \n"
    "   |                \n"
    "   |                \n"
    "   |     \n"
    " -----   \n",

    "   -------------    \n"
    "   |           |    \n"
    "   |                \n"
    "   |                \n"
    "   |                \n"
    "   |     \n"
    " -----   \n",

    "   -------------    \n"
    "   |           |    \n"
    "   |           O    \n"
    "   |                \n"
    "   |                \n"
    "   |     \n"
    " -----   \n",

    "   -------------    \n"
    "   |           |    \n"
    "   |           O    \n"
    "   |           |    \n"
    "   |                \n"
    "   |     \n"
    " -----   \n",

    "   -------------    \n"
    "   |           |    \n"
    "   |           O    \n"
    "   |          /|    \n"
    "   |                \n"
    "   |     \n"
    " -----   \n",

    "   -------------    \n"
    "   |           |    \n"
    "   |           O    \n"
    "   |          /|\\  \n"
    "   |                \n"
    "   |     \n"
    " -----   \n",

    "   -------------    \n"
    "   |           |    \n"
    "   |           O    \n"
    "   |          /|\\  \n"
    "   |          /     \n"
    "   |     \n"
    " -----   \n",

    "   -------------    \n"
    "   |           |    \n"
    "   |           O    \n"
    "   |          /|\\  \n"
    "   |          / \\  \n"
    "   |     \n"
    " -----   \n"
};


void init(int &randomNumber){
    randomNumber = rand()%MAX_WORD;
    return;
}

void check(const string &guessWord, const char &guessChar, const int &n, int &mistake,
           int &countChar, string &playerAnswer)
{
    bool correct = false;
    for(int i = 0; i < n; i++){
        if(guessWord[i] == guessChar && playerAnswer[i] == '*'){
            playerAnswer[i] = guessChar;
            countChar++;
            correct = true;
        }
    }

    if(!correct) mistake++;
    return;
}

void gameLoop(const string &guessWord)
{
    int mistake = 0, countChar = 0;
    char guessChar;
    int n = guessWord.size();
    string playerAnswer = "";
    for(int i = 0; i < n; i++) playerAnswer += "*";

    do
    {
        // Clear screen
        system("CLS");

        // Draw game
        cout << FIGURE[mistake] << endl;
        cout << "Your answer: ";
        for(int i = 0; i < n; i++) cout << playerAnswer[i];
        cout << endl;

        // Player guess
        if(mistake == 7 || countChar == n) break;
        cout << "Guess a character: "; cin >> guessChar;
        check(guessWord, guessChar, n, mistake, countChar, playerAnswer);

    }while(mistake <= 7 && countChar <= n);

    // Show the answer
    cout << "The answer is: ";
    for(int i = 0; i < n; i++) cout << guessWord[i];
    cout << endl;

    if(mistake == 7) cout << "Lose!" << endl;
    else cout << "Win!" << endl;


    return;
}

int main(int argc, char* args[])
{
    srand(time(0));
    Play:
        // Setup word
        int randNumber = 0;
        init(randNumber);
        string guessWord = word[randNumber];

        // Play game
        gameLoop(guessWord);

        // Play again
        cout << "Ban co muon choi lai khong? Choi lai an 'Y' hoac an 'N' de thoat game: ";
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

