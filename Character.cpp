#pragma once

/** @ Character.h */

/** Straightforward object that stores all of the necessary information
about a given warhammer character. Considers inherent stats, ranged and
melee weapons, as well as detailed output to the outstream when
engaging in combat with other characters. */

#include <string>
#include <iostream>
#include <vector>
#include "Character.h";

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

[M] [WS] [BS] [S] [T] [W] [A] [Ld] [Sv]

Precondition: The string must observe the correct format.
Postcondition: The stats are stored in the character. Returns
true if succesful. */
bool Character::setStats(string input)
{
   //Code??
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