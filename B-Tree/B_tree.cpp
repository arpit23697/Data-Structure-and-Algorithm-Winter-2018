//To include all the libraries of the c++
#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <cmath>

using namespace std;

#include "vector.cpp"
Vector <int> ans;

class nodeB
{
    public :
        int n;
        nodeB *child;
        int *key;
        bool leaf;
    nodeB ()
    {
        n = 0;
    }

    nodeB (int t)
    {
        child = (nodeB *) malloc ((2*t) * sizeof (nodeB));
        key = (int *) malloc ((2*t-1) * sizeof (int));
        leaf = false;           //by default it is going to be the leaf;
        n = 0;
    }

    nodeB (const nodeB &x)
    {
        n = x.n;
        key = x.key;
        child = x.child;        
        leaf = x.leaf;

    }
};

class B_Tree 
{
    public :
        nodeB root;
        int T = -1;

    public:
    void Create_tree() //this function just create the empty tree
    {
          nodeB x = nodeB(T);
          x.leaf = true;
          x.n = 0;
          root = x;
    }

    B_Tree (int x)
    {
          T = x;
          Create_tree();
    }

   

    //give the node x (which is non full ) and the integer i -th child (which is full) ; this function is going to split 
    //child and make necessary adjustments to the the node x;
    void B_Tree_split_child (nodeB &x , int i)
    {
        nodeB z = nodeB (T);            //new node is the z child
        nodeB y = x.child[i];               //child is in y                
        z.leaf = y.leaf;
        z.n = T-1;
        //copying the key into the z
        for (int j = 0 ; j < T-1 ; j++)
            z.key[j] = y.key[j+T];
        
        //copying the children into the z
        if (y.leaf == false)
        {
            for (int j = 0 ; j < T ; j++ )
            z.child[j] = y.child[j+T];
        }
        y.n = T-1;

        //shifting the child in the parent node
        for (int j = x.n ; j >= i+1 ; j--)
            x.child[j+1] = x.child[j];

        

        //shifting the keys in the parent node
        for (int j = x.n -1 ; j > i-1 ; j--)
        x.key[j+1] = x.key[j];
        x.key[i] = y.key[T-1];
        x.n = x.n+1;            //setting the new value of the n
        x.child[i] = y;
        x.child[i + 1] = z;
    }

    //this fucntion is for the special case which is taking the root case separately
    void B_Tree_insert (int k)
    {
        nodeB r = root;
        if (r.n == 2 * T - 1)
        {
            nodeB s = nodeB (T);
            s.leaf = false;
            s.n = 0;
            s.child[0] = r;
            root = s;
            B_Tree_split_child (root , 0);
            B_Tree_insert_NonFull (root , k);
        }
        else B_Tree_insert_NonFull (root , k );
    }

    //this function inserts the element in the B_tree whose node is not full
    void B_Tree_insert_NonFull ( nodeB &x , int k )
    {
        int i = x.n -1;
        //if x is a leaf then just add it
        if (x.leaf == true)
        {
            while (i >= 0 && k < x.key[i])
            {
                x.key[i+1] = x.key[i];
                i--;
            }
            x.key[i+1] = k;
            x.n = x.n+1;
        }

        //if the node is  not leaf
        else
        {
            while (i >= 0 && k < x.key[i])
            i--;
            i = i+1;
            if (x.child[i].n == 2*T - 1)
            {
                B_Tree_split_child (x , i);
                if (k > x.key[i]) 
                i++;
            } 
            B_Tree_insert_NonFull(x.child[i] , k);
        }
    }

    //searches the key in the B_tree
    bool B_tree_search (nodeB &x , int k)
    {
        int i = 0;
        while (i < x.n && k > x.key[i])
            i++;
        
        if (i < x.n && k == x.key[i])
        {
            ans.push_back (i);
            return true;
        }
        else if (x.leaf == true)
            return false;
        else 
        {   
            ans.push_back(i);
            B_tree_search (x.child[i] , k);
        }
    }

    void print_tree ( nodeB &x , int offset)
    {
        if (x.leaf == true)
        {
            for (int i= 0 ; i < x.n ; i++)
            {
                for (int j = 0 ; j < offset ; j++)
                cout << "\t";
                cout << x.key[i] << endl;

            }
        }
        if (x.leaf == false)
        {
            int i;
            for (i = 0 ; i < x.n ; i++)
            {
                print_tree (x.child[i] , offset + 1); 
                for (int j = 0 ; j < offset ; j++)
                cout << "\t";
                cout << x.key[i] << endl;
            }
            print_tree (x.child[i] , offset + 1);
        }
    }

