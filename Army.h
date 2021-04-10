#pragma once
/** @Army.h */
/** 
Michael Patrick

Army class that stores multiple Character objects
in a AVL tree. Intended to provide quick
access to characters sorted by name. 

AVL Tree functionality largely taken from:
https://www.geeksforgeeks.org/avl-tree-set-1-insertion/
with slight modifications. */

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
   int max(int a, int b) const;

   /** Determines height of the given node... */
   int height(Node* node) const;

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
   int getBalance(Node* node) const;

   /** Outputs the BST using inorder search.
   
   "node" is the root of a subtree.

   Precondition: None.
   Postcondition: Sends Character << operator to output. */
   void toString(Node* root) const;

   /** Private recursive helper method for the destructor. Deletes
 *  the given node any all of its children.
 *  node is the root of any subtree.
 *  Precondition: Requires a tree object.
 *  Postcondition: Deletes all nodes of the tree stored in dynamic
 *  memory. */
   void deleteNodes(Node* node);

   /** Private recursive method for output operator.
   Takes a node and an army object and outputs all characters
   using inorder traversal.

   Precondition: None.
   Postcondition: Sends all strings to outstream. */
   friend void sendSubTreeToOut(ostream& os, const Army& army, Army::Node* node);

   /** Locates a Character pointer with a string key, starting at the given root
   of a subtree. 
   
   "key" is a string with the exact name of the character.
   "root" is a Node pointer, the root of a subtree. 
   
   Precondition: None.
   Postcondition: Returns a pointer to the Character object in question. If the object
   is not found, returns nullptr. */
   Character* searchByName(string name, Node* node) const;

   Node* root;
   int size;


public:

   /** Basic constructor for the class. Starts off empty. 
   
   Precondition: None.
   Postcondition: Creates an Army object. */
   Army();

   /** Special constructor for initializing an army based on
   an input file. The input file must adhere to the
   following format...
   
   [Character 1 Name]
   [Character 1 Stats]
   [Character Psychic Abilities] (if none, "None")
   Ranged [Character 1 Ranged 1]
   .
   .
   .
   Melee [Character 1 Melee 1]
   .
   .
   .
   [Space]
   [Character 2 Name]
   .
   .
   .
   etc.

   "fileName" is a string of the file name, ending with ".txt"

   Precondition: The passed file must be a valid text file that exists
   in the same folder as Army.h
   Postcondition: Creates Character pointers and adds them to the
   new Army object. */
   Army(string fileName);

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
   a character once the Army it is in is deleted. 
   
   Also assumes this will only be called once on the
   Army object.*/
   ~Army();

   /** Outputs the BST using inorder search, starting
   from the root.
   
   Precondition: None.
   Postcondition: Outputs every character stored in tree. */
   void toString() const;

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
   Character* retrieve(string name) const; //Get Character ptr by name

   /** Rotates the unbalanced node with its left child.

   "node" is the unbalanced node passed by reference.

   Precondition: Assumes that it is true that the node needs
   to be rotated in order to maintain the balance of the tree.
   Will not verify this before performing the operation.
   Postcondition: The given node now points to the left
   node, and the right child of the node is passed to
   the original node. */
   Node* rotateWithLeftChild(Node* node);

   /** Rotates the unbalanced node with its right child.

   "node" is the unbalanced node passed by reference.

   Precondition: Assumes that it is true that the node needs
   to be rotated in order to maintain the balance of the tree.
   Will not verify this before performing the operation.
   Postcondition: The given node now points to the right
   node, and the left child of the node is passed to
   the original node. */
   Node* rotateWithRightChild(Node* node);

   /** Returns the number of Characters in the Army.
   
   Precondition: None.
   Postcondition: Returns the number of Characters as an int. */
   int numCharacters() const; //Return size

   /** Overloaded output operator. Details all of the characters
   in the army, including all their names, statistics, weapons,
   and psychic abilities.
   
   Precondition: None.
   Postcondition: Outputs all of the Character data to the outstream.
   Outputs a string saying the Army is empty if there are no characters
   added. */
   friend ostream& operator<<(ostream& os, const Army& army);

};

