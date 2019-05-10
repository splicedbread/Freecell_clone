#define _CRTDBG_MAP_ALLOC
#include "Freecell.h"
#include <iostream>
#include <Windows.h>
#include <crtdbg.h>

using std::cin;
using std::cout;
using std::endl;

/*//////////////////////////////////////////
	Project Name: Freecell
	Author: Jacob Vanderkarr
	Date (finished) 5/10 (I know its late)

	Purpose:
		A game that you play freecell and such

	Notes: Click the center symbol to 
		restart a game

	Notes ps: 
		I know I turned this in late, its no 
		big deal because I had learned a few things
		about graphical processes and events

		I see this as a total win.

*////////////////////////////////////////////
void gameStub();

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	cout << "launching openGL application...." << endl;
	//Remove the console window
	gameStub();
	return 0;
}

void gameStub()
{
	char selection[20];
	int val = 0;
	//ask the user for the size
	cout << "Please Select a size (number):\n";
	cout << "(1). Small (smallest resolution supported).\n";
	cout << "(2). Medium (1600 x 900).\n";
	cout << "(3). Large (1920 x 1080).\n";

	do
	{
		cin >> selection;

		val = atoi(selection);

		if (val < 1 || val > 3)
		{
			cout << "Invalid Selection. Try again.\n";
		}
	
	} while (val < 1 || val > 3);

	FreeConsole(); //Comment out when needing the console for debugging

	Freecell game;
	game.ChooseSize(static_cast<Freecell::WindowSize>(val - 1));

}