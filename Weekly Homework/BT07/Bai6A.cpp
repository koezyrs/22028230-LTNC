#include <iostream>
#include <cstring>
using namespace std;

int main(int argc, const char * argv[]) {
	cout << "Number of command-line arguments: " << argc << endl;
	for (int i = 0; i < argc; i++) {
		cout << "Argument #" << i << ": _" << argv[i] << "_\n";
	}

	if(strcmp(argv[1], "1") == 0)
    {
        cout << "Program is running" << endl;
    }else
    {
        cout << "Please run the program with argument 1" << endl;
    }
	return 0;
}

