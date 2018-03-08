#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <cmath>

using namespace std;

class pairs
{
    public :
    int first;
    int second;

    pairs (int x , int y)
    {
        first = x;
        second = y;
    }

    pairs ( const pairs &p1)
    {
        first = p1.first;
        second = p1.second;
    }

    bool operator < (pairs const &p2)
    {
        if (first < p2.first)
            return true;
        else
            return false;
    }

    bool operator > (pairs const &p2)
    {
        if (first > p2.first)
            return true;
        else
            return false;
    }

};
//test bench
/*
int main ()
{
    pairs p1 = pairs (20 , 30);
    pairs p2 = pairs (30 , 40);

    pairs *arr = (pairs * )malloc (10 * sizeof (pairs));
    for (int i = 0 ; i < 10 ; i++)
    {
        arr[i].first = i;
        arr[i].second = i+1;
    }

    for (int i = 0 ; i < 10 ; i++)
    {
        cout << arr[i].first << " " << arr[i].second << endl;
    }

    cout << p1.first <<  " " << p1.second << endl;
    cout << p2.first << " " << p2.second << endl;
    if (p1 < p2)
        cout << "p1 is less than p2" << endl;

    return 0;
}
*/
