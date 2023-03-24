#include <iostream>
#include <cstring>

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cout << "Usage: " << argv[0] << " <string1> <string2>\n";
        return 1;
    }

    const char* str1 = argv[1];
    const char* str2 = argv[2];
    int count = 0;

    while (*str2 != '\0') {
        if (strcmp(str1, str2) == 0) {
            count++;
        }
        str2++;
    }

    std::cout << "The first string appears " << count << " times in the second string.\n";
    return 0;
}
