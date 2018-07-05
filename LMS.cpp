/*
    The program implements the recursive relation
    LMS( i + 1, n ) = input[i+1] @ LMS( i, n )
    if input[i] <= LMS( i, n ).front
    LMS( i + 1, n ) = LMS( i, n ) otherwise.
    It computes the lms in a bottom-up fashion
    in the first for loop.
    The program runs in O( n ) time since it
    scans once the array and once the LMS and
    takes O( n ) space for storing the input array.
    Reference:none.
 */
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main( ) 
{
    string input;
    getline( cin, input );
    vector<char> lms;
    lms.push_back( input.back( ) );
    for( int i = input.size( ) - 2; i >= 0; i-- ) {
        if( lms.back( ) <= input[i] ) {
            lms.push_back( input[i] );
        }
    }
    for( auto it = lms.rbegin( ); it != lms.rend( ); it++ ) {
        cout << *it;
    }
    cout << endl;
}
