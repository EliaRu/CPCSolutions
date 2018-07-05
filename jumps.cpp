/*
    The program uses an approach based on dynamic-programming.
    Starting from the end of the input array it computes the
    number of jumps needed to get at the end. In general if
    the program is at position i it searches for the elemtent
    that needs the least number of jumps among the ones it can reach.
    The last element needs 0 jumps to get to the end. Moreover
    if an element is equal to 0 the program uses the value 200 as
    a placeholder for not being able to move forward. This cannot
    be mistaken as n <= 100 and so the maximum number of jumps is
    100.
    The program takes O( n^2 ) time since for each element it must 
    find a minimum on subarray that could be O( n ) long.
    The program takes O( n ) space since it store the input array
    and the jumps array.
    Reference: none
 */
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int main( )
{
    int noTests;
    cin >> noTests;
    while( noTests-- ) {
        int n;
        cin >>  n;
        vector<int> input( n );
        for( int i = 0; i < n; i++ ) {
            cin >> input[i];
        }
        vector<int> jumps( n );
        jumps[n - 1] = 0;
        for( int i = n - 2; i >= 0; i-- ) {
            if( input[i] == 0 ) {
                jumps[i] = 200;
            } else if( input[i] + i >= n ) { 
                jumps[i] = 1;
            } else {
                int min = *min_element( 
                    jumps.begin( ) + i + 1,
                    jumps.begin( ) + i + input[i] + 1 );
                if( min == 200 ) {
                    jumps[i] = 200;
                } else {
                    jumps[i] = min + 1;
                }
            }
        }
        if( jumps[0] == 200 ) {
            cout << -1 << endl;
        } else {
            cout << jumps[0] << endl;
        }
    }
}
