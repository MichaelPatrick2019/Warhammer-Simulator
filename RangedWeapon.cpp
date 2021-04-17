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
#include "RangedWeapon.h"

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
RangedWeapon::RangedWeapon(Character user, string name, int range, string type, int attacks, int strength,
   int ap, int damage, string abilities) : name_(name), range_(range), type_(type), attacks_(attacks), 
   strength_(strength), ap_(ap), damage_(damage), abilities_(abilities)
{
   if (strength < 0) strength_ = user.getStrength();
}

/** Returns the weapon's name.

Precondition: None.
Postcondition: Returns a string. */
string RangedWeapon::getName() const
{
   return name_;
}

/** Returns the weapon's range (in inches).

Precondition: None.
Postcondition: Returns an int. */
int RangedWeapon::getRange() const
{
   return range_;
}

/** Returns the weapon's type.

Precondition: None.
Postcondition: Returns a string. */
string RangedWeapon::getType() const
{
   return type_;
}

/** Returns the number of attacks the weapon uses.

Precondition: None.
Postcondition: Returns an int. */
int RangedWeapon::getAttacks() const
{
   return attacks_;
}

/** Returns the strength of the weapon.

Precondition: None.
Postcondition: Returns an int. */
int RangedWeapon::getStrength() const
{
   return strength_;
}

/** Returns the armor piercing value of the weapon as a
positive value.

Precondition: None.
Postcondition: Returns an int. */
int RangedWeapon::getAP() const
{
   return ap_;
}

/** Returns the damage of each hit of the weapon.

Precondition: None.
Postcondition: Returns an int. */
int RangedWeapon::getDamage() const
{
   return damage_;
}

/** Returns any abilities the weapon has.

Postcondition: Returns a string, formatted as follows:
[ability one] [ability two] ... etc. */
string RangedWeapon::getAbilities() const
{
   return abilities_;
}