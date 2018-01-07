//To include all the libraries of the c++
#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <cmath>


using namespace std;

//including the self made libraries
#include "vector.cpp"
#include "stack.cpp"
#include "Graph.cpp"

int main ()
{
	Graph G;

	char filename[100];
	cout << "Enter the name of the file : ";
	cin >> filename;

	//reading the graph and checking for the error
	if (!G.read_Graph (filename))
		return 0;

	//printing the Graph 
	G.print_list();
	G.print_matrix();

	return 0;
}