/*
    The program uses Mo's algorithm. The add and remove operations 
    simply update the frequency of the current element, the current
    range and its power.
    The program takes O( ( t + n )sqrt( n ) ) time due to the Mo's algorithm
    that is larger than the O( tlogt ) factor to sort the queries array.
    However the use of Mo's algorithm weren't enough to pass the test on the
    site. For this reason I've decided to allocate in static memory of
    the program the arrays that contain the elements, frequencies and results
    and give them a size that would be known at compile time equal to the 
    their maximum sizes based on the problem paramenters.
    Reference: codeforces.
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <cstdint>

using namespace std;

struct Query{
    int left;
    int right;
    int ogPosition;
    int64_t result;
};

int sqrtn;
vector<int> elements( 200000 );
vector<int64_t> frequencies( 1000001, 0 );
vector<int64_t> results( 200000 );

int main( )
{
    ios::sync_with_stdio( false );
    int n;
    cin >> n;
    int t;
    cin >> t;
    int max;
    int i = 0;

    for( int i = 0; i < n; i++ ) {
        int tmp;
        cin >> tmp;
        elements[i] = tmp;
    }
    vector<Query> queries( t );
    for( int i = 0; i < t; i++ ) {
        int tmpL;
        int tmpR;
        cin >> tmpL;
        cin >> tmpR;
        queries[i] = { tmpL - 1, tmpR - 1, i, 0 };
    }

    sqrtn = sqrt( n );
    sort( queries.begin( ), queries.end( ),
        []( Query a, Query b ) {
            if( ( a.left / sqrtn ) != ( b.left / sqrtn ) ) {
                return a.left < b.left;
            } else {
                return a.right < b.right;
            }
        }
    );

    int currentL = 0;
    int currentR = 0;
    int64_t fr = ++frequencies[elements[currentL]];
    int64_t power = fr * fr * elements[currentL];
    for( int i = 0; i < t; i++ ) {
        int l = queries[i].left;
        int r = queries[i].right;
        int pos = queries[i].ogPosition;
        while( currentL < l ) {
            //remove
            int el = elements[currentL];
            int64_t fr = frequencies[el];
            power -= ( 2*fr - 1 ) * el;
            frequencies[el]--;
            currentL++;
        }
        while( currentL > l ) {
            //add
            currentL--;
            int el = elements[currentL];
            int64_t fr = frequencies[el];
            power += ( 2*fr + 1 ) * el;
            frequencies[el]++;
        }
        while( currentR < r ) {
            //add
            currentR++;
            int el = elements[currentR];
            int64_t fr = frequencies[el];
            power += ( 2*fr + 1 ) * el;
            frequencies[el]++;
        }
        while( currentR > r ) {
            //remove
            int el = elements[currentR];
            int64_t fr = frequencies[el];
            power -= ( 2*fr - 1 ) * el;
            frequencies[el]--;
            currentR--;
        }
        results[pos] = power;
    }
    for( int i = 0; i < t; i++ ) {
        cout << results[i] << endl;
    }
}

