#include <iostream>
#include <string>
#include <list>
#include <algorithm>
#include <array>
#include <random>
#include "macros.h"
#include "functions.h"
#include "globals.h"

class Property {
private:
    int id;
    int color;
    int value;

public:
    Property() {
        id = 0;
        color = 0;
        value = 0;
    }
    Property(int ID, int col, int val) {
        id = ID;
        color = col;
        value = val;
    }
    Property operator = (const Property & other) {
        id = other.id;
        color = other.color;
        value = other.value;
        return *this;
    }
};

class Square {
protected:
    int index;
    std::string name;
};

class propertySquare : public Square {
private:
    Property * property; //each Property Square contains a pointer to a property
public:
    propertySquare(int myIndex, std::string myName, int ID, int col, int val) {
        Property * newProp = new Property(ID, col, val); //allocating memory for the new property
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

