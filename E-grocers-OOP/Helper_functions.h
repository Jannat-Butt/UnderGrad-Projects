#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include"Product.h"
#include"Payment.h"
#include"Customer.h"
#include"Cart.h"
#include"Order.h"
#include"Feedback.h"
#include"Inventory.h"
#include"Transportation.h"

using namespace std;

void Welcome_category(string category)
{
	cout << "***********************************************************************************************************************" << endl;
	cout << endl;
	cout << "\t\t\t\t\t" << "Welcome to " << category << " Category" << endl;
	cout << endl;
	cout << "***********************************************************************************************************************" << endl;
}

void Welcome()
{
	cout << "***********************************************************************************************************************" << endl;
	cout << endl;
	cout << setw(70) << "Welcome to E-Grocers" << endl;
	cout << setw(85) << "Get everything at your doorstep within one touch ;)" << endl;
	cout << endl;
	cout << "***********************************************************************************************************************" << endl;
}

/*----------------------------------------------------------------------------------------------------------------
												Customer
----------------------------------------------------------------------------------------------------------------*/
void write_customer(string filename, Customer C)
{
	ofstream fout(filename + ".dat", ios::binary | ios::app);
	fout.write((char*)&C, sizeof(C));
	fout.close();
}
void read_customer(string filename)
{
	Customer temp;
	ifstream fin(filename + ".dat", ios::binary);
	while (fin.read((char*)&temp, sizeof(temp)))
	{
		temp.display_customer();
	}
	fin.close();
}

void Update_customer(string filename, Customer customer)
{
	Customer temp;
	fstream file(filename + ".dat", ios::binary | ios::in| ios:: out);
	while (file.read((char*)&temp, sizeof(temp)))
	{
		if (strcmp(temp.get_userName().c_str(), customer.get_userName().c_str()) == 0)
		{
			temp.set_customer_address(customer.get_customer_address());
			int current_position = file.tellg();
			int size = sizeof(Customer);
			file.seekp(current_position - size, ios::beg);
			file.write((char*)&temp, sizeof(temp));
			file.close();
		}
	}
}

void Signup_or_Signin(Customer& customer)
{
	int option = 0;
	cout << "Select one from the following options: " << endl;
	cout << "1. Register" << endl;
	cout << "2. Login" << endl;
	do
	{
		cin >> option;
		if (option < 0 || option > 2)
		{
			cout << "Oops! Invalid choice. Please try again" << endl;
		}
	} while (option < 0 || option > 2);
	switch (option)
	{
	case 1:
		customer.registration();
		write_customer("Customer", customer);
		break;

	case 2:
		customer.login();
		while (!(customer.customer_validation("Customer")))
		{
			customer.login();
		}
		break;
	}
}

/*----------------------------------------------------------------------------------------------------------------
												Address
----------------------------------------------------------------------------------------------------------------*/

void input_address(Customer& customer)
{
	string street, city;
	int postal_code = 0;
	cin.ignore();
	cout << "***********************************************************************************************************************" << endl;
	cout << endl;
	cout << "\t\t\t\t\t" << "Please Enter the Address for delivery:" << endl;
	cout << endl;
	cout << "***********************************************************************************************************************" << endl;
	cout << endl;
	cout << setw(65) << "TRANSPORTATION DETAILS" << endl;
	cout << endl;
	cout << "\t\t\t------------------------------------------------------------------------------\t\t\t" << endl;
	cout << endl;
	cout << "\t\t\t\t" << setw(15) << left << "City: " << setw(10);
	getline(cin, city);
	cout << endl;
	cout << "\t\t\t------------------------------------------------------------------------------\t\t\t" << endl;
	cout << endl;
	cout << "\t\t\t\t" << setw(15) << left << "Street: " << setw(10);
	getline(cin, street);
	cout << endl;
	cout << "\t\t\t------------------------------------------------------------------------------\t\t\t" << endl;
	cout << endl;
	cout << "\t\t\t\t" << setw(15) << left << "Postal Code: " << setw(10);
	cin >> postal_code;
	cout << endl;
	cout << "\t\t\t------------------------------------------------------------------------------\t\t\t" << endl;
	Address* customer_address = new Address(street, city, postal_code);
	customer.set_customer_address(*customer_address); //passed by value
	Update_customer("Customer", customer);
	system("cls");
}
/*----------------------------------------------------------------------------------------------------------------
												Product
----------------------------------------------------------------------------------------------------------------*/

