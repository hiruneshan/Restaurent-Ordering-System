#ifndef SENECA_BILLABLE_H
#define SENECA_BILLABLE_H
#include <iostream>
namespace seneca {
	class Billable {
		char* m_name = nullptr;
		double m_price;

	protected:
		void price(double value); // setting the items price
		void name(const char* name); // setting the items name

	public:
		Billable() :m_name{ nullptr }, m_price{ 0.0 } {}
		Billable(const Billable& other); // copy constructor 
		Billable& operator=(const Billable& other);
		virtual ~Billable();
		virtual double price() const;
		virtual std::ostream& print(std::ostream& ostr = std::cout) = 0;
		virtual bool order() = 0;
		virtual bool ordered() const = 0;
		virtual std::ifstream& read(std::ifstream& file) = 0;
		operator const char* ()const;

	};
	double operator+(double money, const Billable& B);
	double& operator+=(double& money, const Billable& B);

}
#endif