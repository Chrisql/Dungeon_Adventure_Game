#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <unistd.h>

using namespace std;

/* Christian Ruth
*Objective : defeat the dungeon!
*
*/

string PLAYERNAME; // Const variable
string playerDecision, loot_option, loot_infoOption; // For when the game ask for player input
int enemy_selector = 0, level_selector = 0, entrySelector = 0, player_hp = 100;
vector <string> playerInventory = {"stick"};
int enemyLevel, enemy_hp, attackDamage, enemyLevelSelector;
int playerDecisionNum, playerAttackDamage;
int loot_number = 0;
bool playerHasKey = false;
bool GAMEWINNER = false;

void loot_boxItems();
void loot_info();
void items_into_inventory();

void monsters() {
  // Change the monster's name

  srand(time(NULL));
  enemyLevelSelector = rand() % 10;

  if(enemyLevelSelector == 1 || enemyLevelSelector == 2 || enemyLevelSelector == 3 || enemyLevelSelector == 4 || enemyLevelSelector == 5) {
    enemyLevel = 1;
  }
  else if(enemyLevelSelector == 6 || enemyLevelSelector == 7 || enemyLevelSelector == 8) {
    enemyLevel = 2;
  }
  else if(enemyLevelSelector == 9 || enemyLevelSelector == 10) {
    enemyLevel = 3;
  }

}

void monster_attackOptions() {
  int attackOption = 0;
  
  srand(time(NULL));
  attackOption = rand() % 6; // Picks number 0-6

  if(enemyLevel == 1) { // For level 1 enemys
    if(attackOption == 0 || attackOption == 1 || attackOption == 2 || attackOption == 3) {
      attackDamage = 1;
    }
    else if(attackOption == 4 || attackOption == 5) {
      attackDamage = 2;
    }
    else if(attackOption == 6) {
      attackDamage = 3;
    }
  }
  else if(enemyLevel == 2) { // For level 2 enemys 
      if(attackOption == 0 || attackOption == 1 || attackOption == 2 || attackOption == 3) {
        attackDamage = 4;
      }
      else if(attackOption == 4 || attackOption == 5) {
        attackDamage = 5;
    }
      else if(attackOption == 6) {
        attackDamage = 6;
      }
  }
  else if(enemyLevel == 3) { // For level 3 enemys
    if(attackOption == 0 || attackOption == 1 || attackOption == 2 || attackOption == 3) {
      attackDamage = 7;
    }
    else if(attackOption == 4 || attackOption == 5) {
      attackDamage = 8;
    }
    else if(attackOption == 6) {
      attackDamage = 9;
    }
  }
  else if(enemyLevel == 10) { // For the boss
    if(attackOption == 0 || attackOption == 1 || attackOption == 2 || attackOption == 3) {
      attackDamage = 13;
    }
    else if(attackOption == 4 || attackOption == 5) {
      attackDamage = 17;
    }
    else if(attackOption == 6) {
      attackDamage = 20;
    }
  }
  player_hp = player_hp - attackDamage;
}

void monster_health() {
  if(enemyLevel == 1) {
    enemy_hp = 10;
  }
  else if(enemyLevel == 2) {
    enemy_hp = 20;
  }
  else if(enemyLevel == 3) {
    enemy_hp = 30;
  }
  else if(enemyLevel == 10) {
    enemy_hp = 80;
  }
}

// Decides the amount of damage the player does to the enemy
void player_attackDamage() {
  if(playerInventory[playerDecisionNum - 1] == "stick") {
    enemy_hp -= 5;
    playerAttackDamage = 5;
  }
  else if(playerInventory[playerDecisionNum - 1] == "Magical Sword") {
    enemy_hp -= 20;
    playerAttackDamage = 20;
  }
  else if(playerInventory[playerDecisionNum - 1] == "Axe") {
    enemy_hp -= 10;
    playerAttackDamage = 10;
  }
  else if(playerInventory[playerDecisionNum - 1] == "Knife and Fork") {
    enemy_hp -= 7;
    playerAttackDamage = 7;
  }
}

