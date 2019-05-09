#include "Freecell.h"
#include <iostream>

using std::cin;
using std::cout;

int main()
{
	int selection;
	//ask the user for the size
	cout << "Please Select a size (number):\n";
	cout << "(1). Small (smallest resolution supported).\n";
	cout << "(2). Medium (1600 x 900).\n";
	cout << "(3). Large (1920 x 1080).\n";

	do
	{
		cin >> selection;

		if (selection < 1 || selection > 3)
		{
			cout << "Invalid Selection. Try again.\n";
		}

	} while (selection < 1 || selection > 3);

	Freecell game;
	game.ChooseSize(static_cast<Freecell::WindowSize>(selection - 1));

	//previous testing code
	//char source[5][50] = {"./Resources/CardBlank.png", "./Resources/Ace.png", "./Resources/Heart.png"};

	//int x = 1600;
	//int y = 900;

	//WDManager working(x, y);

	////working.SetDimension(1920, 1080);

	////working.SetDimension(MIN_X_RES, MIN_Y_RES);

	//Deck myDeck;
	//GroupObj myGroup;

	//float scale = static_cast<float>(x) / static_cast<float>(MIN_X_RES);

	//myDeck.SetScale(scale);
	//myDeck.Reset();
	////myDeck.Randomise();

	//try
	//{
	//	int i = 20 * scale;
	//	int j = 20 * scale;
	//	while (myDeck.GetSize() > 0)
	//	{
	//		myGroup = myDeck.Draw().GetCard(true);
	//		myGroup.SetPos(i, j);
	//		working.DrawObj(myGroup);
	//		i += 50 * scale;
	//		if (i >= 650 * scale)
	//		{
	//			i = 20 * scale;
	//			j += 50 * scale;
	//		}
	//	}
	//}
	//catch (Exception except)
	//{
	//	std::cout << except.GetMessage() << std::endl;
	//}

	//working.SetTitle("Bill & Ted's fabulous Freecell Adventure - Test");

	//working.Update();

	//cin.ignore();

	//working.SetTitle("Something differnt after we are gone");

	//cin.ignore();

	return 0;
}