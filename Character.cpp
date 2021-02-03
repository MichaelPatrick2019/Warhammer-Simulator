#pragma once

/** @ Character.h */

/** Straightforward object that stores all of the necessary information
about a given warhammer character. Considers inherent stats, ranged and
melee weapons, as well as detailed output to the outstream when
engaging in combat with other characters. */

#include <string>
#include <iostream>
#include <vector>
#include "Character.h"

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

   while (end < str.size()) {
      start = end + 1;

      //Move start to point to next item after a delimiter
      //Or, reaches the end of the substring.
      while (start < str.size() && str.substr(start, delimiter.size()) == delimiter) {
         start += delimiter.size(); //Should point eventually to a non-delimiter.
      }

      if (start >= str.size()) start = str.size();

      //End points to the next delimiter after the object
      end = str.substr(start).find(delimiter) + start;

      //If no delimiter until end of str...
      if (str.substr(start).find(delimiter) == string::npos
         || end >= str.size()) end = str.size();

      result->push_back(str.substr(start, end - start));
   }

   return result;
}

/** Adds a weapon to the collection of ranged weapons. Characters
may have multiple ranged weapons.

"input" is a string formatted to represent a ranged weapon...

[Name] [Range] [Type] [number of attacks] [S] [AP] [Abilities]

Precondition: The input string must adhere to the above format.
Postcondition: The ranged weapon is added, and will be used to calculate
ranged damage output in combat. Returns true if succesful. */
bool Character::setRanged(string input)
{
   vector<string>* rangedSplit = split(" ", input);

   vector<string>* singleWeapon = new vector<string>;

   for (int i = 0; i < NUM_RANGED; i++) {
      singleWeapon->push_back(rangedSplit->at(i));
   }

   rangedWeapons_.push_back(singleWeapon);

   delete rangedSplit;

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


   //Psychic abilities?????

   for (int i = 0; i < character.rangedWeapons_.size(); i++) {
      //Should be numranged, set to -1 for testing?
      for (int j = 0; j < NUM_RANGED; j++) {
         vector<string>* givenWeapon = character.rangedWeapons_[i];
         os << givenWeapon->at(j) << " ";
      }
      os << endl;
   }
   
   //Melee Weapons

   return os;
}
