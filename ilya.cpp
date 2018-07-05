/*
    The program keeps an array to store which i 
    input[i] == input[i + 1] holds for.
    Then it computes the prefix sum over the array
    and it uses it to return the result.
    The program takes O( n ) time for computing 
    the prefix sum and takes O( n ) space for
    storing the input string and all the sums.
    Reference: none.
 */
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main( )
{
    string input;
    getline( cin, input );
    vector<int> prefixSum( input.size( ) + 1, 0 );
    for( int i = 0; i < input.size( ) - 1; i++ ) {
        if( input[i] == input[i + 1] ) {
            prefixSum[i + 1] = 1;
        }
    }
    for( int i = 1; i < prefixSum.size( ); i++ ) {
        prefixSum[i] += prefixSum[i - 1];
    }
    int noTests;
    cin >> noTests;
    while( noTests-- ) {
        int l, r;
        cin >> l;
        cin >> r;
        cout << prefixSum[r - 1] - prefixSum[l - 1] << endl;
    }
    return 0;
}
