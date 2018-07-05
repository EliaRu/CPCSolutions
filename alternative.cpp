/*
    By flipping a substring as descibed in the problem
    we can at most increment the longest alternating
    subsequence by two. If this subsequence is the entire
    atring we cannot do better. If there is a pair that
    has the same value we can flip the substring from the
    second one to the end and increment the length of the
    subsequence by one. If there are two pairs we can flip
    the substring between these two and have an increment
    of two. The program scans the screen to find which
    case may apply. So the program takes O( n ) time.
    Reference: none;
 */
#include <vector>
#include <iostream>

using namespace std;

int main( )
{
    int n;
    cin >> n;
    vector<char> input( n );
    for( int i = 0; i < n; i++ ) {
        cin >> input[i];
    }
    int increment = 0;
    for( int i = 0; i < n - 1; i++ ) {
        if( input[i] == input[i + 1] && increment < 2 ) {
            increment++;
        }
    }
    int length = 0;
    for( int i = 0; i < n - 1; i++ ) {
        if( input[i] != input[i + 1] ) {
            length++;
        }
    }
    cout << length + 1 + increment << endl;
}
