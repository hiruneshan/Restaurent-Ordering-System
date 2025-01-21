#ifndef SENECA_MENU_H
#define SENECA_MENU_H
#include <iostream>
#include "constants.h"

namespace seneca{
	class MenuItem {
		char* m_menuContent = nullptr;
		size_t m_numOfIndentations;
		size_t m_sizeOfIndentation;
		int m_menuItemNum;


	public:
		MenuItem(const char* content, int indentation, int sizeIdentation, int rowNum);
		MenuItem(const MenuItem& other) = delete;
		MenuItem& operator=(const MenuItem& other) = delete;
		virtual ~MenuItem();
		operator bool()const;
		std::ostream& display(std::ostream& ostr = std::cout)const;

	};

}
#endif // !SENECA_MENU_H