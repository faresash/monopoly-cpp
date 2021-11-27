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
list<string> players_ll; //linked list of player names
int seed;

int main() {
//--------------------------------------------------------------------------------------------------//
//----------------------------------------Basic Starting Menu---------------------------------------//

    //-------------------------------------Player Name Input----------------------------------------//
    string input;
    int playerCount = 0;


    cout << "                  MONOPOlY\n" << "Enter seed number:\n";
    cin >> seed;
    cout << "2-8 players\n"
         << "Once all names are entered, type 'start' to begin.\n"
         << "Enter names below:\n";

    while (1) {
        while (input != "start") {
            cin >> input;
            if (playerCount > 7) cout << "Too many players! Please begin game.\n";
            else if (input != "start") {
                playerCount++;
                players_ll.push_back(input);
            }
        }
        input.clear();
        if (playerCount < 2) cout << "Too few players! Add more players before starting:\n";
        else break;
    }

    //----------------------------------Player Order Shuffle---------------------------------------//
    auto it = players_ll.cbegin();
    string players_arr[playerCount];
    for (int i = 0; i < playerCount; i++) {
        players_arr[i] = *it++;
    }

    shuffle(players_arr, players_arr + playerCount, default_random_engine(seed));

    cout << "Awesome! Before we begin, here is the order you will play in:\n";
    for (int i = 0; i < playerCount; i++) {
        cout << i << ": " << players_arr[i] << " -- $1,500" << endl;
    }

    cout << "As you can see, all of you have $1,500. Try not to lose it.\n";

    cout << "Enjoy!\n";
//------------------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------//

//------------------------------------------------------------------------------------------------//
//--------------------------------------Game Function Call----------------------------------------//


    runGame();


//------------------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------//

    return 0;
}