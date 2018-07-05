/*
    The program uses a DP strategy to solve this problem.
    When computing V[i, j] it takes the maximum between 
    the value it gets by choosing the i-th object and by not
    choosing the i-th object.
    More precisly 
        V[i, j] = max( 
            V[i - 1, j], 
            V[i - 1, j - weight[i]] + value[i] )
    The table is filled bottom-up and this takes O( n * W ) time.
    Reference: Professor's notes
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
        int noItems;
        cin >> noItems;
        int maxWeight;
        cin >> maxWeight;
        vector<int> values( noItems );
        vector<int> weights( noItems );
        for( int i = 0; i < noItems; i++ ) {
            cin >> values[i];
        }
        for( int i = 0; i < noItems; i++ ) {
            cin >> weights[i];
        }
        int n = noItems + 1;
        int m = maxWeight + 1;
        vector<int> table( n * m );
        for( int j = 0; j < m; j++ ) {
            table[j] = 0;
        }
        for( int i = 0; i < n; i++ ) {
            table[i * m ] = 0;
        }
        for( int i = 1; i < n; i++ ) {
            for( int j = 1; j < m; j++ ) {
                if( j < weights[i - 1] ) {
                    table[i * m + j] = table[( i - 1 ) * m + j];
                } else {
                    table[i * m + j] = max( 
                        table[( i - 1 ) * m + j],
                        table[( i - 1 ) * m + j - weights[i - 1]] + values[i - 1]
                    );
                }
            }
        }
        cout << table[ n * m - 1] << endl;
    }
}
