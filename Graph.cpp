//To include all the libraries of the c++
#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <cmath>

using namespace std;

class Graph 
{
	public :
		Vector <int> *AL;
		int ** AM;
		int vectices;

	bool read_Graph (char filename[]);
	//this function reads the graph

	//this function prints the graph in the form of the list
	void print_list ()
	{
		for (int i =0 ; i < vectices ; i++)
			AL[i].print();
	}

	//this function prints the graph in the form of the matrix 
	void print_matrix ()
	{
		for (int i = 0; i< vectices ; i++)
		{
			for (int j =0 ; j < vectices ; j++)
				cout << AM[i][j] << " ";

			cout << endl;
		}
	}

};

bool Graph :: read_Graph (char filename[])
	{
		if (freopen (filename , "r" , stdin))
		{
			char c[20];
			scanf("%s",c);

			if (c[1] == 'L')
			{
				scanf ("%d",&vectices);
				int n = vectices;

				//this is to initialise the Adjaceny matrix
				AM = (int **)malloc (n * sizeof (int *));
				for (int i = 0 ; i < n ; i++)
					AM[i] = (int *)malloc (n * sizeof (int));

				//to make all the values 0
				for (int i =0 ; i < n ; i++)
					for (int j =0 ; j < n ; j++)
						AM[i][j] = 0;

				//initialise the adjacency list
				AL = (Vector <int> *) malloc (n * sizeof (Vector <int>));

				//this initialise all the vectors
				for (int i =0 ; i < n ;i++)
					AL[i] = Vector <int>();

 				
				//reading the graph
 				for (int i =0 ; i<n ; i++)
				{
					int temp ;
					while (scanf ("%d",&temp) == 1 && temp != -1)
					{
						AL[i].push_back (temp);		//storing the value in the adjacency list
						AM[i][temp] = 1;			//storing the value in the adjacency matrix
					}
				}
			}
			else if (c[1] == 'M')
			{
				scanf ("%d",&vectices);
				int n = vectices;

				//this is to initialise the Adjaceny matrix
				AM = (int **)malloc (n * sizeof (int *));
				for (int i = 0 ; i < n ; i++)
					AM[i] = (int *)malloc (n * sizeof (int));

				//initialise the adjacency list
				AL = (Vector <int> *) malloc (n * sizeof (Vector <int>));

				//reading the graph from the Adjacency matrix
				for (int i = 0 ; i < n ; i++)
					for (int j = 0 ; j < n ; j++)
					{
						int x;
						scanf("%d",&x);
						AM[i][j] = 1;			//storing the value in the adjacency matrix

						if (x == 1)
						AL[i].push_back(j);		//stroing the value in the adjacency list
					}

			}
			return true;
		}
		else
		{
			//printing the error message if there is error in reading the file
			cout << "Error in opening the file\n";
			return false;
		}
	}

