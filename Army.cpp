/** @Army.cpp */
/**
Michael Patrick

Army class that stores multiple Character objects
in a AVL tree.Intended to provide quick
access to characters sorted by name.* /
/** Basic constructor for the class. Starts off empty.

Precondition: None.
Postcondition: Creates an Army object. */
#include "Army.h"

/** Node constructor that assigns the node a Character value.
Precondition: None.
Postcondition: Assigns the character pointer, and sets left and
right pointers to nullptr. */
Army::Node::Node(Character* character) : character(character), 
                 left(nullptr), right(nullptr), height(1)
{
}

Army::Army() : root(nullptr), size(0)
{
}


/** Adds a Character to the Army.


"newChar" is a Character pointer.

Precondition: Character should be initialized
fully so it is ready to participate in "battle".
Postcondition: Adds the Character pointer to the
Army. Takes responsibility for the Character's data. */
bool Army::add(Character* newChar)
{
   if (root == nullptr) root = new Node(newChar);
   else {
      insert(root, newChar);
   }
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
   if (key < node->character) {
      node->left = insert(node->left, key);
   }
   else if (key > node->character) {
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
   if (balance > 1 && key < node->left->character) {
      return rotateWithRightChild(node);
   }

   //Right-right
   if (balance < -1 && key < node->left->character) {
      return rotateWithLeftChild(node);
   }

   //Left-Right
   if (balance > 1 && key > node->left->character){
      node->left = rotateWithLeftChild(node->left);
      return rotateWithRightChild(node);
   }

   //Right-left
   if (balance < -1 && key < node->right->character) {
      node->right = rotateWithRightChild(node->right);
      return rotateWithLeftChild(node);
   }
}

/** Quick function that returns max of two integers */
int max(int a, int b)
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
Army::Node* Army::rotateWithLeftChild(Node*& node)
{
   Node* leftChild = node->left;
   node->left = leftChild->right;
   leftChild->right = node;
   node = leftChild;

   //Update heights
   node->height = max(height(node->left), height(node->right));
   node->right->height = max(height(node->right->left), 
                             height(node->right->right));


   return node;

}

/** Rotates the unbalanced node with its right child.

"node" is the unbalanced node passed by reference.

Precondition: Assumes that it is true that the node needs
to be rotated in order to maintain the balance of the tree.
Will not verify this before performing the operation.
Postcondition: The given node now points to the right
node, and the left child of the node is passed to
the original node. */
Army::Node* Army::rotateWithRightChild(Node*& node)
{
   Node* rightChild = node->right;
   node->right = rightChild->left;
   rightChild->left = node;
   node = rightChild;

   //Update heights
   node->height = max(height(node->left), height(node->right));
   node->left->height = max(height(node->right->left),
      height(node->right->right));

   return node;
}