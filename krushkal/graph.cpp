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

class edges
{
    public:
        int weight;
        int u , v;

    edges (int x , int y ,int z)
    {
        weight = x;
        u = y;
        v = z;
    }

    bool operator < (edges const &x)
    {
        if (weight < x.weight)
            return true;
        else
            return false;
    }

    bool operator > (edges const &x)
    {
        if (weight > x.weight)
            return true;
        else
            return false;
    }
};

class Graph
{
	public :
		edges *E;
		int vertices;
		int m;

	bool read_Graph_edges (char filename[]);
	//this function clear the memory of the graph
	void clear (){free (E);}
};

bool Graph :: read_Graph_edges (char filename[])
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
			fscanf (file , "%d", &m);
			int n = vertices;

            //initialise the array of the edges
			E = (edges *)malloc (m * sizeof (edges));

			//reading the graph
 				for (int i =0 ; i< m ; i++)
				{
					int a , b , w;
					fscanf (file , "%d %d %d" , &a , &b , &w);
					edges temp = edges (w , a , b);
                    E[i] = temp;
				}
			//closing the file
			fclose (file);
			return true;
}
