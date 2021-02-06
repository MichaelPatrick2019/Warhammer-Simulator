#include <string>
#include <iostream>
#include <vector>
#include "Character.h";
#include <assert.h>


//Test Character.cpp

using namespace std;

int main()
{
   Character character;

   string test = "  A  b c               d   ";
   vector<string>* strVector = character.split(" ", test);

   string result = "";

   for (int i = 0; i < strVector->size(); i++) {
      result += strVector->at(i);
   }

   assert(result == "Abcd");

   delete strVector;

   character.setName("John Krasinski");
   character.setStats("11 4 5 4 4 4 6 10 3 5");

   character.setRanged("Bolter 18 Assault D6 4 -1 None");
   character.setMelee("Claws User 0 2 None");
   character.setPsychic("Smite Catalyst");

   cout << character;
}