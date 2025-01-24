#include "Billable.h"
#include "Utils.h"

namespace seneca {
	void Billable::price(double value)
	{
		m_price = value;
	}
	void Billable::name(const char* name)
	{
		ut.alocpy(m_name, name);
	}
	Billable::Billable(const Billable& other)
	{
		m_name = new char[strlen(other.m_name) + 1];
		ut.strcpy(m_name, other.m_name);
		m_price = other.m_price;
	}
	Billable& Billable::operator=(const Billable& other)
	{
		if (this != &other) {
			ut.alocpy(m_name, other.m_name);

			m_price = other.m_price;
		}
		return *this;
	}
	Billable::~Billable()
	{
		delete[] m_name;
	}
	double Billable::price() const
	{
		return m_price;
	}
	Billable::operator const char* () const
	{
		return m_name;
	}
	double operator+(double money, const Billable& B)
	{
		return money + B.price();
	}
	double& operator+=(double& money, const Billable& B)
	{
		money += B.price();
		return money;
	}
}