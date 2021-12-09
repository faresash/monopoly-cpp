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
#include <ctime>
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
void* Board[40];
bool roll_flag = false;
string purchase_decision;
Property current;
Property * curr;
bool flag = true;

int main() {
    srand(time(NULL));
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
        play1.jailStatus = false;
        playerList.push_back(play1);
    }

    chanceDeck myDeck; //Initialize the deck of Chance Cards
//------------------------------------------------------------------------------------------------//
//--------------------------------------Initialize Board Squares----------------------------------//

    Board[0] = new goSquare(200, "Go", 0);
    Board[1] = new propertySquare(1, "MEDITERRANEAN_AVENUE", 0, "brown", 60);
    Board[2] = new Chance;
    Board[3] = new propertySquare(3, "BALTIC_AVENUE", 1, "brown", 60);
    Board[4] = new taxSquare(200, "Tax", 5);
    Board[5] = new propertySquare(5, "READING_RAILROAD", 0, "black", 200);
    Board[6] = new propertySquare(6, "ORIENTAL_AVENUE", 0, "light_blue", 100);
    Board[7] = new Chance;
    Board[8] = new propertySquare(8, "VERMONT_AVENUE", 1, "light_blue", 100);
    Board[9] = new propertySquare(9, "CONNECTICUT_AVENUE", 2, "light_blue", 120);
    //Board[10] = new justVisitingSquare();
    Board[11] = new propertySquare(11, "ST.CHARLES_PLACE", 0, "pink", 140);
    Board[12] = new propertySquare(12, "ELECTRIC_COMPANY", 0, "white", 140);
    Board[13] = new propertySquare(13, "STATES_AVENUE", 1, "pink", 140);
    Board[14] = new propertySquare(14, "VIRGINIA_AVENUE", 2, "pink", 160);
    Board[15] = new propertySquare(15, "PENNSYLVANIA_RAILROAD", 1, "black", 200);
    Board[16] = new propertySquare(16, "ST.JAMES_PLACE", 0, "orange", 180);
    Board[17] = new Chance;
    Board[18] = new propertySquare(18, "TENNESSEE_AVENUE", 1, "orange", 180);
    Board[19] = new propertySquare(18, "NEWYORK_AVENUE", 2, "orange", 200);
    Board[20] = new freeParking;
    Board[21] = new propertySquare(20, "KENTUCKY_AVENUE", 0, "red", 220);
    Board[22] = new Chance;
    Board[23] = new propertySquare(23, "INDIAN_AVENUE", 1, "red", 220);
    Board[24] = new propertySquare(24, "ILLINOIS_AVENUE", 2, "red", 240);
    Board[25] = new propertySquare(25, "B.&O._RAILROAD", 2, "black", 200);
    Board[26] = new propertySquare(26,"ATLANTIC_AVENUE", 0, "yellow", 260);
    Board[27] = new propertySquare(27, "VENTNOR_AVENUE", 1, "yellow", 260);
    Board[28] = new propertySquare(28, "WATER_WORKS", 1, "white", 150);
    Board[29] = new propertySquare(29, "MARVIN_GARDENS", 2, "yellow", 280);
    Board[30] = new goToJailSquare(-1, "Got to Jail", 10);
    Board[31] = new propertySquare(31, "PACIFIC_AVENUE", 0, "green", 300);
    Board[32] = new propertySquare(32, "NORTH_CAROLINA_AVENUE", 1, "green", 300);
    Board[33] = new Chance;
    Board[34] = new propertySquare(34, "PENNSYLVANIA_AVENUE", 2, "green", 300);
    Board[35] = new propertySquare(35, "SHORT_LINE", 4, "black", 320);
    Board[36] = new Chance;
    Board[37] = new propertySquare(37, "PARK_PLACE", 0, "blue", 350);
    Board[38] = new taxSquare(100, "Luxury Tax", 38);
    Board[39] = new propertySquare(39, "BOARDWALK", 1, "blue", 400);

    // DECIPHERING BOARD ARRAY EXAMPLE:  cout << (*((goSquare *) Board[0])).money;
    //cout << (*((goSquare *) Board[0])).money;
    //cout << (*((propertySquare *) Board[9])).property.getValue();

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
            cout << "END GAME\n";
            cout << "The winner is: \n";
            break;
        }

        if (command == "next") {
            list<Player>::iterator iter;
            for (iter = playerList.begin(); iter != playerList.end(); ++iter) {
                while (exit_decision != "no") {
                    cout << iter->name << ", what action would you like to take?\n";
                    cin >> decision;

                    if (decision == "sell") {
                        /*
                         1. Your options to sell are: [DISPLAY OWNED PROPERTIES]
                         2. Pick property to sell:
                         3. IMPLEMENT SELLING PICKED PROPERTY
                         */
                        string propSell;
                        cout << "Your options to sell are: ";
                        iter->Check_Properties();
                        cout << "Which property to sell: ";
                        cin >> propSell;

                        iter->sellProperty(propSell);
                        cout << "\nProperty Sold!\n";

                        cout << "\nWant to take another action?\n";
                        cin >> exit_decision;
                    }
                    if (decision == "trade") {
                        string tradePartner;
                        double tradeAmount;
                        string tradeProperty;
                        string trade;
                        string agreement;
                        /*
                         1. What Player to Trade with?
                         2. Manually add or remove properties/money from both players through commands
                         */
                        cout << "Choose a player to trade with: ";
                        cin >> tradePartner;
                        cout << "\nChoose a positive monetary value to offer money and negative to request money: ";
                        cin >> tradeAmount;
                        cout << "\nChoose a property to trade: ";
                        cin >> tradeProperty;
                        cout << "\nWould you like to buy or sell this property? "; // ONLY OPTIONS SHOULD BE "BUY" OR "SELL"
                        cin >> trade;
                        cout << "\nDid the other player agree to your offer? ";
                        cin >> agreement;

                        if ((agreement == "no") || (agreement == "No")) {
                            // Do Nothing
                        }
                        else {
                            list<Player>::iterator iterator;
                            for (iterator = playerList.begin(); iterator != playerList.end(); ++iterator) {
                                if (iterator->name == tradePartner) {
                                    iter->payPlayer(*iterator, tradeAmount);
                                    iter->transferProperty(*iterator, tradeProperty, trade);
                                    cout << "\nTrade has been completed!\n";
                                }
                            }
                        }
                        cout << "Want to take another action?\n";
                        cin >> exit_decision;
                    }

                    if (decision == "show") {
                        iter->Check_Status();
                        cout << "\n";
                    }

                    if (iter->jailStatus) { // If in Jail then...
                        if (decision == "roll") {
                            cout << "\nYou cannot roll while in jail, please choose another option.\n";
                        }
                        if (decision == "pay_jail") {
                            /*
                             1. remove $50 from player's account
                             2. Roll dice for player to get to new index
                             */
                            iter->wallet -= 50;
                            iter->jailStatus = false;

                            cout << "Want to take another action?\n";
                            cin >> exit_decision;
                        }
                    }
                    else { // Ensures that player can't roll while in jail
                        if (decision == "roll") {
                            if (!roll_flag) {
                                roll_flag = true;
                                dice[0] = 1 + (rand() % 6);
                                dice[1] = 1 + (rand() % 6);
                                cout << "Dice 1: " << dice[0] << "     ";
                                cout << "Dice 2: " << dice[1] << endl;
                                iter->move_forward(dice[0] + dice[1]);
                                cout << "You are at position index " << iter->position << "\n";
                                switch (iter -> position) {
                                    // State machine that relates position index to board array
                                    case 0:
                                        cout << "Go Square\n";
                                        iter->addMoney((*((goSquare *) Board[iter -> position])).money);
                                        break;
                                    case 1:
                                        //set a current value to reference the property were on
                                        curr = (*((propertySquare *) Board[iter -> position])).property;

                                        //prints out important facts about property
                                        cout << "Property Square: ";
                                        cout << curr->name << endl;
                                        cout << "Color: " << curr->color << endl;
                                        cout << "Value: " << curr->value << endl;
                                        // IF the property is owned then you pay a fixed rate of 0.1 * the property value as rent
                                        if (current.owned_flag) {
                                            cout << current.name << " is owned by " << curr->owner -> name << endl;
                                            cout << "You must pay: " << (0.1 * curr->value) << "\n";
                                            iter->payPlayer(*curr->owner, (0.1 * curr->value));
                                        }
                                            // Otherwise ask if player wants to buy
                                        else {
                                            cout << "This property is unowned\n" << "Would you like to buy it?\n";
                                            cin >> purchase_decision;
                                            if (purchase_decision == "yes") {
                                                // IF player is broke they cannot buy the property and so they c
                                                if (iter -> wallet < curr->value) cout << "You're too broke\n";
                                                else {
                                                    curr->owned_flag = true;
                                                    iter -> addProperty(*curr);
                                                    iter -> chargeMoney(curr->value);
                                                    curr->owner = &*iter;
                                                }
                                            }
                                        }
                                        break;
                                    case 2:
                                        cout << "Chance Square!\n";
                                        myDeck.executeChance(*iter, playerList);
                                        myDeck.popChance();
                                        break;
                                    case 3:
                                        //set a current value to reference the property were on
                                        curr = (*((propertySquare *) Board[iter -> position])).property;

                                        //prints out important facts about property
                                        cout << "Property Square: ";
                                        cout << curr->name << endl;
                                        cout << "Color: " << curr->color << endl;
                                        cout << "Value: " << curr->value << endl;
                                        // IF the property is owned then you pay a fixed rate of 0.1 * the property value as rent
                                        if (current.owned_flag) {
                                            cout << current.name << " is owned by " << curr->owner -> name << endl;
                                            cout << "You must pay: " << (0.1 * curr->value) << "\n";
                                            iter->payPlayer(*curr->owner, (0.1 * curr->value));
                                        }
                                            // Otherwise ask if player wants to buy
                                        else {
                                            cout << "This property is unowned\n" << "Would you like to buy it?\n";
                                            cin >> purchase_decision;
                                            if (purchase_decision == "yes") {
                                                // IF player is broke they cannot buy the property and so they c
                                                if (iter -> wallet < curr->value) cout << "You're too broke\n";
                                                else {
                                                    curr->owned_flag = true;
                                                    iter -> addProperty(*curr);
                                                    iter -> chargeMoney(curr->value);
                                                    curr->owner = &*iter;
                                                }
                                            }
                                        }
                                        break;
                                    case 4:
                                        cout << "Tax Square!\n";
                                        iter->chargeMoney((*((taxSquare *) Board[iter -> position])).taxRate);
                                        break;
                                    case 5:
                                        //set a current value to reference the property were on
                                        curr = (*((propertySquare *) Board[iter -> position])).property;

                                        //prints out important facts about property
                                        cout << "Property Square: ";
                                        cout << curr->name << endl;
                                        cout << "Color: " << curr->color << endl;
                                        cout << "Value: " << curr->value << endl;
                                        // IF the property is owned then you pay a fixed rate of 0.1 * the property value as rent
                                        if (current.owned_flag) {
                                            cout << current.name << " is owned by " << curr->owner -> name << endl;
                                            cout << "You must pay: " << (0.1 * curr->value) << "\n";
                                            iter->payPlayer(*curr->owner, (0.1 * curr->value));
                                        }
                                            // Otherwise ask if player wants to buy
                                        else {
                                            cout << "This property is unowned\n" << "Would you like to buy it?\n";
                                            cin >> purchase_decision;
                                            if (purchase_decision == "yes") {
                                                // IF player is broke they cannot buy the property and so they c
                                                if (iter -> wallet < curr->value) cout << "You're too broke\n";
                                                else {
                                                    curr->owned_flag = true;
                                                    iter -> addProperty(*curr);
                                                    iter -> chargeMoney(curr->value);
                                                    curr->owner = &*iter;
                                                }
                                            }
                                        }
                                        break;
                                    case 6:
                                        //set a current value to reference the property were on
                                        curr = (*((propertySquare *) Board[iter -> position])).property;

                                        //prints out important facts about property
                                        cout << "Property Square: ";
                                        cout << curr->name << endl;
                                        cout << "Color: " << curr->color << endl;
                                        cout << "Value: " << curr->value << endl;
                                        // IF the property is owned then you pay a fixed rate of 0.1 * the property value as rent
                                        if (current.owned_flag) {
                                            cout << current.name << " is owned by " << curr->owner -> name << endl;
                                            cout << "You must pay: " << (0.1 * curr->value) << "\n";
                                            iter->payPlayer(*curr->owner, (0.1 * curr->value));
                                        }
                                            // Otherwise ask if player wants to buy
                                        else {
                                            cout << "This property is unowned\n" << "Would you like to buy it?\n";
                                            cin >> purchase_decision;
                                            if (purchase_decision == "yes") {
                                                // IF player is broke they cannot buy the property and so they c
                                                if (iter -> wallet < curr->value) cout << "You're too broke\n";
                                                else {
                                                    curr->owned_flag = true;
                                                    iter -> addProperty(*curr);
                                                    iter -> chargeMoney(curr->value);
                                                    curr->owner = &*iter;
                                                }
                                            }
                                        }
                                        break;
                                    case 7:
                                        cout << "Chance Square!\n";
                                        myDeck.executeChance(*iter, playerList);
                                        myDeck.popChance();
                                        break;
                                    case 8:
                                        //set a current value to reference the property were on
                                        curr = (*((propertySquare *) Board[iter -> position])).property;

                                        //prints out important facts about property
                                        cout << "Property Square: ";
                                        cout << curr->name << endl;
                                        cout << "Color: " << curr->color << endl;
                                        cout << "Value: " << curr->value << endl;
                                        // IF the property is owned then you pay a fixed rate of 0.1 * the property value as rent
                                        if (current.owned_flag) {
                                            cout << current.name << " is owned by " << curr->owner -> name << endl;
                                            cout << "You must pay: " << (0.1 * curr->value) << "\n";
                                            iter->payPlayer(*curr->owner, (0.1 * curr->value));
                                        }
                                            // Otherwise ask if player wants to buy
                                        else {
                                            cout << "This property is unowned\n" << "Would you like to buy it?\n";
                                            cin >> purchase_decision;
                                            if (purchase_decision == "yes") {
                                                // IF player is broke they cannot buy the property and so they c
                                                if (iter -> wallet < curr->value) cout << "You're too broke\n";
                                                else {
                                                    curr->owned_flag = true;
                                                    iter -> addProperty(*curr);
                                                    iter -> chargeMoney(curr->value);
                                                    curr->owner = &*iter;
                                                }
                                            }
                                        }
                                        break;
                                    case 9:
                                        //set a current value to reference the property were on
                                        curr = (*((propertySquare *) Board[iter -> position])).property;

                                        //prints out important facts about property
                                        cout << "Property Square: ";
                                        cout << curr->name << endl;
                                        cout << "Color: " << curr->color << endl;
                                        cout << "Value: " << curr->value << endl;
                                        // IF the property is owned then you pay a fixed rate of 0.1 * the property value as rent
                                        if (current.owned_flag) {
                                            cout << current.name << " is owned by " << curr->owner -> name << endl;
                                            cout << "You must pay: " << (0.1 * curr->value) << "\n";
                                            iter->payPlayer(*curr->owner, (0.1 * curr->value));
                                        }
                                            // Otherwise ask if player wants to buy
                                        else {
                                            cout << "This property is unowned\n" << "Would you like to buy it?\n";
                                            cin >> purchase_decision;
                                            if (purchase_decision == "yes") {
                                                // IF player is broke they cannot buy the property and so they c
                                                if (iter -> wallet < curr->value) cout << "You're too broke\n";
                                                else {
                                                    curr->owned_flag = true;
                                                    iter -> addProperty(*curr);
                                                    iter -> chargeMoney(curr->value);
                                                    curr->owner = &*iter;
                                                }
                                            }
                                        }
                                        break;
                                    case 10:
                                        cout << "Just Visiting!";
                                        break;
                                    case 11:
                                        //set a current value to reference the property were on
                                        curr = (*((propertySquare *) Board[iter -> position])).property;

                                        //prints out important facts about property
                                        cout << "Property Square: ";
                                        cout << curr->name << endl;
                                        cout << "Color: " << curr->color << endl;
                                        cout << "Value: " << curr->value << endl;
                                        // IF the property is owned then you pay a fixed rate of 0.1 * the property value as rent
                                        if (current.owned_flag) {
                                            cout << current.name << " is owned by " << curr->owner -> name << endl;
                                            cout << "You must pay: " << (0.1 * curr->value) << "\n";
                                            iter->payPlayer(*curr->owner, (0.1 * curr->value));
                                        }
                                            // Otherwise ask if player wants to buy
                                        else {
                                            cout << "This property is unowned\n" << "Would you like to buy it?\n";
                                            cin >> purchase_decision;
                                            if (purchase_decision == "yes") {
                                                // IF player is broke they cannot buy the property and so they c
                                                if (iter -> wallet < curr->value) cout << "You're too broke\n";
                                                else {
                                                    curr->owned_flag = true;
                                                    iter -> addProperty(*curr);
                                                    iter -> chargeMoney(curr->value);
                                                    curr->owner = &*iter;
                                                }
                                            }
                                        }
                                        break;
                                    case 12:
                                        //set a current value to reference the property were on
                                        curr = (*((propertySquare *) Board[iter -> position])).property;

                                        //prints out important facts about property
                                        cout << "Property Square: ";
                                        cout << curr->name << endl;
                                        cout << "Color: " << curr->color << endl;
                                        cout << "Value: " << curr->value << endl;
                                        // IF the property is owned then you pay a fixed rate of 0.1 * the property value as rent
                                        if (current.owned_flag) {
                                            cout << current.name << " is owned by " << curr->owner -> name << endl;
                                            cout << "You must pay: " << (0.1 * curr->value) << "\n";
                                            iter->payPlayer(*curr->owner, (0.1 * curr->value));
                                        }
                                            // Otherwise ask if player wants to buy
                                        else {
                                            cout << "This property is unowned\n" << "Would you like to buy it?\n";
                                            cin >> purchase_decision;
                                            if (purchase_decision == "yes") {
                                                // IF player is broke they cannot buy the property and so they c
                                                if (iter -> wallet < curr->value) cout << "You're too broke\n";
                                                else {
                                                    curr->owned_flag = true;
                                                    iter -> addProperty(*curr);
                                                    iter -> chargeMoney(curr->value);
                                                    curr->owner = &*iter;
                                                }
                                            }
                                        }
                                        break;
                                    case 13:
                                        //set a current value to reference the property were on
                                        curr = (*((propertySquare *) Board[iter -> position])).property;

                                        //prints out important facts about property
                                        cout << "Property Square: ";
                                        cout << curr->name << endl;
                                        cout << "Color: " << curr->color << endl;
                                        cout << "Value: " << curr->value << endl;
                                        // IF the property is owned then you pay a fixed rate of 0.1 * the property value as rent
                                        if (current.owned_flag) {
                                            cout << current.name << " is owned by " << curr->owner -> name << endl;
                                            cout << "You must pay: " << (0.1 * curr->value) << "\n";
                                            iter->payPlayer(*curr->owner, (0.1 * curr->value));
                                        }
                                            // Otherwise ask if player wants to buy
                                        else {
                                            cout << "This property is unowned\n" << "Would you like to buy it?\n";
                                            cin >> purchase_decision;
                                            if (purchase_decision == "yes") {
                                                // IF player is broke they cannot buy the property and so they c
                                                if (iter -> wallet < curr->value) cout << "You're too broke\n";
                                                else {
                                                    curr->owned_flag = true;
                                                    iter -> addProperty(*curr);
                                                    iter -> chargeMoney(curr->value);
                                                    curr->owner = &*iter;
                                                }
                                            }
                                        }
                                        break;
                                    case 14:
                                        //set a current value to reference the property were on
                                        curr = (*((propertySquare *) Board[iter -> position])).property;

                                        //prints out important facts about property
                                        cout << "Property Square: ";
                                        cout << curr->name << endl;
                                        cout << "Color: " << curr->color << endl;
                                        cout << "Value: " << curr->value << endl;
                                        // IF the property is owned then you pay a fixed rate of 0.1 * the property value as rent
                                        if (current.owned_flag) {
                                            cout << current.name << " is owned by " << curr->owner -> name << endl;
                                            cout << "You must pay: " << (0.1 * curr->value) << "\n";
                                            iter->payPlayer(*curr->owner, (0.1 * curr->value));
                                        }
                                            // Otherwise ask if player wants to buy
                                        else {
                                            cout << "This property is unowned\n" << "Would you like to buy it?\n";
                                            cin >> purchase_decision;
                                            if (purchase_decision == "yes") {
                                                // IF player is broke they cannot buy the property and so they c
                                                if (iter -> wallet < curr->value) cout << "You're too broke\n";
                                                else {
                                                    curr->owned_flag = true;
                                                    iter -> addProperty(*curr);
                                                    iter -> chargeMoney(curr->value);
                                                    curr->owner = &*iter;
                                                }
                                            }
                                        }
                                        break;
                                    case 15:
                                        //set a current value to reference the property were on
                                        curr = (*((propertySquare *) Board[iter -> position])).property;

                                        //prints out important facts about property
                                        cout << "Property Square: ";
                                        cout << curr->name << endl;
                                        cout << "Color: " << curr->color << endl;
                                        cout << "Value: " << curr->value << endl;
                                        // IF the property is owned then you pay a fixed rate of 0.1 * the property value as rent
                                        if (current.owned_flag) {
                                            cout << current.name << " is owned by " << curr->owner -> name << endl;
                                            cout << "You must pay: " << (0.1 * curr->value) << "\n";
                                            iter->payPlayer(*curr->owner, (0.1 * curr->value));
                                        }
                                            // Otherwise ask if player wants to buy
                                        else {
                                            cout << "This property is unowned\n" << "Would you like to buy it?\n";
                                            cin >> purchase_decision;
                                            if (purchase_decision == "yes") {
                                                // IF player is broke they cannot buy the property and so they c
                                                if (iter -> wallet < curr->value) cout << "You're too broke\n";
                                                else {
                                                    curr->owned_flag = true;
                                                    iter -> addProperty(*curr);
                                                    iter -> chargeMoney(curr->value);
                                                    curr->owner = &*iter;
                                                }
                                            }
                                        }
                                        break;
                                    case 16:
                                        //set a current value to reference the property were on
                                        curr = (*((propertySquare *) Board[iter -> position])).property;

                                        //prints out important facts about property
                                        cout << "Property Square: ";
                                        cout << curr->name << endl;
                                        cout << "Color: " << curr->color << endl;
                                        cout << "Value: " << curr->value << endl;
                                        // IF the property is owned then you pay a fixed rate of 0.1 * the property value as rent
                                        if (current.owned_flag) {
                                            cout << current.name << " is owned by " << curr->owner -> name << endl;
                                            cout << "You must pay: " << (0.1 * curr->value) << "\n";
                                            iter->payPlayer(*curr->owner, (0.1 * curr->value));
                                        }
                                            // Otherwise ask if player wants to buy
                                        else {
                                            cout << "This property is unowned\n" << "Would you like to buy it?\n";
                                            cin >> purchase_decision;
                                            if (purchase_decision == "yes") {
                                                // IF player is broke they cannot buy the property and so they c
                                                if (iter -> wallet < curr->value) cout << "You're too broke\n";
                                                else {
                                                    curr->owned_flag = true;
                                                    iter -> addProperty(*curr);
                                                    iter -> chargeMoney(curr->value);
                                                    curr->owner = &*iter;
                                                }
                                            }
                                        }
                                        break;
                                    case 17:
                                        cout << "Chance Square!\n";
                                        myDeck.executeChance(*iter, playerList);
                                        myDeck.popChance();
                                        break;
                                    case 18:
                                        //set a current value to reference the property were on
                                        curr = (*((propertySquare *) Board[iter -> position])).property;

                                        //prints out important facts about property
                                        cout << "Property Square: ";
                                        cout << curr->name << endl;
                                        cout << "Color: " << curr->color << endl;
                                        cout << "Value: " << curr->value << endl;
                                        // IF the property is owned then you pay a fixed rate of 0.1 * the property value as rent
                                        if (current.owned_flag) {
                                            cout << current.name << " is owned by " << curr->owner -> name << endl;
                                            cout << "You must pay: " << (0.1 * curr->value) << "\n";
                                            iter->payPlayer(*curr->owner, (0.1 * curr->value));
                                        }
                                            // Otherwise ask if player wants to buy
                                        else {
                                            cout << "This property is unowned\n" << "Would you like to buy it?\n";
                                            cin >> purchase_decision;
                                            if (purchase_decision == "yes") {
                                                // IF player is broke they cannot buy the property and so they c
                                                if (iter -> wallet < curr->value) cout << "You're too broke\n";
                                                else {
                                                    curr->owned_flag = true;
                                                    iter -> addProperty(*curr);
                                                    iter -> chargeMoney(curr->value);
                                                    curr->owner = &*iter;
                                                }
                                            }
                                        }
                                        break;
                                    case 19:
                                        //set a current value to reference the property were on
                                        curr = (*((propertySquare *) Board[iter -> position])).property;

                                        //prints out important facts about property
                                        cout << "Property Square: ";
                                        cout << curr->name << endl;
                                        cout << "Color: " << curr->color << endl;
                                        cout << "Value: " << curr->value << endl;
                                        // IF the property is owned then you pay a fixed rate of 0.1 * the property value as rent
                                        if (current.owned_flag) {
                                            cout << current.name << " is owned by " << curr->owner -> name << endl;
                                            cout << "You must pay: " << (0.1 * curr->value) << "\n";
                                            iter->payPlayer(*curr->owner, (0.1 * curr->value));
                                        }
                                            // Otherwise ask if player wants to buy
                                        else {
                                            cout << "This property is unowned\n" << "Would you like to buy it?\n";
                                            cin >> purchase_decision;
                                            if (purchase_decision == "yes") {
                                                // IF player is broke they cannot buy the property and so they c
                                                if (iter -> wallet < curr->value) cout << "You're too broke\n";
                                                else {
                                                    curr->owned_flag = true;
                                                    iter -> addProperty(*curr);
                                                    iter -> chargeMoney(curr->value);
                                                    curr->owner = &*iter;
                                                }
                                            }
                                        }
                                        break;
                                    case 20:
                                        cout << "Free Parking!\n";
                                        break;
                                    case 21:
                                        //set a current value to reference the property were on
                                        curr = (*((propertySquare *) Board[iter -> position])).property;

                                        //prints out important facts about property
                                        cout << "Property Square: ";
                                        cout << curr->name << endl;
                                        cout << "Color: " << curr->color << endl;
                                        cout << "Value: " << curr->value << endl;
                                        // IF the property is owned then you pay a fixed rate of 0.1 * the property value as rent
                                        if (current.owned_flag) {
                                            cout << current.name << " is owned by " << curr->owner -> name << endl;
                                            cout << "You must pay: " << (0.1 * curr->value) << "\n";
                                            iter->payPlayer(*curr->owner, (0.1 * curr->value));
                                        }
                                            // Otherwise ask if player wants to buy
                                        else {
                                            cout << "This property is unowned\n" << "Would you like to buy it?\n";
                                            cin >> purchase_decision;
                                            if (purchase_decision == "yes") {
                                                // IF player is broke they cannot buy the property and so they c
                                                if (iter -> wallet < curr->value) cout << "You're too broke\n";
                                                else {
                                                    curr->owned_flag = true;
                                                    iter -> addProperty(*curr);
                                                    iter -> chargeMoney(curr->value);
                                                    curr->owner = &*iter;
                                                }
                                            }
                                        }
                                        break;
                                    case 22:
                                        cout << "Chance Square!\n";
                                        myDeck.executeChance(*iter, playerList);
                                        myDeck.popChance();
                                        break;
                                    case 23:
                                        //set a current value to reference the property were on
                                        curr = (*((propertySquare *) Board[iter -> position])).property;

                                        //prints out important facts about property
                                        cout << "Property Square: ";
                                        cout << curr->name << endl;
                                        cout << "Color: " << curr->color << endl;
                                        cout << "Value: " << curr->value << endl;
                                        // IF the property is owned then you pay a fixed rate of 0.1 * the property value as rent
                                        if (current.owned_flag) {
                                            cout << current.name << " is owned by " << curr->owner -> name << endl;
                                            cout << "You must pay: " << (0.1 * curr->value) << "\n";
                                            iter->payPlayer(*curr->owner, (0.1 * curr->value));
                                        }
                                            // Otherwise ask if player wants to buy
                                        else {
                                            cout << "This property is unowned\n" << "Would you like to buy it?\n";
                                            cin >> purchase_decision;
                                            if (purchase_decision == "yes") {
                                                // IF player is broke they cannot buy the property and so they c
                                                if (iter -> wallet < curr->value) cout << "You're too broke\n";
                                                else {
                                                    curr->owned_flag = true;
                                                    iter -> addProperty(*curr);
                                                    iter -> chargeMoney(curr->value);
                                                    curr->owner = &*iter;
                                                }
                                            }
                                        }
                                        break;
                                    case 24:
                                        //set a current value to reference the property were on
                                        curr = (*((propertySquare *) Board[iter -> position])).property;

                                        //prints out important facts about property
                                        cout << "Property Square: ";
                                        cout << curr->name << endl;
                                        cout << "Color: " << curr->color << endl;
                                        cout << "Value: " << curr->value << endl;
                                        // IF the property is owned then you pay a fixed rate of 0.1 * the property value as rent
                                        if (current.owned_flag) {
                                            cout << current.name << " is owned by " << curr->owner -> name << endl;
                                            cout << "You must pay: " << (0.1 * curr->value) << "\n";
                                            iter->payPlayer(*curr->owner, (0.1 * curr->value));
                                        }
                                            // Otherwise ask if player wants to buy
                                        else {
                                            cout << "This property is unowned\n" << "Would you like to buy it?\n";
                                            cin >> purchase_decision;
                                            if (purchase_decision == "yes") {
                                                // IF player is broke they cannot buy the property and so they c
                                                if (iter -> wallet < curr->value) cout << "You're too broke\n";
                                                else {
                                                    curr->owned_flag = true;
                                                    iter -> addProperty(*curr);
                                                    iter -> chargeMoney(curr->value);
                                                    curr->owner = &*iter;
                                                }
                                            }
                                        }
                                        break;
                                    case 25:
                                        //set a current value to reference the property were on
                                        curr = (*((propertySquare *) Board[iter -> position])).property;

                                        //prints out important facts about property
                                        cout << "Property Square: ";
                                        cout << curr->name << endl;
                                        cout << "Color: " << curr->color << endl;
                                        cout << "Value: " << curr->value << endl;
                                        // IF the property is owned then you pay a fixed rate of 0.1 * the property value as rent
                                        if (current.owned_flag) {
                                            cout << current.name << " is owned by " << curr->owner -> name << endl;
                                            cout << "You must pay: " << (0.1 * curr->value) << "\n";
                                            iter->payPlayer(*curr->owner, (0.1 * curr->value));
                                        }
                                            // Otherwise ask if player wants to buy
                                        else {
                                            cout << "This property is unowned\n" << "Would you like to buy it?\n";
                                            cin >> purchase_decision;
                                            if (purchase_decision == "yes") {
                                                // IF player is broke they cannot buy the property and so they c
                                                if (iter -> wallet < curr->value) cout << "You're too broke\n";
                                                else {
                                                    curr->owned_flag = true;
                                                    iter -> addProperty(*curr);
                                                    iter -> chargeMoney(curr->value);
                                                    curr->owner = &*iter;
                                                }
                                            }
                                        }
                                        break;
                                    case 26:
                                        //set a current value to reference the property were on
                                        curr = (*((propertySquare *) Board[iter -> position])).property;

                                        //prints out important facts about property
                                        cout << "Property Square: ";
                                        cout << curr->name << endl;
                                        cout << "Color: " << curr->color << endl;
                                        cout << "Value: " << curr->value << endl;
                                        // IF the property is owned then you pay a fixed rate of 0.1 * the property value as rent
                                        if (current.owned_flag) {
                                            cout << current.name << " is owned by " << curr->owner -> name << endl;
                                            cout << "You must pay: " << (0.1 * curr->value) << "\n";
                                            iter->payPlayer(*curr->owner, (0.1 * curr->value));
                                        }
                                            // Otherwise ask if player wants to buy
                                        else {
                                            cout << "This property is unowned\n" << "Would you like to buy it?\n";
                                            cin >> purchase_decision;
                                            if (purchase_decision == "yes") {
                                                // IF player is broke they cannot buy the property and so they c
                                                if (iter -> wallet < curr->value) cout << "You're too broke\n";
                                                else {
                                                    curr->owned_flag = true;
                                                    iter -> addProperty(*curr);
                                                    iter -> chargeMoney(curr->value);
                                                    curr->owner = &*iter;
                                                }
                                            }
                                        }
                                        break;
                                    case 27:
                                        //set a current value to reference the property were on
                                        curr = (*((propertySquare *) Board[iter -> position])).property;

                                        //prints out important facts about property
                                        cout << "Property Square: ";
                                        cout << curr->name << endl;
                                        cout << "Color: " << curr->color << endl;
                                        cout << "Value: " << curr->value << endl;
                                        // IF the property is owned then you pay a fixed rate of 0.1 * the property value as rent
                                        if (current.owned_flag) {
                                            cout << current.name << " is owned by " << curr->owner -> name << endl;
                                            cout << "You must pay: " << (0.1 * curr->value) << "\n";
                                            iter->payPlayer(*curr->owner, (0.1 * curr->value));
                                        }
                                            // Otherwise ask if player wants to buy
                                        else {
                                            cout << "This property is unowned\n" << "Would you like to buy it?\n";
                                            cin >> purchase_decision;
                                            if (purchase_decision == "yes") {
                                                // IF player is broke they cannot buy the property and so they c
                                                if (iter -> wallet < curr->value) cout << "You're too broke\n";
                                                else {
                                                    curr->owned_flag = true;
                                                    iter -> addProperty(*curr);
                                                    iter -> chargeMoney(curr->value);
                                                    curr->owner = &*iter;
                                                }
                                            }
                                        }
                                        break;
                                    case 28:
                                        //set a current value to reference the property were on
                                        curr = (*((propertySquare *) Board[iter -> position])).property;

                                        //prints out important facts about property
                                        cout << "Property Square: ";
                                        cout << curr->name << endl;
                                        cout << "Color: " << curr->color << endl;
                                        cout << "Value: " << curr->value << endl;
                                        // IF the property is owned then you pay a fixed rate of 0.1 * the property value as rent
                                        if (current.owned_flag) {
                                            cout << current.name << " is owned by " << curr->owner -> name << endl;
                                            cout << "You must pay: " << (0.1 * curr->value) << "\n";
                                            iter->payPlayer(*curr->owner, (0.1 * curr->value));
                                        }
                                            // Otherwise ask if player wants to buy
                                        else {
                                            cout << "This property is unowned\n" << "Would you like to buy it?\n";
                                            cin >> purchase_decision;
                                            if (purchase_decision == "yes") {
                                                // IF player is broke they cannot buy the property and so they c
                                                if (iter -> wallet < curr->value) cout << "You're too broke\n";
                                                else {
                                                    curr->owned_flag = true;
                                                    iter -> addProperty(*curr);
                                                    iter -> chargeMoney(curr->value);
                                                    curr->owner = &*iter;
                                                }
                                            }
                                        }
                                        break;
                                    case 29:
                                        //set a current value to reference the property were on
                                        curr = (*((propertySquare *) Board[iter -> position])).property;

                                        //prints out important facts about property
                                        cout << "Property Square: ";
                                        cout << curr->name << endl;
                                        cout << "Color: " << curr->color << endl;
                                        cout << "Value: " << curr->value << endl;
                                        // IF the property is owned then you pay a fixed rate of 0.1 * the property value as rent
                                        if (current.owned_flag) {
                                            cout << current.name << " is owned by " << curr->owner -> name << endl;
                                            cout << "You must pay: " << (0.1 * curr->value) << "\n";
                                            iter->payPlayer(*curr->owner, (0.1 * curr->value));
                                        }
                                            // Otherwise ask if player wants to buy
                                        else {
                                            cout << "This property is unowned\n" << "Would you like to buy it?\n";
                                            cin >> purchase_decision;
                                            if (purchase_decision == "yes") {
                                                // IF player is broke they cannot buy the property and so they c
                                                if (iter -> wallet < curr->value) cout << "You're too broke\n";
                                                else {
                                                    curr->owned_flag = true;
                                                    iter -> addProperty(*curr);
                                                    iter -> chargeMoney(curr->value);
                                                    curr->owner = &*iter;
                                                }
                                            }
                                        }
                                        break;
                                    case 30:
                                        iter -> goToJail();
                                        break;
                                    case 31:
                                        //set a current value to reference the property were on
                                        curr = (*((propertySquare *) Board[iter -> position])).property;

                                        //prints out important facts about property
                                        cout << "Property Square: ";
                                        cout << curr->name << endl;
                                        cout << "Color: " << curr->color << endl;
                                        cout << "Value: " << curr->value << endl;
                                        // IF the property is owned then you pay a fixed rate of 0.1 * the property value as rent
                                        if (current.owned_flag) {
                                            cout << current.name << " is owned by " << curr->owner -> name << endl;
                                            cout << "You must pay: " << (0.1 * curr->value) << "\n";
                                            iter->payPlayer(*curr->owner, (0.1 * curr->value));
                                        }
                                            // Otherwise ask if player wants to buy
                                        else {
                                            cout << "This property is unowned\n" << "Would you like to buy it?\n";
                                            cin >> purchase_decision;
                                            if (purchase_decision == "yes") {
                                                // IF player is broke they cannot buy the property and so they c
                                                if (iter -> wallet < curr->value) cout << "You're too broke\n";
                                                else {
                                                    curr->owned_flag = true;
                                                    iter -> addProperty(*curr);
                                                    iter -> chargeMoney(curr->value);
                                                    curr->owner = &*iter;
                                                }
                                            }
                                        }
                                        break;
                                    case 32:
                                        //set a current value to reference the property were on
                                        curr = (*((propertySquare *) Board[iter -> position])).property;

                                        //prints out important facts about property
                                        cout << "Property Square: ";
                                        cout << curr->name << endl;
                                        cout << "Color: " << curr->color << endl;
                                        cout << "Value: " << curr->value << endl;
                                        // IF the property is owned then you pay a fixed rate of 0.1 * the property value as rent
                                        if (current.owned_flag) {
                                            cout << current.name << " is owned by " << curr->owner -> name << endl;
                                            cout << "You must pay: " << (0.1 * curr->value) << "\n";
                                            iter->payPlayer(*curr->owner, (0.1 * curr->value));
                                        }
                                            // Otherwise ask if player wants to buy
                                        else {
                                            cout << "This property is unowned\n" << "Would you like to buy it?\n";
                                            cin >> purchase_decision;
                                            if (purchase_decision == "yes") {
                                                // IF player is broke they cannot buy the property and so they c
                                                if (iter -> wallet < curr->value) cout << "You're too broke\n";
                                                else {
                                                    curr->owned_flag = true;
                                                    iter -> addProperty(*curr);
                                                    iter -> chargeMoney(curr->value);
                                                    curr->owner = &*iter;
                                                }
                                            }
                                        }
                                        break;
                                    case 33:
                                        cout << "Chance Square!\n";
                                        myDeck.executeChance(*iter, playerList);
                                        myDeck.popChance();
                                        break;
                                    case 34:
                                        //set a current value to reference the property were on
                                        curr = (*((propertySquare *) Board[iter -> position])).property;

                                        //prints out important facts about property
                                        cout << "Property Square: ";
                                        cout << curr->name << endl;
                                        cout << "Color: " << curr->color << endl;
                                        cout << "Value: " << curr->value << endl;
                                        // IF the property is owned then you pay a fixed rate of 0.1 * the property value as rent
                                        if (current.owned_flag) {
                                            cout << current.name << " is owned by " << curr->owner -> name << endl;
                                            cout << "You must pay: " << (0.1 * curr->value) << "\n";
                                            iter->payPlayer(*curr->owner, (0.1 * curr->value));
                                        }
                                            // Otherwise ask if player wants to buy
                                        else {
                                            cout << "This property is unowned\n" << "Would you like to buy it?\n";
                                            cin >> purchase_decision;
                                            if (purchase_decision == "yes") {
                                                // IF player is broke they cannot buy the property and so they c
                                                if (iter -> wallet < curr->value) cout << "You're too broke\n";
                                                else {
                                                    curr->owned_flag = true;
                                                    iter -> addProperty(*curr);
                                                    iter -> chargeMoney(curr->value);
                                                    curr->owner = &*iter;
                                                }
                                            }
                                        }
                                        break;
                                    case 35:
                                        //set a current value to reference the property were on
                                        curr = (*((propertySquare *) Board[iter -> position])).property;

                                        //prints out important facts about property
                                        cout << "Property Square: ";
                                        cout << curr->name << endl;
                                        cout << "Color: " << curr->color << endl;
                                        cout << "Value: " << curr->value << endl;
                                        // IF the property is owned then you pay a fixed rate of 0.1 * the property value as rent
                                        if (current.owned_flag) {
                                            cout << current.name << " is owned by " << curr->owner -> name << endl;
                                            cout << "You must pay: " << (0.1 * curr->value) << "\n";
                                            iter->payPlayer(*curr->owner, (0.1 * curr->value));
                                        }
                                            // Otherwise ask if player wants to buy
                                        else {
                                            cout << "This property is unowned\n" << "Would you like to buy it?\n";
                                            cin >> purchase_decision;
                                            if (purchase_decision == "yes") {
                                                // IF player is broke they cannot buy the property and so they c
                                                if (iter -> wallet < curr->value) cout << "You're too broke\n";
                                                else {
                                                    curr->owned_flag = true;
                                                    iter -> addProperty(*curr);
                                                    iter -> chargeMoney(curr->value);
                                                    curr->owner = &*iter;
                                                }
                                            }
                                        }
                                        break;
                                    case 36:
                                        cout << "Chance Square!\n";
                                        myDeck.executeChance(*iter, playerList);
                                        myDeck.popChance();
                                        break;
                                    case 37:
                                        //set a current value to reference the property were on
                                        curr = (*((propertySquare *) Board[iter -> position])).property;

                                        //prints out important facts about property
                                        cout << "Property Square: ";
                                        cout << curr->name << endl;
                                        cout << "Color: " << curr->color << endl;
                                        cout << "Value: " << curr->value << endl;
                                        // IF the property is owned then you pay a fixed rate of 0.1 * the property value as rent
                                        if (current.owned_flag) {
                                            cout << current.name << " is owned by " << curr->owner -> name << endl;
                                            cout << "You must pay: " << (0.1 * curr->value) << "\n";
                                            iter->payPlayer(*curr->owner, (0.1 * curr->value));
                                        }
                                            // Otherwise ask if player wants to buy
                                        else {
                                            cout << "This property is unowned\n" << "Would you like to buy it?\n";
                                            cin >> purchase_decision;
                                            if (purchase_decision == "yes") {
                                                // IF player is broke they cannot buy the property and so they c
                                                if (iter -> wallet < curr->value) cout << "You're too broke\n";
                                                else {
                                                    curr->owned_flag = true;
                                                    iter -> addProperty(*curr);
                                                    iter -> chargeMoney(curr->value);
                                                    curr->owner = &*iter;
                                                }
                                            }
                                        }
                                        break;
                                    case 38:
                                        cout << "Luxury Tax Square! (Fancy)\n";
                                        iter->chargeMoney((*((taxSquare *) Board[iter -> position])).taxRate);
                                        break;
                                    case 39:
                                        //set a current value to reference the property were on
                                        curr = (*((propertySquare *) Board[iter -> position])).property;

                                        //prints out important facts about property
                                        cout << "Property Square: ";
                                        cout << curr->name << endl;
                                        cout << "Color: " << curr->color << endl;
                                        cout << "Value: " << curr->value << endl;
                                        // IF the property is owned then you pay a fixed rate of 0.1 * the property value as rent
                                        if (current.owned_flag) {
                                            cout << current.name << " is owned by " << curr->owner -> name << endl;
                                            cout << "You must pay: " << (0.1 * curr->value) << "\n";
                                            iter->payPlayer(*curr->owner, (0.1 * curr->value));
                                        }
                                            // Otherwise ask if player wants to buy
                                        else {
                                            cout << "This property is unowned\n" << "Would you like to buy it?\n";
                                            cin >> purchase_decision;
                                            if (purchase_decision == "yes") {
                                                // IF player is broke they cannot buy the property and so they c
                                                if (iter -> wallet < curr->value) cout << "You're too broke\n";
                                                else {
                                                    curr->owned_flag = true;
                                                    iter -> addProperty(*curr);
                                                    iter -> chargeMoney(curr->value);
                                                    curr->owner = &*iter;
                                                }
                                            }
                                        }
                                        break;
                                }
                                cout << "Want to take another action?\n";
                                cin >> exit_decision;
                            }
                            else {
                                cout << "You can't roll twice. Don't be greedy.\n";
                            }
                        }
                    }
                }
                exit_decision = " ";
                roll_flag = false;
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