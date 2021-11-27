#ifndef MONOPOLY_CPP_OBJECTS_H
#define MONOPOLY_CPP_OBJECTS_H

class Property {
private:
    int id;
    int color;
    int value;
    std::string name;

public:
    Property() {
        id = 0;
        color = 0;
        value = 0;
        name = "No name";
    }
    Property(int ID, int col, int val, std::string nam) {
        id = ID;
        color = col;
        value = val;
        name = nam;
    }
    Property operator = (const Property & other) {
        id = other.id;
        color = other.color;
        value = other.value;
        name = other.name;
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









#endif //MONOPOLY_CPP_OBJECTS_H
