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

};

class goSquare : public Square {

};

class jailSquare : public Square {

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

    void Check_Status(string Name, int playerNumber, int position, double wallet, double debt, list<Property> ownedProperties) {
        cout << Name << "\n";
        cout << playerNumber << "\n";
        cout << position << "\n";
        cout << wallet << "\n";
        cout << debt << "\n";
        list <Property> :: iterator it;
        for(it = ownedProperties.begin(); it != ownedProperties.end(); ++it)
            cout << ', ' << it->getName();
        cout << '\n';
    }

    void addProperty(Property house) {
        ownedProperties.push_back(house);
    }

};









#endif //MONOPOLY_CPP_OBJECTS_H
