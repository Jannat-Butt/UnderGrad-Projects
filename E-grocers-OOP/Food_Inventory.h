#pragma once
#include<iostream>
#include<fstream>
#include"Inventory.h"
using namespace std;

class Food : public Inventory
{
	 string category = "Food";
public:
	string get_category()
	{
		return category;
	}
	static void load_food_inventory()
	{
		Food F;
		string name[15] = { "Bread","Eggs","Milk","Peanut Butter","Jam","Cream","Snacks","Paratha","Macroni",
			"Rice","Flour","Meat","Chicken","Soft drinks","Juices" };
		float price[15] = { 75,80,100,120,90,65,50,110,130,150,140,240,300,150,180 };
		int quantity[15] = { 250,400,400,150,200,100,300,270,310,330,340,200,200,400,350 };
		F.set_inventory(F.get_category(), name, price, quantity);
	}
};

