#pragma once
#include<iostream>
#include<fstream>
#include"Inventory.h"
using namespace std;

class Garments_and_Accessories : public Inventory
{
	string category = "Garments & Accessories";
public:
	string get_category()
	{
		return category;
	}
	static void load_Garments_and_Accessories_inventory()
	{
		Garments_and_Accessories GA;
		string name[15] = { "Trousers","Skirts","Pants","Shirts","Bags","Hats","Scarfs","Socks","Jackets",
			"Waisecoats","Shorts","Shoes","Sunglasses","Watches","Jewellery" };
		float price[15] = { 75,80,100,120,90,65,50,110,130,150,140,240,300,150,180 };
		int quantity[15] = { 250,400,400,150,200,100,300,270,310,330,340,200,200,400,350 };
		GA.set_inventory(GA.get_category(), name, price, quantity);
	}
};

