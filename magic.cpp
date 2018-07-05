/*
    The program scans backwards the string and tries
    to match the characters accordingly.
 */
#include <iostream>
#include <string>

using namespace std;

int main( ) 
{
    string input;
    getline( cin, input );
    long long i = input.size( ) - 1;
    bool isMagic = true;
    while( i >= 0 ) {
        if( input[i] == '1' ) {
            i--;
        } else if( input[i] == '4' ) {
            i--;
            if( i >= 0 && input[i] == '1' ) {
                i--;
            } else if( i >= 0 && input [i] == '4' ) {
                i--;
                if( i >= 0 && input[i] == '1' ) {
                    i--;
                } else {
                    isMagic = false;
                    break;
                }
            } else {
                isMagic = false;
                break;
            }
        } else {
            isMagic = false;
            break;
        }
    }
    cout << ( ( isMagic ) ? "YES" : "NO" ) << endl;
}
