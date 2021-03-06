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

const int NUM_STATS = 10;
const int NUM_RANGED = 7;
const int NUM_MELEE = 5;

class Character
{
private:
   string name_;
   int stats_[NUM_STATS]{ }; //Array of ints of inherent stats.
   bool psyker_; //Does the character manifest psychic abilities?

   vector<string*> psychicAbilities_; //Store as list of strings
                                      //of abilities

   //Unknown number of weapons...
   //Destructor has to manage this dynamically allocated memory!
   vector<vector<string>*> rangedWeapons_; //Must account for certain keywords
   vector<vector<string>*> melee_; //Also has special keywords that are input as
   //strings

   /** Private helper function that creates a vector and pushes it
   to the appropriate data field.
   
   Precondition: Only works in relation to extant data fields, so the
   sizeOfWeaponData should be either NUM_STATS, NUM_RANGED, or NUM_MELEE.
   Postcondition: Adds a weapon to the rangedWeapons or melee field vectors.
   Returns true if succesful. */
   bool setWeapon(string input, int sizeOfWeaponData);

public:

   //Make me private please!
   /** Basic function that splits a string by a certain delimiter and returns
   a string array.
   
   "delimiter" is a string used as a delimiter.
   "str" is the string to be broken up.

   Precondition: None.
   Postcondition: Returns a pointer to a string vector,
   broken up by the given delimiter.
   The calling function must delete the dynamically allocated vector.
   */
   vector<string>* split(string delimiter, string str);

   //Make me private!!!
   /** Private helper function that takes a given vector full of
   vector pointers and fully deletes them.
   
   Precondition: Passed object must be a vector of pointers to
   string vectors.
   Postcondition: All dynamically allocated memory stored in the
   passed vector is deleted. */
   void deleteVectorOfVectors(vector<vector<string>*>& toDelete);

   /** Default constructor for a character. Doesn't need to have anything allocated
   at the start. Defaults all fields to default values.
   
   Precondition: None.
   Postcondition: A Character object is created. */
   Character();

   /** Needs to manage all of the dynamically allocated memory in
   psychicAbilities_, rangedWeapons_, and melee_ */
   //Implement me!!!
   ~Character();

   /** Sets the name of the character to the provided input.
   
   "input" is a string - what the name will be set to.

   Precondition: None.
   Postcondition: The character's name is changed to the given
   string. Returns true if succesful. */
   bool setName(string input);

   /** Sets the stats of the character to the input. Takes in a string.
   
   "input" is a string in a specified format...
   
   [M] [WS] [BS] [S] [T] [W] [A] [Ld] [Armor Sv] [Invuln Sv]

   If your character doesn't have a save, enter 0 for that value.
   Rolls will be calculated based on whichever is higher.

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
   
   "input" is the name of any number of psychic abilities as a string.
   Separate abilities by a space...
   [Psychic Ability 1] [Psychic Ability 2] ...

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

   /**Overloaded output operator that displays the name, stats,
   psychic abilities, ranged abilities, and melee abilities of the unit
   to the output stream. 

   "os" is the output stream.
   "character" is the passed Character object whose data is to be
   output.
   
   Precondition: None.
   Postcondition: Outputs series of strings to the output stream.*/
   friend ostream& operator<<(ostream& os, const Character& character);

   /** Overloaded less than operator so the class can be added
   to a binary search tree. Determined based on name field.

   "other" is another Character object.
   
   Precondition: Character must have a name.
   Postcondition: Returns true if given character is less than
   other. Otherwise returns false. */
   bool operator<(const Character& other);

   /** Overloaded greater than operator so the class can be added
   to a binary search tree. Determined based on name field.

   "other" is another Character object.

   Precondition: Character must have a name.
   Postcondition: Returns true if given character is greater than
   other. Otherwise returns false. */
   bool operator>(const Character& other);
};