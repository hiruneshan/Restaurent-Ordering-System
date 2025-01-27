#include <fstream>
#include "Drink.h"
#include "Utils.h"
#include "Menu.h"

using namespace std;
namespace seneca {


	std::ostream& Drink::print(std::ostream& ostr)
	{

		char buffer[26] = {};
		const char* name = *this;
		if (name)
			ut.strcpy(buffer, name, 25);
		buffer[25] = '\0';

		ostr.width(28);
		ostr.fill('.');
		ostr.setf(ios::left);
		ostr << buffer;
		ostr.unsetf(ios::left);


		//printing the size
		if (ordered()) {
			if (m_size == 'S') {
				ostr << "SML..";
			}
			else if (m_size == 'M') {
				ostr << "MID..";
			}
			else if (m_size == 'L') {
				ostr << "LRG..";
			}
			else if (m_size == 'X') {
				ostr << "XLR..";
			}
		}
		else {
			ostr << ".....";
		}

		//printing price
		ostr.width(7);
		ostr.fill(' ');
		ostr.precision(2);
		ostr.setf(ios::fixed);
		ostr.setf(ios::right);
		ostr << price();
		ostr.unsetf(ios::right);

		return ostr;

	}

	bool Drink::order()
	{
		Menu drinkMenu("Drink Size Selection", "Back", 3);
		drinkMenu << "Small" << "Medium" << "Larg" << "Extra Large";


		int userInput = drinkMenu.select();

		switch (userInput) {
		case 1:
			m_size = 'S';
			return true;
		case 2:
			m_size = 'M';
			return true;
		case 3:
			m_size = 'L';
			return true;
		case 4:
			m_size = 'X';
			return true;
		case 0:
			m_size = '\0';
			return false;
		default:
			return false;
		}

	}

	bool Drink::ordered() const
	{

		return m_size != '\0';
	}

	std::ifstream& Drink::read(std::ifstream& file)
	{

		char tempName[100]{};
		double tempPrice;

		file.getline(tempName, 100, ',');
		file >> tempPrice;
		file.ignore();

		if (file) {
			name(tempName);

			Billable::price(tempPrice);
			m_size = '\0';
		}

		return file;

	}

	double Drink::price()const
	{
		double tempPrice = Billable::price();

		if (m_size == 'S') {
			tempPrice *= 0.5;
		}
		else if (m_size == 'M') {
			tempPrice *= 0.75;
		}
		else if (m_size == 'X') {
			tempPrice *= 1.5;
		}
		return tempPrice;


	}

}