#include <iostream>
using namespace std;

int main(int argv, char* args[])
{
    int n; cin >> n;
    string* arr = new string[n];
    for(int i = 0; i < n; i++){
        cin >> arr[i];
    }
    string* reversearr = new string[n];

    for(int i = 0; i < n; i++){
        string temp = "";
        string password = arr[i];
        int k = password.length();
        for(int j = k - 1; j >= 0; j--){
            temp = temp + password[j];
        }
        reversearr[i] = temp;
    }

    for(int i = 0; i < n; i++){
        string password = arr[i];
        int passLength = password.length();
        if( passLength % 2 == 0) continue;
        for(int j = 0; j < n; j++)
        if(password == reversearr[j]){cout << password.length() << " " << password[passLength / 2]; goto End;}
    }

    End:
    delete[] arr;
    delete[] reversearr;
    return 0;
}
