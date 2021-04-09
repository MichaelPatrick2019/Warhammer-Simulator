#pragma once
/** Michael Patrick
4/6/21
MeleeWeapon
Warhammer-Simulator

Class for specifying melee weapons for use by Character objects
in Warhammer-Simulator.

Melee weapons have the following attributes:

[Name] [Strength] [Armor Piercing] [Damage] [Abilities]

OR

[N] [S] [AP] [D] [Ab.]
*/

#include <string>
#include "Character.h"

using namespace std;

class MeleeWeapon
{
private:
   string name_;
   int strength_;
   int ap_;
   int damage_;
   string abilities_;

public:
   /** Basic constructor for melee weapons. All MeleeWeapon objects
   must have all of the following paramaters in order to be
   initialized.

   [N][S][AP][D][Ab.]

   "Character" is the character that will be using the weapon.
   "name" is a string
   "range" is an int
   "type" is a string
   "attacks" is an int
   "strength" is an int
   "ap" is an int
   "damage" is an int
   "abilities" is a string
   
   Precondition: None.
   Postcondition: Creates a fully initalized MeleeWeapon object. */
   MeleeWeapon(Character user, int strength, int ap, int damage, string abilities);

   /** Returns the name of the melee weapomn.
   
   Precondition: None.
   Postcondition: Returns a string. */
   string getName();

   /** Returns the strength of the melee weapon. 
   
   Precondition: None.
   Postcondition: Returns an int. */
   int getStrength();

   /** Returns the armor piercing value of the melee weapon. 
   
   Precondition: None.
   Postcondition: Returns an int. */
   int getAP();

   /** Returns the damage value of each hit of the melee weapon.
   
   Precondition: None.
   Postcondition: Returns an int. */
   int getDamage();

   /** Returns a string of all of the abilities the melee weapon has.
   
   Precondition: None.
   Postcondition: Returns a string, formatted as follows:
   [ability one] [ability two] ... etc. */
   string getAbilities();
};