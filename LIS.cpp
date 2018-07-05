/*
    T[i] = max( T[j] : 0 <= j < i && input[i] > input[j] )
         = 1 if it doesn't esist such j
    and to find which value each time the program scans the array 
    from 0 to i. Finally it searches for the biggest T[i].
    In this way the program takes O( n^2 ) time.
    Reference: none
        
 */
#include <vector>
#include <iostream>
#include <algorithm>
#include <cassert>

using namespace std;

int main( )
{
    int noTests;
    cin >> noTests;
    while( noTests-- ) {
        int n;
        cin >> n;
        vector<int> input( n );
        for( int i = 0; i < n; i++ ) {
            cin >> input[i];
        }
        vector<int> table( n, 0 );
        if( n > 1 ) {
            table[0] = 1;
            int maxValue;
            for( int i = 1; i < n; i++ ) {
                maxValue = -1;
                for( int j = 0; j < i; j++ ) {
                    if( input[j] < input[i] && table[j] > maxValue ) {
                        maxValue = table[j];
                    }
                }
                table[i] = max( maxValue + 1, 1 );
            }
            maxValue = table[0];
            for( int i = 1; i < n; i++ ) {
                maxValue = ( table[i] > maxValue ) ? table[i] : maxValue;
            }
            cout << maxValue << endl;
        } else {
            cout << 0 << endl;
        }
    }
}
