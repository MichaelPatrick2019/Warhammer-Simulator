#pragma once
/** Michael Patrick
4/6/21
Warhammer-Simulator

General parent class for all kinds of combat between
two Character units for Warhammer-Simulator.

All subclasses are required to implement a fight() method
specific to their unique combat type. */

#include "Character.h"

class Combat
{
public:

   /** Method that executes some type of combat between two Character
   objects.

   "attacker" and "defender" are both Character objects passed by reference.
   
   Precondition: Both Character objects should be initialized correctly.
   Postcondition: Edits the health attribute of each Character to reflect
   the result of the combat. Returns true if succesful fight. Returns false
   if not - for example, if the health attribute of a character is zero. */
   virtual bool fight(Character* attacker, Character* defender) = 0;
   

};
