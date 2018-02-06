//==========================================================//
//	Name  				- 	Arpit singh						//
//	Roll number 		- 	111601031						//
//	Date				-   Januray 6 , 2018				//
//	program Description - 	Implementation of the heap      //
//							also implements the heapsort	//
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


//including the self made libraries
#include "pairs.cpp"
#include "vector.cpp"
#include "stack.cpp"

template <typename T>
struct min_node
{
    T data;
    int pos;
};


template <typename T>
class Min_Heap
{
public:

        struct min_node <T> *a;
        int size;
        int *x;


        public:
        //
        Min_Heap (){
            a = (struct min_node <T> *)malloc (10000 * sizeof (struct min_node <T>));
            size = 0;

        }

        Min_Heap (T * array , int n) {
            a = (struct min_node <T> *)malloc (10000 * sizeof (struct min_node <T>));
            x = (int *)malloc (100000 * sizeof (int));
            build (array , n);

        }

        //return the left child if exist else -1
        int getSize () { return size;}
        int left (int index)
        {
                if (2 * index > size)return -1;
                else
                    return 2 * index;
        }

        //return the right child if exist else -1;
        int right (int index) {
            if (2 * index + 1 > size)
                return -1;
            else
                return 2 * index + 1;
        }

        //return the parent else return -1
        int parent (int index )
        {
            if (index > size)
                return -1;
            else
                return index/2;
        }

        //this function implements the min-heapify with the given min index
        void Min_heapify (int index)
        {


            if (index > size)
            {
                cout << "Index out of range : Min_heapify \n";
                return ;
            }

            else
            {

            	//finds the min element
                T minimum = a[index].data;
                int replace = index;
                if (left (index ) != -1 && a[left (index)].data < minimum){
                    minimum = a[left (index)].data;
                    replace = left (index);
                }
                if (right(index) != -1 && a[right (index)].data < minimum){
                    minimum = a[right(index)].data;
                    replace = right (index);
                }

                //swap the min element
                if (minimum < a[index].data)
                {
                    int temp2 = a[index].pos;
                    a[index].pos = a[replace].pos;
                    a[replace].pos = temp2;
                     

                    T temp = a[index].data;
                    a[index].data = a[replace].data;
                    a[replace].data = temp;

                    Min_heapify (replace);
                }
            }

        }

        //this function takes the array and creates the heap
        void build (T * array , int n)
        {
            for (int i = 0 ; i < n ; i++ )
            {
                a[i+1].data = array[i];
                x[array[i]] = i+1;
                a[i+1].pos = i+1;
                size = n;
            }
            for (int i = size ; i >= 1 ; i--){
                Min_heapify (i);


            }
        }

        void decrease_key (int posn)
        //this is going to decrease the key and then return the new index of the key
        {
            
            while (posn > 1 && a[posn].data < a[posn/2].data)
            {
                int temp2 = a[posn].pos;
                a[posn].pos = a[posn/2].pos;
                a[posn/2].pos = temp2;

                T temp = a[posn];
                a[posn] = a[posn / 2];
                a[posn / 2] = temp;
                posn = posn / 2;
            }



            

        }

        //insert the element into the heap
        void insert (T element)
        {
            size++;

            if (size >= 10000)
            {
                cout << "Maximum limit crossed \n";
                return;
            }

            //inserting the element
            a[size].data = element;
            a[size].pos = size;
            int posn = size;
            while (posn > 1 && a[posn].data < a[posn/2].data)
            {
                int temp = x[a[posn/2].data];
                a[size].pos = posn/2;
                a[x].pos = posn;


                T temp = a[posn].data;
                a[posn].data = a[posn / 2].data;
                a[posn / 2].data = temp;
                posn = posn/2;

            }
        }

        //returns the minimum element and pop it away
        T Min_pop ()
        {
            T result = a[1].data;
            a[1].data = a[size].data;

            a[1].pos = a[size].pos;

            size--;
            if (size > 1)
            Min_heapify (1);
            return result;
        }

        //just return the min element
        T Find_Min ()
        {
            return a[1].data;
        }

        T ind (int i)
        {
            return a[i+1].data;
        }

        void destroy (){
            cout << "The heap is destroyed \n";
            size = 0;
        }

};
//test bench


//for printing the menu
void print_Menu ()
{
   cout<<"Menu:"<<endl;
   cout<<"  1. Create New Heap"<<endl;
   cout<<"  2. Insert the element in the heap"<<endl;
   cout<<"  3. Delete the mininum element"<<endl;
   cout<<"  4. Heapsort [will also destroy the heap]"<<endl;
   cout<<"  5. Display in tree like form"<<endl;
   cout<<"  6. Display the minimum element"<<endl;
   cout<<"  7. Display the size of heap"<<endl;
   cout<<"  8. Delete the entire heap"<<endl;
   cout<<"  9. print the heap in array form" <<endl;
   cout<<"  10. Exit"<<endl;
   cout<<"  Enter your choice: ";

}

int main ()
{
    int choice;			//for selecting from the menu
    int n =0 ;
    Min_Heap <pairs> myHeap = Min_Heap <pairs>();		//declaring the heap
    do
    {


        print_Menu ();
        cin >> choice;

        switch (choice)
        {
        	//create the heap
                case(1): { cout << "Enter the number of the elements :";
                        
                        cin >> n;
                        pairs * array  = (pairs *) malloc (n * sizeof (pairs));
                        cout << "Enter the elements of the array\n";
                        for (int i = 0 ; i < n ; i++)
                        {
                            cin >> array[i].first ;
                            cin >> array[i].second ;
                        }
                        myHeap.build (array , n);
                        break;
                    }
            //insert the element
                case (2):{
                     cout << "Enter the value of the element : ";
                        pairs element = pairs (0 , 0);
                        int a , b;
                        cin >> a >> b;

                        element.first = a;
                        element.second = b;

                        myHeap.insert (element);

                        break;
                    }
            //delete the element
                case (3):{
                    pairs p1 = myHeap.Min_pop();
                    cout << "The minimum element is " <<p1.first << " " << p1.second  << endl;
                        break;
                    }
            //heap sort
                case (4):{
                            printf ("The sorted elements of the array\n");
                            int m = myHeap.getSize();
                            for (int i = 0 ; i < m ; i++)
                            {
                                pairs p1 = myHeap.Min_pop();
                                cout << p1.first << " " << p1.second << endl ;
                            }
                        break;
                    }
            //print in tree like form
                case(5):{
                		//myHeap.printTree();
                        break;
                    }
            //finds the min element
                case(6):{
                    pairs p1 = myHeap.Find_Min();
                    cout << "The minimum element is " << p1.first << " " << p1.second << endl;
                        break;
                    }

            //prints the size of the heap
                case(7):{ cout << "The size of the heap is " << myHeap.getSize() << endl;
                        break;
                    }

            //destroy the heap
                case(8):{//  myHeap.destroy();
                        break;
                    }
            //prints the heap in the array form
                case(9):{//myHeap.print();
                for (int i = 1 ; i <= myHeap.size ; i++)
                {
                    cout << myHeap.a[i].data.first << " " << myHeap.a[i].data.second << endl;
                }
                break;}
            //for exiting
                case(10):{break;}
                default : {cout << "Please enter appropriate choice \n";}
                break;
        }

        for (int i = 1 ; i <= myHeap.size ; i++)
            cout << myHeap.a[i].pos << " ";
        cout << endl;
        
    }while (choice != 10);

    return 0;
}