Product Search(string filename, int id)
{
	Product purchased_product;
	fstream file(filename + ".dat", ios::in | ios::out | ios::binary);
	while (file.read((char*)&purchased_product, sizeof(purchased_product)))
	{
		if (purchased_product.get_id() == id)
		{
			file.close();
			return purchased_product;
		}
	}
}

void write_inventory(string filename, Product P)
{
	ofstream write_file(filename, ios::binary | ios::app);
	write_file.write((char*)&P, sizeof(P));
	write_file.close();
}

void read_inventory(string filename)
{
	Product Temp;
	ifstream read_file(filename + ".dat", ios::binary);
	cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "\t\t\t" << setw(10) << left << "ID" << "\t" << setw(20) << left << "Name" << setw(15) << left
		<< "Price" << setw(10) << left << "Quantity" << endl;
	cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
	cout << endl;
	while (read_file.read((char*)&Temp, sizeof(Temp)))
	{
		Temp.display();
	}
	cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
	read_file.close();
}

bool Purchased(string filename, int id, int purchased_quantity)
{
	Product purchased_product;
	fstream file(filename + ".dat", ios::in | ios::out | ios::binary);
	while (file.read((char*)&purchased_product, sizeof(purchased_product)))
	{
		if (purchased_product.get_id() == id)
		{
			if (purchased_product.get_quantity() >= purchased_quantity)
			{
				purchased_product.set_quantity(purchased_product.get_quantity() - purchased_quantity);
				int current_position = file.tellg();
				int size = sizeof(Product);
				file.seekp(current_position - size, ios::beg);
				file.write((char*)&purchased_product, sizeof(purchased_product));
				file.close();
				return 1;
			}
			else
			{
				cout << "Not enough " << purchased_product.get_name() << " in stock" << endl;
				return 0;
			}
		}
	}
}

void return_back_to_inventory(string filename,int id,int returned_quantity)
{
	Product returned_product;
	fstream file(filename + ".dat", ios::in | ios::out | ios::binary);
	while (file.read((char*)&returned_product, sizeof(returned_product)))
	{
		if (returned_product.get_id() == id)
		{
			returned_product.set_quantity(returned_product.get_quantity() + returned_quantity);
			int current_position = file.tellg();
			int size = sizeof(Product);
			file.seekp(current_position - size, ios::beg);
			file.write((char*)&returned_product, sizeof(returned_product));
			file.close();
		}
	}
}
void Delete(string filename, Product deleted_product)
{
	Product temp;
	ifstream filein(filename + ".dat", ios::binary | ios::app);
	ofstream fileout("new_file.dat", ios::binary | ios::app);
	while (filein.read((char*)&temp, sizeof(temp)))
	{
		if (!(temp.get_name()._Equal(deleted_product.get_name())))	//if they are not equal
		{
			fileout.write((char*)&temp, sizeof(temp));
		}
	}
	fileout.close();
	filein.close();
	string file_name = filename + ".dat";
	remove(file_name.c_str());
	/*if (rename("new_file.dat", file_name.c_str()) != 0)
	{
		cout << "error" << endl;
	}
	else
	{
		cout << "success" << endl;
	}*/
	//read_inventory(filename);
	system("pause");
}

int Login_choice()
{
	int choice = 0;
	cout << "LOGIN as:" << endl;
	cout << "1. Admin" << endl;
	cout << "2. Customer" << endl;
	cout << "3. Display feedbacks" << endl;
	cout << "4. Exit" << endl;
	cout << endl;
	cout << "Enter your choice: " << endl;
	cin >> choice;
	cout << endl;
	return choice;
}

int category_choice()
{
	int choice = 0;
	cout << "Please select a category:" << endl;
	cout << "1. Household" << endl;
	cout << "2. Food" << endl;
	cout << "3. Garments & Accessories" << endl;
	cout << "4. Beauty & Personal Care" << endl;
	cout << "5. Log out" << endl;
	cout << endl;
	cout << "Enter your choice: " << endl;
	cin >> choice;
	if (choice < 0 || choice > 5)
	{
		cout << "Oops! Invalid choice. Please try again" << endl;  
	}
	cout << endl;
	return choice;
}

