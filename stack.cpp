//To include all the libraries of the c++
#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <cmath>

using namespace std;
//Stack is defined using the stack class here

template <typename T>
struct node 
{
	T data;
	struct node * next;
	struct node * prev;
};

template <typename T>
class Stack
{

	private :
		struct node <T> *head;
		struct node <T> *tale;
		int s = 0; 

	public:
		Stack ()
		{
			head = NULL;
			tale = NULL;
		}
	//all the functions 

	//this function is used to check wether is stack is empty or not	
	bool empty ()
	{
		if (s == 0)
			return true;
		else
			return false;
	}

	//this function returns the size of the stack
	int size (){ return s;}
	
	//this function return the top value of the 
	T top (){return tale -> data;}

	//this is used to push the element at the top of the stack
	void push (T x)
	{
		struct node <T> *temp = (struct node <T> * )malloc (sizeof (struct node <T>));
		temp -> data = x;

		if (head == NULL)
		{
			head = temp;
			head -> next = NULL;
			head -> prev = NULL;
			tale = head;
		}

		else
		{
			tale -> next = temp;
			temp -> prev = tale;
			temp -> next = NULL;
			tale = temp;
		}
		s++;
	}

	//pop is to pop the element out of the stack
	bool pop ()
	{
		if (size() != 0)
		{
			struct node <T>* temp = (struct node <T> *)malloc (sizeof (struct node <T>));
			temp = tale;
			tale = tale -> prev;

			if (tale != NULL)
			tale -> next = NULL;
			free(temp);	
			s--; 
			return true;
		}
		else
			return false;
	} 
};



