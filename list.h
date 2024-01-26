#include<iostream>
using namespace std;

//..................................................Node class...............................................
class ND
{
private:
	int data;
	ND* next_ptr;
public:
	ND();
	ND(int x);
	void set_data(int);
	int get_data();
	void set_next(ND*);
	ND* get_next();
};
//..................................................getter setters...............................................
ND::ND()
{
	data = 0;
	next_ptr = NULL;
}
ND::ND(int x)
{
	data = x;
	next_ptr = NULL;
}
void ND::set_data(int value)
{
	data = value;
}
void ND::set_next(ND* ptr)
{
	next_ptr = ptr;
}
int ND::get_data()
{
	return (this->data);
}
ND* ND::get_next()
{
	return (this->next_ptr);
}

//.....................................................list class...................................................
class List
{
private:
	ND* head;
public:
	List();
	void set_head(ND*);
	ND* getHead();
	void insertAtEnd(int);
	void deleteAtStart();
	void deleteAtEnd();
	void push_front(int);
	void push_back(int);
	void insertAtHead(int);
	void pop_front();
	void pop_back();
	bool empty();
	int front();
	int back();
};
//............................................list getter setters...................................................
List::List()
{
	head = NULL;
}
void List::set_head(ND* head)
{
	this->head = head;
}
ND* List::getHead()
{
	return (head);
}
//................................................linked list functions..................................................
void List::insertAtEnd(int val)
{
	ND* newnode = new ND;
	if (head == NULL)
	{
		newnode->set_data(val);
		head = newnode;

	}
	else
	{
		ND* temp_forw = head;
		ND* temp_prev = head;
		while (temp_forw->get_next() != NULL)
		{
			temp_prev = temp_forw;
			temp_forw = temp_forw->get_next();
		}
		newnode->set_data(val);
		temp_prev->set_next(newnode);

	}
}
//.................................................insertAtHead.......................................................
void List::insertAtHead(int i_value) {
	if (head == NULL)
	{
		ND* n_node = new ND(i_value);
		head = n_node;

	}
	else
	{
		ND* temp = head;
		ND* n_node = new ND(i_value);
		n_node->set_next(head);
		head = n_node;

	}

}
//...................................................deleteAtStart................................................

void List::deleteAtStart()
{
	if (head == NULL)
	{
		return;
	}
	else
	{
		ND* temp = head;
		head = head->get_next();
		delete temp;

	}
}
//...............................................deleteAtEnd..................................................
void List::deleteAtEnd()
{
	if (head == NULL)
	{
		return;
	}
	else
	{
		ND* temp_forw = head;
		ND* temp_prev = head;
		while (temp_forw->get_next() != NULL)
		{
			temp_prev = temp_forw;
			temp_forw = temp_forw->get_next();
		}
		delete temp_forw;
		temp_prev->set_next(NULL);

	}
}
void List::push_front(int x)
{
	insertAtHead(x);
}
void List::push_back(int x)
{
	insertAtEnd(x);
}
bool List::empty()
{
	if (head == NULL)
	{
		return true;
	}
	else {
		return false;
	}
}
int List::front()
{
	if (head == NULL)
	{

		return -7860;
	}
	else
	{
		int temp = head->get_data();

		return temp;
	}
}
void List::pop_front()
{
	deleteAtStart();
}
void List::pop_back()
{
	deleteAtEnd();
}
int List::back()
{

	if (head == NULL)
	{

		return -7860;
	}
	else
	{
		ND* temp = head;
		ND* temp_prev = head;
		while (temp->get_next() != NULL)
		{

			temp = temp->get_next();
		}
		return temp->get_data();
	}
}