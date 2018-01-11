//============================================================//
//  Name                -   Arpit singh                       //
//  Roll number         -   111601031                         //                
//  Date                -   Januray 6 , 2018                  //
//  program Description -   This program takes input from the //
//                          binary file and produce output as //
//                          the text file which is in         //
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

    //setting file of n1 , difference and First (when it is going into the file)
    int n1 = 1;
    int difference = 1;
    bool First = false;
    int flag = 0;
    
    //setting the name of the file and declaring the file
        char filename1[100] , filename2[100];
        strcpy (filename1 , "check.bin");
        strcpy (filename2 , "check2.bin");
        FILE *file1 , *file2;
        

    while (1)
    {
        //if Flag == 1 it indicates that enters in the while loop for the second time
            if (flag == 1)
            {
                fclose (file1);
                fclose (file2);
                strcpy(filename1 , "check3.bin");
            }

        //setting flag1 and n1
            n1 = 1;
            flag = 1;
        
        //altering the value of the First ; to indicate which file to open in the "w" form
            if (First)
                First = false;
            else
                First = true;

        //opening the file
            if (First)
            {
                file1 = fopen (filename1 , "r");
                file2 = fopen (filename2 , "w");
            }
            else
            {
                file1 = fopen (filename2 , "r");
                file2 = fopen (filename1 , "w");
            }

        //checking wether the whole file is sorted or not
            fseek (file1 , difference * 4 , SEEK_SET);
            if (fgetc (file1) == EOF)
                break;


        while(1)
        {


            //setting all the variables
                bool complete1 = false;             //to indicate that the first pointer do not reach to the end of the file
                bool complete2 = false;
                bool read1 = true;                  //to indicate that first index need to be read
                bool read2 = true;
                int a , b;                          //variables to store the value
                int counter1 = 0;                   //counters to keep track of the number of the values that has been copied
                int counter2 = 0;
                int index1 = (n1 - 1);              //setting the indices
                int index2 = (n1 -1) + difference ;
            while (counter1 < difference && counter2 < difference)
            {

                //reading through the first pointer
                if (read1)
                {
                    fseek (file1 , index1 * 4 , SEEK_SET );
                    if (fread (&a , 4 , 1 , file1) == 1)
                        index1++;
                    else
                        complete1 = true;
                }

                //reading through the second index
                if (read2)
                {
                    fseek (file1 , index2 * 4 , SEEK_SET);
                    if (fread (&b , 4 , 1 , file1))
                        index2++;
                    else
                    {
                        complete2 = true;
                        break;
                    }
                }
                //comparing the values  and printing it in accoradance
                    if (a <= b)
                    {
                        fwrite (&a , 4 , 1 , file2);
                        read1 = true;
                        read2 = false;
                        counter1++;
                    }

                else
                {
                    fwrite (&b , 4 , 1 , file2);
                    read1 = false;
                    read2 = true;
                    counter2++;
                }

            }
            //reading the remaining values
                if (counter2 < difference)
                {
                    index2--;
                    do
                    {
                        if (complete2 == true)
                            break;

                        fwrite (&b , 4 , 1 , file2);
                        counter2++;
                        index2++;
                        fseek (file1 , index2 * 4 , SEEK_SET);
                    }while ((counter2 < difference) && fread (&b , 4 , 1 , file1));

                }
            //reading the remainging values of the second part
            if (counter1 < difference )
            {
                index1--;
                do
                {
                    if (complete1 == true)
                        break;


                    fwrite ( &a, 4 , 1 , file2);
                    counter1++;
                    index1++;
                    fseek (file1 , index1 * 4 , SEEK_SET);
                }while ((counter1 < difference) && fread (&a , 4 , 1 , file1));

                
            }

            //reading is completed then break
                if (complete1 || complete2)
                    break;


            //updating the value of n after each iteration
             n1 += 2 * difference;
        }
        //updatinf the value of the difference
            difference = 2 * difference;
    }


    //opening the file and printing it in the output file in the readable formate
        FILE *file;

        if (First == false)
            file =  fopen (filename2 , "r");
        else
            file = fopen (filename1 , "r");



    int c;
    file2 = fopen ("outAns.txt" , "w");
    while (fread (&c , 4 , 1 , file))
        fprintf(file2, "%d\n",c );

    //closing the files
        fclose (file);
        fclose (file2);
    return 0;
}

