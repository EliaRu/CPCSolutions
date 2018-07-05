/*
    The solution implements a DP algorithm. The table is a
    matrix where each row i corresponds to the string 
    str1[0, i - 1] and each column j corresponds to the
    string str2[0, j - 1]. The first row and the first column
    correspond to the empty string.
    These one are computed first: edit[ i, 0] means we have
    to add i letter to the second string in order to match.
    The same reasoning can be applied to edit[ 0, j ].
    Then for edit[ i, j ] the program take the minimum value 
    between:
        edit[i - 1, j - 1] in case str1[i] == str2[j] ( no edits )
        or
        edit[i - 1, j - 1] + 1 otherwise ( 1 replacement )
        and
        edit[i - 1, j ] ( 1 insertion/deletion )
        and
        edit[i, j - 1] ( 1 insertion/deletion )
    The result is in edit[ p, q ]
    Since the program must compile the entire table it will take 
    O( p * q )
    Reference: none
 */
#include <vector>
#include <iostream>
#include <cassert>
#include <algorithm>

using namespace std;

int main( ) 
{
    int noTests;
    cin >> noTests;
    while( noTests-- ) {
        int p, q;
        cin >> p >> q;
        vector<char> str1( p + 1 );
        vector<char> str2( q + 1);
        for( int i = 1; i <= p; i++ ) {
            cin >> str1[i];
        }
        for( int i = 1; i <= q; i++ ) {
            cin >> str2[i];
        }
        vector<int> table( ( p + 1 ) * ( q + 1 ) );
        for( int i = 0; i <= q; i++ ) {
            table[i] = i;
        }
        for( int i = 0; i <= p; i++ ) {
            table[i * ( q + 1 )] = i;
        }
        for( int i = 1; i <= p; i++ ) {
            for( int j = 1; j <= q; j++ ) {
                int tmp;
                if( str1[i] == str2[j] ) {
                    tmp = table[( i - 1 ) * ( q + 1 ) + j - 1];
                } else {
                    //replace
                    tmp = table[( i - 1 ) * ( q + 1 ) + j - 1] + 1;
                }
                int min;
                min = std::min( 
                    table[( i - 1 ) * ( q + 1 ) + j] + 1,
                    table[i * ( q + 1 ) + j - 1] + 1 );
                min = std::min( min, tmp );
                table[i * ( q + 1 ) + j] = min;
            }
        }
        cout << table[( q + 1 ) * ( p + 1 ) - 1] << endl;
    }
}
