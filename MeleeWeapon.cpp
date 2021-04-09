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
#include "MeleeWeapon.h"
#include "Character.h"

using namespace std;

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

Notes:
If the strength value passed is -1, the strength value will be taken from
"user"

Precondition: None.
Postcondition: Creates a fully initalized MeleeWeapon object. */
MeleeWeapon::MeleeWeapon(Character user, int strength, int ap, int damage, string abilities)
{
}