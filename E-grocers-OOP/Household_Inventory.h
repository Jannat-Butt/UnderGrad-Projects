#pragma once
#include<iostream>
#include<fstream>
#include"Inventory.h"
using namespace std;

class HouseHold : public Inventory
{
	string category = "HouseHold";
public:
	string get_category()
	{
		return category;
	}

	static void load_household_inventory()
	{
		HouseHold H;
		string name[15] = { "Toothpaste","Toothbrush" ,"Shampoo","Soap","Disinfectant","Dish Cleaner","Scrub",
			"Floor Cleaner","Mop", "Detergent","Broom", "Bucket","Vaccum","Cleaning Brush","Cleaning Cloth" };
		float price[15] = { 75,80,100,120,90,65,50,110,130,150,140,240,300,150,180 };
		int quantity[15] = { 250,400,400,150,200,100,300,270,310,330,340,200,200,400,350 };
		H.set_inventory(H.get_category(), name, price, quantity);
	}
};
