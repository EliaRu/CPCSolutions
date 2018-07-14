/*
    The program is divided into two parts: in the first one
    the values of f( 1, i, a[i] ) and f( j, n, a[j] ) are computed
    for all possible is and js and stored in two 
    separate arrays. 
    This is done by sorting the input array so the positions that
    have the same value will be next to each other and in asceding
    order. To compute f( 1, i, a[i] ) the program simply scans the
    array keeping track of how many elements with the same value
    has seen. Same thing for f( j, n, a[j] ) but starting from the
    bottom.
    In the second part the program computes for 
    how many pairs ( i, j ) f( 1, i, a[i] ) > f( j, n, a[j] ) holds.
    This is done by computing how many js has f( j, n, a[j] ) equal
    to k and store this information in an array at position k.
    Then the prefix sums of this array is computed so that at position
    k we have how many js has f( j, n, a[j] ) less or equal than k.
    Then starting from the position 0 the program updates the prefix
    sum removing the contribution from the current position, retrieves
    f( 1, i, a[i] ) and adds to the total the value stored in the
    prefix sum at position f( 1, i, a[i] ) - 1 ( that gives how many
    js has f( j, n, a[j] ) less than f( 1, i, a[i] ) ).
    The prefix sums are computed and updated with a Fenwick Tree so 
    the program takes O( nlogn ) time to sort the array and mantain
    the prefix sums. 
    The program takes O( n ) space since it must store the input and
    the Fenwick Tree.
    Reference: none.
    
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class FenwickTree {
public:
    FenwickTree( int size ) :
    elements( size + 1, 0 ),
    size( size + 1 ) { }

    void add( long long value, int pos ) {
        for( int i = pos + 1; i < size; i += i & ( -i ) ) {
            elements[i] += value;
        }
    }

    long long query( int pos ) {
        long long sum = 0;
        for( int i = pos + 1; i > 0; i -= i & ( -i ) ) {
            sum += elements[i];
        }
        return sum;
    }

private:
    vector<long long> elements;
    int size;
};

int main( )
{
    ios::sync_with_stdio( false );
    cin.tie( nullptr );
    int n;
    cin >> n;
    vector<pair<int, int>> input( n );
    for( int i = 0; i < n; i++ ) {
        cin >> input[i].first;
        input[i].second = i;
    }

    sort( input.begin( ), input.end( ),
        []( pair< int, int >& a, pair<int, int>& b ) {
            if( a.first == b.first ) {
                return a.second < b.second;
            } else {
                return a.first < b.first;
            }
        }
    );
    
    vector<int> fromOne( n );
    int counter = 1;
    fromOne[input[0].second] = counter;
    for( int i = 1; i < n; i++ ) {
        if( input[i].first == input[i - 1].first ) {
            counter++;
        } else {
            counter = 1;
        }
        fromOne[input[i].second] = counter;
    }

    vector<int> fromN( n );
    counter = 1;
    fromN[input[n - 1].second] = counter;
    for( int i = n - 2; i >= 0; i-- ) {
        if( input[i].first == input[i + 1].first ) {
            counter++;
        } else {
            counter = 1;
        }
        fromN[input[i].second] = counter;
    }

    FenwickTree ft( n );
    for( int i = 0; i < n; i++ ) {
        ft.add( 1, fromN[i] );
    }

    long long sum = 0;
    for( int i = 0; i < n - 1; i++ ) {
        ft.add( -1, fromN[i] );
        sum += ft.query( fromOne[i] - 1 );
    }
    cout << sum << endl;

    return 0;
}
