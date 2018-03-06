//==========================================================//
//	Name  				- 	Arpit singh						//
//	Roll number 		- 	111601031						//
//	Date				-   February  6 , 2018				//
//	program Description - 	Takes the graph 			    //
//							find the single source shortest	//
//							path using Bellman ford			//
//==========================================================//






//To include all the libraries of the c++
#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <cmath>

using namespace std;

//including the self made libraries
#include "vector.cpp"
#include "pairs.cpp"
#include "Graph.cpp"

int inf = 1000000;

//global variable for the clock
int *pre;
int *dist;
bool Bellman (Graph &G , int start);
bool Relax (int u , int v , int weight);

int main ()
{

	Graph G;
	//reading the graph and checking for the error
	if (!G.read_Graph_AL ())
		return 0;

	int n = G.vertices;
	int start;
	scanf ("%d",&start);

	pre = (int *) malloc (n * sizeof (int));
	dist = (int*)malloc (n * sizeof (int));
	//G.print_list();

	//detecting and printing the cycle
	bool isCycle = Bellman (G , start);
	if (isCycle)
	{
		cout << "There is a negative weighted cycle in the graph that is reachable from the start vertex" << endl;
		for (int i =0  ; i < n ; i++)
		{
			bool flag;
			for (struct node <pairs> *c = G.AL[i].begin() ; c != NULL ; c = c -> next)
			{
				int u = i;
				pairs p = c->data;
				int v = p.first;
				int weight = p.second;
				
				//seeing if the edge is relaxed then printing the cycle
				Vector <int> cycle = Vector <int> ();
				if (dist[v] > dist[u] + weight)
				{
					
					int current = v;
					flag = true;			//to see if this is involved in the cycle or not
					int x = 0;
					while (1)
					{
						x++;
						//cout << x << endl;
						cycle.push_back (current);
						current = pre[current];
						if (current == -1)
						{
							flag = false;
							break;
						}
						if (current == v)
						{
							flag = true;
							break;
						}

						if (x > n)
						{
							flag = false;
							break;
						}
					}

				//if the cycle is there then printing the cycle
				if (flag)
				{
					cout << "The negative weighted cycle is  : " << endl;
					//printing the cycle
					for (struct node <int> * c = cycle.tale ; c != NULL ; c = c-> prev)
						cout << c->data << "--";

					cout << endl;
					break;	
				}

			}
				if (flag)
					break;
		}
	}
	}

	else
	{
		//if there is no negative weight cycle then printing the result i.e. the distances and the pre values
		cout << "There is no negative weight cycle" << endl;
		cout << "The distance of each of the vertices and there previous values are" << endl;

		for (int i = 0 ; i < n ; i++)
		{
			if (dist[i] != inf)
			cout << i << ".   " << dist[i] << " 	" << pre[i] << endl;
			else
			cout << i << ".   " << "infintity" << "		 "  << "not reachable " << endl;
		}
	}


	G.clear();
	return 0;
}

//function to relax the edges ; returns true if the edge is relaxed otherwise return false
bool Relax (int u , int v , int weight)
{
	if (dist[v] > dist[u] + weight)
	{
		pre[v] = u;
		dist[v] = dist[u] + weight;
		return true;
	}
	return false;
}

//bellman ford algorithm
bool Bellman (Graph &G , int start )
{
	//initialising the dist and pre value of the vertices
	int n = G.vertices;
	for (int i =0 ; i < n ; i++)
	{
		dist[i] = inf;
		pre[i] = -1;	
	}
	dist[start] = 0;


	//looping through all the edges n-1 times
	for (int i =0  ; i < n-1 ; i++)
	{
		bool flag = false;		//to check if there is any update or not
		//relaxing each edge
		for (int j = 0 ; j < n ; j++)
		{
			for (struct node <pairs> *c = G.AL[j].begin() ; c != NULL ; c = c -> next)
			{
				int u = j;
				pairs p = c->data;
				int v = p.first;
				int weight = p.second;
				//cout << u << " " << v << " " << weight << endl;
				if (Relax(u , v , weight)) 
					flag = true; 

			}
		}
	
		//if there is no update then break
		if (!flag)
			break;
		
	}
	//to see if there is a negative cycle if so then return true else return false
	for (int i = 0 ; i < n ; i++)
	{
		for (struct node <pairs> *c= G.AL[i].begin() ; c != NULL ; c = c-> next)
		{
			int u = i;
			pairs p = c->data;
			int v = p.first;
			int weight = p.second;
			if (dist[v] > dist[u] + weight)
				return true;
		}
	}
	return false;

}
