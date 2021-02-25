#pragma once
/** @Army.h */
/** 
Michael Patrick

Army class that stores multiple Character objects
in a AVL tree. Intended to provide quick
access to characters sorted by name. */

#include "Character.h"
#include <fstream>

class Army
{

private:

   struct Node
   {
      Character* character;
      Node* left;
      Node* right;
      int height; //Default 1, because node is always initially a leaf
      
      /** Node constructor that assigns the node a Character value. 
      Precondition: None.
      Postcondition: Assigns the character pointer, and sets left and
      right pointers to nullptr. */
      Node(Character* character);
   };

   /** Quick function that returns max of two integers */
   int max(int a, int b);

   /** Determines height of the given node... */
   int height(Node* node);


   /** Private helper method for recursively adding a node
   to the AVL tree.
   
   Precondition: None.
   Postcondition: Returns the root of the subtree the value
   is added into. Once recursion
   terminates, the node is added to the correct location on
   the tree */
   Node* insert(Node* node, Character* key);

   /** Checks the level of balance of the given node.
   
   Precondition: None.
   Postcondition: Returns an int representing the difference
   in height between both subtrees of the node. If the difference
   is greater than 1, the tree is considered unbalanced. */
   int getBalance(Node* node);

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

   /** Rotates the unbalanced node with its left child.

   "node" is the unbalanced node passed by reference.

   Precondition: Assumes that it is true that the node needs
   to be rotated in order to maintain the balance of the tree.
   Will not verify this before performing the operation.
   Postcondition: The given node now points to the left
   node, and the right child of the node is passed to
   the original node. */
   Node* rotateWithLeftChild(Node*& node);

   /** Rotates the unbalanced node with its right child.

   "node" is the unbalanced node passed by reference.

   Precondition: Assumes that it is true that the node needs
   to be rotated in order to maintain the balance of the tree.
   Will not verify this before performing the operation.
   Postcondition: The given node now points to the right
   node, and the left child of the node is passed to
   the original node. */
   Node* rotateWithRightChild(Node*& node);

   /** Rotates the current node with the left child of
   the right child of the passed node. Used for when
   the added node that unbalances the passed node is
   in the left subtree of the right child.

   "node" is the unbalanced node passed by reference.

   Precondition: Assumes the passed node is unbalanced, and
   will become balanced once the method is finished. Does
   not verify a height inbalance, or that this is in fact
   the correct method call.
   Postcondition: Switches the passed node with the left
   child of the right child of the original node. */
   void doubleRotateWithLeftChild(Node*& node);

   /** Rotates the current node with the right child of
   the left child of the passed node. Used for when
   the added node that unbalances the passed node is
   in the right subtree of the left child.

   "node" is the unbalanced node passed by reference.

   Precondition: Assumes the passed node is unbalanced, and
   will become balanced once the method is finished. Does
   not verify a height inbalance, or that this is in fact
   the correct method call.
   Postcondition: Switches the passed node with the right
   child of the left child of the original node. */
   void doubleRotateWithRightChild(Node*& node);

   /** Returns the number of Characters in the Army.
   
   Precondition: None.
   Postcondition: Returns the number of Characters as an int. */
   int numCharacters(); //Return size

   /** Overloaded output operator. Details all of the characters
   in the army, including all their names, statistics, weapons,
   and psychic abilities.
   
   Precondition: None.
   Postcondition: Outputs all of the Character data to the outstream.
   Outputs a string saying the Army is empty if there are no characters
   added. */
   friend ostream& operator<<(ostream& os, const Army& army);
};

