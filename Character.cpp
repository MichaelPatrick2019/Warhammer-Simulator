/** @ Character.h */

/** Straightforward object that stores all of the necessary information
about a given warhammer character. Considers inherent stats, ranged and
melee weapons, as well as detailed output to the outstream when
engaging in combat with other characters. */

#include "Character.h"
#include "MeleeWeapon.h"
#include "RangedWeapon.h"
#include <string>
#include <iostream>
#include <vector>
#include <random>
#include <chrono>

using namespace std;

/** Default constructor for a character. Doesn't need to have anything allocated
at the start. Defaults all fields to default values.

Precondition: None.
Postcondition: A Character object is created. */
Character::Character()
{
   name_ = "[Unnamed]";
   psyker_ = false;

}

/** Needs to manage all of the dynamically allocated memory in
psychicAbilities_, rangedWeapons_, and melee_ */
Character::~Character()
{
   //Delete string pointers in psychicAbilities_
   for (string* ptr : psychicAbilities_) {
      delete ptr;
   }

   //Delete vector of vectors in rangedWeapons_
   deleteVectorOfVectors(rangedWeapons_);

   //Delete vector of vectors in melee_
   deleteVectorOfVectors(melee_);
}

//Make me private!!!
/** Private helper function that takes a given vector full of
vector pointers and fully deletes them.

Precondition: Passed object must be a vector of pointers to
string vectors.
Postcondition: All dynamically allocated memory stored in the
passed vector is deleted. */
void Character::deleteVectorOfVectors(vector<vector<string>*>& toDelete)
{
   for (vector<string>* dynamicVector : toDelete) {
      delete dynamicVector;
   }

   toDelete.clear();
}

/** Sets the name of the character to the provided input.

"input" is a string - what the name will be set to.

Precondition: None.
Postcondition: The character's name is changed to the given
string. Returns true if succesful. */
bool Character::setName(string input)
{
   name_ = input;
   return true;
}

/** Returns the name of the Character as a string.

Precondition: None.
Postcondition: Returns a string. */
string Character::getName() const
{
   return name_;
}

/** Sets the stats of the character to the input. Takes in a string.

"input" is a string in a specified format...

[M] [WS] [BS] [S] [T] [W] [A] [Ld] [Armor Sv] [Invuln Sv]

If your character doesn't have a save, enter 0 for that value.
Rolls will be calculated based on whichever is higher.

Precondition: The string must observe the correct format.
Postcondition: The stats are stored in the character. Returns
true if succesful. */
bool Character::setStats(string input)
{
   vector<string>* statList = split(" ", input);

   for (int i = 0; i < NUM_STATS; i++) {
      stats_[i] = stoi(statList->at(i));
   }

   delete statList;

   return true;
}

/** Basic function that splits a string by a certain delimiter and returns
a string array.

"delimiter" is a string used as a delimiter.
"str" is the string to be broken up.

Precondition: None.
Postcondition: Returns a pointer to a string vector,
broken up by the given delimiter.
The calling function must delete the dynamically allocated vector.
*/
vector<string>* Character::split(string delimiter, string str)
{
   vector<string>* result = new vector<string>;

   int start = 0;
   int end = str.find(delimiter);

   string word = str.substr(start, end - start);
   if (word != "") { //Edge case where function starts with delim
      result->push_back(str.substr(start, end - start));
   }

   while (unsigned(end) < str.size()) {
      start = end + 1;

      //Move start to point to next item after a delimiter
      //Or, reaches the end of the substring.
      while (unsigned(start) < str.size() && str.substr(start, delimiter.size()) == delimiter) {
         start += delimiter.size(); //Should point eventually to a non-delimiter.
      }

      if (unsigned(start) >= str.size()) start = str.size();

      //End points to the next delimiter after the object
      end = str.substr(start).find(delimiter) + start;

      //If no delimiter until end of str...
      if (str.substr(start).find(delimiter) == string::npos
         || unsigned(end) >= str.size()) end = str.size();

      result->push_back(str.substr(start, end - start));
   }

   return result;
}

