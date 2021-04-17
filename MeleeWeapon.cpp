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

#include "Character.h"
#include "MeleeWeapon.h"
#include <string>

using namespace std;

/** Basic constructor for melee weapons. All MeleeWeapon objects
must have all of the following paramaters in order to be
initialized.

[N][S][AP][D][Ab.]

"characterStrength" is the strength of the Character using the weapon.
"name" is a string
"range" is an int
"type" is a string
"attacks" is an int
"strength" is an int
"ap" is an int
"damage" is an int
"abilities" is a string

Notes:
If the strength value passed is -1, the strength value will be taken from
"user"

Precondition: None.
Postcondition: Creates a fully initalized MeleeWeapon object. */
MeleeWeapon::MeleeWeapon(int characterStrength, string name, int strength, int ap, int damage, string abilities) :
   name_(name), strength_(strength), ap_(ap), damage_(damage), abilities_(abilities)
{
   if (strength < 0) {
      strength_ = characterStrength;
   }
}

/** Returns the name of the melee weapomn.

Precondition: None.
Postcondition: Returns a string. */
string MeleeWeapon::getName() const
{
   return name_;
}

/** Returns the strength of the melee weapon.

Precondition: None.
Postcondition: Returns an int. */
int MeleeWeapon::getStrength() const
{
   return strength_;
}

/** Returns the armor piercing value of the melee weapon.

Precondition: None.
Postcondition: Returns an int. */
int MeleeWeapon::getAP() const
{
   return ap_;
}

/** Returns the damage value of each hit of the melee weapon.

Precondition: None.
Postcondition: Returns an int. */
int MeleeWeapon::getDamage() const
{
   return damage_;
}

/** Returns a string of all of the abilities the melee weapon has.

Precondition: None.
Postcondition: Returns a string, formatted as follows:
[ability one] [ability two] ... etc. */
string MeleeWeapon::getAbilities() const
{
   return abilities_;
}

/** Displays the weapon characteristics in the order
initialized as a string.

Precondition: None.
Postcondition: Returns a string. */
string MeleeWeapon::toString() const
{
   string result = "";
   result += getName() + " ";
   result += to_string(getStrength()) + " ";
   result += to_string(getAP()) + " ";
   result += to_string(getDamage()) + " ";
   result += getAbilities();

   return result;
}