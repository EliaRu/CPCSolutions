/*
    The program starts to rebuild the forest by the leaves.
    This may be recognized by the fact they have only one
    adjacent node. These are inserted in a queue and 
    extracted one by one.
    Each time the program makes a new edge between the leaf
    and the node given by its Sv value. Then the degree of this node
    and its Sv are updated and if the node has become a leaf is
    added to the queue.
    The program runs in O( n ) time since it must parse the input
    and find the edge that make up the forest that are at most n - 1.
    It also takes O( n ) space as it must store the input and the 
    edges.
    Reference: editiorial on Codeforces
 */
#include <vector>
#include <queue>
#include <iostream>
#include <utility>

using namespace std;

int main( )
{
    ios::sync_with_stdio( false );
    int n;
    cin >> n;
    vector<pair<int, int>> input( n );
    vector<pair<int, int>> res;
    queue<int> q;
    for( int i = 0; i < n; i++ ) {
        cin >> input[i].first;
        cin >> input[i].second;
        if( input[i].first == 1 ) {
            q.push( i );
        }
    }
    while( !q.empty( ) ) {
        int node = q.front( );
        q.pop( );
        if( input[node].first != 0 ) {
            input[node].first--;
            int next = input[node].second;
            input[node].second = 0;
            res.push_back( make_pair( node, next ) );
            input[next].first--;
            input[next].second ^= node;
            if( input[next].first == 1 ) {
                q.push( next );
            }
        }
    }
    cout << res.size( ) << endl;
    for( int i = 0; i < res.size( ); i++ ) {
        cout << res[i].first << " " << res[i].second << endl;
    }
    return 0;
}
