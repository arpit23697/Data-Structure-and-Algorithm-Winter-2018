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

    void print_tree ( nodeB &x , int nodes_printed)
    {
        cout << nodes_printed << ".  :  n = " << x.n << " --- ";
        for (int i= 0 ; i < x.n ; i++)
        cout << x.key[i] << " ";
        cout << endl;
        if (x.leaf == false)
        {
        for (int i = 0 ; i <= x.n ; i++)
        {
            nodes_printed++;
            print_tree (x.child[i] , nodes_printed); 
        }
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


};

int main ()
{
    B_Tree myTree = B_Tree (3);         //this is the creation of the B_tree with the min parameter to be set to 2;
    int n;
    cout << "Enter n :";
    cin >> n;

    cout << "Insert the element one by one " << endl;
    for (int i= 0 ; i < n ; i++)
    {
        int a;
        cin >> a;
        myTree.B_Tree_insert (a);
        myTree.print_tree (myTree.root , 1);
        //myTree.print_in_ascending (myTree.root);
    }

    int x;
    cout << "Enter the values you want to find" << endl;
    while (1) 
    {
        cin >> x;
        if (x == -1)
        break;
        ans = Vector <int> ();

        //printing the output 
        if (myTree.B_tree_search (myTree.root , x))
        {
            cout << "key found ; The path is " << endl;
            cout << "root->  ";
            for (struct node <int> *c = ans.head ; c != ans.tale ; c = c->next)
            {
                cout << "child " << c->data+1 << " -> ";
            }
            cout << "index " << ans.tale->data+1 << endl;
        }
        else 
        {
            cout << "The key not found " << endl;
        }
    }

    return 0;

}