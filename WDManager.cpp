/*////////////////////////////////////////////////
	Author: Jacob Vanderkarr
	Date: 5/4/19
	File: WDManager.cpp
	Purpose: Implementation for WDManager class
*/////////////////////////////////////////////////
#include "WDManager.h"

//default ctor
/*
	the smallest resolution shall be 480p
*/
WDManager::WDManager() : m_x_size(MIN_X_RES), m_y_size(MIN_Y_RES), m_title(nullptr)
{
	m_title = new char[strlen("Freecell - The Unoriginal Card Game - JV") + 1];
	strcpy(m_title, "Freecell - The Unoriginal Card Game - JV");

	m_window.create(VideoMode(m_x_size, m_y_size), m_title, Style::Titlebar | Style::Close);
	m_window.setFramerateLimit(G_FRAMERATE); //framerate limit of 60, no need for 3000frames
	Update();
}

//2 arg ctor
WDManager::WDManager(int x, int y) : m_x_size(MIN_X_RES), m_y_size(MIN_Y_RES), m_title(nullptr)
{
	m_title = new char[strlen("Freecell - The Unoriginal Card Game - JV") + 1];
	strcpy(m_title, "Freecell - The Unoriginal Card Game - JV");

	//gives a loose basis that their quotient is within the 16:9 ratio (sorta)
	//check to make sure the resolution is not bigger than the desktop resolution

	if (VideoMode::getDesktopMode().width >= x && VideoMode::getDesktopMode().height >= y && y > 0)
	{
		if (static_cast<double>(x) / static_cast<double>(y) >= 1.6 
			&& static_cast<double>(x) / static_cast<double>(y) <= 1.8 
			&& x >= MIN_X_RES && y >= MIN_Y_RES)
		{
			if ((x % R_ASPECT_X) == 0 && (y % R_ASPECT_Y) == 0)
			{
				//any 16:9 ratio is supported
				m_x_size = x;
				m_y_size = y;

				std::cout << "resized the window .\n";

				//WARNING, SIZES LARGER THAN THE DESKTOP RESOLTION MAY NOT WORK,
				//WILL INCORPORATE THAT AT SOME POINT
			}

		}
	}

	m_window.create(VideoMode(m_x_size, m_y_size), m_title, Style::Titlebar | Style::Close);
	m_window.setFramerateLimit(G_FRAMERATE); //framerate limit of 60, no need for 3000frames
	Update();
}

//copy ctor
/*
	I REPEAT, THIS REALLY IS NOT NECESSARY, BECAUSE THERE IS / SHOULD
	BE ONLY ONE INSTANCE, IM DOING THIS SO THE BIG T IS HAPPY WITH ME
*/
WDManager::WDManager(const WDManager & cpy) : m_x_size(cpy.m_x_size), m_y_size(cpy.m_y_size), m_title(nullptr)
{
	m_title = new char[strlen(cpy.m_title) + 1];
	strcpy(m_title, cpy.m_title);

	//dont need as much as a mess here because the default handles a lot

	m_window.create(VideoMode(m_x_size, m_y_size), m_title, Style::Titlebar | Style::Close);
	m_window.setFramerateLimit(60); //framerate limit of 60, no need for 3000frames
	Update();
}

//dtor
WDManager::~WDManager()
{
	delete m_title;
	m_title = nullptr;
	m_x_size = 0;
	m_y_size = 0;

	m_window.close();
}

//asignment operator overload
WDManager & WDManager::operator=(const WDManager & rhs)
{
	if (this != &rhs)
	{
		if (rhs.m_title != nullptr)
		{
			delete m_title;
			m_title = new char[strlen(rhs.m_title) + 1];
			strcpy(m_title, rhs.m_title);
		}
		
		m_x_size = rhs.m_x_size;
		m_y_size = rhs.m_y_size;

		m_window.close();
		m_window.create(VideoMode(m_x_size, m_y_size), m_title, Style::Titlebar | Style::Close);
		m_window.setFramerateLimit(60); //framerate limit of 60, no need for 3000frames
		Update();
	}
	return *this;
}