/** Adds a weapon to the collection of ranged weapons. Characters
may have multiple ranged weapons. Uses the RangedWeapon class.

"input" is a string formatted to represent a ranged weapon...

[Name] [Range] [Type] [number of attacks] [S] [AP] [Abilities]

Precondition: The input string must adhere to the above format.
Postcondition: The ranged weapon is added, and will be used to calculate
ranged damage output in combat. Returns true if succesful. */
bool Character::setRangedNew(string input)
{
   vector<string>* rangedSplit = split(" ", input);

   string name = rangedSplit->at(0);
   int range = stoi(rangedSplit->at(1));
   string type = rangedSplit->at(2);
   int attacks = stoi(rangedSplit->at(3));
   int strength;
   if (rangedSplit->at(4) == "User")
      strength = -1;
   else
      strength = stoi(rangedSplit->at(1));
   int ap = stoi(rangedSplit->at(5));
   int damage = stoi(rangedSplit->at(6));
   string abilities = rangedSplit->at(7);

   RangedWeapon* weapon = new RangedWeapon(getStrength(), name, range, type, attacks, 
      strength, ap, damage, abilities);

   delete rangedSplit;

   rangedList_.push_back(weapon);

   return true;
}

/** Adds a melee weapon to the collection of ranged weapons. Characters
may have multiple melee weapons they can choose from in melee combat.
Accounts for the special case of certain melee weapons that are used to
provide additional attacks alongside other melee weapons. Uses MeleeWeapon class.

"input" is a string formatted to represent a melee weapon.

[Name] [S] [AP] [D] [Abilities]

Precondition: The input string must adhere to the above format.
Postcondition: The melee weapon is added, and will be referenced when
offering players the option of melee weapon they would like to use in
combat. Returns true if succesful. */
bool Character::setMeleeNew(string input)
{
   vector<string>* meleeSplit = split(" ", input);

   string name = meleeSplit->at(0);
   int strength;
   if (meleeSplit->at(1) == "User")
      strength = -1;
   else
      strength = stoi(meleeSplit->at(1));
   int ap = stoi(meleeSplit->at(2));
   int damage = stoi(meleeSplit->at(3));
   string abilities = meleeSplit->at(4);

   MeleeWeapon* weapon = new MeleeWeapon(getStrength(), name, strength, ap, damage,
      abilities);

   delete meleeSplit;

   meleeList_.push_back(weapon);

   return true;

}

/** Sets the psychic abilities of the unit if the unit is a psyker.
* References the psychic ability from a database. If passed "None",
* returns false.

"input" is the name of any number of psychic abilities as a string.
Separate abilities by a space...
[Psychic Ability 1] [Psychic Ability 2] ...

Precondition: None.
Postcondition: The psychic ability is added to the given character
for potential use during the psychic phase. Returns true if the
added ability is valid, and labels the character as a psyker.
If it's not, returns false, and doesn't
add the psychic ability to the character. */
bool Character::setPsychic(string input)
{
   if (input.compare("None") == 0) return false;

   vector<string>* psychicSplit = split(" ", input);

   for (int i = 0; unsigned(i) < psychicSplit->size(); i++) {
      //Call string copy constructor on values in psychicSplit()
      string* temp = new string(psychicSplit->at(i));

      //Push to vector field
      psychicAbilities_.push_back(temp);
   }

   delete psychicSplit;

   psyker_ = true; //Did I not set this to true before??
   return true;
}


