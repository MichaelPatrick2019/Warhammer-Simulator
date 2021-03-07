/** @Army.cpp */
/**
Michael Patrick

Army class that stores multiple Character objects
in a AVL tree. Intended to provide quick
access to characters sorted by name.

AVL Tree functionality largely taken from:
https://www.geeksforgeeks.org/avl-tree-set-1-insertion/
with slight modifications. */


/** Basic constructor for the class. Starts off empty.

Precondition: None.
Postcondition: Creates an Army object. */
#include "Army.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

/** Node constructor that assigns the node a Character value.
Precondition: None.
Postcondition: Assigns the character pointer, and sets left and
right pointers to nullptr. */
Army::Node::Node(Character* character) : character(character), 
                 left(nullptr), right(nullptr), height(1)
{
}

/** Basic constructor for the class. Starts off empty.

Precondition: None.
Postcondition: Creates an Army object. */
Army::Army() : root(nullptr), size(0)
{
}

/** Special constructor for initializing an army based on
an input file. The input file must adhere to the
following format...

[Character 1 Name]
[Character 1 Stats]
[Character Psychic Abilities] (if none, "None")
Ranged [Character 1 Ranged 1] (if none, "None");
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
Army::Army(string fileName)
{
   //Standard initialization
   root = nullptr;
   size = 0;

   ifstream characterFile(fileName);
   string line;
   if (characterFile.is_open()) {
      while (!characterFile.eof()) {
         //Initalize new Character
         Character* newChar = new Character();

         //First line is the name...
         getline(characterFile, line);
         newChar->setName(line);

         //Next line is stats
         getline(characterFile, line);
         newChar->setStats(line);

         //Next line is psyker abilities
         getline(characterFile, line);
         newChar->setPsychic(line);

         //Next is multiple ranged weapons...
         getline(characterFile, line);
         if (line.compare("None") != 0) {
            while (line.substr(0, 6).compare("Ranged") == 0) {
               newChar->setRanged(line.substr(7));
               getline(characterFile, line);
            }
         }
         else {
            getline(characterFile, line);
         }

         //Next is multiple melee weapons...
         if (line.compare("None") != 0) {
            while (line.substr(0, 5).compare("Melee") == 0) {
               newChar->setMelee(line.substr(6));
               getline(characterFile, line);
               if (characterFile.eof() || line.compare("") == 0) break;
            }
         }

         //Reach end of given Character, add to Army.

         add(newChar);
      }
   }
   else {
      cout << "File couldn't be opened..." << endl;
   }

   characterFile.close();
}

/** Private recursive helper method for the destructor. Deletes
 *  the given node any all of its children.
 *  node is the root of any subtree.
 *  Precondition: Requires a tree object.
 *  Postcondition: Deletes all nodes of the tree stored in dynamic
 *  memory. */
void Army::deleteNodes(Node* node)
{
   if (node == nullptr) {
      return;
   }

   deleteNodes(node->left);
   deleteNodes(node->right);

   //Makes sure there aren't any pointers pointing to garbage.
   node->left = nullptr;
   node->right = nullptr;

   delete node->character;
   delete node;
}

/** Custom destructor that handles all of the
dynamically allocated memory in the Army object.

Precondition: None.
Postcondition: Destroys all data associated with the
Army object. Takes responsibility for any character
pointers added. This means you won't be able to access
a character once the Army it is in is deleted.

Also assumes this will only be called once on the
Army object.*/
Army::~Army()
{
   deleteNodes(root);
}

/** Outputs the BST using inorder search.

"node" is the root of any subtree. 

Precondition: None.
Postcondition: Sends Character << operator to output. */
void Army::toString(Node* node)
{
   if (node == nullptr) {
      return;
   }

   toString(node->left);
   cout << *node->character << endl;
   toString(node->right);
}

void Army::toString()
{
   toString(root);
}


/** Adds a Character to the Army.


"newChar" is a Character pointer.

Precondition: Character should be initialized
fully so it is ready to participate in "battle".
Postcondition: Adds the Character pointer to the
Army. Takes responsibility for the Character's data. */
bool Army::add(Character* newChar)
{
   root = insert(root, newChar);

   size++;
   return true;
}

