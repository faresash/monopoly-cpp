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

void runGame() {
    Player play1("fares", 1);
    Property house(1, 2, 5000, "Blue House");
    Property villa(2, 2, 60000, "Big House");
    play1.addProperty(house);
    play1.addProperty(villa);
}
