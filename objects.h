#ifndef MONOPOLY_CPP_OBJECTS_H
#define MONOPOLY_CPP_OBJECTS_H

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
};

class Chance {
private:
    int numDeck; // Number within Deck
    std::string Name; // Name of chance card
    int index;
public:

    Chance() {
        numDeck = 0;
        Name = "No name";
        index = 0;
    }

    Chance(int Num, std::string Nam, int ind) { //parameterized constructor
        numDeck = Num;
        Name = Nam;
        index = ind;
    }
    Chance operator = (const Chance & other) { //= operator overload
        numDeck = other.numDeck;
        Name = other.Name;
        index = other.index;
        return *this;
    }
    std::string getName() {
        return Name;
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

class goToJailSquare : public Square {

};

class freeParkingSquare : public Square {

};

class taxSquare : public Square {

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
        if ((wallet <= -1) || (debt > wallet)) {
            bankruptcyStatus = true;
        }
    }

    void addProperty(Property house) {
        ownedProperties.push_back(house);
    }

};









#endif //MONOPOLY_CPP_OBJECTS_H
