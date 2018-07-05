/*
    The program computes for each position of the input
    array the longest increasing subsequence and the 
    longest decreasing subsequence. The lenght of a bitonic 
    subsequence of a given position is computed as the sum
    of the LIS and the LDS minus one in that position.
    Finally it finds the position where the length is largest.
    The program uses DP to find the both the LIS and LDS, as
    the second one is the an increasing sequence but starting
    from the end. Each one takes O( n^2 ) time to complete so 
    the whole program runs in O( n^2 ) time.
    Reference:none
 */
#include <vector>
#include <iostream>

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
        vector<int> tableLis( n, 0 );
        tableLis[0] = 1;
        int maxValue;
        for( int i = 1; i < n; i++ ) {
            maxValue = -1;
            for( int j = 0; j < i; j++ ) {
                if( input[j] < input[i] && tableLis[j] > maxValue ) {
                    maxValue = tableLis[j];
                }
            }
            tableLis[i] = max( maxValue + 1, 1 );
        }
        vector<int> tableLds( n, 0 );
        tableLds[n - 1] = 1;
        for( int i = n - 2; i >= 0; i-- ) {
            maxValue = -1;
            for( int j = i + 1; j < n; j++ ) {
                if( input[j] < input[i] && tableLds[j] > maxValue ) {
                    maxValue = tableLds[j];
                }
            }
            tableLds[i] = max( maxValue + 1, 1 );
        }
        int max = tableLis[0] + tableLds[0] - 1;
        for( int i = 1; i < n; i++ ) {
            int currentVal = tableLis[i] + tableLds[i] - 1;
            max = ( currentVal > max ) ? currentVal : max;
        }
        cout << max << endl;
    }
}
