#define _CRT_SECURE_NO_WARNINGS
#include "Food.h"
#include "Utils.h"
#include "Menu.h"
#include <fstream>
using namespace std;
namespace seneca {

	Food::Food()
	{
		m_ordered = false;
		m_child = false;
		m_customize = nullptr;

	}
	
	Food::Food(const Food& other) :Billable(other)
	{

		ut.alocpy(m_customize, other.m_customize);
		m_ordered = other.m_ordered;
		m_child = other.m_child;


	}
	Food& Food::operator=(const Food& other)
	{
		if (this != &other) {
			Billable::operator=(other);
			ut.alocpy(m_customize, other.m_customize);
			m_ordered = other.m_ordered;
			m_child = other.m_child;
		}
		return *this;
	}
	Food::~Food()
	{
		delete[] m_customize;
	}
	ostream& Food::print(ostream& ostr)
	{
		char buffer[26];
		const char* name = *this;
		ut.strcpy(buffer, name, 25);

		ostr.width(28);
		ostr.fill('.');
		ostr.setf(ios::left);
		ostr << buffer;
		ostr.unsetf(ios::left);


		if (ordered()) {
			if (m_child) {
				ostr << "Child";
			}
			else {
				ostr << "Adult";
			}
		}
		else {
			ostr << ".....";
		}

		ostr.width(7);
		ostr.fill(' ');
		ostr.precision(2);
		ostr.setf(ios::fixed);
		ostr.setf(ios::right);
		ostr << price();
		ostr.unsetf(ios::right);

		if (m_customize != nullptr && &ostr == &cout) {
			ostr << " >> ";

			char buffer[31] = {};
			ut.strcpy(buffer, m_customize);

			ostr << buffer;

		}

		return ostr;
	}
	bool Food::order()
	{
		Menu foodMenu("Food Size Selection", "Back", 3);
		foodMenu << "Adult" << "Child";

	
		int userInput = foodMenu.select(); 

		
		if (userInput == 0) {
			m_ordered = false;
			delete[] m_customize;
			m_customize = nullptr;
			return false;
		}

		m_ordered = true;
		
		if (userInput == 2) {  
			m_child = true;
		}
		else {
			m_child = false;  
		}
		
		char temp[100]{};
		cout << "Special instructions\n";
		cout << "> ";
	
		cin.getline(temp, 100);

		if (ut.strlen(temp) == 0) {
			delete[] m_customize;
			m_customize = nullptr;
		}
		else {
			ut.alocpy(m_customize, temp);
		}

		return true;

	}
	bool Food::ordered() const
	{
		return m_ordered;
	}
	ifstream& Food::read(ifstream& file)
	{
		char nameBuffer[100]{};
		double priceBuffer;

		file.getline(nameBuffer, 100, ',');
		file >> priceBuffer;
		file.ignore(1000, '\n');

		if (file) {
			name(nameBuffer);
			
			Billable::price(priceBuffer);
			m_child = false;
			m_ordered = false;
			delete[] m_customize;
			m_customize = nullptr;

		}
		return file;
	}

	double Food::price() const
	{
	
		if (ordered() && m_child) {
			return Billable::price() / 2;
		}
		else {
			return Billable::price();
		}

	}
}
