//==========================================================//
//	Name  				- 	Arpit singh						//
//	Roll number 		- 	111601031						//				
//	Date				-   Januray 6 , 2018				//
//	program Description - 	This is the checker program that//
//							verifies the output 			//
//==========================================================//


//To include all the libraries of the c++
#include <bits/stdc++.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <cmath>

int main ()
{
	//opening the file and checking for the error
		if (!freopen ("outAns.txt" , "r" , stdin))
		{
			printf("Error in opening the file\n");
			return 0;
		}
	//declaring the variable and checking wehter it is in the ascending order or not
		int a;
		int b;
		scanf ("%d",&a);
		while (scanf ("%d",&b) == 1)
		{
			if (a > b)
			{
				printf("The file is not in the ascending order\n");
				fclose (stdin);
				return 0;
			}
			a = b;

		}
	//printing the output
		printf("The file is in the ascending order\n");
		return 0;
}