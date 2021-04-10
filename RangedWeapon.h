#pragma once
/** Michael Patrick
4/8/21/
RangedWeapon

Class for specifying ranged weapons for use by Character objects
in Warhammer-Simulator.

Ranged Weapons have the following attributes:

[Name][Range][Type][number of attacks][Strength]
[Armor Piercing][Damage][Abilities]

OR

[N][R][T][A][S][AP][D][Ab.]

These will all be immutable data members. The values of the initialized
weapon can not be changed.
*/

#include <string>
#include "Character.h"

using namespace std;

class RangedWeapon
{
private:
   string name_;
   int range_;
   string type_;
   int attacks_;
   int strength_;
   int ap_;
   int damage_;
   string abilities_;


public:
   /** Must construct a ranged weapon with the following attributes:
   [N][R][T][A][S][AP][D][Ab.]

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
   Postcondition: A RangedWeapon object is initialized with the above
   attributes. */
   RangedWeapon(Character user, string name, int range, string type, int attacks, int strength,
      int ap, int damage, string abilities);


   /** Returns the weapon's name.
   
   Precondition: None.
   Postcondition: Returns a string. */
   string getName() const;

   /** Returns the weapon's range (in inches).
   
   Precondition: None.
   Postcondition: Returns an int. */
   int getRange() const;

   /** Returns the weapon's type.
   
   Precondition: None.
   Postcondition: Returns a string. */
   string getType() const;

   /** Returns the number of attacks the weapon uses. 
   
   Precondition: None.
   Postcondition: Returns an int. */
   int getAttacks() const;

   /** Returns the strength of the weapon. 
   
   Precondition: None.
   Postcondition: Returns an int. */
   int getStrength() const;
   
   /** Returns the armor piercing value of the weapon as a 
   positive value. 
   
   Precondition: None.
   Postcondition: Returns an int. */
   int getAP() const;

   /** Returns the damage of each hit of the weapon.
   
   Precondition: None.
   Postcondition: Returns an int. */
   int getDamage() const;

   /** Returns any abilities the weapon has.
   
   Postcondition: Returns a string, formatted as follows:
   [ability one] [ability two] ... etc. */
   string getAbilities() const;
};