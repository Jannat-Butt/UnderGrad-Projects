#pragma once
#include<iostream>
#include<string>
#include"Account.h"
#include"Cart.h"
#include"Address.h"
#include"Inventory.h"
using namespace std;

class Customer : public Account
{
private:
	Address customer_address;
	Cart customer_cart;
public:
	Customer():  customer_address()
	{

	}
	void login()
	{
		string temp;
		cin.ignore();
		system("cls");
		cout << "***********************************************************************************************************************" << endl;
		cout << endl;
		cout << setw(70) << "Welcome Customer" << endl;
		cout << setw(75) << "Please Login to continue: " << endl;
		cout << endl;
		cout << "***********************************************************************************************************************" << endl;
		cout << endl;
		cout << setw(65) << "LOGIN" << endl;
		cout << endl;
		cout << "\t\t\t------------------------------------------------------------------------------\t\t\t" << endl;
		cout << endl;
		cout << "\t\t\t\t" << setw(15) << left << "User Name: " << setw(10);
		getline(cin, temp);
		this->set_userName(temp);
		cout << endl;
		cout << "\t\t\t------------------------------------------------------------------------------\t\t\t" << endl;
		cout << endl;
		cout << "\t\t\t\t" << setw(15) << left << "Email: " << setw(10);
		getline(cin, temp);
		this->set_email(temp);
		cout << endl;
		cout << "\t\t\t------------------------------------------------------------------------------\t\t\t" << endl;
		cout << endl;
		cout << "\t\t\t\t" << setw(15) << left << "Password: " << setw(10);
		getline(cin, temp);
		this->set_password(temp);
		cout << endl;
		cout << "\t\t\t------------------------------------------------------------------------------\t\t\t" << endl;
	}
	void registration()
	{
		system("cls");
		string temp;
		cin.ignore();
		cout << "***********************************************************************************************************************" << endl;
		cout << endl;
		cout << setw(70) << "Welcome Customer" << endl;
		cout << setw(75) << "Please Register to continue: " << endl;
		cout << endl;
		cout << "***********************************************************************************************************************" << endl;
		cout << endl;
		cout << setw(65) << "REGISTRATION" << endl;
		cout << endl;
		cout << "\t\t\t------------------------------------------------------------------------------\t\t\t" << endl;
		cout << endl;
		cout << "\t\t\t\t" << setw(15) << left << "Name: " << setw(10);
		getline(cin, temp);
		this->set_name(temp);
		cout << endl;
		cout << "\t\t\t------------------------------------------------------------------------------\t\t\t" << endl;
		cout << endl;
		cout << "\t\t\t\t" << setw(15) << left << "User Name: " << setw(10);
		getline(cin, temp);
		this->set_userName(temp);
		cout << endl;
		cout << "\t\t\t------------------------------------------------------------------------------\t\t\t" << endl;
		cout << endl;
		cout << "\t\t\t\t" << setw(15) << left << "Email: " << setw(10);
		getline(cin, temp);
		this->set_email(temp);
		cout << endl;
		cout << "\t\t\t------------------------------------------------------------------------------\t\t\t" << endl;
		cout << endl;
		cout << "\t\t\t\t" << setw(15) << left << "Password: " << setw(10);
		getline(cin, temp);
		this->set_password(temp);
		cout << endl;
		cout << "\t\t\t------------------------------------------------------------------------------\t\t\t" << endl;
		cout << endl;
		cout << "\t\t\t\t" << setw(15) << left << "Phone Number: " << setw(10);
		cin >> this->phone_num;
		cout << endl;
		cout << "\t\t\t------------------------------------------------------------------------------\t\t\t" << endl;
	}
/*----------------------------------------------------------------------------------------------------------------
														SETTERS
----------------------------------------------------------------------------------------------------------------*/	
	void set_customer_address(const Address address)
	{
		this->customer_address = address;
		this->customer_address.set_city(address.get_city());
		this->customer_address.set_street(address.get_street());
		this->customer_address.set_postal_code(address.get_postal_code());
	}	
/*----------------------------------------------------------------------------------------------------------------
													GETTERS
----------------------------------------------------------------------------------------------------------------*/
	Address get_customer_address() const
	{
		return customer_address;
	}
	Cart get_customer_cart() const
	{
		return customer_cart;
	}
/*----------------------------------------------------------------------------------------------------------------
													OTHER FUNCTIONS
----------------------------------------------------------------------------------------------------------------*/
	void display_customer()
	{
		cout << "...................Displaying Customer..................";
		cout << endl << "Name:" << this->get_name() << endl;
		cout << endl << "City:" << this->customer_address.get_city() << endl;
		cout << endl << "Street:" << this->customer_address.get_street() << endl;
		cout << endl << "Postal Code:" << this->customer_address.get_postal_code() << endl;
	}
	bool customer_validation(string filename)
	{
		Customer temp;
		ifstream file(filename + ".dat", ios::binary);
		while (file.read((char*)&temp, sizeof(temp)))
		{
			if (temp.get_userName()._Equal(this->get_userName()) &&
				temp.get_email()._Equal(this->get_email()) &&
				temp.get_password()._Equal(this->get_password()))	//to search
			{
				cout << "Login Successful!" << endl;
				return 1;
			}
			else
			{
				cout << "Login failed. Please try again." << endl;
				return 0;
			}
		}
	}
	bool give_feedback()
	{
		char ch;
		cout << "Would you like to give us a feedback?" << endl;
		cout << "Press: " << endl;
		cout << "1. y for yes" << endl;
		cout << "2. n for no" << endl;
		do
		{
			cin >> ch;
			if (ch == 'N' || ch == 'n')
			{
				cout << "Okay :( " << endl;
				return 0;
			}
			else if (ch == 'Y' || ch == 'y')
			{
				return 1;
			}
			else
			{
				cout << "Oops! Invalid option. Please try again." << endl;
			}
		} while (ch != 'N' && ch != 'n' && ch != 'Y' && ch != 'y');
	}
};
//input_address(customer);
////customer.display_customer();
////cout << "*************************************************" << endl;
//read_customer("Customer");