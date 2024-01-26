#pragma once
#include<iostream>
#include<iomanip>
using namespace std;

class Product
{
private:
	int product_id;
	char product_name[25];
	float product_price;
	int product_quantity;

public:
	Product(int id = 0, int quantity = 0, float price = 0.00, string name = " ")
	{
		product_id = id;
		strcpy_s(this->product_name, name.c_str());
		product_price = price;
		product_quantity = quantity;
	}
/*----------------------------------------------------------------------------------------------------------------
													SETTERS
----------------------------------------------------------------------------------------------------------------*/
	void set_id(const int id)
	{
		product_id = id;
	}
	void set_name(const string name)
	{
		strcpy_s(this->product_name, name.c_str());
	}
	void set_price(const float price)
	{
		product_price = price;
	}
	void set_quantity(const int quantity)
	{
		product_quantity = quantity;
	}
/*----------------------------------------------------------------------------------------------------------------
													GETTERS
----------------------------------------------------------------------------------------------------------------*/
	int get_id() const
	{
		return product_id;
	}
	string get_name() const
	{
		return product_name;
	}
	float get_price() const
	{
		return product_price;
	}
	int get_quantity() const
	{
		return product_quantity;
	}
/*----------------------------------------------------------------------------------------------------------------
													Display
----------------------------------------------------------------------------------------------------------------*/
	void display() const
	{
		cout << "\t\t\t" << setw(10) << left << this->get_id() << "\t" << setw(20) << left << this->get_name()
			<< setw(15) << left << this->get_price() << setw(10) << left << this->get_quantity() << endl;
	}
};