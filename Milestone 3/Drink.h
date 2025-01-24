#ifndef SENECA_DRINK_H
#define SENECA_DRINK_H
#include "Billable.h"
namespace seneca {
	class Drink : public Billable {
		char m_size = '\0';

	public:
		std::ostream& print(std::ostream& ostr = std::cout);
		bool order();
		bool ordered() const;
		std::ifstream& read(std::ifstream& file);
		double price()const;
	

	};
}
#endif // !SENECA_DRINK_H