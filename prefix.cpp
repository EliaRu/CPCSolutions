#include <vector>
#include <iostream>
#include <string>

using namespace std;

int main( )
{
    ios::sync_with_stdio( false );
    int noTests;
    cin >> noTests;
    string input;
    getline( cin, input );
    while( noTests-- ) {
        getline( cin, input );
        vector<int> pi( input.size( ), 0 );
        pi[0] = 0;
        int k = -1;
        for( int q = 1; q < input.size( ); q++ ) {
            while( k > -1 && input[k + 1] != input[q] ) {
                k = pi[k] - 1;
            }
            if( input[k + 1] == input[q] ) {
                k++;
            }
            pi[q] = k + 1;
        }
        cout << pi.back( ) << endl;
    }
}
