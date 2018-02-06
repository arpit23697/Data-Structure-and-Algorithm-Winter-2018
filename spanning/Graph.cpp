//==========================================================//
//	Name  				- 	Arpit singh						//
//	Roll number 		- 	111601031						//
//	Date				-   Januray 6 , 2018				//
//	program Description - 	For graph library				//
//															//
//==========================================================//



//To include all the libraries of the c++
#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <cmath>
#include <stdlib.h>

using namespace std;

class Graph
{
	public :
		Vector <pairs> *AL;
		//int ** AM;
		int vertices;
		int edges;

	bool read_Graph_AL (char filename[]);
	//this function reads the graph

	//this function reads the graph in AM form (Adjacency matrix form)
	bool read_Graph_AM (char filename[]);

	//this function prints the graph in the form of the list
	void print_list ()
	{
		for (int i =0 ; i < vertices ; i++)
		{
			for (struct node <pairs> *c = AL[i].begin() ; c != NULL ; c = c-> next)
			{
				pairs p1 = c -> data;
				cout << "(" << p1.first << " , " << p1.second  << ") ";
			}
			cout << endl;
		}
	}

	//this function clear the memory of the graph
	void clear ()
	{
		free (AL);
	}

};

bool Graph :: read_Graph_AL (char filename[])
	{
		//opening the file
		FILE *file;
		file = fopen (filename , "r");

		//checking if the wrong file is not entered
		if (file == 0)
		{
			//printing the error message if there is error in reading the file
			cout << "Error in opening the file\n";
			return false;
		}
			fscanf (file , "%d",&vertices);
			fscanf (file , "%d", &edges);
			int n = vertices;
				//initialise the adjacency list
				AL = (Vector <pairs> *) malloc (n * sizeof (Vector <pairs>));

				//this initialise all the vectors
				for (int i =0 ; i < n ;i++)
					AL[i] = Vector <pairs>();
			//reading the graph
 				for (int i =0 ; i< edges ; i++)
				{
					int a , b , weight;
					fscanf (file , "%d %d %d" , &a , &b , &weight);
					pairs p = pairs (b , weight);
					AL[a].push_back (p);
					p.first = a;
					AL[b].push_back (p);
				}
			//closing the file
			fclose (file);
			return true;


	}
