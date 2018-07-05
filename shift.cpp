#include <vector>
#include <iostream>
#include <string>

using namespace std;

void ComputePrefix( string& pattern, vector<int>& pi )
{
    pi[0] = 0;
    int k = -1;
    for( int q = 1; q < pattern.size( ); q++ ) {
        while( k > -1 && pattern[k + 1] != pattern[q] ) {
            k = pi[k] - 1;
        }
        if( pattern[k + 1] == pattern[q] ) {
            k++;
        }
        pi[q] = k + 1;
    }
}

int KMP( string& text, string& pattern )
{
    int n = text.size( );
    int m = pattern.size( );
    vector<int> pi( m, 0 );
    ComputePrefix( pattern, pi );
    int q = -1;
    int maxShift;
    int maxLength = 0;
    int shift;
    int length = 0;
    for( int i = 0; i < n; i++ ) {
        while( q > -1 && pattern[q + 1] != text[i] ) {
            if( length > maxLength ) {
                maxShift = shift;
                maxLength = length;
            }
            q = pi[q] - 1;
            length = q + 1;
            shift = i - length;
        }
        if( pattern[q + 1] == text[i] ) {
            if( q == -1 ) {
                shift = i;
            }
            length++;
            q++;
        }
    }
    return maxShift;
}

int main( )
{
    int n;
    cin >> n;
    string A;
    for( int i = 0; i < n; i++ ) {
        char c;
        cin >> c;
        A.push_back( c );
    }
    string B;
    for( int i = 0; i < n; i++ ) {
        char c;
        cin >> c;
        B.push_back( c );
    }
    B.append( B );
    cout << KMP( B, A ) << endl;
}
