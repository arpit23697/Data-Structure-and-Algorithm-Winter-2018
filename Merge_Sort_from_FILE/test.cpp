//============================================================//
//  Name                -   Arpit singh                       //
//  Roll number         -   111601031                         //                
//  Date                -   Januray 6 , 2018                  //
//  program Description -   This is the program that generates//
//                          the test file that contains lot of//
//                          numbers that needs to be in       //
//                          ascending order                   //
//============================================================//

//To include all the libraries of the c++
#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <cmath>
#include <cstdlib>
#include <cstdio>

using namespace std;

int main ()
{
        //asking for the name of the file
                cout << "Enter the name of the file\n";
                char filename[100];
                cin >> filename;

        //Generating the file (binary file) with lots of numbers
                FILE *file = fopen (filename , "w");
                for (int i =0 ; i < 10000 ; i++)
                {
                        int temp = rand();
                        fwrite (&temp , sizeof (temp) , 1 , file);
                }

        //closing the file        
                fclose (file);
        
        //opening the binary file in th readable form and a text file in "W" mode
                file = fopen (filename , "r");
                FILE *file2 = fopen ("out.txt" , "w");

        
        //writing the file in the text file
                int x ;
                while (fread(&x,  4 , 1 , file))	
                        fprintf( file2, "%d\n",x );
           
        return 0;
}
