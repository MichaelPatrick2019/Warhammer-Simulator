#pragma once
/** Michael Patrick
4/6/21
Warhammer-Simulator

Hash table that returns particular dummy classes that can
execute particular combat methods. */

#include "Combat.h"
#include "RangedCombat.h"
#include "MeleeCombat.h"

class CombatFactory
{
private:

    const int BUCKET_CAPACITY = 99;

   //Small bucket - only 2 maximum combat types (for now)
   Combat* buckets[99] = { };

   /** Hashes a string into the hash table.
   
   "input" is some string input
   
   Precondition: None.
   Postcondition: Returns an int, that represents an index for
   the hash table */
   int hash(string input);

   /** Adds a particular Combat pointer associated with a given
   word.
   
   Precondition: None.
   Postcondition: Checks for collisions. Returns true if succesfully
   added. */
   bool add(string input, Combat* combatPointer);

public:

   /** Basic constructor for the hash table, where the strings
   "melee" and "ranged" must be initialized to the appropriate
   dummy objects.
   
   Precondition: None.
   Postcondition: A CombatFactory is created, with "melee" and
   "ranged" initialized to specific dummy objects. */
   CombatFactory();

   /** Destructor for CombatFactory. Very simple - must delete the 
   Character* pointers stored in the buckets. 
   
   Precondition: None.
   Postcondition: All dynamically allocated objects are destroyed. */
   ~CombatFactory();

   /** Generates a index based on the input string.
   For this class, it will need to index, specifically, "melee" and
   "ranged". 

   "input" is some string.
   
   Precondition: None.
   Postcondition: Returns a Combat pointer, from which the caller is
   expected to call the fight() method. */
   Combat* generateCombatObject(string input);
};