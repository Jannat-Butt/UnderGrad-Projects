#include<iostream>
#include<fstream>
#include<string>
#include"Product.h"
#include"Inventory.h"
#include"Food_Inventory.h"
#include"Beauty_and_Personal_Care_Inventory.h"
#include"Garments_and_Accessories_Inventory.h"
#include"Household_Inventory.h"
#include"Helper_functions.h"
using namespace std;

class Admin: public Account
{
private:
	int pin_code;
public:
	void login()
	{
		system("cls");
		cout << "***********************************************************************************************************************" << endl;
		cout << endl;
		cout << setw(70) << "Welcome Admin" << endl;
		cout << setw(75) << "Please Login to continue: " << endl;
		cout << endl;
		cout << "***********************************************************************************************************************" << endl;
		cout << endl;
		cout << setw(65) << "LOGIN" << endl;
		cout << endl;
		cout << "\t\t\t------------------------------------------------------------------------------\t\t\t" << endl;
		cout << endl;
		cout << "\t\t\t\t" << setw(15) << left << "Name: " << setw(10);
		cin >> this->name;
		cout << endl;
		cout << "\t\t\t------------------------------------------------------------------------------\t\t\t" << endl;
		cout << endl;
		cout << "\t\t\t\t" << setw(15) << left << "Pin Code: " << setw(10);
		cin >> this->pin_code;
		cout << endl;
		cout << "\t\t\t------------------------------------------------------------------------------\t\t\t" << endl;
	}

	bool validation()
	{
		int pin_code = 12345;
		string name = "Admin";
		if (name._Equal(this->name) && this->pin_code == pin_code)
		{
			cout << "Login Successful" << endl;
			return 1;
		}
		else
		{
			cout << "Invalid Name or Pin code. Please try again" << endl;
			return 0;
		}
	}

	void Update_Product(string filename)
	{
		read_inventory(filename);
		int id = input_ID();
		float price = 0;
		cout << "Enter the updated price: " << endl;
		cin >> price;
		Product temp;
		fstream file(filename + ".dat", ios::in | ios::out | ios::binary);
		while (file.read((char*)&temp, sizeof(temp)))
		{
			if (temp.get_id() == id)
			{
				temp.set_price(price);
				int current_position = file.tellg();
				int size = sizeof(Product);
				file.seekp(current_position - size, ios::beg);
				file.write((char*)&temp, sizeof(temp));
				file.close();
			}
		}
		system("cls");
		cout << "Updated Inventory: " << endl;
		read_inventory(filename);
	}
	void Add_Product(string filename)
	{
		Product product_to_be_added = input_product(filename);
		write_inventory(filename + ".dat", product_to_be_added);
		system("cls");
		read_inventory(filename);
	}
	void Delete_Product(string filename)
	{
		read_inventory(filename);
		int id = input_ID();
		Product temp;
		ifstream filein(filename + ".dat", ios::in | ios::binary);
		ofstream fileout("new_file.dat", ios::out | ios::binary);
		while (filein.read((char*)&temp, sizeof(temp)))
		{
			if (temp.get_id() != id)
			{	
				fileout.write((char*)&temp, sizeof(temp));
			}
		}
		filein.close();
		fileout.close();
		string file_name = filename + ".dat";
		remove(file_name.c_str());
		if (rename("new_file.dat",file_name.c_str()) != 0)
		{
			cout << "error" << endl;
		}
		else
		{
			cout << "success" << endl;
		}
		read_inventory(filename);
	}
	void Refill_Inventory(string filename)
	{
		read_inventory(filename);
		int id = input_ID();
		int quantity = input_quantity();
		Product temp;
		fstream file(filename + ".dat", ios::in | ios::out | ios::binary);
		while (file.read((char*)&temp, sizeof(temp)))
		{
			if (temp.get_id() == id)
			{
				temp.set_quantity(temp.get_quantity() + quantity);
				int current_position = file.tellg();
				int size = sizeof(Product);
				file.seekp(current_position - size, ios::beg);
				file.write((char*)&temp, sizeof(temp));
				file.close();
			}
		}
		system("cls");
		cout << "Refilled Inventory: " << endl;
		read_inventory(filename);
	}
	void Display_all_Products()
	{
		cout << "Household Inventory is: " << endl;
		read_inventory("Household");
		cout << "Food Inventory is: " << endl;
		read_inventory("Food");
		cout << "Garments & Accessories Inventory is: " << endl;
		read_inventory("Garments & Accessories");
		cout << "Beauty & Personal Care Inventory is: " << endl;
		read_inventory("Beauty & Personal Care");
	}
};