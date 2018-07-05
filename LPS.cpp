/*
    The program uses a DP technique based on memoization.
    LPS[i, j] = 
        0 if i > j
        1 if i == j ( that character is a palindrome subsequence )
        2 + LPS[i - 1, j - 1]
        ( input[i] == input[j] so we may add input[i] at the 
        beginning of a palindrome subsequence obtained from
        input[i - 1, j - 1], input[j] at the end and still have
        a palindrome subsequence )
        max( LPS[i - 1, j], LPS[ i, j - 1] )
        ( the longest palindrome subsequence between discarding
        input[i] or input[j] )
    Since it must fill the whole table the program takes O( n^2 )
    time.
    Reference: professor's note
 */
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

int LPS( string& input, vector<int>& table, int n, int i, int j ) {
    if( i > n - 1 || j < 0  ) {
        return 0;
    } else if( table[i * n + j] != -1 ) {
        return table[i * n + j];
    } else {
        if( i > j ) {
            table[i * n + j] = 0;
        } else if( i == j ) {
            table[i * n + j] = 1;
        } else if( input[i] == input[j] ) {
            table[i * n + j] = 
                2 + LPS( input, table, n, i + 1, j - 1 );
        } else {
            table[i * n + j] = max( 
                LPS( input, table, n, i, j - 1 ),
                LPS( input, table, n, i + 1, j )
            );
        }
        return table[i * n + j];
    }
}

int main( )
{
    int noTests;
    cin >> noTests;
    string input;
    getline( cin, input );
    while( noTests-- ) {
        getline( cin, input );
        int n = input.size( );
        vector<int> table( n * n, -1 );
        cout << LPS( input, table, n, 0, n - 1 ) << endl;
    }
}
