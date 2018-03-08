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
#include "Min_Heap.cpp"
#include "graph.cpp"
#include "union.cpp"

int main ()
{

    Graph G;

//asking for the file name
    char filename[100];
    cout << "Enter the name of the file : ";
    cin >> filename;


//reading the graph and checking for the error
    if (!G.read_Graph_edges (filename))
        return 0;


//putting all the edges in the min heap for sorting
    int n = G.vertices;
    Min_Heap <edges> myHeap = Min_Heap <edges>(G.E , G.m);

//creating the union set
    unionFind mySet = unionFind (n);
    cout << "The edges of the min spanning tree is " << endl;

//performing the krushkal algorithm
    int counter = 0;
    int totalEdgeWeight = 0;    
    while (counter < n -1)
    {
        edges temp = myHeap.Min_pop ();
        int u = temp.u;
        int v = temp.v;

        if (mySet.find(u) != mySet.find (v))
        {
            cout << u << " -- " << v << endl;
            mySet.Union (u , v);
            totalEdgeWeight += temp.weight;
            counter++;
        }
    }

    cout << "The total weight of the edges is " << totalEdgeWeight << endl;


    return 0;
}