string Category(int input)
{
	switch (input)
	{
	case 1:
		return "Household";
	case 2:
		return "Food";
	case 3:
		return "Garments & Accessories";
	case 4:
		return "Beauty & Personal Care";
	case 5:
		break;
	}
}

int admin_menu()
{
	int choice = 0;
	cout << "Please select one from the following options:" << endl;
	cout << "1. Display all Products" << endl;
	cout << "2. Update a Product" << endl;
	cout << "3. Add a Product" << endl;
	cout << "4. Delete a Product" << endl;
	cout << "5. Refill Inventory" << endl;
	cout << "6. Return to Main Menu" << endl;
	cout << endl;
	cout << "Enter your choice: " << endl;
	cin >> choice;
	if (choice < 0 || choice > 6)
	{
		cout << "Oops! Invalid choice. Please try again" << endl; 
	}
	cout << endl;
	return choice;
}

Product input_product(string category)
{
	string name;
	int quantity = 0, id = 0;
	float price = 0;
	cout << "Current Inventory" << endl;
	read_inventory(category);
	cout << "Enter Product ID: " << endl;
	cin >> id;
	cout << "Enter Product Name: " << endl;
	cin.ignore();
	getline(cin, name);
	cout << "Enter Product Price: " << endl;
	cin >> price;
	cout << "Enter Product Quantity: " << endl;
	cin >> quantity;
	Product product(id, quantity, price, name);
	return product;
}

int input_ID()
{
	int id = 0;
	do
	{
		cout << "Enter ID: " << endl;
		cin >> id;
		if (id < 0 || id > 16)
		{
			cout << "Oops! Invalid ID. Please try again" << endl;
		}
	} while (id < 0 || id > 16);
	return id;
}

int input_quantity()
{
	int quantity = 0;
	do
	{
		cout << "Enter Quantity: " << endl;
		cin >> quantity;
		if (quantity < 0 || quantity > 500)
		{
			cout << "Oops! Invalid Quantity. Please try again" << endl;
		}
	} while (quantity < 0 || quantity > 500);
	return quantity;
}


int next_operation()
{
	char choice;
	do
	{
		cout << "what do you want to do next? Press" << endl;
		cout << "1. r to remove a Product of current section from Cart" << endl;
		cout << "2. y to continue shopping in current section" << endl;
		cout << "3. b to go back to the categories menu" << endl;
		cout << "4. o to proceed to order" << endl;
		cin >> choice;
		if (!(choice == 'B' || choice == 'b' || choice == 'R' || choice == 'r' || choice == 'Y'
			|| choice == 'y' || choice == 'O' || choice == 'o'))
		{
			cout << "Oops! Invalid Operation. Please try again." << endl;
		}
	} while (!(choice == 'B' || choice == 'b' || choice == 'R' || choice == 'r' || choice == 'Y'
		|| choice == 'y' || choice == 'O' || choice == 'o'));
	return choice;
}

/*----------------------------------------------------------------------------------------------------------------
												Payment
----------------------------------------------------------------------------------------------------------------*/
void payment(double& bill)
{
	Payment* customer_payment = nullptr;
	switch (customer_payment->payment_mode())
	{
	case 1: 
		customer_payment = new Cash_on_delivery(bill);
		cout << "Payment will be done on delivery." << endl;
		break;

	case 2:
		customer_payment = new Credit_card_payment(bill);
		if (customer_payment->Pay())
		{
			system("cls");
			cout << "Payment through credit card has been done." << endl;
			bill = 0;  // payment done
		}
		break;
	}
}



/*----------------------------------------------------------------------------------------------------------------
												Feedback
----------------------------------------------------------------------------------------------------------------*/
void write_feedback(string CustomerFeedBack, Feedback f)
{
	ofstream fout(CustomerFeedBack, ios::binary | ios::app);
	fout.write((char*)&f, sizeof(f));
	fout.close();
}
void read_feedback(string  CustomerFeedBack)
{
	Feedback temp;
	ifstream fin(CustomerFeedBack, ios::binary);
	while (fin.read((char*)&temp, sizeof(temp)))
	{
		temp.display_feedback();
	}
	fin.close();
}

