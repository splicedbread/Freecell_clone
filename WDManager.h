#ifndef WDMANAGER_H
#define WDMANAGER_H
/*////////////////////////////////////////////////////
	Author: Jacob Vanderkarr
	Date: 5/4/19
	File: WDManager.h
	Purpose: Definition of window manager class

	Description:
		Because of my wacky antics, I have 
		decided to split the openGL interpretation
		into a seperate class whose entire
		job is to take in data and display
		that to the screen. As well
		as managing the window properties.
*/////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>
#include "GroupObj.h"
#include "Array.h"

using namespace sf;

#define WD_ALLOC_SIZE 5

class WDManager
{
public:
	WDManager();
	WDManager(int x_size, int y_size);
	WDManager(const WDManager & cpy);
	~WDManager();

	WDManager & operator=(const WDManager & rhs);

	void SetWidth(int x);
	void SetHeight(int y);
	void SetTitle(char * title);
	void SetWindow(const RenderWindow & win);

	int GetWidth() const;
	int GetHeight() const;
	const char * GetTitle() const;
	const RenderWindow & GetWindow() const;



private:
	int m_x_size;
	int m_y_size;

	char * m_title;

	RenderWindow m_window;

	int m_c_objs;

	Array<GroupObj> m_objs;
};
#endif // !WDMANAGER_H