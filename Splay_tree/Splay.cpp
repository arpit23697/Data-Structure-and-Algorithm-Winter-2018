
//To include all the libraries of the c++
#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <cmath>

using namespace std;

//making the classes for the node
struct splayNode
{
    splayNode *left;
    splayNode *right;
    splayNode *parent;
    int key;
};

class splay_tree
{
    public:
    splayNode *root = NULL;
    int size = 0;

    splay_tree ()
    {
        root = NULL;
        size = 0;
    }

    void build (int *array , int n)
    {
        for (int i =0 ; i < n; i++)
        insert (root , array[i]);
    }

 
    //this will rotate the given node in the given way
    void rotate (splayNode * x )
    {
        if (x->parent == NULL )
            return ;

        //x is the left child of its parent
        if (x == x->parent->left)
        {
           splayNode * p = x->parent;       //p is the parent
           splayNode * g = p->parent;       //g is the grand parent
           if (g != NULL && p == g->left)
           {
               g->left = x;
               x->parent = g;
           } 
           else if (g!= NULL && p == g->right)
           {
               g->right = x;
               x->parent = g;
           }
           else
           {
               x->parent = g;
           }
           p->parent = x;
           if (x->right != NULL)
           x->right->parent = p;
           p->left = x->right;
           x->right = p;

           if (g == NULL)
           {
               root = x;
           }
        }
        //if x is the right child
        else
        {
            splayNode * p = x->parent;
            splayNode *g = p->parent;
            if (g!= NULL && p == g->left)
            {
                g->left = x;
                x->parent = g;
            }
            else if (g != NULL && p == g->right)
            {
                g->right = x;
                x->parent = g;
            }
            else
            {
                x->parent= g;
            }

            p->parent = x;
            if (x->left != NULL)
            x->left->parent = p;
            p->right = x->left;
            x->left = p;
            if (g == NULL)
            root = x;
        }
    }

    //now doing the splaying
    void splay (splayNode *head , splayNode *x )
    {
        if (x == NULL)
            return ;
        if (x->parent == NULL)
        return;

        //if the parent is the root of the tree
        if (x->parent == head)
        {
            rotate (x);
        }
        else
        {
            splayNode *p = x->parent;
            splayNode *g = p->parent;

            //doing the zig zig operation
            if (p == g->left && x == p->left)
            {
                rotate(p);
                rotate(x);
            }
            else if (p == g->right && x == p->right)
            {
                rotate(p);
                rotate(x);
            }
            else
            {
                rotate(x);
                rotate(x);
            }
            splay (head , x);
        }   
    }

    splayNode * search (splayNode *r , int value)
    {
        if (r == NULL || r->key == value)
            return r;
        if (value < r->key )
            return search (r->left , value);
        else 
            return search (r->right , value);
    }
    void insert (splayNode *r , int value)
    {

        if (r == NULL)
        {
            splayNode *temp = (splayNode *)malloc (sizeof (splayNode ));
            temp -> key = value;
            temp -> parent = NULL;
            temp -> right = NULL;
            temp -> left = NULL;
            r  = temp;
            root = r;
            size++;
        }
        else
        {
            if (value < r->key )
            {
                if (r->left == NULL)
                {
                    splayNode *temp = (splayNode *)malloc (sizeof (splayNode));
                    temp-> key = value;
                    temp->parent = r;
                    temp -> left = NULL;
                    temp -> right = NULL;
                    r->left = temp;
                    size++;
                    splay (root , temp);
                }
                else
                    insert (r->left , value);
            }
            else if (value > r->key )
            {
                if (r->right == NULL)
                {
                    splayNode *temp = (splayNode *)malloc (sizeof (splayNode));
                    temp -> key = value;
                    temp -> parent = r;
                    temp -> left = NULL;
                    temp -> right = NULL;
                    r->right = temp;
                    size++;
                    splay (root , temp);
                }
                else
                    insert (r->right , value);
            }
            //splaying if the value is found
            else if (value == r->key)
            {
                cout << "The value is already present in the tree " << endl;
                splay (root , r);
            }
        }
    }

    splayNode *find_min (splayNode *r)
    {
        if (r->left == NULL)
            return r;
        else
            return find_min (r->left);
    }
    splayNode *find_max (splayNode *r)
    {
        if (r->right == NULL)
            return r;
        else
            return find_max (r->right);
    }
    //joins the two nodes s1 and s2
    //all the elements of s1 is smaller than the elements of s2
    void join (splayNode *s1 ,splayNode *s2)
    {
        if (s1 == NULL && s2 == NULL)
        return ;
        else if (s1 == NULL)
        {
           
            s2->parent = NULL;
            root = s2;
            return;
        }
        else if (s2 == NULL)
        {
            
            s1->parent = NULL;
            root = s1;
            return;
        }
        splay (s1 , find_max (s1) );
        s1->parent = NULL;
        s1->right = s2;
        s2->parent = s1;
        root = s1;
    }

    //prints the inorder order
    void inorder(splayNode *r)
    {
        if (r == NULL)
            return;
        inorder(r->left);
        cout << r->key << endl;
        inorder(r->right);
    }

