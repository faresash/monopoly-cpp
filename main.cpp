#include <iostream>
#include <string>
#include <list>
#include "macros.h"
#include "functions.h"
#include "globals.h"

using namespace std;

int main() {
    //----------------------------------------------------------------------------------------------//
    //------------------------------------Basic Starting Menu---------------------------------------//
	string input;
	int playerCount = 0;
	cout << "                  MONOPOlY\n" 
	     << "2-8 players.\n" 
		 << "Once all names are entered, type 'start' to begin.\n" 
		 << "Enter names below:\n";
		 
	while (1) {
		while (input != "start") {
			cin >> input;
			if (playerCount > 8) cout << "Too many players! Please begin game.\n";
			else if (input != "start") {
				playerCount++; 
				//insert new node into player list
			}
		}
		input.clear();
		if (playerCount < 2) cout << "Too few players! Add more players before starting:\n";
		else break;
	}
	
	cout << "Enjoy!\n";
    //--------------------------------------------------------------------------------------------//
    //--------------------------------------------------------------------------------------------//

    //--------------------------------------------------------------------------------------------//
    //----------------------------------Game Function Call----------------------------------------//


	                  //call function to begin game in while-loop.cpp


    //--------------------------------------------------------------------------------------------//
    //--------------------------------------------------------------------------------------------//
		
	return 0;
}
