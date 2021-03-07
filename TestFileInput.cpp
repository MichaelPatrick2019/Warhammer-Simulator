/** Quick main() for testing Army file input constructor. */
#include "Army.h"
#include <string>
int main()
{
   cout << "Testing adding Characters to an army by file." << endl;
   Army newArmy("army.txt");
   cout << newArmy;
}