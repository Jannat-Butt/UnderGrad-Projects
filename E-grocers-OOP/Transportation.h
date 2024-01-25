#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include"Helper_functions.h"
using namespace std;

class Transportation
{
private:
	Customer customer;
	char driver_name[30];
	char driver_phone[12];
	int vehicle_id;
	Transportation* transports[5];
public:
	Transportation(string driver_name = "Default", string driver_phoneNum = "00000000000", int vehicle_ID = 0)
	{
		strcpy_s(this->driver_name, driver_name.c_str());
		strcpy_s(this->driver_phone, driver_phoneNum.c_str());
		this->vehicle_id = vehicle_ID;
	}
/*----------------------------------------------------------------------------------------------------------------
													SETTERS
----------------------------------------------------------------------------------------------------------------*/

	void set_Customer(const Customer customer)
	{
		this->customer = customer;
	}
	void set_driverName(const string driver_name)
	{
		strcpy_s(this->driver_name, driver_name.c_str());
	}
	void set_driverPhone(const string driver_phoneNum)
	{
		strcpy_s(this->driver_phone, driver_phoneNum.c_str());
	}
	void set_VehicleID(const int Vehicle_ID)
	{
		this->vehicle_id = Vehicle_ID;
	}
/*----------------------------------------------------------------------------------------------------------------
													GETTERS
----------------------------------------------------------------------------------------------------------------*/
	int get_VehicleID() const
	{
		return this->vehicle_id;
	}
	string get_driverPhone() const
	{
		return this->driver_phone;
	}
	string get_driverName()const
	{
		return driver_name;
	}
	Customer get_Customer() const
	{
		return this->customer;
	}
/*----------------------------------------------------------------------------------------------------------------
												OTHER FUNCTIONS
----------------------------------------------------------------------------------------------------------------*/
	void display_driver()
	{
		cout << endl << "Name: " << driver_name << endl;
		cout << "Phone Num: " << driver_phone << endl;
		cout << "Vehicle ID: " << vehicle_id << endl;
		cout << "Address: " << endl;
		customer.display_customer();
	}
	void write_driver(string filename, Transportation obj)
	{
		ofstream fout(filename + ".dat", ios::binary | ios::app);
		fout.write((char*)&obj, sizeof(obj));
		fout.close();
	}

	void read_driver(string filename)
	{
		Transportation temp;
		ifstream fin(filename + ".dat", ios::binary);
		cout << "...............Displaying Drivers.............." << endl;
		while (fin.read((char*)&temp, sizeof(temp)))
		{
			temp.display_driver();
		}
		fin.close();
	}
	void set_driver(string filename, string* driverName, string* phoneNum)
	{
		for (int i = 0; i < 5; i++)
		{
			this->transports[i] = new Transportation(driverName[i], phoneNum[i], i + 1);
			write_driver(filename, *(this->transports[i]));
		}
	}
	static void set_name_phoneNum()
	{
		Transportation temp;
		string driver[5] = { "Ahmed","Hameed","Zain","Imran","Naveed" };
		string phone_num[5] = { "03315660345","03325671452","03321041231","03245057112","03234012567" };
		temp.set_driver("Transportation_details", driver, phone_num);
	}

	void assign_driver(Customer& customer)
	{
		srand(time(0));
		int random_id = rand() % 6;
		Transportation temp;
		ifstream file("Transportation_details.dat", ios::in | ios::binary);
		while (file.read((char*)&temp, sizeof(temp)))
		{
			if (temp.get_VehicleID() == random_id)
			{
				*this = temp;
				this->customer = customer;
			}
		}
	}
};