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

    Property(int ID, int col, int val) {id = ID; color = col; value = val;}
};

class Square {
protected:
    int index;
    std::string name;
};

class propertySquare : public Square {

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

