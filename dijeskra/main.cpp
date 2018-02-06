//==========================================================//
//	Name  				- 	Arpit singh						//
//	Roll number 		- 	111601031						//
//	Date				-   Januray 6 , 2018				//
//	program Description - 	Takes the graph , do DFS search //
//							and list all the edges			//
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
	int start;
	cout << "Enter the starting vertex\n";
	cin >> start;


	int * distance = dijeksra (G , 0);
	for (int i = 0; i< n ; i++)
		cout << distance[i] << endl;
	//printing the Graph
	G.print_list();


	G.clear();
	return 0;
}

int * dijeksra (Graph &G , int start)
{
	int n = G.vertices ;
	int * distance = (int *)sizeof (n * sizeof (int));
	for (int i = 0 ; i < n ; i++)
		distance[i] = 1000000;
	distance[start] = 0;

	pairs * array;
	array = (pairs *)malloc (n * sizeof (pairs));

	for (int i =0 ; i < n ; i++)
	{
		array[i].first = 1000000;
		array[i].second = i;
	}
	array[start].first = 0;

	Min_Heap < pairs > myHeap = Min_Heap <pairs>();
	myHeap.build (array , n);

	bool * visited = (bool *)malloc (n * sizeof(bool));
	for (int i = 0 ;  i < n ; i++)
		visited[i] = false;

	int totalVisited = 0;
	while (totalVisited < n)
	{
		pairs p = myHeap.Min_pop();
		distance[p.second] = p.first;
		int vertex = p.second;

		visited[vertex] = true;
		totalVisited ++;

		for (struct node <pairs> *c = G.AL[vertex].begin() ; c != NULL ; c = c->next)
		{
			pairs current = c-> data;
			int weight = current.second;
			int u = current.first;
			if (visited[u] == false)
			{
				if (distance[u] > distance[vertex] + weight)
				{
					distance[u] = distance[vertex] + weight;
				}
			}
		}
	}

}