/*//////////////////////////////////////////////////////////////
	Set Dimension
		alters the size of the window
		(do note that the window cannot be resized by the user)
		maybe I will have a menu option for sizes

		enforces the 16:9 ratio
*///////////////////////////////////////////////////////////////
void WDManager::SetDimension(int x, int y)
{
	bool resized = false;
	//gives a loose basis that their quotient is within the 16:9 ratio (sorta)
	//check to make sure the resolution is not bigger than the desktop resolution
	if (VideoMode::getDesktopMode().width >= x && VideoMode::getDesktopMode().height >= y && y > 0)
	{
		if (static_cast<double>(x) / static_cast<double>(y) >= 1.6
			&& static_cast<double>(x) / static_cast<double>(y) <= 1.8
			&& x >= MIN_X_RES && y >= MIN_Y_RES)
		{
			if ((x % R_ASPECT_X) == 0 && (y % R_ASPECT_Y) == 0)
			{
				//any 16:9 ratio is supported
				m_x_size = x;
				m_y_size = y;

				resized = true;

				//WARNING, SIZES LARGER THAN THE DESKTOP RESOLTION MAY NOT WORK,
				//WILL INCORPORATE THAT AT SOME POINT
			}

		}
	}

	if (resized && m_window.isOpen())
	{
		m_window.close(); //close the window first
	}
	
	if (resized)
	{
		m_window.create(VideoMode(m_x_size, m_y_size), m_title, Style::Titlebar | Style::Close);
		Update();
	}
}

/*///////////////////////////
	Set Title
		Sets the title of the
		window
*////////////////////////////
void WDManager::SetTitle(const char * title)
{
	if (title != nullptr)
	{
		delete m_title;
		m_title = new char[strlen(title) + 1];
		strcpy(m_title, title);
		m_window.setTitle(String(m_title));
	}
}

//getters

//get width
int WDManager::GetWidth() const
{
	return m_x_size;
}

//get height
int WDManager::GetHeight() const
{
	return m_y_size;
}

//get title
const char * WDManager::GetTitle() const
{
	return m_title;
}

//get window
RenderWindow & WDManager::GetWindow()
{
	return m_window;
}

/*////////////////////////////////////////////////////
	Draw Obj
	takes an Group Obj
	and draw that to the current buffer

	NOTE: when drawing to the buffer, keep in mind
	that other objects may be there,
	drawing to the buffer effectively is like a stack
	The oldest items are at the bottom

	Throws an exception if a texture is not found
*/////////////////////////////////////////////////////
void WDManager::DrawObj(const GroupObj & obj)
{
	Node<DrawableObj>* travel;
	travel = obj.m_group.GetHead();

	//a while loop to draw all objects in the group
	while (travel != nullptr)
	{
		//New Texture Obj
		Texture texture;
		if (!texture.loadFromFile(travel->GetData().GetSrc()))
		{
			//texture loading failed, throw an exception
			throw Exception("Exception: Failed to load image from file.");
		}

		//after loading the texture, we must apply it into a sprite, so we can manipulate
		//it
		Sprite spr;
		spr.setTexture(texture);

		/*
			after making the sprite with a texture, position it
			first arg is the x position, the second is the y pos.
			it is assumed that the position for the objects in the group
			are relative to the first member when constructing. 
			first it takes the group position (position of the obj)
			plus the individual postion of the elements
		*/
		spr.setScale(travel->GetData().GetScale(), travel->GetData().GetScale());

		spr.setPosition(static_cast<float>(obj.m_Xpos + travel->GetData().GetXpos()), 
						static_cast<float>(obj.m_Ypos + travel->GetData().GetYpos()));

		//after setting the position, update the window
		m_window.draw(spr);


		//continue traveling with travel node
		travel = travel->GetNext();
	}
}

/*////////////////////////////////////////////
	Update
		Update finalizes
		the window buffer and 
		actually displays it to the window

		It is highly recommended to do a WIPE
		between Displaying the previous screen
		and drawing objects in their updated
		positions
*//////////////////////////////////////////////
void WDManager::Update()
{
	m_window.display();
	Wipe();
}

/*////////////////////////////////////
	Wipe
		'resets' the 
		hidden buffer with the color
		meant for the background.
*//////////////////////////////////////
void WDManager::Wipe()
{
	//'clears' the screen with a nice to look at felt green color.
	m_window.clear(Color(51, 153, 102, 255));
}