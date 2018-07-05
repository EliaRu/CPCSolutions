/*
    Instead of adding the value to each position
    the program adds that value to the first element
    in the range and subtracts the same value to the first
    element outside the range.
    After all the updates are done it computes the prefix
    sums of the array and answer to each query.
    The program runs in O( m + n + q ) time where m is the number
    of updates, n is the size of the array and q is the number
    of queries.
    The program takes O( n ) space as it must store the array of
    the prefix sums.
    Reference: none.
 */
#include <iostream>
#include <vector>

using namespace std;

struct Update {
    int l;
    int r;
    int val;
};

int main( ) 
{
    ios::sync_with_stdio( false );
    int noTests;
    cin >> noTests;
    while( noTests-- ) {
        int n;
        int u;
        cin >> n;
        cin >> u;
        vector<long long> array( n, 0 );
        while( u-- ) {
            Update u;
            cin >> u.l;
            cin >> u.r;
            cin >> u.val;
            array[u.l] += u.val;
            if( u.r + 1 < n ) {
                array[u.r + 1] -= u.val;
            }
        }
        for( int i = 1; i < n; i++ ) {
            array[i] += array[i - 1];
        }
        int q;
        cin >> q;
        for( int i = 0; i < q; i++ ) {
            int j;
            cin >> j;
            cout << array[j] << endl;
        }
    }
}
