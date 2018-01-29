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

class Min_Heap
{
        private:

        int a[10000];
        int size;

        public:
        //
        Min_Heap (){size = 0;}

        Min_Heap (int * array , int n) {build (array , n);}

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
                int minimum = a[index];
                int replace = index;
                if (left (index ) != -1 && a[left (index)] < minimum){
                    minimum = a[left (index)];
                    replace = left (index);
                }
                if (right(index) != -1 && a[right (index)] < minimum){
                    minimum = a[right(index)];
                    replace = right (index);
                }

                //swap the min element
                if (minimum < a[index])
                {
                    int temp = a[index];
                    a[index] = a[replace];
                    a[replace] = temp;
                    Min_heapify (replace);
                }
            }
        }

        //this function takes the array and creates the heap
        void build (int * array , int n)
        {
            for (int i = 0 ; i < n ; i++ )
            {
                a[i+1] = array[i];
                size = n;
            }
            for (int i = size ; i >= 1 ; i--){
                Min_heapify (i);
            }
        }

        //insert the element into the heap
        void insert (int element)
        {
            size++;

            if (size >= 10000)
            {
                cout << "Maximum limit crossed \n";
                return;
            }

            //inserting the element
            a[size] = element;
            int posn = size;
            while (posn > 1 && a[posn] < a[posn/2])
            {
                int temp = a[posn];
                a[posn] = a[posn / 2];
                a[posn / 2] = temp;
                posn = posn/2;

            }
        }

        //returns the minimum element and pop it away
        int Min_pop ()
        {
            if (size == 0)
            {
                cout << "Heap is empty \n";
                return -1;
            }
            int result = a[1];
            a[1] = a[size];
            size--;
            if (size > 1)
            Min_heapify (1);
            return result;
        }

        //just return the min element
        int Find_Min ()
        {
            return a[1];
        }

        //print the array in the array form
        void print ()
        {
            for (int i = 1 ; i <= size ; i++)
                cout << a[i] << "   " ;
            cout << endl;
        }

        int ind (int i)
        {
            return a[i+1];
        }

        void destroy (){
            cout << "The heap is destroyed \n";
            size = 0;
        }

        void printSpace (int n)
		{
			for (int i = 0 ; i < n ; i++)
			cout << " ";
		}

		//print the heap in the tree form
		void printTree ()
		{
			int countSpace = 64;		//counts the space that is to be printed
			int i = 1;

			int level = 1;		//checks which level it is printing
			while (i <= size)
			{
				
				//prints the element
				for (int j = 0 ; j < level && i <= size ; j++)
				{
					if (j == 0)
					{	
						printSpace(countSpace);
						cout << a[i];
						i++;
					}
					else
					{
						printSpace(2 * countSpace);
						printf("%d", a[i]);
						i++;
					}
				}
				cout << endl << endl;
				level *= 2;
				countSpace /= 2;
				
			}
		}


};
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
    int n;
    Min_Heap myHeap = Min_Heap();		//declaring the heap
    do
    {
        print_Menu ();
        cin >> choice;

        switch (choice)
        {
        	//create the heap
                case(1): { cout << "Enter the number of the elements :";
                        int n;
                        cin >> n;
                        int array[n];
                        cout << "Enter the elements of the array\n";
                        for (int i = 0 ; i < n ; i++)
                            cin >> array[i];
                        myHeap.build (array , n);
                        break;
                    }
            //insert the element        
                case (2):{ cout << "Enter the value of the element : ";
                        int element;
                        cin >> element;
                        myHeap.insert (element);
                        break;
                    }
            //delete the element       
                case (3):{ cout << "The minimum element is " << myHeap.Min_pop() << endl;
                        break;
                    }
            //heap sort
                case (4):{
                            printf ("The sorted elements of the array\n");
                            int m = myHeap.getSize();
                            for (int i = 0 ; i < m ; i++)
                                cout << myHeap.Min_pop() << "   ";
                            cout <<endl;
                        break;
                    }
            //print in tree like form
                case(5):{ 
                		myHeap.printTree();
                        break;
                    }
            //finds the min element
                case(6):{ cout << "The minimum element is " << myHeap.Find_Min() << endl;
                        break;
                    }

            //prints the size of the heap
                case(7):{ cout << "The size of the heap is " << myHeap.getSize() << endl;
                        break;
                    }

            //destroy the heap
                case(8):{  myHeap.destroy();
                        break;
                    }
            //prints the heap in the array form        
                case(9):{myHeap.print();}
            //for exiting
                case(10):{break;}
                default : {cout << "Please enter appropriate choice \n";}
                break;
        }
    }while (choice != 10);

    return 0;
}
