#pragma once

/** @Army.h */
/** Army class that stores multiple Character objects
in a AVL tree. Intended to provide quick
access to characters sorted by name. */

#include "Character.h"
#include <fstream>

class Army
{

private:

   struct Node
   {
      Character character;
      Node* left;
      Node* right;
   };

   Node* root;
   int size;



public:

   /** Basic constructor for the class. Starts off empty. 
   
   Precondition: None.
   Postcondition: Creates an Army object. */
   Army();

   //Need a way to read in armies from a file...
   /** Initializes an army object based off a formatted file.
   File format..

   ??
   "inFile" is an ifstream object that reads from a particular
   file.

   Precondition: file being read must be formatted to above
   specifications.
   Postcondition: Creates a filled Army object. */
   Army(ifstream& inFile);

   /** Custom destructor that handles all of the
   dynamically allocated memory in the Army object.
   
   Precondition: None.
   Postcondition: Destroys all data associated with the
   Army object. Takes responsibility for any character
   pointers added. This means you won't be able to access
   a character once the Army it is in is deleted. */
   ~Army();

   /** Adds a Character to the Army.
    
   
   "newChar" is a Character pointer.
    
   Precondition: Character should be initialized
   fully so it is ready to participate in "battle".
   Postcondition: Adds the Character pointer to the
   Army. Takes responsibility for the Character's data. */
   bool add(Character* newChar);

   /** Searches for a certain character by its name and returns
   a pointer to it.

   "name" is a string key for finding the character. NOT case
   sensitive.
   
   Precondition: None.
   Postcondition: If the army is deleted, the pointer will point
   to garbage. */
   Character* retrieve(string name); //Get Character ptr by name

   /** Rotates the inner tree impementation to keep it as balanced
   as possible.
   
   "node" is a node pointer to a node in the AVL tree. 

   Precondition: None.
   Postcondition: Modifies the tree so it remains as balanced as possible. */
   void rotate(Node* node); //AVL tree...

   /** Returns the number of Characters in the Army.
   
   Precondition: None.
   Postcondition: Returns the number of Characters as an int. */
   int size(); //Return size

   /** Overloaded output operator. Details all of the characters
   in the army, including all their names, statistics, weapons,
   and psychic abilities.
   
   Precondition: None.
   Postcondition: Outputs all of the Character data to the outstream.
   Outputs a string saying the Army is empty if there are no characters
   added. */
   friend ostream& operator<<(ostream& os, const Army& army);

};

