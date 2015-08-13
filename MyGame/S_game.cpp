#include<iostream>
#include<string>
#include<vector>
#include "ship.h"
#include "inventory.h"
#include "IND_Animation.h"

using namespace std;

int main()
{
	back: cout << "                             *WELCOME TO BATTLEDOME2*\n\n" << endl;
	enum menu{ currentPosition = 1, visualise = 3, setPosition = 2, inventory = 4 };
	cout << "  Your default positon:    [press 1 and Enter]\n";
	cout << "  Set position:            [press 2 and Enter]\n";
	cout << "  Visualize ship:          [press 3 and Enter]\n";
	cout << "  Open inventory:          [press 4 and Enter]\n\n";

	Ship boat(2.1,3.1);
	Inventory items;

	int selectedOpt = 0;
	cin >> selectedOpt;
	system("CLS");

	switch (selectedOpt)
	{
		case currentPosition:
		{	
			cout << "Your ship's default position is: \n";
			boat.currentPosition();
			system("pause");
			system("CLS");
			goto back;
			break;
		}
		case visualise:
		{
			boat.visualise();
			system("pause");
			system("CLS");
			goto back;
			break;
		}
		case setPosition:
		{
			double x = 0.0;
			double y = 0.0;
			cout << "Enter new coordinates: \n";
			cout << "x= "; cin >> x;
			cout << "y= "; cin >> y;
			boat.setPosition(x, y);
			cout << "Your newest position is: "; boat.currentPosition();
			system("pause");
			system("CLS");
			goto back;
			break;
		}
		case inventory:
		{
			back2: cout << "Fill your inventory: \n\n";
			items.getItems();
			items.showItems();
			system("CLS");
			goto back2;
			break;
		}
		default:
			cout << "You've clearly lost your mind...\n\n";
			goto back;
		}

	boat.~Ship();
	system("pause");
	return 0;
}