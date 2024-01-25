#pragma once
#include<iostream>
#include"Order.h"
using namespace std;

class Payment
{
protected:									
	double bill;
public:
	Payment()
	{
		// default constructor
	}
	Payment(double bill)
	{
		this->bill = bill;
	}
	virtual bool Pay()
	{
		//polymorphism
		return 1;
	}
	int payment_mode()
	{
		int mode = 0;
		cout << "How do you want to pay? Please select one of the following options." << endl;
		cout << "1. Cash on Delivery" << endl;
		cout << "2. Payment through credit card" << endl;
		do
		{
			cin >> mode;
			if (mode < 0 || mode > 2)
			{
				cout << "Oops! Invalid choice. Please try again" << endl;
			}
		} while (mode < 0 || mode > 2);
		return mode;
	}
};

class Cash_on_delivery : public Payment
{
	double cash_paid;
	float change_returned;
public:
	Cash_on_delivery(double bill) :  Payment(bill)
	{ 
	
	}
	bool Pay()
	{
		change_returned = cash_paid - bill;
		return 1;
	}
};

class Credit_card_payment : public Payment
{
	char card_holder_name[30];
	double balance;
	char card_number[16];
public:
	Credit_card_payment(double bill) : Payment(bill)
	{
		string temp;
		cin.ignore();
		cout << "Enter Card holder name: " << endl;
		getline(cin, temp);
		this->set_card_holder_name(temp);
		cout << "Enter card no: " << endl;
		for (int i = 0; i < 16; i++)
		{
			cin >> card_number[i];
			while (!(card_number[i] >= 48 && card_number[i] <= 57))
			{
				cout << "Invalid number. Try again" << endl;
				cin >> card_number[i];
			}
		}
		cout << "Enter balance: " << endl;
		cin >> this->balance;
	}
	void set_card_holder_name(const string name)
	{
		strcpy_s(this->card_holder_name, name.c_str());
	}
	bool Pay()
	{
		balance = balance - bill;
		return 1;
	}
};