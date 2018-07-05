/*
    The program takes the number in input as a string,
    inserts each digit in the array inputDigits then
    sorts the array in decreasing order.
    Because we want the largest even number, if possible,
    it searches the smallest even digit starting from the end.
    If the program can't find such a digit outputs the array 
    as is otherwise it erases the digit from
    the current position and pushes it to the end and 
    finally outputs the number.
    The program takes O( nlogn ) time becase it sorts the
    array with the std sort algorithm. In this case a sorting
    algorithm such as counting sort could have been used.
    Note that the erase member function doesn't take constant
    time but is O( n ) in the worst case.
    The program takes O( n ) space for storing the input in 
    two arrays.
    Reference: none
 */
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

int main( ) 
{
    int noTests;
    cin >> noTests;
    while( noTests-- ) {
        char *input = new char[1001];
        scanf( "%s", input );
        vector<char> inputDigits;
        int i = 0;
        while( i < 1000 && input[i] != '\0' ) {
            inputDigits.push_back( input[i] );
            i++;
        }
        sort( inputDigits.begin( ), inputDigits.end( ),
            []( char a, char b ) {
                if( a > b ) {
                    return true;
                } else {
                    return false;
                }
            }
        );
        i = inputDigits.size( ) - 1;
        bool found = false;
        while( i >= 0 ) {
            if( ( inputDigits[i] % 2 ) == 0 ) {
                found = true;
                break;
            }
            i--;
        }
        if( found ) {

            inputDigits.push_back( inputDigits[i] );
            inputDigits.erase( inputDigits.begin( ) + i );
            strncpy( input, inputDigits.data( ), inputDigits.size( ) ); 
            input[inputDigits.size( )] = '\0';
            printf( "%s\n", input );
        } else {
            strncpy( input, inputDigits.data( ), inputDigits.size( ) ); 
            input[inputDigits.size( )] = '\0';
            printf( "%s\n", input );
        }
        delete[] input;
    }
}