    void print_in_ascending (nodeB &x)
    {
        if (x.leaf == true)
        {
            for (int i =0 ;  i < x.n ; i++)
            cout << x.key[i] << endl;
        }
        else
        {
            for (int i =0  ; i < x.n ; i++)
            {
                print_in_ascending (x.child[i]);
                cout << x.key[i] <<endl;
            }
            print_in_ascending (x.child[x.n]);
        }
    }

    void deleteKey (nodeB &x , int del)
    //node is x and the key to be deleted is del
    {
        int i= 0 ;
        while (i < x.n && del > x.key[i])
            i++;
        
        //we have found the key 
        if (i < x.n && del == x.key[i])
        {
            if (x.leaf == true)
            {
                for (int j = i ; j < x.n-1 ; j++)
                    x.key[j] = x.key[j+1];
                
                x.n = x.n -1;
            }
            else            //if the key to be deleted is present in the node but it is the internal node 
            {              //so we first delete the predecessor then replace it with the key
                if (x.child[i].n != T-1)
                {
                    nodeB z = x.child[i]; //this is to store the predecessor the predecessor
                    while (z.leaf == false)
                        z = z.child[z.n];        //this is to get the (n+1)th child
                
                    int predecessor = z.key[z.n-1];
                    deleteKey (x , predecessor);
                    x.key[i] = predecessor;
                    return;
                }
                else if (i < x.n && x.child[i+1].n != T-1)
                {
                    nodeB z = x.child[i+1];
                    while (z.leaf == false)
                        z = z.child[0];

                    int successor = z.key[0];
                    deleteKey (x , successor);
                    x.key[i] = successor;
                    return;
                }
            }

            
        }
        if (x.leaf == true)
        {
            //cout << "The delete key " << del << " is not present in the tree " << endl;
            return;
        }
        //the child to which we are descending is not minimal
        if (x.child[i].n != T-1)
        {
            deleteKey(x.child[i] , del);
            return ;
        }

        //means  the child to which we are descending is minimal
        if (x.child[i].n == T-1)
        {
            if (i > 0 && x.child[i-1].n != T-1)     //left child is not minimal then do the local rotation
            {
                nodeB center = x.child[i];
                nodeB lSibling = x.child[i-1];
                
                //shifting the keys of the center to the right
                for (int i = center.n - 1 ; i >= 0 ; i--)
                    center.key[i+1] = center.key[i];

                //shifting the children to the right if it is not a leaf
                if (center.leaf == false)
                {
                    for (int i = center.n ; i >= 0 ; i--)
                    center.child[i+1] = center.child[i];
                }
                center.n = center.n+1;
                //copying the key of the parent and the child to the parent 
                center.key[0] = x.key[i-1];
                if (center.leaf == false)
                    center.child[0] = lSibling.child[lSibling.n];

                //updating the x
                x.key[i-1] = lSibling.key[lSibling.n - 1];

                //updating the leftSibling
                lSibling.n = lSibling.n - 1;
                x.child[i-1] = lSibling;
                x.child[i] = center;
                deleteKey (x.child[i] , del);  
                return;   
            }
            else if (i < x.n && x.child[i+1].n != T-1)
            {
                nodeB rSibling = x.child[i+1];
                nodeB center = x.child[i];

                //taking the value of the left most key of the rSibling to the x
                center.key[center.n - 1] = x.key[i];
                x.key[i] = rSibling.key[0];
                center.n = center.n + 1;

                if (center.leaf == false)
                center.child[center.n] = rSibling.child[0];

                //now the remaining part is to update the rSibling by shifting left
                for (int i= 0 ; i < rSibling.n-1 ; i++)
                rSibling.key[i] = rSibling.key[i+1];

                //shifting the child if the node is not the leaf
                if (rSibling.leaf == false)
                {
                    for (int i= 0 ; i < rSibling.n ; i++)
                    rSibling.child[i] = rSibling.child[i+1];
                }
                rSibling.n = rSibling.n - 1;
                x.child[i] = center;
                x.child[i+1] = rSibling;
                deleteKey (x.child[i] , del);
                return;
                
            }
            //if both the immediate siblings are also minimal then just merge it with the appropriate sibling
            else
            {
                bool merge = false;
                if (i > 0)
                {
                    //merging with the left sibling
                    nodeB center = x.child[i];
                    nodeB lSibling = x.child[i-1];
                    
                    //copying the keys
                    lSibling.key[T-1] = x.key[i-1];
                    for (int j = 0 ; j < T-1 ; j++)
                    lSibling.key[T+j] = center.key[j];

                    if (center.leaf == false)
                    {
                        for (int j = 0 ; j < T ; j++)
                        lSibling.child[T+j] = lSibling.child[j];
                    }
                    lSibling.n = 2*T - 1;

                    //now updating the value of x
                        for (int j = i-1 ; j < x.n ; j++)
                        x.key[j] = x.key[j+1];

                        if (x.leaf == false)
                        {
                            for (int j = i ; j < x.n ; j++)
                            x.child[j] = x.child[j+1];
                        }
                        x.n = x.n - 1;
                        x.child[i-1] = lSibling;

                        //updating the root if necessary
                        if (x.n == 0)
                        root = x.child[i-1];

                        merge = true;       //indicating that the cells are merged
                       // cout << "=============================" << endl;
                       // print_tree(root, 0);
                       // cout << "=============================" << endl;
                        deleteKey (x , del);
                        return ;
                
                }
                if (merge == false && i < x.n)
                {
                    nodeB center = x.child[i+1];
                    nodeB lSibling = x.child[i];

                    lSibling.key[T - 1] = x.key[i];
                    for (int j = 0; j < T - 1; j++)
                        lSibling.key[T + j] = center.key[j];

                    if (center.leaf == false)
                    {
                        for (int j = 0; j < T; j++)
                            lSibling.child[T + j] = lSibling.child[j];
                    }
                    lSibling.n = 2 * T - 1;

                    //now updating the value of x
                    for (int j = i ; j < x.n; j++)
                        x.key[j] = x.key[j + 1];

                    if (x.leaf == false)
                    {
                        for (int j = i+1; j < x.n; j++)
                            x.child[j] = x.child[j + 1];
                    }
                    x.n = x.n - 1;
                    x.child[i] = lSibling;

                    //updating the root if necessary
                   if (x.n == 0)
                  root = x.child[i];

                    merge = true; //indicating that the cells are merged
                  //  cout << "=============================" << endl;
                  //  print_tree(root, 0);
                  //  cout << "=============================" << endl;
                    deleteKey(x, del);
                    return;
                }

            }
            
        }
    }


};

