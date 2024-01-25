#pragma once
#include<iostream>
#include<fstream>
#include"Inventory.h"
using namespace std;

class Beauty_and_Personal_Care_Inventory: public Inventory
{
	string category = "Beauty & Personal Care";
public:
	string get_category()
	{
		return category;
	}
	static void load_Beauty_and_Personal_Care_inventory()
	{
		Beauty_and_Personal_Care_Inventory BPC;
		string name[15] = { "Sunblock","Perfume","Toner","Exfoliator","Face Mask","Face Cream","Lipsticks",
			"Lotion", "Nails", "Lense","Foundations","Highlighter","Mascara","Eyeshadow","Makeup Remover", };
		float price[15] = { 75,80,100,120,90,65,50,110,130,150,140,240,300,150,180 };
		int quantity[15] = { 250,400,400,150,200,100,300,270,310,330,340,200,200,400,350 };
		BPC.set_inventory(BPC.get_category(), name, price, quantity);
	}
};

