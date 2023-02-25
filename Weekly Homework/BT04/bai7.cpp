#include <iostream>
#include <string>
using namespace std;

void Listing(const string &s, string res, const int &n)
{
    if(res.length() > 3) return;
    if(res.length() >= 2) cout << res << " ";
    for(int i = 0; i < n; i++){
        string temp = res + s[i];
        Listing(s, temp, n);
    }
    return;
}

int main(int argv, char* args[])
{
    string s; cin >> s;
    int n = s.length();
    string res = "";
    Listing(s, res, n);
    return 0;
}