// For the blank level
void level_default() {
  cout << "|    V    | \n" << "|         |\n" << "|         |\n" << endl;
}

// For the door level
void level_door() {
  cout << "|    V     |\n" << "|        /\n" << "|         |"<< endl;
}

void level_doorEntry() {
  cout << "--------------|\n" << "|             |\n" << "|             |\n" << 
  "\\   >         |\n" << "|             |\n" << "|             |\n" << "--------------|\n" << endl;
}

void level_doorEntryEnemy() {
  cout << "--------------|\n" << "|             |\n" << "|             |\n" << 
  "\\   >     !   |\n" << "|             |\n" << "|             |\n" << "--------------|\n" << endl;
}

void level_doorEntryLoot() {
  cout << "--------------|\n" << "|             |\n" << "|             |\n" << 
  "\\   >     $   |\n" << "|             |\n" << "|             |\n" << "--------------|\n" << endl;
}

void level_doorEntryKey() {
  cout << "--------------|\n" << "|             |\n" << "|         k  ||\n" << "\\   >     e |||\n" << "|         y  ||\n" << "|             |\n" << "--------------|\n" << endl;
}

void level_doorEntryBossBattle() {
  cout << "--------------|\n" << "|             |\n" << "|            ||\n" << "\\          >|||\n" << "|            ||\n" << "|             |\n" << "--------------|\n" << endl;
}

// For the loot level
void level_loot() {
  cout << "|    V    |\n" << "|    $    |\n" << "|         |" << endl;
    
}

// For the enemy level
void level_enemy() {
  cout << "|    V    |\n" << "|         |\n" << "|    !    |" << endl;
}

// For the boss level
void level_boss() {
  cout << "--------------|\n" << "__|             |\n" << "         !!     |\n" << "     >    !!    |\n" << "__       !!     |\n" << "  |             |\n" << "  --------------|\n" << endl;
}

// What spawns in the door when the player goes in
void entryGen() {
  // Creating the seed for the random number generator
  srand(time(NULL));
  entrySelector = rand() % 5; // Get's a number between 0-3

  if(entrySelector == 0 || entrySelector == 1) {
level_doorEntryEnemy();
  }
  else if(entrySelector == 2 || entrySelector == 3) {
level_doorEntryLoot();   
  }
  else if(entrySelector == 4 || entrySelector == 5) {
    level_doorEntryKey();
  }
}

// Generates the level for the player
void levelGen() {
  // Creating the seed for the random number generator
  srand(time(NULL));
  level_selector = rand() % 6; // Get's a number between 0-10 

  // Selecting the level with the random number
  if(level_selector == -1) {
    level_default();
  }
  else if(level_selector == 0 || level_selector == 1) {
    level_door(); // This is the level that it's on
  }
  else if(level_selector == 2 ||level_selector == 3 || level_selector == 4) {
    level_enemy();
  }
  else if(level_selector == 5 || level_selector == 6) {
    level_loot();
  }
}

// Displaying the player inventory
void display_inventory() {
  for(int i = 0;i < playerInventory.size();++i) {
    if(i == 0) {
      cout << "1" << " " << playerInventory[i] << " ";
    }
    else if(i != 0) {
      cout << i + 1<< " " << playerInventory[i] << " ";
    }
  }
}

// Deciding what the loot box gives the player
void loot_boxItems() {
  
  srand(time(NULL));
  loot_number = rand() % 5;
  if(loot_number == 0){
    cout << "You've aquired 20 coins\nType \"ok\" to continue > ";
      cin >> playerDecision;
  }
  else if(loot_number == 1) {
    cout << "You've aquired the Magical Sword!\n";
  loot_option = "Magical Sword";

   cout << "Do you want weapon info?(yes or no) > ";
    cin >> playerDecision;

    if(playerDecision == "Yes" || playerDecision == "yes") {
      system("clear");
      loot_infoOption = "Magical Sword";
      loot_info();
      items_into_inventory();
    }else{
      system("clear");
      items_into_inventory();
      cout << "";
    }
  }
  else if(loot_number == 2) {
  cout << "You've aquired the axe\n";
    loot_option = "Axe";
    
  cout << "Do you want weapon info?(yes or no) > ";
    cin >> playerDecision;
    
      if(playerDecision == "Yes" || playerDecision == "yes") {
        system("clear");
        loot_infoOption = "Axe";
        loot_info();
        items_into_inventory();
      }else{
        system("clear");
        items_into_inventory();
        cout << "";
      }
    }
  else if(loot_number == 3) {
    cout << "You've aquired the knife and fork\n";
      loot_option = "Knife and Fork";

    cout << "Do you want weapon info?(yes or no) > ";
      cin >> playerDecision;

    if(playerDecision == "Yes" || playerDecision == "yes") {
      system("clear");
      loot_infoOption = "Knife and Fork";
      loot_info();
      items_into_inventory();
    }else{
      system("clear");
      items_into_inventory();
      cout <<"";
    }
  }
}

