//==========================================================//
//	Name  				- 	Arpit singh						//
//	Roll number 		- 	111601031						//
//	Date				-   Januray 6 , 2018				//
//	program Description - 	For vector library				//
//															//
//==========================================================//


//To include all the libraries of the c++
#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <cmath>

using namespace std;

//defining the struct node
template <typename T>
struct node
{
	T data;
	struct node *next;
	struct node *prev;
};

template <typename T>
class Vector
{
	//declaration of the private variables
	private :
	int s = 0;

	//declaration of the public variables
	public :
	struct node <T> *head;
	struct node <T> *tale;

	//constuctor
	Vector ()
	{
		head = NULL;
		tale = NULL;
		s = 0;
	}

	//member functions
	//this function returns the pointer to the beginning of the vector
	struct node <T> * begin (){ return head; }

	//this function returns the pointer to the end of the vector
	struct node <T> * end () {return NULL;}

	//returns the size of the vector
	int size () { return s;}

	//test wether the vector is empty or not
	bool empty ()
	{
		if (s == 0)
			return true;
		else
			return false;
	}

	//this function returns the value at the pos index
	T at (int pos)
	{
		int index = 0;
		if (pos < s)
		{
			struct node <T> *current;
			current = head;
			while (index != pos)
			{
				current = current -> next;
				index++;
			}
			return current -> data;
		}
		else
			cout << "Index out of limit\n";

	}

	//this function returns the front element
	T front () { return head -> data; }

	//this function returns the value at the end
	T back () { return tale -> data; }

	//this function push the element at the back
	void push_back (T x)
	{
		struct node <T> *temp = (struct node <T> *) malloc (sizeof (struct node <T>));
		temp -> data = x;

		if (head == NULL)
		{
			temp -> next = NULL;
			temp -> prev = NULL;
			head = temp;
			tale = temp;
		}

		else
		{
			tale -> next = temp;
			temp -> next = NULL;
			temp -> prev = tale;
			tale = temp;
		}
		s++;
	}

	//this function pop the element from the back
	bool pop_back ()
	{
		if (size() != 0)
		{
			struct node <T> * temp = (struct node <T> *)malloc (sizeof (struct node <T>));
			temp = tale;
			tale = tale -> prev;

			if (tale != NULL)
			tale -> next = NULL;
			free (temp);
			s--;
			return true;
		}

		else
			return false;
	}

	//this function inserts the element at the given index
	//parameter as the pos and the value where to insert
	bool insert (int pos , T x)
	{
		struct node <T> * temp = (struct node <T> *)malloc (sizeof (struct node <T>));
		temp -> data = x;

		if (pos == s)
		{
			push_back (x);
			return true;
		}

		else if (pos == 0)
		{
			temp -> prev = NULL;
			temp -> next = head;
			head -> prev = temp;
			head = temp;
			s++;
			return true;
		}

		else if (pos < s)
		{
			struct node <T>* before;
			struct node <T>* after;
			before = head;
			int index = 0;
			while (index != pos-1 && before != NULL)
			{
				before = before -> next;
				index++;
			}

			after = before -> next;
			before -> next = temp;
			temp -> prev = before;
			temp -> next = after;

			if (after != NULL)
			after -> prev = temp;
			s++;
			return true;
		}

		return false;
	}
	//this function also return but it takes the pointer and the value to be inserted
	void insert (struct node <T>* before , T x)
	{
		struct node <T> * temp = (struct node <T> *)malloc (sizeof (struct node <T>));
		temp -> data = x;

		if (before == head)
		{
			temp -> prev = NULL;
			temp -> next = head;
			head -> prev = temp;
			head = temp;
			s++;
		}
		else if (before == NULL)
			push_back (x);

		else
		{

			struct node <T>* after;
			if (before != NULL)
			before = before -> prev;

			if (before != NULL)
			after = before -> next;
			before -> next = temp;
			temp -> prev = before;
			temp -> next = after;

			if (after != NULL)
			after -> prev = temp;
			s++;
		}
	}

	//this function erases the first element of the given value
	bool erase (struct node <T> *del )
	{
		if (del == head)
		{
			struct node <T> * temp = head;
			head = head -> next;
			if (head != NULL)
				head -> prev = NULL;

			free (temp);
			s--;
		}
		else if (del == tale)
			pop_back();

		else
		{
			struct node <T> * before;
			struct node <T> * after;

			before = del -> prev;
			after = del -> next;
			before -> next = after;
			after -> prev = before;
			free (del);
			s--;
		}
	}
	//this function erases the elements of given pos
	//secure to use;
	bool erase (int pos)
	{
		if (pos == 0)
		{
			struct node <T> * temp = head;
			head = head -> next;
			if (head != NULL)
				head -> prev = NULL;

			free (temp);
			s--;
		}
		else if (pos == s-1)
			pop_back();
		else if (pos < s-1)
		{
			int index = 0;
			struct node <T> *current = head;
			while (index != pos && current != NULL)
			{
				index++;
				current = current -> next;
			}
			struct node <T> * before;
			struct node <T> * after;

			before = current -> prev;
			after = current -> next;
			before -> next = after;
			after -> prev = before;
			free (current);
			s--;

		}
		else
			cout << "Index limit exceeded\n";
	}

	//this function finds the index of the given element if found otherwise return -1
	int find (T x)
	{
		struct node <T>* current = head;
		int index = 0;
		while (current != NULL)
		{
			if (current -> data == x)
				return index;
			current = current -> next;
			index++;
		}

		return -1;
	}
	//print the whole vector
	void print ()
	{
	//	cout << s << endl;
		struct node <T>* current = head;
		while (current != NULL)
		{
			cout << current -> data << " ";
			current = current -> next;
		}
		cout << endl;
	}

	//clear the whole link list
	void clear ()
	{
		while (!empty())
			pop_back();
	}


};

//this is the test bench
/*
int main ()
{
	Vector <pairs> vec = Vector<pairs>();
	pairs p1;
	p1.first = 20;
	p1.second = 30;

	vec.push_back(p1);
	//vec.push_back(p1);

	struct node <pairs> *c = vec.head;
	p1 = c -> data;
	cout << p1.first << " " << p1.second << endl;

	for (int i = 0; i < 20 ; i++)
	{
		pairs p;
		p.first = i*1;
		p.second = (i+1)*2;
		vec.push_back(p);
	}

	for (struct node <pairs> *c = vec.head ; c != NULL ; c = c-> next)
	{
		pairs p = c -> data;
		cout << p.first << " " << p.second << endl;
	}
*/
/*
	vec.push_back(10);
	vec.print();
	vec.push_back(5);
	vec.print();
	vec.insert(vec.tale, 100);
	vec.print();
	vec.pop_back();
	vec.print();
	vec.insert(1 , 200);
	vec.print();
	vec.erase(5);
	vec.print();

	for (struct node <double>* c = vec.begin() ; c != vec.end() ; c = c-> next)
		cout << c->data << " ";
	cout << endl;

	cout << vec.at (5) << endl;
*/
/*
	return 0;

}
*/
