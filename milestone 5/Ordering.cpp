#define _CRT_SECURE_NO_WARNINGS
#include "Drink.h"
#include "Food.h"
#include "Billable.h"
#include "Ordering.h"
#include "constants.h"
#include "Menu.h"
#include "Utils.h"
#include <cstdio>
#include <fstream>
using namespace std;
namespace seneca {


	ostream& Ordering::prnBillTittle(std::ostream& ostr) const
	{
		//printing the header for the bill 
		ostr << "Bill" << " # ";
		ostr.width(3);
		ostr.fill('0');
		ostr << m_billNumber << " =============================" << "\n";
		ostr.fill(' '); // reset the fill character
		return ostr;
	}

	std::ostream& Ordering::prnBillTotal(std::ostream& ostr, double total) const
	{
		//print bill total (footer)
		double finalTax = total * 0.13;

		ostr.width(21);
		ostr << " ";
		ostr.setf(ios::left);
		ostr << "Total:";
		ostr.unsetf(ios::left);
		ostr.precision(2);
		ostr.width(13);
		ostr.setf(ios::right);
		ostr << total << "\n";
		ostr.unsetf(ios::right);

		ostr.width(21);
		ostr << " ";
		ostr.precision(2);
		ostr.setf(ios::left);
		ostr << "Tax:";
		ostr.unsetf(ios::left);
		ostr.width(15);
		ostr.precision(2);
		ostr.setf(ios::right);
		ostr << finalTax << "\n";
		ostr.unsetf(ios::right);

		ostr.width(21);
		ostr << " ";
		ostr.setf(ios::left);
		ostr << "Total+Tax:";
		ostr.unsetf(ios::left);
		ostr.width(9);
		ostr.precision(2);
		ostr.setf(ios::right);
		ostr << (finalTax + total) << "\n";



		ostr << "========================================\n";


		return ostr;
	}

	size_t Ordering::countRecords(const char* file) const
	{
		size_t newLineCounter = 0;

		//opening file in read mode.
		ifstream f(file);
		char ch;

		while (f.get(ch)) {

			if (ch == '\n') {
				newLineCounter++;
			}

		}

		f.close();
		return newLineCounter;
	}

	Ordering::Ordering(const char* drinkFile, const char* foodFile)
	{
		m_drinkArray = nullptr;
		m_foodArray = nullptr;
		m_billableCounter = 0;
		m_billNumber = 1;

		// Initialize m_billItems array to nullptr
		for (int i = 0; i < m_billableCounter; i++) {
			m_billItems[i] = nullptr;
		}


		size_t drinkFileCount = countRecords(drinkFile);
		size_t foodFileCount = countRecords(foodFile);

		ifstream drinkF(drinkFile);
		ifstream foodF(foodFile);



		if (drinkF && foodF) {

			m_foodArray = new Food[foodFileCount]{};
			m_drinkArray = new Drink[drinkFileCount]{};
			//drink array
			size_t readCountD = 0u;
			while (readCountD < drinkFileCount && drinkF) {
				m_drinkArray[readCountD].read(drinkF);
				readCountD++;
			}

			//FoodArray
			size_t readCountF = 0u;
			while (readCountF < foodFileCount && foodF) {
				m_foodArray[readCountF].read(foodF);
				readCountF++;
			}

			if (readCountD != drinkFileCount || readCountF != foodFileCount) {

				delete[] m_drinkArray;
				m_drinkArray = nullptr;

				delete[] m_foodArray;
				m_foodArray = nullptr;
			}
			else {
				m_drinkCounter = readCountD;
				m_foodCounter = readCountF;
			}
		}
		drinkF.close();
		foodF.close();


	}

	Ordering::~Ordering()
	{
		delete[] m_foodArray;
		delete[] m_drinkArray;

		for (size_t i = 0; i < m_billableCounter; i++) {
			delete m_billItems[i];
		}
	}

	Ordering::operator bool() const
	{
		return (m_foodArray != nullptr) && (m_drinkArray != nullptr);
	}

	unsigned int Ordering::noOfBillItems()const
	{
		return m_billableCounter;
	}

	bool Ordering::hasUnsavedBill() const
	{
		return m_billableCounter > 0;
	}

	//printint the list of food
	void Ordering::listFoods()
	{
		//header
		cout << "List Of Avaiable Meals" << endl;
		cout << "========================================\n";

		//printing the list of food
		for (size_t i = 0; i < m_foodCounter; i++) {
			m_foodArray[i].print() << "\n";
		}

		//footer
		cout << "========================================\n";

	}


	//printing the list of driks 
	void Ordering::ListDrinks()
	{
		cout << "List Of Avaiable Drinks" << endl;
		cout << "========================================\n";

		for (size_t i = 0; i < m_drinkCounter; i++) {
			m_drinkArray[i].print() << "\n";
		}
		//footer
		cout << "========================================\n";

	}

	void Ordering::orderFood()
	{
		Menu foodMenu("Food Menu", "Back to Order", 2);
		for (size_t i = 0; i < m_foodCounter; i++) {
			foodMenu << m_foodArray[i];
		}

		size_t userInput = foodMenu.select();

		if (userInput != 0) {
			Food* selectedFood = new Food(m_foodArray[userInput - 1]);
			m_billItems[m_billableCounter] = selectedFood;


			if (selectedFood->order()) {
				m_billableCounter++;
			}
			else {
				delete selectedFood;
			}
		}
	}

	void Ordering::orderDrink()
	{
		Menu drinkMenu("Drink Menu", "Back to Order", 2);
		for (size_t i = 0; i < m_drinkCounter; i++) {
			drinkMenu << m_drinkArray[i];
		}

		int userInput = drinkMenu.select();

		if (userInput != 0) {
			Drink* selectedDrink = new Drink(m_drinkArray[userInput - 1]);
			m_billItems[m_billableCounter] = selectedDrink;

			if (selectedDrink->order()) {
				m_billableCounter++;
			}
			else {
				delete selectedDrink;
			}
		}
	}

	void Ordering::printBill(ostream& ostr)
	{
		double totalP = 0.0;
		prnBillTittle(ostr);

		for (size_t i = 0; i < m_billableCounter; i++) {
			m_billItems[i]->print(ostr) << endl;
			totalP += m_billItems[i]->price();
		}

		prnBillTotal(ostr, totalP);
	}

	void Ordering::resetBill()
	{
		char* fileName = new char[21];
		ut.makeBillFileName(fileName, m_billNumber);

		ofstream file(fileName);

		printBill(file);


		cout << "Saved bill number " << m_billNumber << endl;;
		cout << "Starting bill number " << m_billNumber + 1 << endl;;


		for (size_t i = 0; i < m_billableCounter; i++) {
			delete m_billItems[i];
		}

		m_billNumber++;
		m_billableCounter = 0;
		delete[] fileName;
	}


}