#pragma once

/** @Army.h */
/** Army class that stores multiple Character objects
in a binary search tree. Intended to provide quick
access to characters sorted by name. */

#include "Character.h"

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




};

