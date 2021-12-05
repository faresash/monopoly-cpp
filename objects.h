#ifndef MONOPOLY_CPP_OBJECTS_H
#define MONOPOLY_CPP_OBJECTS_H

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

void runGame();

class Property {
private:
    int id; //Unique ID of the property
    int color; //What color it has
    int value; //Its value according to the bank
    std::string name; //Name of the property

public:
    Property() { //default constructor
        id = 0;
        color = 0;
        value = 0;
        name = "No name";
    }
    Property(int ID, int col, int val, std::string nam) { //parameterized constructor
        id = ID;
        color = col;
        value = val;
        name = nam;
    }
    Property operator = (const Property & other) { //= operator overload
        id = other.id;
        color = other.color;
        value = other.value;
        name = other.name;
        return *this;
    }
    std::string getName() {
        return name;
    }

    int getValue() {
        return value;
    }
};

class Chance {
private:
    std::string Name; // Name of chance card
    int index;
public:
    Chance() {
        Name = "No name";
        index = 0;
    }

    Chance(int Num) { //parameterized constructor
        switch (Num)
            index = Num;
    }
    Chance operator = (const Chance & other) { //= operator overload
        Name = other.Name;
        index = other.index;
        return *this;
    }
    std::string getName() {
        return Name;
    }

    int getIndex() {
        return index;
    }
};

class chanceDeck {
private:
    list <Chance> deck;
public:
    chanceDeck() {
        int indexArr[10] = {0,1,2,3,4,5,6,7,8,9};
        shuffle(indexArr, indexArr + 10, default_random_engine(seed));

        for (int i = 0; i < 10; i++) {
            Chance card (indexArr[i]);
            deck.push_back(card);
        }
    }
    void executeChance (Player play) {
        auto it = deck.begin();
        switch (it->getIndex()) {
            case 0: { //Get out of jail free
                play.jailStatus = true;
                break;
            }
            case 1: { //Go back 3 spaces
                play.move_back(3);
                break;
            }
            case 2: { //Go to jail, no $200
                play.goToJail();
                break;
            }
            case 3: { //Pay each player $50
                auto it = playerList.begin();
                break;
            }
            case 4: break;
            case 5: break;
            case 6: break;
            case 7: break;
            case 8: break;
            case 9: break;
        }
    }
};

class Square {
protected:
    int index;
    std::string name;
};

class propertySquare : public Square {
private:
    Property property; //each Property Square contains a pointer to a property
public:
    propertySquare(int myIndex, std::string myName, int ID, int col, int val, std::string nam) {
        Property newProp(ID, col, val, nam); //allocating memory for the new property
        index = myIndex; //setting square index to argument
        name = myName; //setting square name to argument
        property = newProp; //setting property to newly allocated one
    }
};

class chanceSquare : public Square {
private:
    Chance chance;
public:
    chanceSquare(int myNumDeck, std::string myName, int myIndex) {
        Chance newChance(myNumDeck, myName, myIndex);
        index = myIndex;
        name = myName;
        chance = newChance;
    }
};

class Go {
private:
    int money; // Cash from Go
    std::string Name; // Name of chance card
    int index;
public:

    Go() {
        money = 0;
        Name = "No name";
        index = 0;
    }

    Go(int Money, std::string Nam, int ind) { //parameterized constructor
        Money = money;
        Name = Nam;
        index = ind;
    }
    Go operator = (const Go & other) { //= operator overload
        money = other.money;
        Name = other.Name;
        index = other.index;
        return *this;
    }
    std::string getName() {
        return Name;
    }
};

class goSquare : public Square {
private:
    Go go;
public:
    goSquare(int myMoney, std::string myName, int myIndex) {
        Go newGo(myMoney, myName, myIndex);
        index = myIndex;
        name = myName;
        go = newGo;
    }
};

class Jail {
private:
    int diceRoll; // last recorded dice roll from jail
    int turns; // turns in jail
    std::string Name; // Name of chance card
    int index; // Index of card
public:
    Jail() {
        diceRoll = 0;
        turns = 0;
        Name = "No name";
        index = 0;
    }

    Jail(int Tur, int Rol, std::string Nam, int ind) { //parameterized constructor
        diceRoll = Rol;
        turns = Tur;
        Name = Nam;
        index = ind;
    }
    Jail operator = (const Jail & other) { //= operator overload
        diceRoll = other.diceRoll;
        turns = other.turns;
        Name = other.Name;
        index = other.index;
        return *this;
    }
    std::string getName() {
        return Name;
    }
};

class jailSquare : public Square {
private:
    Jail jail;
public:
    jailSquare(int mydiceRoll, int myturns, std::string myName, int myIndex) {
        Jail newJail(mydiceRoll, myturns, myName, myIndex);
        index = myIndex;
        name = myName;
        jail = newJail;
    }
};

