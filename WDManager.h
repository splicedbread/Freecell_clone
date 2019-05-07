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

#define MIN_X_RES 848
#define MIN_Y_RES 480

#define R_ASPECT_X 16
#define R_ASPECT_Y 9

using namespace sf;

class WDManager
{
public:
	WDManager();
	WDManager(int x_size, int y_size);
	WDManager(const WDManager & cpy);
	~WDManager();

	WDManager & operator=(const WDManager & rhs);

	void SetDimension(int x, int y);
	void SetTitle(const char * title);

	int GetWidth() const;
	int GetHeight() const;
	const char * GetTitle() const;
	RenderWindow & GetWindow();

	//most importantly
	void DrawObj(const GroupObj & obj);

	//secondly
	void Update();
	void Wipe();

private:
	int m_x_size;
	int m_y_size;

	char * m_title;

	RenderWindow m_window;
};
#endif // !WDMANAGER_H