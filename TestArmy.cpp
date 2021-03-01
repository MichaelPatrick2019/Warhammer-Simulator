/** @TestArmy.cpp */

//Michael Patrick
/** Basic series of tests for Army object. Includes testing
insert, balancing(rotations), and deletions of dynamic memory */

#include "Army.h"
#include "Character.h"

int main()
{
   Army army;

   Character* first = new Character;
   first->setName("John Krasinski");
   first->setStats("11 4 5 4 4 4 6 10 3 5");

   first->setRanged("Bolter 18 Assault D6 4 -1 None");
   first->setMelee("Claws User 0 2 None");
   first->setPsychic("Smite Catalyst");

   Character* second = new Character;
   second->setName("Andrew Johnson");
   second->setStats("6 4 3 4 2 4 1 6 3 2");

   second->setRanged("HandCannon 18 Assault D5 3 -3 None");
   second->setMelee("Hands User 0 2 None");
   second->setPsychic("Smite Pyschokinesis");

   Character* third = new Character;
   third->setName("Miguel");
   third->setStats("1 2 3 4 5 6 7 8 9 10");

   third->setRanged("Gun 20 Heavy 5 9 0 None");
   third->setMelee("Knife User 0 1 None");
   third->setPsychic("None");

   Character* fourth = new Character;
   fourth->setName("Zebra");
   fourth->setStats("10 9 8 7 6 5 4 3 2 1");

   fourth->setRanged("Spittle 10 Pistol 3 4 -1 None");
   fourth->setMelee("Hooves 20 -10 D40 None");
   fourth->setPsychic("None");

   army.add(second);
   army.add(first);
   army.add(third);
   army.add(fourth);

   army.toString();
}