/*
    The program scans the input and tries to match
    each character of the string "hello" starting from
    the 'h' character. Time complexity O( n ).
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
    vector<char> hello = { 'o', 'l', 'l', 'e', 'h' };
    for( int i = 0; i < input.size( ); i++ ) {
        if( input[i] == hello.back( ) ) {
            hello.pop_back( );
        }
    }
    cout << ( ( hello.empty( ) ) ? "YES" : "NO" ) << endl;
}
