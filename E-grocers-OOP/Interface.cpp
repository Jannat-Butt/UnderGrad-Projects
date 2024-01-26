#include<iostream>
#include<iomanip>
#include<conio.h>
#include"Food_Inventory.h"
#include"Household_Inventory.h"
#include"Garments_and_Accessories_Inventory.h"
#include"Beauty_and_Personal_Care_Inventory.h"
#include"Helper_functions.h"
#include"Order.h"
#include"Customer.h"
#include"Admin.h"
using namespace std;

int main()
{
	/*Food::load_food_inventory();
	HouseHold::load_household_inventory();
	Garments_and_Accessories::load_Garments_and_Accessories_inventory();
	Beauty_and_Personal_Care_Inventory::load_Beauty_and_Personal_Care_inventory();
	Transportation::set_name_phoneNum();*/
	string category;
	Customer customer;
	bool flag;			// to exit certain menu
	bool exit = false;		// to exit program
	Admin admin;
	read_driver("driverFile.dat");
	do
	{
		system("cls");
		Welcome();
		switch (Login_choice())
		{
			case 1:     // Admin
				do
				{	
					admin.login();
					if (admin.validation())
					{
						break;
					}
					system("pause");
					system("cls");
				} while (1);
				system("cls");
				flag = false;
				do
				{
					system("cls");   
					switch (admin_menu())
					{
					case 1:
						admin.Display_all_Products();
						system("pause");
						break;

					case 2:
						category = Category(category_choice());
						admin.Update_Product(category);
						break;

					case 3:
						category = Category(category_choice());
						admin.Add_Product(category);
						break;

					case 4:
						category = Category(category_choice());
						admin.Delete_Product(category);
						break;

					case 5:
						category = Category(category_choice());
						admin.Refill_Inventory(category);
						system("pause");
						break;

					case 6:
						flag = true;
						break;
					}
				} while (flag == false);
				break;

		case 2:			//customer
			Signup_or_Signin(customer);
			system("cls");
			cout << "Welcome " << customer.get_userName() << endl;
			flag = false;
			do
			{
				switch (category_choice())
				{
				case 1:
					category = "HouseHold";
					Buyer(category, customer);
					break;

				case 2:
					category = "Food";
					Buyer(category, customer);
					break;

				case 3:
					category = "Garments & Accessories";
					Buyer(category, customer);
					break;

				case 4:
					category = "Beauty & Personal Care";
					Buyer(category, customer);
					break;

				case 5:
					flag = true;
					break;

				default:
					cout << "Invalid Input" << endl;
				}
			} while (flag == false);
			break;

			case 3:
				Feedback ratings();
				read_feedback("CustomerFeedBack.dat");
				cout << endl;
				system("pause");
				break;

			case 4:
				exit = true;
				cout << setw(70) << "Thanks for visiting us :)" << endl;
				cout << setw(65) << "See you soon" << endl;
				cout << setw(65) << "GoodBye :(" << endl;
				break;
		}
	} while (exit == false);   //breaks at case 4 else continues

	return 0;
}
