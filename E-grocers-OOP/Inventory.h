#pragma once
#include<iostream>
#include<fstream>
#include"Product.h"
#include"Helper_functions.h"
using namespace std;

class Inventory
{
protected:
	Product* products[15];
public:
	void set_inventory(string filename, string* name, float* price, int* quantity)
	{
		for (int i = 0; i < 15; i++)
		{
			this->products[i] = new Product(i + 1, quantity[i], price[i], name[i]);
			write_inventory(filename + ".dat", *(this->products[i]));
		}
	}
};


