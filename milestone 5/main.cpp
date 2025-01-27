/***********************************************************************
// OOP244 Project, milestone 5, main.cpp
//
// File	main.cpp
// Version 1.0
// Date: 2024 - 11 - 29
// Author: Hiru Neshan Wijemanne
// Description
//
// Revision History
// -----------------------------------------------------------
// Name                     Date              Reason
// Hiru Neshan Wijemanne    2024 - 12 - 01    Updating the end program. 
/////////////////////////////////////////////////////////////////
***********************************************************************/

#include <iostream>
#include "Menu.h"
#include "Ordering.h"
using namespace std;
using namespace seneca;

int main() {
	
	const char* foodFile = "foods.csv";
	const char* drinkFile = "drinks.csv";

	Ordering ord(drinkFile, foodFile);

	if (!ord) {
		cout << "Failed to open data files or the data files are corrupted!";
		return 1; // turminating the program if the file fails to open.
	}

	Menu mainMenu("Seneca Restaurant ", "End Program");
	mainMenu << "Order" << "Print Bill" << "Start a New Bill" << "List Foods" << "List Drinks";

	Menu subMenu("Order Menu", "Back to main menu", 1);
	subMenu << "Food" << "Drink";

	Menu confirmationMenu("You have bills that are not saved. Are you sure you want to exit?", "No");
	confirmationMenu << "Yes";

    size_t selection;

    while (true) {
        selection = mainMenu.select();

        switch (selection) {
        case 1: {
          
            while (true) {  // Loop until the user returns to the main menu
                size_t subSelection = subMenu.select();

                if (subSelection == 0) {
                    break;  // Return to the main menu
                }

                switch (subSelection) {
                case 1:
                    ord.orderFood();
                    break;
                case 2:
                    ord.orderDrink();
                    break;
                }
            }
            break;
        }
        case 2:
            ord.printBill(cout);
            break;
        case 3:
            ord.resetBill();
            break;
        case 4:
            ord.listFoods();
            break;
        case 5:
            ord.ListDrinks();
            break;

        case 0:
            if (ord.hasUnsavedBill()) {
                if (confirmationMenu.select() == 1) {
                    return 0; 
                }
            }
            else {
                return 0;
            }
            break;
        }
    }

    return 0;

}