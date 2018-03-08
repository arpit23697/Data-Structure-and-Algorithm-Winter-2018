//==========================================================//
//	Name  				- 	Arpit singh						//
//	Roll number 		- 	111601031						//
//	Date				-   Januray 6 , 2018				//
//	program Description - 	Takes the graph , do DFS search //
//							and list all the edges			//
//==========================================================//


//note use g++ -std=c++11 for compiling the program
//chapter 3.9 , 3.16
//To include all the libraries of the c++
#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <cmath>

using namespace std;

class unionFind
{
    public:
        int *rank;
        int *parent;
        int n;

    unionFind (int size)
    {
        n = size;
        rank = (int *)malloc (n * sizeof(int));
        parent = (int *)malloc (n * sizeof(int));

        for (int i =0 ; i < n ; i++)
        {
            rank[i] = 0;
            parent[i] = i;
        }
    }

    int find (int u)
    {
        if (parent[u] == u)
            return u;

        int v = find(parent[u]);
        parent[u] = v;
        return v;
    }

    void Union (int u , int v)
    {
        int x = find(u);
        int y = find(v);

        if (x != y)
        {
            if (rank[x] == rank[y])
            {
                parent[y] = x;
                rank[x]++;
            }
            else if (rank[x] > rank[y])
                parent[y] = x;
            else
                parent[x] = y;
        }
    }
};
