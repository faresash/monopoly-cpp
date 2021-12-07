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
int endgame = 0;
int seed;
char move;
int playerCount;
list<Player> playerList;
int state = 0;
bool turnFlg = 0;
int dice[2] = {0, 0};
string decision;
string exit_decision;

int main() {
//--------------------------------------------------------------------------------------------------//
//----------------------------------------Basic Starting Menu---------------------------------------//

    //-------------------------------------Player Name Input----------------------------------------//
    string input;


    cout << "                  MONOPOlY\n" << "Enter seed number:\n";
    cin >> seed;
    cout << "2-8 players\n"
         << "Once all names are entered, type 'start' to begin.\n"
         << "Enter names below:\n";

    while (true) {
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
    for (int i = 0; i < playerCount; i++) {
        Player play1(players_arr[i], i);
        playerList.push_back(play1);
    }
//------------------------------------------------------------------------------------------------//
//--------------------------------------Initialize Board Squares----------------------------------//



//------------------------------------------------------------------------------------------------//
//--------------------------------------Game Operating System-------------------------------------//

    cout << "\n\nSTARTED GAME \n";
    cout << "press \"next\" to start turn.\n";
    while (true) {
        string command;
        cin >> command;

        if (command == "next") {
            state += 1;
            cout << "\nTURN " << state << "\n";
        }

        if (command == "show") {
            list<Player>::iterator iter;
            for (iter = playerList.begin(); iter != playerList.end(); ++iter) {
                iter->Check_Status();
                cout << "\n";
            }
        }

        if ((command == "quit") || (command == "q")) {
            cout << "Thanks for playing!";
            break;
        }

        // Check for Bankruptcy and End Game
        list<Player>::iterator iter_endgame;
        for (iter_endgame = playerList.begin(); iter_endgame != playerList.end(); ++iter_endgame) {
            iter_endgame->Is_Bankrupt();
            if (iter_endgame->bankruptcyStatus) {
                endgame = 1;
            }
        }

        if (endgame == 1) {
            cout << "END GAME";
            break;
        }


        if (command == "next") {

            list<Player>::iterator iter;
            for (iter = playerList.begin(); iter != playerList.end(); ++iter) {
                while(exit_decision != "no") {
                    cout << iter->name << " ,what action would you like to take?\n";
                    cin >> decision;
                    if (decision == "roll") {
                        dice[0] = 1 + (rand() % 6);
                        dice[1] = 1 + (rand() % 6);
                        iter->move_forward(dice[0] + dice[1]);
                        cout << "You are at position index " << iter->position << "\n";
                        cout << "Want to take another action?\n";
                        cin >> exit_decision;
                    }
                    if (decision == "sell") {
                        /*
                         1. Your options to sell are: [DISPLAY OWNED PROPERTIES]
                         2. Pick property to sell:
                         3. IMPLEMENT SELLING PICKED PROPERTY
                         */
                        int propSell;
                        cout << "Your options to sell are: ";
                        iter->Check_Properties();
                        cout << "Which property to sell: ";
                        cin >> propSell;

                        cout << "\nWant to take another action?\n";
                        cin >> exit_decision;
                    }
                    if (decision == "trade") {
                        /*
                         1. What Player to Trade with?
                         2. Manually add or remove properties/money from both players through commands
                         */
                        cout << "Want to take another action?\n";
                        cin >> exit_decision;
                    }
                    if (decision == "pay_jail") {
                        /*
                         1. remove $50 from player's account
                         2. Roll dice for player to get to new index
                         */
                        cout << "Want to take another action?\n";
                        cin >> exit_decision;
                    }
                }
                exit_decision = " ";
            }
            cout << "\nEnter \"next\" for next turn.\n";
            cout << "      \"quit\" to exit the game.\n";
            cout << "      \"show\" to show players' info.\n";
        }

    }

//------------------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------//

        return 0;
}