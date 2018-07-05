#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main( )
{
    string input;
    getline( cin, input );
    vector<char> hello = { 'o', 'l', 'l', 'e', 'h' };
    for( int i = 0; i < input.size( ); i++ ) {
        if( input[i] == hello.back( ) ) {
            hello.pop_back( );
        }
    }
    cout << ( ( hello.empty( ) ) ? "YES" : "NO" ) << endl;
}