/** Private helper method for recursively adding a node
to the AVL tree.

Precondition: None.
Postcondition: Returns the root of the subtree the value
is added into. Once recursion
terminates, the node is added to the correct location on
the tree */
Army::Node* Army::insert(Node* node, Character* key)
{
   //Standard insertion
   if (node == nullptr) return new Node(key);
   if (*key < *node->character) { //Don't comapre addresses!
      cout << "key < node..." << endl;
      node->left = insert(node->left, key);
   }
   else if (*key > *node->character) {
      node->right = insert(node->right, key);
   }
   else {
      return node; //This code doesn't allow duplicates
      //How will we handle duplicate characters? Should be OK....
      //Need some way of distinguishing?
   }

   //Update height of ancestor
   node->height = 1 + max(height(node->left), height(node->right));

   //Find balance of node post-insertion
   int balance = getBalance(node);

   //4 cases, depending on balance...

   //Left-left
   if (balance > 1 && *key < *node->left->character) { //Balance prevents
                                                       //bad references
      return rotateWithLeftChild(node);
   }

   //Right-right
   if (balance < -1 && *key > *node->right->character) {
      return rotateWithRightChild(node);
   }

   //Left-Right
   if (balance > 1 && *key > *node->left->character){
      node->left = rotateWithRightChild(node->left);
      return rotateWithLeftChild(node);
   }

   //Right-left
   if (balance < -1 && *key < *node->right->character) {
      node->right = rotateWithLeftChild(node->right);
      return rotateWithRightChild(node);
   }

   return node;
}

/** Quick function that returns max of two integers */
int Army::max(int a, int b)
{
   //Ternary operator - if a > b, return a, else return b
   return (a > b) ? a : b;
}

/** Determines height of the given node... */
int Army::height(Node* node)
{
   if (node == nullptr) return 0;
   return node->height;
}

/** Checks the level of balance of the given node.

Precondition: None.
Postcondition: Returns an int representing the difference
in height between both subtrees of the node. If the difference
is greater than 1, the tree is considered unbalanced. */
int Army::getBalance(Node* node)
{
   if (node == nullptr) return 0;
   return (height(node->left) - height(node->right));
}

/** Rotates the unbalanced node with its left child.

"node" is the unbalanced node passed by reference.

Precondition: Assumes that it is true that the node needs
to be rotated in order to maintain the balance of the tree.
Will not verify this before performing the operation.
Postcondition: The given node now points to the left
node, and the right child of the node is passed to
the original node. Returns the new, higher node...*/
Army::Node* Army::rotateWithLeftChild(Node* node)
{
   Node* leftChild = node->left;
   Node* rightOfLeftChild = leftChild->right;

   //Rotate
   leftChild->right = node;
   node->left = rightOfLeftChild;

   //Update heights
   node->height = max(height(node->left), height(node->right)) + 1;
   leftChild->height = max(height(leftChild->left), 
                             height(leftChild->right)) + 1;


   return leftChild;

}

/** Rotates the unbalanced node with its right child.

"node" is the unbalanced node passed by reference.

Precondition: Assumes that it is true that the node needs
to be rotated in order to maintain the balance of the tree.
Will not verify this before performing the operation.
Postcondition: The given node now points to the right
node, and the left child of the node is passed to
the original node. */
Army::Node* Army::rotateWithRightChild(Node* node)
{
   Node* rightChild = node->right;
   Node* leftOfRightChild = rightChild->left;

   //Rotate
   rightChild->left = node;
   node->right = leftOfRightChild;


   //Update heights
   node->height = max(height(node->left), height(node->right)) + 1;
   rightChild->height = max(height(rightChild->left),
      height(rightChild->right)) + 1;

   return rightChild;
}

/** Returns the number of Characters in the Army.

Precondition: None.
Postcondition: Returns the number of Characters as an int. */
int Army::numCharacters()
{
   return size;
}

/** Overloaded output operator. Details all of the characters
in the army, including all their names, statistics, weapons,
and psychic abilities.

Precondition: None.
Postcondition: Outputs all of the Character data to the outstream.
Outputs a string saying the Army is empty if there are no characters
added. */
ostream& operator<<(ostream& os, const Army& army)
{ 
   sendSubTreeToOut(os, army, army.root);
   return os;
}

/** Private recursive method for output operator.
Takes a node and an army object and outputs all characters
using inorder traversal.

Precondition: None.
Postcondition: Sends all strings to outstream. */
void sendSubTreeToOut(ostream& os, const Army& army, Army::Node* node)
{
   if (node == nullptr) {
      return;
   }

   sendSubTreeToOut(os, army, node->left);
   os << *node->character << endl;
   sendSubTreeToOut(os, army, node->right);
}