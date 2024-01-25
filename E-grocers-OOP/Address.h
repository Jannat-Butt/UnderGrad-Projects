#include<iostream>
using namespace std;

class Address
{
private:
	char street[30];
	char city[30];
	int postal_code;
public:
	Address(string, string, int);
	
	void set_street(const string);
	void set_city(const string);
	void set_postal_code(const int);

	string get_street()const;
	string get_city()const;
	int get_postal_code()const;
};

Address::Address(string street = "default", string city = "default", int postal_code = 0)
{
	strcpy_s(this->street, street.c_str());
	strcpy_s(this->city, city.c_str());

	this->postal_code = postal_code;
}
/*----------------------------------------------------------------------------------------------------------------
													SETTERS
----------------------------------------------------------------------------------------------------------------*/
void Address::set_city(const string city)
{
	strcpy_s(this->city, city.c_str());
}
void Address::set_street(const string street)
{
	strcpy_s(this->street, street.c_str());
}
void Address::set_postal_code(const int postal_code)
{
	this->postal_code = postal_code;
}
/*----------------------------------------------------------------------------------------------------------------
													GETTERS
----------------------------------------------------------------------------------------------------------------*/
string Address::get_street()const
{
	return street;
}
string Address::get_city()const
{
	return city;
}
int Address::get_postal_code()const
{
	return postal_code;
}