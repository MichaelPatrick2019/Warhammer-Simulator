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
   else {
      cout << endl;
   }

   Character* first = trueCharacter;
   Character* second = newArmy.retrieve((string)"Test Character One");
   cout << endl;

   //Testing combat...
   //cout << "test char two attacking test char one:" << endl;
   //first->meleeAttack(*second);
   //cout << endl << endl;

   //cout << "test char two attacking test char one again:" << endl;
   //first->meleeAttack(*second);
   //cout << endl;


   cout << "test char two shooting char one" << endl;
   first->rangedAttack(*second);
   cout << endl;
}