//==========================================================//
//	Name  				- 	Arpit singh						//
//	Roll number 		- 	111601031						//
//	Date				-   February  6 , 2018				//
//	program Description - 	Takes the graph 			    //
//							finds the minimum spanning tree	//
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
void span (Graph &G , int start);

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


	pre = (int *) malloc (n * sizeof (int));


	span (G , 0);



	cout << "The corresponding edges of the minimum spanning tree is " << endl;
	for (int i = 0; i < n ; i++)
		if (pre[i] != -1)
		cout << i << " " << pre[i] << endl;
	//printing the Graph
	//G.print_list();


	G.clear();
	return 0;
}


void span (Graph &G , int start)
{
	int n = G.vertices ;
	for (int i = 0 ; i < n ; i++)
		pre[i] = -1;


	pre[start] = -1;

	pairs *array = (pairs *)malloc (n * sizeof (pairs));
	for (int i =0 ; i < n ; i++)
	{
		if (i == start)
		{
			pairs temp = pairs (0 , start);
			array[i] = temp;
		}
		else
		{
			pairs temp = pairs (100000 , i);
			array[i] = temp;
		}
	}

	bool *visited = (bool *)malloc (n * sizeof (bool));
	for (int i = 0; i < n ; i++)
		visited[i] = false;
	//creating the heap and putting the element
	Min_Heap < pairs > myHeap = Min_Heap <pairs>(array , n);


	while (!myHeap.isEmpty())
	{

		//popping the element
			pairs p = myHeap.Min_pop();

			int vertex = p.second;
			visited[vertex] = true;
			int wt = p.first;

			

		//going through all the vertices of the vertex
		for (struct node <pairs> *c = G.AL[vertex].begin() ; c != NULL ; c = c->next)
		{

			pairs current = c-> data;
			int weight = current.second;
			int u = current.first;

			
			int cost = myHeap.a[myHeap.listOfindices[u]].data.first;
			
			//updating the distance and pushing it into the priority queue
				if (!visited[u] && cost > weight)
				{

					pre[u] = vertex;
					cost = weight;
					pairs temp = pairs (cost , u);
					myHeap.decrease_key (myHeap.listOfindices[u] , temp);

				}
		}
	}


}
