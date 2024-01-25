#pragma once
#include<iostream>
using namespace std;

class Account
{
protected:
	char name[30];
	char user_name[30];
	char email[30];
	char password[20];
	long long int phone_num;
public:
	Account(string name = " ", string user_name = " ", string email = " ", string password = " ",
		long long int phoneNum = 0)
	{
		strcpy_s(this->name, name.c_str());
		strcpy_s(this->user_name, user_name.c_str());
		strcpy_s(this->email, email.c_str());
		strcpy_s(this->password, password.c_str());
		this->phone_num = phoneNum;
	}

	virtual void login() = 0;

	void set_name(const string name)
	{
		strcpy_s(this->name, name.c_str());
	}
	void set_userName(const string username)
	{
		strcpy_s(this->user_name, username.c_str());
	}
	void set_email(const string email)
	{
		strcpy_s(this->email, email.c_str());
	}
	void set_password(const string password)
	{
		strcpy_s(this->password, password.c_str());
	}
	void set_phoneNum(const long long int phoneNum)
	{
		this->phone_num = phoneNum;
	}
	string get_name()const
	{
		return name;
	}
	string get_userName()const
	{
		return user_name;
	}
	string get_email()const
	{
		return email;
	}
	string get_password()const
	{
		return password;
	}
	long long int get_phoneNum()const
	{
		return phone_num;
	}
};
