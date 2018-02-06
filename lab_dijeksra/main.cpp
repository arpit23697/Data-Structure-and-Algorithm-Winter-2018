//==========================================================//
//	Name  				- 	Arpit singh						//
//	Roll number 		- 	111601031						//
//	Date				-   February  6 , 2018				//
//	program Description - 	Takes the graph , do dijeskra   //
//							find shortest distance to all edges	//
//==========================================================//






//To include all the libraries of the c++
#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <cmath>

using namespace std;

//including the self made libraries
#include "pairs.cpp"
#include "vector.cpp"
#include "stack.cpp"

#include "Min_Heap.cpp"
#include "Graph.cpp"

//global variable for the clock
int *pre;
int * dijeksra (Graph &G , int start);

int main ()
{

	Graph G;

	//asking for the file name
	char filename[100];
	cout << "Enter the name of the file : ";
	cin >> filename;


	//reading the graph and checking for the error
	if (!G.read_Graph_AL (filename))
		return 0;

	int n = G.vertices;
	int start = G.start;

	pre = (int *) malloc (n * sizeof (int));


	int * distance = dijeksra (G , 0);

	cout << "Each vertices and there distances are" << endl;
	for (int i = 0; i< n ; i++)
	{
		if (distance[i] != 1000000)
		cout << i << " " << distance[i] << endl;
		
		else
			cout << i << "  infinity" << endl;
	}

	cout << "The corresponding parent values are " << endl;
	for (int i = 0; i < n ; i++)
		cout << i << " " << pre[i] << endl;
	//printing the Graph
//	G.print_list();


	G.clear();
	return 0;
}


int * dijeksra (Graph &G , int start)
{
	int n = G.vertices ;
	int * distance = (int *)malloc(n * sizeof (int));
	for (int i = 0 ; i < n ; i++)
	{
		pre[i] = -2;
		distance[i] = 1000000;
	}
	
	distance[start] = 0;
	pre[start] = -1;


	//creating the heap and putting the element
	Min_Heap < pairs > myHeap = Min_Heap <pairs>();
	pairs temp = pairs (distance[start] , start);
	myHeap.insert (temp);

	while (!myHeap.isEmpty())
	{

		//popping the element
			pairs p = myHeap.Min_pop();
			
			int vertex = p.second;
			int wt = p.first;
		
		//going through all the vertices of the vertex
		for (struct node <pairs> *c = G.AL[vertex].begin() ; c != NULL ; c = c->next)
		{
			pairs current = c-> data;
			int weight = current.second;
			int u = current.first;
			
			//updating the distance and pushing it into the priority queue
				if (distance[u] > distance[vertex] + weight)
				{
					pre[u] = vertex;
					distance[u] = distance[vertex] + weight;
					pairs temp = pairs (distance[u] , u);
					myHeap.insert (temp);
				}
		}
	}
	return distance;

}