/**Overloaded output operator that displays the name, stats,
psychic abilities, ranged abilities, and melee abilities of the unit
to the output stream.

"os" is the output stream.
"character" is the passed Character object whose data is to be
output.

Precondition: None.
Postcondition: Outputs series of strings to the output stream.*/
ostream& operator<<(ostream& os, const Character& character)
{
   os << character.name_ << " " << endl;
   for (int i = 0; i < NUM_STATS; i++) {
      os << character.stats_[i] << " ";
   }
   os << endl;

   //Psychic Abilities
   if (!character.psyker_) os << "None" << endl;
   else {
      for (int i = 0; unsigned(i) < character.psychicAbilities_.size(); i++) {
            os << *character.psychicAbilities_[i] << " ";
         }
         os << endl;
   }
   

   //Ranged Weapons
   // You should be able to refactor me since same code is used
   // for rangedWeapons_ and melee_.
   for (int i = 0; unsigned(i) < character.rangedList_.size(); i++) {
      os << character.rangedList_.at(i)->toString() << endl;
      //for (int j = 0; j < NUM_RANGED; j++) {
      //   vector<string>* ranged = character.rangedWeapons_[i];
      //   os << ranged->at(j) << " ";
      //}
      //os << endl;
   }
   
   //Melee Weapons
   for (int i = 0; unsigned(i) < character.meleeList_.size(); i++) {
      os << character.meleeList_.at(i)->toString() << endl;
      //for (int j = 0; j < NUM_MELEE; j++) {
      //   vector<string>* melee = character.melee_[i];
      //   os << melee->at(j) << " ";
      //}
      //os << endl;
   }

   return os;
}

/** Overloaded less than operator so the class can be added
to a binary search tree. Determined based on name field.

"other" is another Character object.

Precondition: Character must have a name.
Postcondition: Returns true if given character is less than
other. Otherwise returns false. */
bool Character::operator<(const Character& other) const
{
   return name_.compare(other.name_) < 0;
}

/** Overloaded greater than operator so the class can be added
to a binary search tree. Determined based on name field.

"other" is another Character object.

Precondition: Character must have a name.
Postcondition: Returns true if given character is greater than
other. Otherwise returns false. */
bool Character::operator>(const Character& other) const
{
   return name_.compare(other.name_) > 0;
}



/** Private helper function that generalizes weapon combat for
either melee or ranged combat.

"enemy" is an enemy Character object being attacked.
"hitStats" are the attacker's hit characteristics (either weapon skill
or ballistic skill), always an int
"userStrength" is an int representing the innate strength characteristic
of the attacker.
"weaponStrength" is a string denoting the strength of the weapon. Occasionally
is "User", so can't be an int.
"weaponAP" is an int that describes the armor piercing ability of the weapon.
"weaponDamage" is the damage output of each succesful wound of the weapon, as an
int.
"stat" is a string that is either BS, or WS, depending on if it is ranged or melee
combat respectively.

Precondition: None. Returns prematurely if the enemy or self has
a W(ound) stat of 0.
Postcondition: Outputs dice rolls and combat results to output,
and changes the W stat of the enemy. */
void Character::combat(Character& enemy, int hitStats, int userStrength, int weaponStrength,
   int weaponAP, int weaponDamage, string stat)
{
   if (enemy.stats_[5] <= 0) {
      cout << "Enemy character is already dead...";
      return;
   }
   else if (stats_[5] <= 0) {
      cout << "Attacking character is already dead...";
      return;
   }

   unsigned seed = (unsigned)chrono::system_clock::now().time_since_epoch().count();
   cout << "Rolling to hit with " << stat << " " << hitStats << "..." << endl;
   default_random_engine generator(seed);
   uniform_int_distribution<int> diceRoll(1, 6);
   vector<int> potentialDamage;

   //Calculating Hits
   int totalHits = 0;
   for (int i = 0; i < stats_[6]; i++) {
      int roll = diceRoll(generator);
      cout << roll << " ";

      if (roll >= hitStats) {
         totalHits++;
      }
   }
   cout << endl << "Total number of hits: " << totalHits << endl;

   //Calculating Wounds
   int str = weaponStrength;

   int tough = enemy.stats_[4];

   //Rules for wounds...
   int woundRoll;
   if (str / 2 >= tough) {
      woundRoll = 2;
   }
   else if (str > tough) {
      woundRoll = 3;
   }
   else if (str == tough) {
      woundRoll = 4;
   }
   else if (tough / 2 >= str) {
      woundRoll = 6;
   }
   else {
      woundRoll = 5;
   }

   cout << "Wounding on " << woundRoll << "s.." << endl;

   int totalWounds = 0;
   for (int i = 0; i < totalHits; i++) {
      int roll = diceRoll(generator);
      cout << roll << " ";

      if (roll >= woundRoll) {
         totalWounds++;
      }
   }

   cout << endl << "Total wounds: " << totalWounds << endl;

   int armorSave = enemy.stats_[8];
   int invulnSave = enemy.stats_[9];
   int bestSave = ((armorSave - weaponAP) >= invulnSave) ?
      (armorSave - weaponAP) : invulnSave;

   cout << "Each hit does " << to_string(weaponDamage) << " damage." << endl;
   cout << "Saving on " << bestSave << "s." << endl;
   int dmg = 0;
   int succesfulHits = 0;
   for (int i = 0; i < totalWounds; i++) {
      int roll = diceRoll(generator);
      cout << roll << " ";

      if (roll < bestSave) {
         dmg += weaponDamage;
         succesfulHits++;
      }
   }
   cout << endl << succesfulHits << " succesful wounds." << endl;
   cout << dmg << " damage done!" << endl;
   enemy.stats_[5] -= dmg;
   
   cout << "Target has " << enemy.stats_[5] << " health left!";
}

