/*
    The program scans the input matrix starting from
    the top. Everytime it encounters a cell that has
    an X that wasn't already discovered it starts to
    search for every Xs that are next to this one. This
    is done in a similar fashion a dfs operates on a 
    graph. When the procedure is done all the nearby
    Xs are found and marked as discovered and the 
    scan resumes.
    The program takes O( n * m ) time as the program
    scans once the input array and the dfs visits each
    X once.
    The program also takes O( n * m ) space to store the
    input matrix.
    Reference: none.
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstring>

using namespace std;

struct Vertex {
    int tag;
    int* adj;
};

int noXShapes = 0;

void dfs( vector<pair<int, int>>& matrix, int i, int j, int n, int m ) {
    matrix[ i * m + j ].second = 1;
    int offset = i - 1;
    if( offset >= 0 
        && matrix[offset * m + j].first == 1
        && matrix[offset * m + j].second == 0 ) {
        dfs( matrix, offset, j, n, m );
    }
    offset = j - 1;
    if( offset >= 0 
        && matrix[i * m + offset].first == 1
        && matrix[i * m + offset].second == 0 ) {
        dfs( matrix, i, offset, n, m );
    }
    offset = i + 1;
    if( offset < n 
        && matrix[offset * m + j].first == 1
        && matrix[offset * m + j].second == 0 ) {
        dfs( matrix, offset, j, n, m );
    }
    offset = j + 1;
    if( offset < m 
        && matrix[i * m + offset].first == 1
        && matrix[i * m + offset].second == 0 ) {
        dfs( matrix, i, offset, n, m );
    }
}

int main( ) 
{
    ios::sync_with_stdio( false );
    cin.tie( nullptr );
    int noTests;
    cin >> noTests;
    while( noTests-- ) {
        int n, m;
        cin >> n;
        cin >> m;
        vector<pair<int, int>> matrix( n * m, make_pair( 0, 0 ) );
        for( int i = 0; i < n * m; i++ ) {
            char c;
            cin >> c;
            if( c == ' ' || c == '\n' ) {
                cin >> c;
            }
            if( c == 'X' ) {
                matrix[i].first = 1;
            }
        }
        noXShapes = 0;
        for( int i = 0; i < n; i++ ) {
            for( int j = 0; j < m; j++ ) {
                auto el = matrix[i * m + j];
                if( el.first == 1 && el.second == 0 ) {
                    dfs( matrix, i, j, n, m );
                    noXShapes++;
                }
            }
        }
        cout << noXShapes << endl;
    }
}