class GoToJail {
private:
    int player; // player id to land on spot
    std::string Name; // Name of chance card
    int index; // Index of card
public:
    GoToJail() {
        player = 0;
        Name = "No name";
        index = 0;
    }

    GoToJail(int pla, std::string Nam, int ind) { //parameterized constructor
        player = pla;
        Name = Nam;
        index = ind;
    }
    GoToJail operator = (const GoToJail & other) { //= operator overload
        player = other.player;
        Name = other.Name;
        index = other.index;
        return *this;
    }
    std::string getName() {
        return Name;
    }
};

class goToJailSquare : public Square {
private:
    GoToJail go_to_jail;
public:
    goToJailSquare(int player, std::string myName, int myIndex) {
        GoToJail newGoToJail(player, myName, myIndex);
        index = myIndex;
        name = myName;
        go_to_jail = newGoToJail;
    }
};

class freeParking {
private:
    std::string Name; // Name of chance card
    int index; // Index of card
public:
    freeParking() {
        Name = "No name";
        index = 0;
    }

    freeParking(std::string Nam, int ind) { //parameterized constructor
        Name = Nam;
        index = ind;
    }
    freeParking operator = (const freeParking & other) { //= operator overload
        Name = other.Name;
        index = other.index;
        return *this;
    }
    std::string getName() {
        return Name;
    }
};

class freeParkingSquare : public Square {
private:
    freeParking free_parking;
public:
    freeParkingSquare(std::string myName, int myIndex) {
        freeParking new_freeParking(myName, myIndex);
        index = myIndex;
        name = myName;
        free_parking = new_freeParking;
    }
};

class tax {
private:
    int taxRate; // Amount paid for tax
    std::string Name; // Name of chance card
    int index; // Index of card
public:
    tax() {
        taxRate = 0;
        Name = "No name";
        index = 0;
    }

    tax(int rate, std::string Nam, int ind) { //parameterized constructor
        taxRate = rate;
        Name = Nam;
        index = ind;
    }
    tax operator = (const tax & other) { //= operator overload
        taxRate = other.taxRate;
        Name = other.Name;
        index = other.index;
        return *this;
    }
    std::string getName() {
        return Name;
    }
};

class taxSquare : public Square {
private:
    tax Tax;
public:
    taxSquare(int mytaxRate, std::string myName, int myIndex) {
        tax new_tax(mytaxRate, myName, myIndex);
        index = myIndex;
        name = myName;
        Tax = new_tax;
    }
};

class Player {
private:
    string name; // Name of player
    int playerNumber; // Player identification number
    int position; // Position of player on the board
    double wallet; // Amount of money player has
    double debt; // Debt the player has incurred
    list<Property> ownedProperties; // List of properties that the player own
public:
    Player(string nam, int num, int pos = 0, double money = 1500, double det = 0) {
        name = nam;
        playerNumber = num;
        position = pos;
        wallet = money;
        debt = det;
    }
    bool jailStatus; // Whether player is in jail
    bool outJailCard; // Whether the player has the "Get out of jail free" card
    bool bankruptcyStatus; // Whether player is bankrupt

    void Check_Status(void) {
        cout << "Player Name: " << name << "\n";
        cout << "Player ID: " << playerNumber << "\n";
        cout << "Player Position: " << position << "\n";
        cout << "Wallet Amount: " << wallet << "\n";
        cout << "Debt Incurred: " << debt << "\n";
        cout << "Properties Held: ";
        list <Property> :: iterator it;
        for(it = ownedProperties.begin(); it != ownedProperties.end(); ++it)
            cout << '\t' << it->getName();
        cout << '\n';
    }


    void Is_Bankrupt(void) {
        cout << "Player Name: " << name << "\n";
        cout << "Player ID: " << playerNumber << "\n";
        cout << "Player Position: " << position << "\n";
        cout << "Wallet Amount: " << wallet << "\n";
        cout << "Debt Incurred: " << debt << "\n";
        cout << "Properties Held: ";
        list <Property> :: iterator it;
        for(it = ownedProperties.begin(); it != ownedProperties.end(); ++it)
            cout << '\t' << it->getName();
    }


    void move_back(int n) { //this function will move a player back with loopback
        if (pos - n >= 0) pos -= n;
        else pos = (pos - n) % 40;
    }

    void move_forward(int n) { //this function will move a player forward with loopback
        if (pos + n < 40) pos += n;
        else pos = (pos + n) % 40;
    }

    void addProperty(Property house) {
        ownedProperties.push_back(house);
    }

    void chargeMoney(int charge) {
        wallet -= charge;
    }

    void addMoney(int add) {
        wallet += add;
    }

    void goToJail(void) {
        jailStatus = true;
        //position = the index of jail;
    }
};


#endif //MONOPOLY_CPP_OBJECTS_H