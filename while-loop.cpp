#include <iostream>
#include <string>
#include <list>
#include <algorithm>
#include <array>
#include <random>
#include "macros.h"
#include "functions.h"
#include "globals.h"
#include "objects.h"
#include <iterator>

using namespace std;

void runGame() {
    while (runstate = 1) {
        for(int i =0; i < playerCount; i++) {
            playerList[i].Check_Status();
           // if (Player.Location == Go) {
           // cout << "1. Roll Dice (R)"
           // cin << move;
           // if (move == r) {rollDice();}
           //}
           // else if (in_jail == True) {
           // cout << "1. Roll Dice (R)" << "\n" << "2. Get out of Jail (J)" << "\n";
           // cin << move;
           //  if (move == r) {rollDice()};
           //  elseif (move == j) {cout << "


           }

        }

        // Check for Bankruptcy
        for(int i = 0; i < playerCount; i++) {
            if (playerList[i].wallet + playerList[i]. < 0) { // One of the players goes into debt

            }

        }
    }
}


/*
Player play1("fares", 1);
Property house(1, 2, 5000, "Blue House");
Property villa(2, 2, 60000, "Big House");
play1.addProperty(house);
play1.addProperty(villa);
play1.Check_Status();
play1.chargeMoney(3000);
cout << play1.bankruptcyStatus;
cout << "\n";
 */