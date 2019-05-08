#include "WDManager.h"
#include "deck.h"
#include <iostream>

using std::cin;

int main()
{

	char source[5][50] = {"./Resources/CardBlank.png", "./Resources/Ace.png", "./Resources/Heart.png"};

	int x = 1600;
	int y = 900;

	WDManager working(x, y);

	//working.SetDimension(1920, 1080);

	//working.SetDimension(MIN_X_RES, MIN_Y_RES);

	Deck myDeck;
	GroupObj myGroup;

	float scale = static_cast<float>(x) / static_cast<float>(MIN_X_RES);

	myDeck.SetScale(scale);
	myDeck.Reset();
	//myDeck.Randomise();

	try
	{
		int i = 20 * scale;
		int j = 20 * scale;
		while (myDeck.GetSize() > 0)
		{
			myGroup = myDeck.Draw().GetCard();
			myGroup.SetPos(i, j);
			working.DrawObj(myGroup);
			i += 50 * scale;
			if (i >= 650 * scale)
			{
				i = 20 * scale;
				j += 50 * scale;
			}
		}
	}
	catch (Exception except)
	{
		std::cout << except.GetMessage() << std::endl;
	}

	working.SetTitle("Bill & Ted's fabulous Freecell Adventure - Test");

	working.Update();

	cin.ignore();

	working.SetTitle("Something differnt after we are gone");

	cin.ignore();

	return 0;
}