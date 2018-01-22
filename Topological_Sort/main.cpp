//==========================================================//
//	Name  				- 	Arpit singh						//
//	Roll number 		- 	111601031						//
//	Date				-   Januray 6 , 2018				//
//	program Description - 	Takes the graph , do DFS search //
//							and list vertices in            //
//							topological_order if possible	//
//==========================================================//


//note use g++ -std=c++11 for compiling the program

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

//global variable for the clock

int cl = 0;
int *pre ;
int *post ;
int *parent;
bool *visited ;
Vector <int> topological_order;
int a , b;


//important functions
void DFS (Graph &G , int v );
bool solve (Graph &G);

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

	topological_order = Vector <int> ();




	//taking this as the number of the vertices
	int n = G.vertices;

	//for visited vertices
	visited = (bool *)malloc (n * sizeof (bool));

	//initialisng the pre and post and parent
	pre = (int *)malloc (n * sizeof (int));
	post = (int *)malloc (n * sizeof (int));
	parent = (int *)malloc (n * sizeof (int));

	//assigning initial values to pre , post and visit
	for (int i =0 ; i< n ; i++)
	{
		visited[i] = false;
		pre[i] = -1;
		post[i] = -1;

		//setting the parent to be at -2
		parent[i] = -2;

	}


	for (int i = 0 ; i < n ; i++)
	{
		if (visited[i] == false)
		{
			DFS (G , i);
			parent[i] = -(i+1);
		}
	}
	if (solve(G))
	{
		cout << "It is directed acylic graph\n";
		cout << "The topological_order is : \n";
		for (struct node <int> *c = topological_order.tale ; c != NULL ; c = c -> prev)
			cout << c -> data << endl;
	}
	else
	{
		cout << "Backedge is found it is not a directed acyclic graph\n";
		Vector <int> cycle = Vector <int> (); 
		int current = a;
		while (current != b)
		{
			cycle.push_back (current);
			current = parent[current];
		}
		cycle.push_back(current);

		for (struct node <int> *c = cycle.tale ; c != NULL ; c = c-> prev)
			cout << " -- " << c->data << " -- ";

		cout << endl;
	}
	//it frees the memory of the graph and other different memories
	free (pre);

	free (post);
	free (parent);
	free (visited);
	G.clear();


	return 0;
}

void DFS (Graph &G , int v )
{
	//for pre and the post visit

	cl++;
	pre[v] = cl;
	visited[v] = true;

	//traversing list of the corresponding vertex
	for (struct node <int> *c = G.AL[v].begin() ; c != G.AL[v].end() ; c = c-> next)
	{
		int u = c->data;

		//if not visited then recursively calling the function
		if (visited[u] == false)
		{
			parent[u] = v;
			DFS (G , u);
		}
	}

	//for post visit of the vertex v
	topological_order.push_back (v);
	cl++;
	post[v] = cl;

}

bool solve(Graph &G)
//this function  look for the back edge
{	
		bool ans = true;
	//asking for and opening the file
		FILE *file;
		cout << "Enter the name of the output file (dot file): " ;
		char filename[100];
		cin >> filename;

		file = fopen (filename , "w");

	//printing the necesssary details
		fprintf(file , "digraph one\n");
		fprintf(file , "{\n");


	for (int i =0 ; i < G.vertices ; i++)
	{
		for (struct node <int> *c = G.AL[i].begin() ; c != G.AL[i].end() ; c = c->next )
		{
			//taking the vertices
			int u = i;
			int v = c -> data;

			fprintf (file , "%d->%d;\n " ,u , v );

			//looking for the back edges
				if (pre[v] < pre[u] && pre[u] < post[u] && post[u] < post[v])
				{
					a = u;
					b = v;
					ans = false;
				}
		}
		if (G.AL[i].size() == 0)
			fprintf(file , "%d;\n", i);
	}
	//backedge is not found return true
	fprintf(file, "}\n");
	fclose(file);
	return ans;
}
