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
		Vector <int> *AL;
		//int ** AM;
		int vertices;

	bool read_Graph_AL (char filename[]);
	//this function reads the graph

	//this function reads the graph in AM form (Adjacency matrix form)
	//bool read_Graph_AM (char filename[]);

	//this function prints the graph in the form of the list
	void print_list ()
	{
		for (int i =0 ; i < vertices ; i++)
			AL[i].print();
	}

	//this function prints the graph in the form of the matrix 
/*	void print_matrix ()
	{
		for (int i = 0; i< vertices ; i++)
		{
			for (int j =0 ; j < vertices ; j++)
				cout << AM[i][j] << " ";

			cout << endl;
		}
	}
*/
	//this function clear the memory of the graph
	void clear ()
	{
		free (AL);
	//	free (AM);
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
			int n = vertices;

			//this is to initialise the Adjaceny matrix
		//		AM = (int **)malloc (n * sizeof (int *));
		//		for (int i = 0 ; i < n ; i++)
		//			AM[i] = (int *)malloc (n * sizeof (int));

			//to make all the values 0
		//		for (int i =0 ; i < n ; i++)
		//			for (int j =0 ; j < n ; j++)
		//				AM[i][j] = 0;

			//initialise the adjacency list
				AL = (Vector <int> *) malloc (n * sizeof (Vector <int>));

			//this initialise all the vectors
				for (int i =0 ; i < n ;i++)
					AL[i] = Vector <int>();

 				
			//reading the graph
 				for (int i =0 ; i<n ; i++)
				{
					int temp ;
					while (fscanf (file , "%d",&temp) == 1 && temp != -1)
					{
						AL[i].push_back (temp);		//storing the value in the adjacency list
					//	AM[i][temp] = 1;			//storing the value in the adjacency matrix
					}
				}

			//closing the file
			fclose (file);
			return true;
		
	
	}
/*
//function reads the file from the Adjaceny matrix
bool Graph :: read_Graph_AM (char filename[])
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
	
		fscanf (file,"%d",&vertices);
		int n = vertices;

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
					fscanf(file , "%d",&x);
					AM[i][j] = x;			//storing the value in the adjacency matrix

					if (x == 1)
					AL[i].push_back(j);		//stroing the value in the adjacency list
				}


		//closing the file
		fclose (file);
		return true;
}
			
*/
