/** Michael Patrick
4/6/21
Warhammer-Simulator

Hash table that returns particular dummy classes that can
execute particular combat methods. */

#include "CombatFactory.h"
#include <string>

using namespace std;

/** Hashes a string into the hash table.

"input" is some string input

Precondition: None.
Postcondition: Returns an int, that represents an index for
the hash table */
int CombatFactory::hash(string input) const
{
   int index = 0;

   char charray[100];
   strcpy_s(charray, input.c_str());

   for (int i = 0; i < (int)input.size(); i++) {
      index += (int)charray[i];
   }

   return index % BUCKET_CAPACITY;
}

/** Adds a particular Combat pointer associated with a given
word.

Precondition: None.
Postcondition: Checks for collisions. Returns true if succesfully
added. */
bool CombatFactory::add(string input, Combat* combatPointer)
{
   int index = hash(input);

   if (buckets[index] == nullptr) {
      buckets[index] = combatPointer;
   }
   else {
      int count = BUCKET_CAPACITY;

      while (buckets[index] == nullptr) {
         index += 1;
         count--;

         if (count < 0) return false;
      }

      buckets[index] = combatPointer;
   }

   return true;
}

/** Basic constructor for the hash table, where the strings
"melee" and "ranged" must be initialized to the appropriate
dummy objects.

Precondition: None.
Postcondition: A CombatFactory is created, with "melee" and
"ranged" initialized to specific dummy objects. */
CombatFactory::CombatFactory()
{
   Combat* melee = new MeleeCombat;
   Combat* ranged = new RangedCombat;

   add((string)"melee", melee);
   add((string)"ranged", ranged);
}

/** Destructor for CombatFactory. Very simple - must delete the
Character* pointers stored in the buckets.

Precondition: None.
Postcondition: All dynamically allocated objects are destroyed. */
CombatFactory::~CombatFactory()
{
   for (int i = 0; i < BUCKET_CAPACITY; i++) {
      if (buckets[i] != nullptr) {
         delete buckets[i];
      }
   }
}

/** Generates a index based on the input string.
For this class, it will need to index, specifically, "melee" and
"ranged".

"input" is some string.

Precondition: None.
Postcondition: Returns a Combat pointer, from which the caller is
expected to call the fight() method. */
Combat* CombatFactory::generateCombatObject(string input) const
{
   return buckets[hash(input)];
}