void printMenu ()
{
    cout << "Menu :" << endl;
    cout << "1.Build" << endl;
    cout << "2.Insert " << endl;
    cout << "3.Print Tree in the readable form " << endl;
    cout << "4.Delete " << endl;
    cout << "5.Search for the key " << endl; 
    cout  << "6.Exit " << endl;  
}
int main ()
{
    int choice;
    int n;
    B_Tree myTree = B_Tree (3);         //this is the creation of the B_tree with the min parameter to be set to 2;    
    do 
    {
        printMenu ();
        cout << "Enter your choice ";
        cin >> choice;
        switch (choice)
        {
            case(1):
            {
                cout << "Enter n :";
                cin >> n;

                cout << "Insert the element one by one " << endl;
                for (int i = 0; i < n; i++)
                {
                    int a;
                    cin >> a;
                    myTree.B_Tree_insert(a);
                   
                }
                break;
            }
            case(2):
            {
                int element;
                cout << "Enter the value of the inserting element " << endl;
                cin >> element;
                myTree.B_Tree_insert (element);
                break;
            }
            case(3):
            {
                cout << "=============================" << endl;
                myTree.print_tree(myTree.root, 0);
                cout << "=============================" << endl;
                break;
            }
            case(4):
            {
                int element;
                cout << "Enter the value of the element " << endl;
                cin >> element;
                myTree.deleteKey (myTree.root , element);
                break;
            }
            case(5):
            {
                int x;
                cout << "Enter the values you want to find" << endl;
                cin >> x;
                    
                ans = Vector<int>();

                    //printing the output
                if (myTree.B_tree_search(myTree.root, x))
                {
                    cout << "key found ; The path is " << endl;
                    cout << "root->  ";
                    for (struct node<int> *c = ans.head; c != ans.tale; c = c->next)
                    {
                        cout << "child " << c->data + 1 << " -> ";
                    }
                    cout << "index " << ans.tale->data + 1 << endl;
                }
                else
                {
                    cout << "The key not found " << endl;
                }
                break;
            }
            
            case(6) : {break; }
            default : {cout << "Enter the correct choice " << endl ;}
            break;

        }

    }while (choice != 6);
    return 0;
}