void delete_feedback(string CustomerFeedBack, string username)
{
	Feedback temp;
	ifstream fin(CustomerFeedBack, ios::binary | ios::in);
	ofstream fout("new_file.dat", ios::out | ios::binary);
	while (fin.read((char*)&temp, sizeof(temp)))
	{
		if (strcmp(temp.get_username().c_str(), username.c_str()) != 0)//because it accepts char *
		{
			fout.write((char*)&temp, sizeof(temp));
		}
	}
	fout.close();
	fin.close();
	remove("CustomerFeedBack.dat");
	rename("new_file.dat", "CustomerFeedBack.dat");
}

void ask_feedback(Customer& customer)
{
	if (customer.give_feedback())
	{
		int stars = 0;
		do
		{
			cout << "Enter ratings from Range 1-5:";
			cin >> stars;
			if (stars < 0 || stars > 5)
			{
				cout << "Oops. Invalid Range. Try again" << endl;
			}
			else
			{
				break;
			}
		} while (1);
		Feedback ratings(stars, customer.get_userName());
		ratings.display_asterisks();
		write_feedback("CustomerFeedBack.dat", ratings);
		cout << "Thankyou for the feedback!" << endl;
		//read_feedback("CustomerFeedBack.dat");
	}
}
/*----------------------------------------------------------------------------------------------------------------
													TRANSPORTATION
----------------------------------------------------------------------------------------------------------------*/

void write_driver(string driverFile, Transportation obj)
{
	ofstream fout(driverFile, ios::binary | ios::app);
	fout.write((char*)&obj, sizeof(obj));
	fout.close();
}

void read_driver(string driverFile)
{
	Transportation temp;
	ifstream fin(driverFile, ios::binary);
	cout << "...............Displaying Drivers.............." << endl;
	while (fin.read((char*)&temp, sizeof(temp)))
	{
		temp.display_driver();
	}
	fin.close();
}

void delete_driver(string driverFile, string driverName)
{
	Transportation temp;
	ifstream fin(driverFile, ios::binary | ios::in);
	ofstream fout("new_driverfile.dat", ios::out | ios::binary);
	while (fin.read((char*)&temp, sizeof(temp)))
	{
		if (strcmp(temp.get_driverName().c_str(), driverName.c_str()) != 0)  //because it accepts char *
		{
			fout.write((char*)&temp, sizeof(temp));
		}
	}
	fout.close();
	fin.close();
	remove("driverFile.dat");
	rename("new_driverfile.dat", "driverFile.dat");
}

/*----------------------------------------------------------------------------------------------------------------

----------------------------------------------------------------------------------------------------------------*/
void Buyer(string category, Customer customer)
{
	system("cls");
	int id = 0;
	int quantity = 0;
	char operation;
	do
	{
		system("cls");
		Welcome_category(category);
		cout << "\t\t\t\t\t" << customer.get_userName() << " Your Cart is: " << endl;
		customer.get_customer_cart().display_cart(customer.get_userName());
		cout << "\t\t\t\t\t\t" << "Inventory" << endl;
		read_inventory(category);
		operation = next_operation();

		if (operation == 'R' || operation == 'r')
		{
			int remove_quantity = 0, remove_id = 0;
			remove_id = input_ID();
			remove_quantity = input_quantity();
			if (customer.get_customer_cart().remove_from_cart(customer.get_userName(), Search(category, remove_id), remove_quantity))
			{
				return_back_to_inventory(category, remove_id, remove_quantity);
			}
		}
		else if (operation == 'Y' || operation == 'y')
		{
			id = input_ID();
			quantity = input_quantity();
			if (Purchased(category, id, quantity))
			{
				customer.get_customer_cart().add_to_cart(customer.get_userName(), Search(category, id), quantity);
			}
			else
			{
				cout << Search(category, id).get_name() << " is Out of Stock" << endl;
			}
		}
		else if (operation == 'B' || operation == 'b')
		{
			system("cls");
			break;
		}
		else  if (operation == 'O' || operation == 'o')
		{
			Order order;
			order.calculate_bill(customer.get_userName(), customer.get_customer_cart());
			system("cls");
			order.display_order(customer.get_userName(), customer.get_customer_cart());
			if (order.confirm_order())
			{
				double bill = order.get_bill();
				payment(bill);
				input_address(customer);
				Transportation transport;
				transport.assign_driver(customer);
				cout << "driver assigned!!" << endl;
				transport.display_driver();
				cout << endl << endl;
				ask_feedback(customer);
			}
			else
			{
				//cancel_order();
			}
			break;
		}
	} while (operation != 'B' && operation != 'b' && operation != 'O' && operation != 'o');
}
