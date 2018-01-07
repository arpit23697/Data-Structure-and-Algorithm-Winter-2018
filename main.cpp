//==========================================================//
//	Name  				- 	Arpit singh						//
//	Roll number 		- 	111601031						//				
//	Date				-   Januray 6 , 2018				//
//	program Description - 	Takes the graph , do DFS search //
//							and list all the edges			//
//==========================================================//


//note use g++ -std=c++11 for compiling the program
//the test generates dot file and list all the edges even those that are not travelled
//red - tree edge
//green - back edge
//blue - cross edge
//brown - forward edge
//black - untravelled edge




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

//important functions
void DFS (Graph &G , int v );
void clasify (Graph &G);

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

	//printing the Graph 
		//G.print_list();
		//G.print_matrix();


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

	//asking for the value of the starting vertex	
	int x;
	cout << "Enter the starting vertex : ";
	cin >> x;

	//calling the DFS function
	DFS (G , x);
	parent[x] = -1;

	cout << "Pre and post visit time of each of the vertices " << endl;
	for (int i = 0 ; i < n ; i++)
		cout << i << "   [ " << pre[i] << " , " << post[i] << " ] "<< endl;

	clasify(G);

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
	cl++;
	post[v] = cl;

}

void clasify(Graph &G)
//this function classifies the vertices
{
	//asking for and opening the file
		FILE *file;
		cout << "Enter the name of the output file (dot file): " ;
		char filename[100];
		cin >> filename;

		file = fopen (filename , "w");

	//printing the necesssary details
		fprintf(file , "digraph one\n");
		fprintf(file , "{\n");

		cout << "All the edges with their types : " << endl;

	for (int i =0 ; i < G.vertices ; i++)
	{
		for (struct node <int> *c = G.AL[i].begin() ; c != G.AL[i].end() ; c = c->next )
		{
			//taking the vertices
			int u = i;
			int v = c -> data;

			if (visited[u] && visited[v])
			{	
			//now classifying the vertices
				if (pre[v] < pre[u] && pre[u] < post[u] && post[u] < post[v])
				{	
					//red for tree edge
					cout << u << " -> " << v << "  Back Edge" << endl;
					fprintf (file , "%d->%d [color = green] [style = dotted];\n " ,u , v );
				}
				else if (post[v] < pre[u] || post[u] < pre[v])
				{
					//blue color for cross edge
					cout << u << " -> " << v << "  Cross Edge" << endl;
					fprintf (file , "%d->%d [color = blue] [style = dotted] ;\n" ,u , v );
				}

				else if (pre[u] < pre[v] && pre[v] < post[v] && post[v] < post[u])
				{
					if (parent[v] == u)
					{	
						cout << u << " -> " << v << "  Tree Edge" << endl;
						fprintf (file , "%d->%d [color = red]; \n" ,u , v );
					}
					else
					{	
						cout << u << " -> " << v << "  Forward Edge" << endl;
						fprintf (file , "%d->%d [color = brown] [style = dotted];\n " ,u , v );
					}
				}
			}
			else
			{
				//for untravelled edges
				cout << u << " -> " << v << "  untravelled Edge" << endl;
				fprintf (file, "%d->%d\n " ,u , v );
			}


		}
		if (G.AL[i].size() == 0)
			fprintf(file , "%d;\n", i);
	}

	fprintf(file, "}\n");
	fclose(file);
}