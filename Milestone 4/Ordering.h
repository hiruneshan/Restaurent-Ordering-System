#ifndef SENECA_ORDERING_H
#define SENECA_ORDERING_H
#include "Food.h"
#include "Drink.h"
#include "Billable.h"
#include "Constants.h"
#include <iostream>

namespace seneca {
	class Ordering {
		unsigned int m_foodCounter = 0; // keep track of food in the file 
		unsigned int m_drinkCounter = 0; //track of drinks
		unsigned int m_billableCounter = 0; //tracks the order.

		unsigned int m_billNumber = 1; 

		Food* m_foodArray = nullptr;
		Drink* m_drinkArray = nullptr;
		Billable* m_billItems[MaximumNumberOfBillItems]{}; //food or drink (array of pointers)

		//pvt methods 
		std::ostream& prnBillTittle(std::ostream& ostr = std::cout)const;
		std::ostream& prnBillTotal(std::ostream& ostr, double total)const;
		size_t countRecords(const char* file)const;

	public:
		Ordering(const char* drinkFile, const char* foodFile);
		virtual ~Ordering();
		operator bool()const;
		unsigned int noOfBillItems()const; //double check this 
		bool hasUnsavedBill()const;
		void listFoods();
		void ListDrinks();
		void orderFood();
		void orderDrink();
		void printBill(std::ostream& ostr);
		void resetBill();
	};


}

#endif // !SENECA_ORDERING_H