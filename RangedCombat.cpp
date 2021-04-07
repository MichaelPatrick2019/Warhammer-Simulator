/** Michael Patrick
4/6/21
Warhammer-Simulator

Inherits the Combat class, and provides specific functionality
for ranged combat between two Characters. */

#include "Combat.h"
#include "RangedCombat.h"

/** Method that executes ranged combat between two Character
objects.

"attacker" and "defender" are both Character objects passed by reference.

Precondition: Both Character objects should be initialized correctly.
Postcondition: Edits the health attribute of each Character to reflect
the result of the combat. Returns true if succesful fight. Returns false
if not - for example, if the health attribute of a character is zero. */
bool RangedCombat::fight(Character* attacker, Character* defender)
{
   attacker->rangedAttack(*defender);
   return true; //To Do: add way to check for zero health
}