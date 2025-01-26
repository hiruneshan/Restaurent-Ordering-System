#ifndef SENECA_FOOD_H
#define SENECA_FOOD_H
#include "Billable.h"
namespace seneca {
	class Food : public Billable {

		bool m_ordered;
		bool m_child;
		char* m_customize{};

	public:
		Food();
		Food(const Food& other);
		Food& operator=(const Food& other);
		virtual ~Food();
		std::ostream& print(std::ostream& ostr = std::cout);
		bool order();
		bool ordered() const;
		std::ifstream& read(std::ifstream& file);
		double price() const;
	};
}
#endif // !SENECA_FOOD_H