    //prints the preorder
    void preorder(splayNode *r)
    {
        if (r == NULL)
            return;
        cout << r->key << endl;
        preorder(r->left);
        preorder(r->right);
    }

    //prints the postorder
    void postorder(splayNode *r)
    {
        if (r == NULL)
            return;
        postorder(r->left);
        postorder(r->right);
        cout << r->key << endl;
    }

    //finding the inorder successor
    splayNode *find_inorder_successor(splayNode *r)
    {
        if (r->right != NULL)
            return find_min(r->right);
        else
        {
            splayNode *current = r;
            splayNode *parent = r->parent;
            while (parent != NULL && current == parent->right)
            {
                current = parent;
                parent = current->parent;
            }
            return parent;
        }
    }

    splayNode *find_inorder_predecessor(splayNode *r)
    {
        if (r == NULL)
            return r;
        if (r->left != NULL)
            return find_max(r->left);
        else
        {
            splayNode *current = r;
            splayNode *parent = r->parent;
            while (parent != NULL && current == parent->left)
            {
                current = parent;
                parent = current->parent;
            }
            return parent;
        }
    }

    void deleteNode (splayNode *r , int key)
    {
        if (r == NULL)
        return ;
        size--;
        splay(r , search (r , key) );
        printTree(root , 0);
        join (root->left , root->right);
    }

    void destroy()
    {
        int n = size;
        for (int i = 0; i < n; i++)
            deleteNode(root , root->key);
    }
    //this will print the tree
    void printTree(splayNode *r, int offset)
    {
        if (r == NULL)
        {
            cout << "No tree" << endl;
            return;
        }

        if (r->right != NULL)
            printTree(r->right, offset + 1);

        for (int i = 0; i < offset; i++)
            cout << "\t";
        cout << r->key << endl
             << endl;

        if (r->left != NULL)
            printTree(r->left, offset + 1);
    }
};

//for printing the menu
void print_Menu()
{
    cout << "Menu:" << endl;
    cout << "  1. Create New splayTree" << endl;
    cout << "  2. Search for the key " << endl;
    cout << "  3. Insert the key (it will avoid the duplictes)" << endl;
    cout << "  4. Find min key" << endl;
    cout << "  5. Inorder traversal" << endl;
    cout << "  6. Postorder traversal" << endl;
    cout << "  7. Find predecessor " << endl;
    cout << "  8. Deleter key" << endl;
    cout << "  9.Print tree " << endl;
    cout << "  10.Destroy the BST" << endl;
    cout << "  11. Exit" << endl;
    cout << "  Enter your choice: ";
}

int main()
{
    int choice; //for selecting from the menu
    int n;
    splay_tree myTree = splay_tree(); //declaring the heap
    do
    {
        print_Menu();
        cin >> choice;

        switch (choice)
        {
            //create the heap
        case (1):
        {
            cout << "Enter the number of the elements :";
            int n;
            cin >> n;
            int array[n];
            cout << "Enter the elements of the array\n";
            for (int i = 0; i < n; i++)
                cin >> array[i];
            myTree.build(array, n);
            break;
        }
            //insert the element
        case (2):
        {
            cout << "Enter the value of the element : ";
            int element;
            cin >> element;
            splayNode *ans = myTree.search(myTree.root, element);
            if (ans == NULL)
                cout << "The key is not found" << endl;
            else
                cout << "The key is found" << endl;
            break;
        }
            //delete the element
        case (3):
        {
            cout << "Enter the value of the element : ";
            int element;
            cin >> element;
            myTree.insert(myTree.root, element);
            
            break;
        }
            //heap sort
        case (4):
        {
            if (myTree.size == 0)
                cout << "The binary search is empty" << endl;

            splayNode *ans = myTree.find_min(myTree.root);
            cout << "The min element is " << ans->key << endl;
            cout << endl;
            break;
        }
            //print in tree like form
        case (5):
        {
            cout << "The inorder traversal" << endl;
            myTree.inorder(myTree.root);
            break;
        }
            //finds the min element
        case (6):
        {
            cout << "The postorder traversal" << endl;
            myTree.postorder(myTree.root);
            break;
        }

            //prints the size of the heap
        case (7):
        {
            cout << "Enter the value of the element : ";
            int element;
            cin >> element;
            splayNode *ans = myTree.search(myTree.root, element);
            if (ans == NULL)
                cout << "The element inserted is not present" << endl;
            else
            {
                splayNode *temp = myTree.find_inorder_predecessor(ans);
                if (temp != NULL)
                    cout << "The inorder predecessor is " << temp->key << endl;
                else
                    cout << "No inorder predecessor" << endl;
            }
            break;
        }

            //destroy the heap
        case (8):
        {
            cout << "Enter the value of the element : ";
            int element;
            cin >> element;
            myTree.deleteNode(myTree.root , element);
            break;
        }
            //prints the heap in the array form
        case (9):
        {
            myTree.printTree(myTree.root, 0);
            break;
        }
            //for exiting
        case (10):
        {
            myTree.destroy();
            break;
        }
        case (11):
        {
            break;
        }
        default:
        {
            cout << "Please enter appropriate choice \n";
        }
        break;
        }
    } while (choice != 11);

    return 0;
}
