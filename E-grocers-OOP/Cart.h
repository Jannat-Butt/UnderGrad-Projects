#pragma once
#include<iostream>
#include<fstream>
#include"Inventory.h"
#include"Helper_functions.h"
#include"Product.h"
using namespace std;

void read_inventory(string filename);
void write_inventory(string filename, Product P);
void Delete(string filename, Product deleted_product);

class Cart
{
private:
	int no_of_products_selected;
	char cart_name[30];
	
public:
	Cart()
	{
		no_of_products_selected = 0;
	}
	void set_no_of_products_selected(const int selected_products_no)
	{
		no_of_products_selected = selected_products_no;
	}
	//---------------------------------------------------------------------
	void set_cart_name(const string cart_name)
	{
		strcpy_s(this->cart_name, cart_name.c_str());
	}
	string get_cart_name() const
	{
		return this->cart_name;
	}
	//---------------------------------------------------------------------
	int get_no_of_products_selected() const
	{
		return no_of_products_selected;
	}
	void add_to_cart(string filename, Product purchased_product, int purchased_quantity)
	{
		Product temp;
		fstream file(filename + ".dat", ios::in | ios::out | ios::binary);
		bool flag = false;		//to check whether the product is already present or not
		while (file.read((char*)&temp, sizeof(temp)))
		{	//searching through name because there is more than 1 similar ID in different categories
			if (temp.get_name() == purchased_product.get_name()) // if the product is already present
			{
				flag = true;
				{
					temp.set_quantity(temp.get_quantity() + purchased_quantity); //to add the same product again
					int current_position = file.tellg();
					int size = sizeof(Product);
					file.seekp(current_position - size, ios::beg);
					file.write((char*)&temp, sizeof(temp));
					break;
				}
			}
		}
		if (flag == false)	// if the product is not already present
		{
			temp = purchased_product;
			temp.set_quantity(purchased_quantity);
			write_inventory(filename + ".dat", temp);
			//no_of_products_selected++;
		}
	}
	bool remove_from_cart(string filename, Product purchased_product, int remove_quantity)
	{
		Product temp;
		bool flag = false;
		fstream file(filename + ".dat", ios::in | ios::out | ios::binary);
		while (file.read((char*)&temp, sizeof(temp)))
		{	//searching through name because there is more than 1 similar ID in different categories
			if (temp.get_name()._Equal(purchased_product.get_name())) 
			{
				if (temp.get_quantity() > remove_quantity)
				{
					temp.set_quantity(temp.get_quantity() - remove_quantity);
					int current_position = file.tellg();
					int size = sizeof(Product);
					file.seekp(current_position - size, ios::beg);
					file.write((char*)&temp, sizeof(temp));
					file.close();
					return 1;
				}
				else if (temp.get_quantity() == remove_quantity)
				{		// if quantity becomes 0 then remove that item from cart
					file.close();
					temp.set_quantity(temp.get_quantity() - remove_quantity);
					flag = true;
				}
			}
		}
		if (flag == true)
		{
			Delete(filename, temp);
			return 1;
		}
		return 0;
	}
	//bool is_empty()
	//{
	//	if (no_of_products_selected == 0)
	//	{
	//		return 1;
	//	}
	//	else
	//	{
	//		return 0;
	//	}
	//}
	void display_cart(string cart_name)
	{
		read_inventory(cart_name);
	}
};