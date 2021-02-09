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

   Army();

   //Need a way to read in armies from a file...
   Army(ifstream& inFile);
   ~Army();

   bool add(Character* newChar);
   Character* retrieve(string name); //Get Character ptr by name
   void rotate(Node* node); //AVL tree...
   int size(); //Return size

   friend ostream& operator<<(ostream& os, const Army& army);

};

