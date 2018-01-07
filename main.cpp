//To include all the libraries of the c++
#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <cmath>
#include "stack.cpp"

using namespace std;


int main ()
{
	Stack<int> s = Stack <int>();
	s.push (10);
	s.push (20);
	cout << s.size() << endl;
	s.push (40);
	s.pop();
	s.pop();

	cout << s.size() << endl;
	s.push(33);
	s.push(37);
	cout << s.size() << endl;

	while (!s.empty())
	{
		cout << s.top() << endl;
		s.pop();
	}

	return 0;
}