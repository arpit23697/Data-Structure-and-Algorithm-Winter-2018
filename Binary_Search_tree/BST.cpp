
//To include all the libraries of the c++
#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <cmath>

using namespace std;

template <typename T> 
struct bst_node 
{
	struct bst_node *left;
	struct bst_node *right;
	struct bst_node *parent;
	T key; 
};

template <typename T>
class BST 
{
	public :
	bst_node <T>*root = NULL;
	int size = 0;

	BST ()
	{
		root = NULL;
		size = 0;
	}


	void build (T * array , int n)
	{
		for (int i = 0 ; i < n ; i++)
			insert (root , array[i]);
	}

	bst_node <T> * search (bst_node <T> * r , T key)
	{
		if (r == NULL || r->key == key)
			return r;
		if (key < r->key)
			return search (r->left , key );
		else 
			return search (r->right , key);
	}
	
	//this function inserts the node at the correct position
	void insert (bst_node<T> *r , T item)
	{
		size++;
		if (r == NULL)
		{
			bst_node <T> *temp = (bst_node <T> *) malloc (sizeof (bst_node <T>));
			temp -> key = item;
			temp -> left = NULL;
			temp -> right = NULL;
			temp -> parent = NULL;
			r = temp;
			root = r;

		}

		else 
		{
			if (item <= r->key)
			{
				if (r->left == NULL)
				{
					bst_node <T> *temp = (bst_node <T> *) malloc (sizeof (bst_node <T>));
					temp->key= item;
					temp->left = NULL;
					temp->right = NULL;
					temp->parent = r;
					r->left = temp;
				}
				else
				 insert (r->left , item);
			}
			else
			{	
				if (r->right == NULL)
				{
					bst_node <T> *temp = (bst_node <T> *)malloc (sizeof (bst_node <T>));
					temp -> key = item;
					temp -> left = NULL;
					temp -> right = NULL;
					temp -> parent = r;
					r->right = temp;
				}
				else
					insert (r->right , item);
			}
				
			
		}
	}

	//for finding the minimum
	bst_node <T> * find_min (bst_node <T> *r)
	{
		if (r->left == NULL)
			return r;
		else
			return find_min (r->left);
	}

	//returns the pointer to the max element
	bst_node <T> *find_max (bst_node <T> *r)
	{
		if (r->right == NULL)
			return r;
		else 
			return find_max (r->right);
	}

	//prints the inorder order
	void inorder (bst_node <T> *r)
	{
		if (r == NULL)
			return ;
		inorder (r->left);
		cout << r->key << endl;
		inorder (r->right);
	}

	//prints the preorder
	void preorder (bst_node <T> *r)
	{
		if (r == NULL)
			return;
		cout << r->key << endl;
		preorder (r->left);
		preorder (r->right);
	}

	//prints the postorder
	void postorder (bst_node <T> *r)
	{
		if (r == NULL)
			return;
		postorder (r->left);
		postorder (r->right);
		cout << r->key << endl;

	}

	//finding the inorder successor
	bst_node <T> * find_inorder_successor (bst_node <T> *r)
	{
		if (r ->right != NULL)
			return find_min (r->right);
		else
		{
			bst_node <T> *current = r;
			bst_node <T> *parent = r-> parent;
			while (parent != NULL && current == parent->right)
			{
				current = parent;
				parent = current -> parent;
			}
			return parent;
		}
	}

	bst_node <T> * find_inorder_predecessor (bst_node <T> *r)
	{
		if (r == NULL)
			return r;
		if (r->left != NULL)
			return find_max (r->left);
		else
		{
			bst_node <T> *current = r;
			bst_node <T> *parent = r->parent;
			while (parent != NULL && current == parent->left)
			{
				current = parent;
				parent = current -> parent;
			}
			return parent;
		}
	}

	void delete_node (bst_node <T> * r)
	{
		
		if (r == NULL)
			return ;
		size--;
		if (r->left == NULL && r->right == NULL)
		{
			bst_node <T> *p = r->parent;
			if (p == NULL)
			{
				root = NULL;
				free (r);
			}

			else
			{
				if (r == p->left)
					p->left = NULL;
				else
					p->right = NULL;

				free (r);
			}
		}
		

		else if (r->left == NULL && r->right != NULL)
		{
			if (r->parent == NULL)
			{
				r->right->parent = NULL ;
				root = r->right;
				free(r);
			}
			else if (r == r->parent->right)
			{
				r->parent->right = r->right;
				r->right->parent = r->parent;
				free (r);
			}
			else
			{
				r->parent->left = r->right;
				r->right->parent = r->parent;
				free(r);
			}
		}
		else if (r->left != NULL && r->right == NULL)
		{
			if (r->parent == NULL)
			{
				r->left->parent = NULL;
				root = r->left;
				free(r);
			}
			else if (r == r->parent->right)
			{
				r->parent->right = r->left;
				r->left->parent = r->parent;
				free(r);
			}
			else 
			{
				r->parent->left = r->left;
				r->left->parent = r->parent;
				free(r);
			}
		}
		else
		{
			bst_node <T> *x = find_inorder_successor (r);
			r->key = x->key;
			delete_node (x);
		}
	}

