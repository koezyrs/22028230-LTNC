#include <iostream>
using namespace std;

int main( )
{
    /* Câu a
   char a[4] = "abc";
   for (char *cp = a; (*cp) != '\0'; cp++) {
      cout << (void*) cp << " : " << (*cp) << endl;
   }
   */

    /* Câu b
   int a[5] = {1,2,3,4, NULL};
   for (int *cp = a; (*cp) != NULL; cp++) {
      cout << (void*) cp << " : " << (*cp) << endl;
   }
   */

    /* Câu c
   double a[5] = {1,2,3,4, NULL};
   for (double *cp = a; (*cp) != NULL; cp++) {
      cout << (void*) cp << " : " << (*cp) << endl;
   }
   */

    /* Câu d
    double a[5] = {1,2,3,4, NULL};
    for (double *cp = a; (*cp) != NULL; cp+=2) {
        cout << (void*) cp << " : " << (*cp) << endl;
    }
   */
   return 0;
}

