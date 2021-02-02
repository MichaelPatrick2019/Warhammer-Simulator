#include <string>
#include <iostream>
#include <vector>
#include "Character.h";


//Test Character.cpp

using namespace std;

int main()
{
   Character character;
   string test = "  A  b c               d   ";
   vector<string>* strVector = character.split(" ", test);

   for (int i = 0; i < strVector->size(); i++) {
      cout << strVector->at(i) << " ";
   }

   delete strVector;
}