// For information about aquired loot
void loot_info() {
  
  if(loot_infoOption == "Magical Sword") {
    cout << "    )         " << endl;
    cout << "          (            " << endl;
    cout << "        '    }      " << endl;
    cout << "      (    '      " << endl;
    cout << "     '      (   " << endl;
    cout << "      )  |    ) " << endl;
    cout << "    '   /|\\    `" << endl;
    cout << "   )   / | \\  ` )   " << endl;
    cout << "  {    | | |  {   " << endl;
    cout << " }     | | |  ." << endl;
    cout << "  '    | | |    )" << endl;
    cout << " (    /| | |\\    ." << endl;
    cout << "  .  / | | | \\  (" << endl;
    cout << "}    \\ \\ | / /  .        " << endl;
    cout << " (    \\ `-' /    }" << endl;
    cout << " '    / ,-. \\    ' " << endl;
    cout << "  }  / / | \\ \\  }" << endl;
    cout << " '   \\ | | | /   } " << endl;
    cout << "  (   \\| | |/  (" << endl;
    cout << "    )  | | |  )" << endl;
    cout << "    .  | | |  '" << endl;
    cout << "       J | L" << endl;
    cout << " /|    J_|_L    |\\" << endl;
    cout << " \\ \\___/ o \\___/ /" << endl;
    cout << "  \\_____ _ _____/" << endl;
    cout << "        |-|" << endl;
    cout << "        |-|" << endl;
    cout << "        |-|" << endl;
    cout << "       ,'-'." << endl;
    cout << "       '---'" << endl;
    
    cout << "The Magical Sword is the best sword in Monster Slayer it's attacks are worth 14 damage.";
    cout << "\nType \"ok\" to continue > ";
      cin >> playerDecision;
    system("clear");
  }
  else if(loot_infoOption == "Axe") {
    cout << "                                           _.gd8888888bp._" << endl;
    cout << "                                        .g88888888888888888p." << endl;
    cout << "                                      .d8888P""       ""Y8888b." << endl;
    cout << "                                      \"Y8P\"               \"Y8P'" << endl;
    cout << "                                         `.               ,'" << endl;
    cout << "                                           \\     .-.     /" << endl;
    cout << "                                            \   (___)   /" << endl;
    cout << " .------------------._______________________:__________j" << endl;
    cout << "/                   |                      |           |`-.,_" << endl;
    cout << "\###################|######################|###########|,-'`" << endl;
    cout << " `------------------'                       :    ___   l" << endl;
    cout << "                                            /   (   )   \\" << endl;
    cout << "                                           /     `-'     \\" << endl;
    cout << "                                         ,'               `." << endl;
    cout << "                                      .d8b.               .d8b." << endl;
    cout << "                                      \"Y8888p..       ,.d8888P\"" << endl;
    cout << "                                        \"Y88888888888888888P\"" << endl;
    cout << "                                           \"\"YY8888888PP\"\"" << endl;
    
    cout << "This is the Axe weapon the axe is capable of doing 10 damage.";
    cout << "\nType \"ok\" to continue > ";
      cin >> playerDecision;
    system("clear");
  }
  else if(loot_infoOption == "Knife and Fork") {
    cout << "      / )" << endl;
    cout << "|||| / /" << endl;
    cout << "||||/ /" << endl;
    cout << "\\__(_/" << endl;
    cout << " ||//" << endl;
    cout << " ||/" << endl;
    cout << " ||" << endl;
    cout << "(||      " << endl;
    cout << " \"\"" << endl;
    cout << "This is the Knife and Fork weapon and it's capable of doing 7 damage";
    cout << "\nType \"ok\" to continue > ";
      cin >> playerDecision;
    system("clear");
  }
  else if(loot_infoOption == "Stick") {
    cout << "     |" << endl;
    cout << "    |" << endl;
    cout << "   |" << endl;
    cout << "  |" << endl;
    cout << " |" << endl;
    cout << "|" << endl;
    cout << "This is the flimsy stick and it's capable of doing 5 damage";
  }
}

