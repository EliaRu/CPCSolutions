/*
    L[i , j] =
        L[i - 1, j - ] + 1 if str1[i] == str2[j]
        ( it has found a character that belongs to both of them )
        max( L[i - 1, j], L[i, j - ] ) otherwise
        ( the best choice between advancing by one character
        in the first string or by one in the second one )
    Since it must fill the whole table the program takes O( n * m)
    Reference: professor's notes
 */
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main( )
{
    int noTests;
    cin >> noTests;
    while( noTests-- ) {
        int size1, size2;
        cin >> size1 >> size2;
        string str1;
        string str2;
        getline( cin, str1 );
        getline( cin, str1 );
        getline( cin, str2 );
        str1.insert( 0, 1, ' ' );
        str2.insert( 0, 1, ' ' );
        vector<int> table( ( size1 + 1 ) * ( size2 + 1 ) );
        for( int j = 0; j < size2 + 1; j++ ) {
            table[j] = 0;
        }
        for( int i = 0; i < size1 + 1; i++ ) {
            table[i * ( size2 + 1 )] = 0;
        }
        for( int i = 1; i < size1 + 1; i++ ) {
            for( int j = 1; j < size2 + 1; j++ ) {
                if( str1[i] == str2[j] ) {
                    table[i * ( size2 + 1 ) + j] =
                        table[( i - 1 ) * ( size2 + 1 ) + j - 1] + 1;
                } else {
                    table[i * ( size2 + 1 ) + j] = max( 
                        table[( i - 1 ) * ( size2 + 1 ) + j],
                        table[ i * ( size2 + 1 ) + j - 1] );
                }
            }
        }
        cout << table[( size1 + 1 ) * ( size2 + 1 ) - 1] << endl;
    }
}
