#include<iostream>
#include<cstdio>
#include<fstream>
using namespace std;

class Feedback
{
private:
	int no_of_stars;
	char comment[15];
	char user_name[30];
public:
	Feedback()
	{

	}
	Feedback(int stars, string user_name)
	{
		no_of_stars = stars;
		strcpy_s(this->user_name, user_name.c_str());
	}
/*----------------------------------------------------------------------------------------------------------------
													SETTERS
----------------------------------------------------------------------------------------------------------------*/
	void set_comment(const string comment)
	{
		strcpy_s(this->comment, comment.c_str());
	}
/*----------------------------------------------------------------------------------------------------------------
													GETTERS
----------------------------------------------------------------------------------------------------------------*/
	int get_no_of_stars() const
	{
		return no_of_stars;
	}
	string get_comment()
	{
		return comment;
	}
	string get_username() const
	{
		return  user_name;
	}
/*----------------------------------------------------------------------------------------------------------------
													OTHER FUNCTIONS
----------------------------------------------------------------------------------------------------------------*/
	void display_asterisks()
	{
		switch (this->get_no_of_stars())
		{
		case 1:
			cout << "* ";
			this->set_comment("Poor");
			break;
		case 2:
			cout << "* * ";
			this->set_comment("Unsatisfactory");
			break;
		case 3:
			cout << "* * * ";
			this->set_comment("Satisfactory");
			break;
		case 4:
			cout << "* * * *";
			this->set_comment("Good");
			break;
		case 5:
			cout << "* * * * *";
			this->set_comment("Excellent");
			break;
		default:
			cout << "Not valid Range";
		}
	}
	void display_feedback()
	{
		cout << endl << "Name:" << this->user_name << endl;
		cout << "Rating: ";
		this->display_asterisks();
		cout << endl << "Comment:" << this->comment << endl;
	}
};
