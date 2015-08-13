#ifndef INVENTORY_H
#define INVENTORY_H
#include<iostream>
#include<vector>
using namespace std;

class Inventory
{
public:
	Inventory();
	~Inventory();
	void getItems();
	void showItems();
	
	int selectedOpt = 0;
	vector<string> inventory;
	enum{roc=1,arm=2,fuel=3,cow=4,back=0};
	int amount=0;
};

#endif