/** Performs a ranged attack upon an enemy character.

"enemy" is another character passed by value.
"stat" is the type of to-hit characteristic being used. In this
case, defaults to "WS".

Precondition: Assumes all of this character's ranged
weapons will be used on the enemy.

Postcondition: Modifies the passed character based on
the outcome of the ranged attack Lists the results of each
dice roll to output as well. */
void Character::rangedAttack(Character& enemy, RangedWeapon* weapon, string stat)
{
   combat(enemy, stats_[2], stats_[3], weapon->getStrength(),
     weapon->getAP(), weapon->getDamage(), stat);
}

/** Performs a melee attack upon an enemy character.

"enemy" is another character passed by value.
"stat" is the type of to-hit characteristic being used. In this
case, defaults to "BS".

Precondition: Assumes a list of melee option have been provided
to the player.
Postcondition: Modifies the enemy character based on the outcome
of the attack. Also provides a list of simulated dice rolls to
the output. */
void Character::meleeAttack(Character& enemy, MeleeWeapon* weapon, string stat)
{
   combat(enemy, stats_[1], stats_[3], weapon->getStrength(), 
      weapon->getAP(), weapon->getDamage(), stat);
}

/** Returns the character's strength value.

Precondition: None.
Postcondition: Returns an int. */
int Character::getStrength() const
{
   return strength_;
}

/** Returns the specified melee weapon from the weapon list.

If a value greater than the number of weapons is passed, the
final one is returned.

Precondition: None.
Postcondition: Returns a MeleeWeapn pointer. */
MeleeWeapon* Character::getMeleeAt(int index)
{
   int retrieve = index;
   if (index >= (int)meleeList_.size())
      retrieve = meleeList_.size() - 1;
   return meleeList_.at(retrieve);
}

/** Returns the specified ranged weapon from the weapon list.

If a value greater than the number of weapons is passed, the
final one is returned.

Precondition: None.
Postcondition: Returns a RangedWeapon pointer. */
RangedWeapon* Character::getRangedAt(int index)
{
   int retrieve = index;
   if (index >= (int)rangedList_.size())
      retrieve = rangedList_.size() - 1;
   return rangedList_.at(retrieve);
}