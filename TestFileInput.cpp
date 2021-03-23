/** Quick main() for testing Army file input constructor. */
#include "Army.h"
#include "Character.h"
#include <string>
int main()
{
   cout << "Testing adding Characters to an army by file." << endl;
   Army newArmy("army.txt");
   cout << newArmy;

   cout << "Searching for Test Character Two: " << endl;
   Character* trueCharacter = newArmy.retrieve((string)"Test Character Two");
   if (trueCharacter != nullptr) {
      cout << *trueCharacter << endl;
   }

   cout << "Searching for Paul McCartney: " << endl;
   Character* falseCharacter = newArmy.retrieve((string)"Paul McCartney");
   if (falseCharacter != nullptr) {
      cout << *falseCharacter << endl;
   }
}