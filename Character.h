#pragma once

/** @ Character.h */

/** Straightforward object that stores all of the necessary information
about a given warhammer character. Considers inherent stats, ranged and
melee weapons, as well as detailed output to the outstream when
engaging in combat with other characters. */

#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Character
{
private:
   string name;
   int stats[9]; //Array of ints of inherent stats.
   bool psyker; //Does the character manifest psychic abilities?

   //Unknown number of weapons...
   vector<string[6]> rangedWeapons; //Must account for certain keywords
   vector<string[4]> melee; //Also has special keywords that are input as strings

public:

   /** Default constructor for a character. Doesn't need to have anything allocated
   at the start. Defaults all fields to default values.
   
   Precondition: None.
   Postcondition: A Character object is created. */
   Character();

   /** Sets the name of the character to the provided input.
   
   "input" is a string - what the name will be set to.

   Precondition: None.
   Postcondition: The character's name is changed to the given
   string. Returns true if succesful. */
   bool setName(string input);

   /** Sets the stats of the character to the input. Takes in a string.
   
   "input" is a string in a specified format...
   
   [M] [WS] [BS] [S] [T] [W] [A] [Ld] [Sv]

   Precondition: The string must observe the correct format.
   Postcondition: The stats are stored in the character. Returns
   true if succesful. */
   bool setStats(string input);

   /** Adds a weapon to the collection of ranged weapons. Characters
   may have multiple ranged weapons. 
   
   "input" is a string formatted to represent a ranged weapon...

   [Name] [Range] [Type] [number of attacks] [S] [AP] [Abilities]
   
   Precondition: The input string must adhere to the above format.
   Postcondition: The ranged weapon is added, and will be used to calculate
   ranged damage output in combat. Returns true if succesful. */
   bool setRanged(string input);

   /** Adds a melee weapon to the collection of ranged weapons. Characters
   may have multiple melee weapons they can choose from in melee combat.
   Accounts for the special case of certain melee weapons that are used to
   provide additional attacks alongside other melee weapons.
   
   "input" is a string formatted to represent a melee weapon.
   
   [Name] [S] [AP] [D] [Abilities]
   
   Precondition: The input string must adhere to the above format.
   Postcondition: The melee weapon is added, and will be referenced when
   offering players the option of melee weapon they would like to use in
   combat. Returns true if succesful. */
   bool setMelee(string input);

   /** Sets the psychic abilities of the unit if the unit is a psyker.
   * References the psychic ability from a database.
   
   "input" is the name of the psychic ability as a string.

   Precondition: None.
   Postcondition: The psychic ability is added to the given character
   for potential use during the psychic phase. Returns true if the
   added ability is valid, and labels the character as a psyker.
   If it's not, returns false, and doesn't
   add the psychic ability to the character. */
   bool setPsychic(string input);

   /** References the stored list of psychic abilities and lists them
   for the player to choose from. Outputs the options to the output.
   
   Precondition: None.
   Postcondition: Outputs the list of psychic abilities that can be
   used. */
   void listPsychicAbilities() const;

   /** Attacks another character with a psychic ability.
   
   "other" is another character object, friend or ally.

   ability is an int representing indicating which psychic ability
   is being manifested.
   
   Precondition: Assumes the player has been provided with a list
   of that units psychic abilities.
   Postcondition: Modifies the passed character object based
   on the results of the psychic phase. */
   void psychicOther(int ability, Character& other);

   /** Casts the psychic ability for that round of the battle. 
   Used for psychic abilities that buff the character casting it.

   Note: Implementing denials??

   "ability" is an int representing which ability is being used.

   Precondition: Assumes the player has been provided with a list
   of that units psychic abilities.
   Postcondition: Casts psychic ability on self for that round. */
   void psychicSelf(int ability);

   /** Performs a ranged attack upon an enemy character.
   
   "enemy" is another character passed by value.

   Precondition: Assumes all of this character's ranged
   weapons will be used on the enemy.

   Postcondition: Modifies the passed character based on
   the outcome of the ranged attack Lists the results of each
   dice roll to output as well. */
   void rangedAttack(Character& enemy);

   /** Performs a melee attack upon an enemy character.
   
   "enemy" is another character passed by value.
   
   Precondition: Assumes a list of melee option have been provided
   to the player.
   Postcondition: Modifies the enemy character based on the outcome
   of the attack. Also provides a list of simulated dice rolls to
   the output. */
   void meleeAttack(Character& enemy);

   /** Performs a morale test on the unit.
   
   Precondition: None.
   Postcondition: Modifies this unit based on the outcome
   of their morale test. Outputs simulated dice rolls to
   the output. */
   void moraleTest();
};