	void destroy ()
	{
		int n = size;
		for (int i = 0 ; i < n; i++)
			delete_node (root);
	}


	//this will print the tree
	void printTree (bst_node <T> *r , int offset)
	{
		if (r == NULL)
		{
			cout << "No tree" <<endl;
			return ;
		}

		if (r->right != NULL)
			printTree (r->right , offset + 1);

		for (int i =0  ; i < offset ; i++)
			cout << "\t";
		cout << r->key << endl << endl ;

		if (r->left != NULL)
			printTree (r->left , offset+1);

	}


};


//for printing the menu
void print_Menu ()
{
   cout<<"Menu:"<<endl;
   cout<<"  1. Create New BST"<<endl;
   cout<<"  2. Search for the key "<<endl;
   cout<<"  3. Insert the key (it will avoid the duplictes)"<<endl;
   cout<<"  4. Find min key"<<endl;
   cout<<"  5. Inorder traversal"<<endl;
   cout<<"  6. Postorder traversal"<<endl;
   cout<<"  7. Find predecessor "<<endl;
   cout<<"  8. Deleter key" <<endl;
   cout<<"  9.Print tree " << endl;
   cout<<"  10.Destroy the BST" << endl;
   cout<<"  11. Exit"<<endl;
   cout<<"  Enter your choice: ";

}

int main ()
{
    int choice;			//for selecting from the menu
    int n;
    BST <int> mySearchTree = BST <int>();		//declaring the heap
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
                        mySearchTree.build (array , n);
                        break;
                    }
            //insert the element        
                case (2):{ cout << "Enter the value of the element : ";
                        int element;
                        cin >> element;
                        bst_node <int > *ans = mySearchTree.search (mySearchTree.root , element);
                        if (ans == NULL)
                        	cout << "The key is not found" << endl;
                        else
                        	cout << "The key is found" << endl;
                        break;
                    }
            //delete the element       
                case (3):{ cout << "Enter the value of the element : ";
                        int element;
                        cin >> element;
                        bst_node <int > *ans = mySearchTree.search (mySearchTree.root , element);
                        if (ans == NULL)
                        	mySearchTree.insert (mySearchTree.root , element);
                        else
                        	cout << "The value is already presented in the BST" << endl;

                        break;
                    }
            //heap sort
                case (4):{
                			if (mySearchTree.size == 0)
                				cout << "The binary search is empty" << endl;

                			bst_node <int> *ans =  mySearchTree.find_min(mySearchTree.root);
                            cout << "The min element is " << ans -> key <<endl;                            cout <<endl;
                        break;
                    }
            //print in tree like form
                case(5):{ 
                		cout << "The inorder traversal" << endl;
                		mySearchTree.inorder(mySearchTree.root);
                        break;
                    }
            //finds the min element
                case(6):{ 
                		cout << "The postorder traversal" << endl;
                		mySearchTree.postorder(mySearchTree.root);
                        break;
                    }

            //prints the size of the heap
                case(7):{ cout << "Enter the value of the element : ";
                        int element;
                        cin >> element;
                        bst_node <int > *ans = mySearchTree.search (mySearchTree.root , element);
                        if (ans == NULL)
                        	cout << "The element inserted is not present" << endl;
                        else
                        {
                        	bst_node <int> *temp = mySearchTree.find_inorder_predecessor (ans);
                        	if (temp != NULL)
                        	cout << "The inorder predecessor is " << temp->key << endl;
                        	else
                        		cout << "No inorder predecessor" << endl;
                        }
                        break;
                    }


            //destroy the heap
                case(8):{  
                	cout << "Enter the value of the element : ";
                        int element;
                        cin >> element;
                        bst_node <int > *ans = mySearchTree.search (mySearchTree.root , element);
                        if (ans == NULL)
                        	cout << "The element is not present" << endl;
                        else
                        	mySearchTree.delete_node (ans);
                        break;
                    }
            //prints the heap in the array form        
                case(9):{mySearchTree.printTree(mySearchTree.root , 0);
                      break;}
            //for exiting
                case(10):
                {
                	mySearchTree.destroy();
                	break;
                }
                case(11):{break;}
                default : {cout << "Please enter appropriate choice \n";}
                break;
        }
    }while (choice != 11);

    return 0;
}
