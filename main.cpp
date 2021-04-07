/** @main.cpp */

/** Program that runs a loop that takes in an army of warhammer characters,
initializes their values, and provides combat with simulated dice rolls. 

Michael Patrick
2/1/21 */

#include <iostream>
#include <string>
#include "Army.h"
#include "Character.h"
#include "CombatFactory.h"
#include "Combat.h"

using namespace std;

/** Creates an instance that requires the user to input a character
name, and assigns it to the Character object passed by value.

"army" is some Army object.

Precondition: There needs to be a character in the passed Army object.
Postcondition: Returns a Character pointer. */
Character* getCharacter(Army& army)
{
   Character* character = nullptr;
   string attackerName;

   getline(cin, attackerName);
   character = army.retrieve(attackerName);

   cout << endl;

   while (character == nullptr)
   {
      cout << "You'll have to enter their name exactly... Try again: ";

      getline(cin, attackerName);
      character = army.retrieve(attackerName);

      cout << endl;
   }

   return character;
}


int main()
{
   cout << "Welcome to Warhammer 40k! Your army will be loaded by army.txt";
   cout << endl << endl;

   Army newArmy("army.txt");

   cout << "Here's a list of all the units in the army currently: " << endl << endl;

   cout << newArmy;

   cout << endl << "Now that we see who we've got, let's practice some combat." << endl;

   cout << "Please enter the name of the character you'd like to initiate an attack: ";

   Character* attacker = getCharacter(newArmy);

   cout << "Great - now, enter the name of the character you want to attack: ";

   Character* defender = getCharacter(newArmy);

   while (attacker == defender) {
      cout << "Please make sure you choose a different character. " << endl << endl;

      cout << "The name of the character you want to attack: ";
      defender = getCharacter(newArmy);
   }

   cout << endl;

   cout << "Please enter either 'ranged' or 'melee' to indicate the type of combat you";
   cout << " would like to occur: ";

   Combat* combatType;
   string combatInput;
   CombatFactory factory;

   cin >> combatInput;
   combatType = factory.generateCombatObject(combatInput);

   cout << endl << "Combat Begins!" << endl << endl;

   combatType->fight(attacker, defender);
   
   cout << endl;



   /**
   bool notDone = true;

   Army playerArmy;
   Army enemyArmy;

   while (notDone) {
      Character character;
      string name;

      cout << "Please enter your character's name...";
      cin >> name;
      character.setName(name);

      cout << "Please enter your character's stats in the following format: ";
      cout << "[M] [WS] [BS] [S] [T] [W] [A] [Ld] [Sv]";
      cout << endl;

      string stats;
      cin >> stats;
      character.setStats(stats);

      cout << "Please enter your character's psychic abilities. If your";
      cout << "character is not a psyker," << endl;
      cout << "please enter 'none' instead.";
      cout << "[Name]";

      string psychic;
      cin >> psychic;
      character.setPsychic(psychic);

      cout << "Please enter your character's ranged weapons. If your";
      cout << "character doesn't have any ranged attacks," << endl;
      cout << "please enter 'none' instead.";
      cout << "[Name] [Range] [Type] [number of attacks] [S] [AP] [Abilities]";

      string ranged;
      cin >> ranged;
      character.setRanged(ranged);

      cout << "Please enter your character's melee weapons. If your";
      cout << "character doesn't have any ranged attacks," << endl;
      cout << "please enter 'none' instead";
      cout << "[Name] [S] [AP] [D] [Abilities]";

      string melee;
      cin >> ranged;
      character.setMelee(melee);

      personalArmy.add(character);

      cout << "Do you have another character to add? Please respond" <<
         "'Y' or 'N'";
   }
   */

}