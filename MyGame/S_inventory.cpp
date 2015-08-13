#include<iostream>
#include<vector>
#include<string>
#include "inventory.h";
using namespace std;

void Inventory::getItems()
{
	back1: cout << "  press 1 for a rocket \n  press 2 for a spare armour \n  press 3 for a filled fuel canister \n  press 4 for a space cow\n\n\n  press 0 to exit\n\n";
	cin >> selectedOpt;
	system("CLS");
	switch (selectedOpt)
	{
	case roc:
	{
			cout << "You've acquired a rocket!\n\n";
			inventory.push_back("rocket");
			system("pause");
			system("CLS");
			break;
	}
	case arm:
	{
			cout << "You've acquired a spare armour!\n\n";
			inventory.push_back("armour");
			system("pause");
			system("CLS");
			break;
	}
	case fuel:
	{
			cout << "You've acquired some fuel!\n\n";
			inventory.push_back("fuel");
			system("pause");
			system("CLS");
			break;
	}
	case cow:
	{
			cout << "You've rescued a cow from outer space!\n\n";
			inventory.push_back("cow");
			system("pause");
			system("CLS");
			break;
	}
	case back:
	{
				 //goto back;
	}
	default:
		cout << "You've clearly lost your mind...\n\n";
		goto back1;
	}
}

void Inventory::showItems()
{
	if (inventory.size() < 10)
	{
		cout << "You have " << inventory.size() << " items.\n\n";
		cout << "\nYour items: \n";
		for (int i = 0; i < inventory.size(); ++i)
		{
			cout << "- " << inventory[i] << endl;
		}
		cout << "\n" << endl;
		system("pause");
		system("CLS");
	}
	else
	{
		cout << "Your inventory is full.\n\n";
		system("pause");
		system("CLS");
	}
}

Inventory::Inventory()
{

}

Inventory::~Inventory()
{

}