// Putting whatever item the player get into their inventory
void items_into_inventory() {
if(loot_number == 1) {
  playerInventory.insert(playerInventory.end(), loot_option);
  }
else if(loot_number == 2) {
  playerInventory.insert(playerInventory.end(), loot_option);
}
else if(loot_number == 3) {
  playerInventory.insert(playerInventory.end(), loot_option);
}
}

void checkingDupes() {
    for (int i = 0; i < playerInventory.size(); ++i) {

    }
}

int main() {
  // Getting the player name
  cout << "Enter your player name." << endl;
    cin >> PLAYERNAME;
  system("clear");
  cout << "Welcome " + PLAYERNAME << " to Monster Slayer!\n";
  cout << "Would you like to go through a tutorial?(yes or no)\n";
    cin >> playerDecision;

  // This is the game tutorial
  if(playerDecision == "yes") {
// Game description
  level_default();
  cout << "In Monster Slayer the goal is to aquire loot and defeat monsters, and then once your ready you can go against the final boss!\nType \"ok\" to  continue > ";
    cin >> playerDecision;
  system("clear");
// Loot box tutorial 
  level_loot();
    cout << "This is a loot box, they are used to get more items in your inventory and also gain more coins.\n";
    cout << "Type \"ok\" to open the loot box > ";
      cin >> playerDecision;
// How to get to loot info explanation
  cout << "You've aquired a stick!\n";
    loot_option = "stick";
  cout << "When items are aquired they're added to your inventory.\n";
    cout << "You can also look at the item info. All you have to do is type \"info\".\nType \"info\" to continue > ";
    cin >> playerDecision;
  system("clear");
// Loot info tutorial
  loot_infoOption = "Stick";
    loot_info();
  cout << "\n\nThe loot info menu is able to give a description about each item that is aquired it very important to use the menu so that you know houw much damge a weapon does.\nType \"ok\" to exit the loot info menu > ";
    cin >> playerDecision;
  system("clear");
// Door level tutorial
level_door();
    cout << "\nThis is the door level whenever you encounter a door you have the option to enter or not to enter type \"ok\" to enter the door.";
    cin >> playerDecision;
  system("clear");
level_doorEntry();
    cout << "\nYou have now entered into the door whenver you enter into a door there is a chance is a chance for loot a key or an enemy to spawn in.\nType \"ok\" to continue > ";
    cin >> playerDecision;
  system("clear");
level_doorEntryEnemy();
    cout << "\n Look a level 1 enemy has appeared! Whenever an enemy appears you have to fight back. Luckily this is only a level 1 enemy so it is only capable of doing 1-3 damage per attack.\nType \"ok\" to continue > ";
    cin >> playerDecision;
   enemyLevel = 1;
monster_health();
monster_attackOptions();
  system("clear");
level_doorEntryEnemy();
    cout << "\n The monster did " << attackDamage << " damage you currently have " << player_hp << " hp. The enemy has " << enemy_hp;
    cout << "\n Now it's your turn to fight back. You have the choice to decide which weapon you would like to attack with.\n\nType \"ok\" to continue > ";
    cin >> playerDecision;  
  system("clear");
level_doorEntryEnemy();
    cout << "\n" << "This is your inventory. Your inventory displays all the weapons you have to attack with. In order to attack the enemy you have to type the number the weapon is associated with.\n";
display_inventory();
    cout << "\nType \"1\" to attack the enemy with the Stick > ";
      cin >> playerDecisionNum;
  system("clear");
level_doorEntryEnemy();
player_attackDamage();
    cout << "Your attack did 5 damage. The enemy has " << enemy_hp << " hp" << endl;
    cout << "Type \"ok\" to continue > ";
      cin >> playerDecision;
monster_attackOptions();
    cout << "\n The monster attacked back and did " << attackDamage << " damage. Your currently have " << player_hp << " hp" << endl;
display_inventory();
    cout << "\nChoose a weapon to combat the monster with > ";
      cin >> playerDecisionNum;
    cout << "\nYour attack did 5 damage. The enemy has been defeated!\nType \"ok\" to continue > ";
      cin >> playerDecision;
    system("clear");
level_doorEntryEnemy();
    cout << "\nCongragulations on defeating your first enemy! Collect your loot and leave the room\n\nType \"ok\" to collect 10 coins > ";
      cin >> playerDecision;
    system("clear");
    cout << "10 coins added to inventory." << endl;
level_doorEntryEnemy();
    cout << "Type \"ok\" to leave the room > ";
      cin >> playerDecision;
    system("clear");
level_door();
    cout << "Tutorial complete good luck on your adventures " << PLAYERNAME << endl;
    cout << "Type \"ok\" to continue > ";
      cin >> playerDecision;
    system("clear");    
      }
  else if(playerDecision == "no") {
    cout << "";
  }

  // Actual Game Starts
  while(player_hp >= 0 && GAMEWINNER == false) {
levelGen();
    if(level_selector == 0 || level_selector == 1) { // Level door
    cout << "Do you want to enter the door?\n";
    cout << "Type \"Yes\" or \"No\" > ";
        cin >> playerDecision;
    
    if(playerDecision == "Yes" || playerDecision == "yes") {
    system("clear");
entryGen();  
      if(entrySelector == 0 || entrySelector == 1) { // Level door enemy
monsters();
monster_health();
      cout << "A enemy has appeard fight back! The monster level is " << enemyLevel;
    if(enemyLevel == 1) {
      cout << "(has 10 hp and is capable of doing 1-3 damage per attack)" << endl;
    }
    else if(enemyLevel == 2) {
      cout << "(has 20 hp and is capable of doing 4-6 damage per attack)" << endl;
    }
    else if(enemyLevel == 3) {
      cout << "(has 30 hp and is capable of doing 7-9 damage per attack)" << endl;
    }
    while(enemy_hp > 0 && player_hp > 0) {
display_inventory();
    cout << "\nChoose a weapon to attack the monster with.\n\nType a number > ";
      cin >> playerDecisionNum;
player_attackDamage();
    cout << "\nYour attack did " << playerAttackDamage << " damage. The monster has ";
      if(enemy_hp < 0) {
        cout << "0 hp" << endl;
      }
      else{
      cout << enemy_hp << " hp" << endl; 
        }
      if(enemy_hp > 0) {
monster_attackOptions();
    cout << "The monster did " << attackDamage << " damage. You have " << player_hp << " hp" << endl;
        }
      cout << "------------------------------------------" << endl;
      }
    cout << "Monster defeated!\nType \"ok\" to continue > ";
        cin >> playerDecision;
      system("clear");
        }
      else if(entrySelector == 2 || entrySelector == 3) { // Level door loot box
    cout << "You found a loot box!\n\nType \"ok\" to open the loot box > ";
      cin >> playerDecision;
loot_boxItems();
        }
      else if(entrySelector == 4) { // Level door boss
        playerHasKey = true;
    cout << "\nYou've found the key! If your ready to battle the boss use the key to unlock the boss battle door\nAre you ready to battle the boss?(yes or no) > ";
        cin >> playerDecision;
      if(playerDecision == "Yes" || playerDecision == "yes") {
level_doorEntryBossBattle();
    cout << "Type\"ok\" to enter into the boss lair > ";
        cin >> playerDecision;      
level_boss();
        cout << "Welcome to the boss lair! The boss is the most powerful being in this dungeon. It is your task to beat it. Good luck!\nType \"ok\" to continue > ";
        cin >> playerDecision;
        system("clear");
level_boss();
        cout << "The boss is capable of doing 13-20 damge per attack. Goodluck!\n";
        enemyLevel = 10;
monster_health();
    while(enemy_hp > 0 && player_hp > 0) {
display_inventory();
    cout << "\nChoose a weapon to attack the boss with.\nType a number > ";
      cin >> playerDecisionNum;
player_attackDamage();
    cout << "Your attack did " << playerAttackDamage << " damage. The monster has ";
      if(enemy_hp < 0) {
        cout << "0 hp" << endl;
      }
      else{
      cout << enemy_hp << " hp" << endl; 
        }
    if(enemy_hp > 0) {
monster_attackOptions();
    cout << "The boss did " << attackDamage << " damage. You have " << player_hp << " hp" << endl;
      }
      else if(enemy_hp <= 0) {
        GAMEWINNER = true;
      }
    cout << "------------------------------------------" << endl; 
    }
      }
      else if(playerDecision == "No" || playerDecision == "no") {
        system("clear");
      } 
        }
      }
    else if(playerDecision == "No" || playerDecision == "no") {
      system("clear");
      }
    }
    else if(level_selector == 2 || level_selector == 3 || level_selector == 4) { // For the enemy level
monsters();
monster_health();
      cout << "A enemy has appeard fight back! The monster level is " << enemyLevel << " ";
    if(enemyLevel == 1) {
      cout << "(has 10 hp and is capable of doing 1-3 damage per attack)\n" << endl;
    }
    else if(enemyLevel == 2) {
      cout << "(has 20 hp and is capable of doing 4-6 damage per attack)\n" << endl;
    }
    else if(enemyLevel == 3) {
      cout << "(has 30 hp and is capable of doing 7-9 damage per attack)\n" << endl;
    }
    while(enemy_hp > 0 && player_hp > 0) { // Fighting the monster
display_inventory();
    cout << "\nChoose a weapon to attack the monster with.\nType a number > ";
      cin >> playerDecisionNum;
player_attackDamage();
    cout << "Your attack did " << playerAttackDamage << " damage. The monster has ";
      if(enemy_hp < 0) {
        cout << "0 hp" << endl;
      }
      else{
      cout << enemy_hp << " hp" << endl; 
        }
    if(enemy_hp > 0) {
monster_attackOptions();
    cout << "The monster did " << attackDamage << " damage. You have " << player_hp << " hp" << endl;
      }
    else if(player_hp <= 0) {
      break;
    }
      cout << "------------------------------------------" << endl;
    }
    cout << "Monster defeated! 10 coins have been added to your inventory.\n\nType \"ok\" to continue > ";
      cin >> playerDecision;
    system("clear");
      
  }
    else if(level_selector == 5 || level_selector == 6) { // For the loot level
    cout << "You've found a loot box!\nType \"ok\" to collect the loot box items > ";
      cin >> playerDecision;  
loot_boxItems();
      system("clear");
    }
    
  } // End of while loop
  if(player_hp <= 0) {
    cout << "You have been defeated by the dungeon.";
  }
  else if(GAMEWINNER == true) {
    cout << "╔═══╗──────────────╔╗───╔╗────╔╗\n" << "║╔═╗║─────────────╔╝╚╗──║║───╔╝╚╗\n" << "║║─╚╬══╦═╗╔══╦═╦══╬╗╔╬╗╔╣║╔══╬╗╔╬╦══╦═╗\n" << "║║─╔╣╔╗║╔╗╣╔╗║╔╣╔╗║║║║║║║║║╔╗║║║╠╣╔╗║╔╗╗\n" << "║╚═╝║╚╝║║║║╚╝║║║╔╗║║╚╣╚╝║╚╣╔╗║║╚╣║╚╝║║║║\n" << "╚═══╩══╩╝╚╩═╗╠╝╚╝╚╝╚═╩══╩═╩╝╚╝╚═╩╩══╩╝╚╝\n" << "──────────╔═╝║\n" << "──────────╚══╝\n" << endl;
    cout << "You Win!";
  }

  
}