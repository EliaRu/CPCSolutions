#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

struct VertexInfo{
    int color;
    int discovered;
    int completed;
    vector<int> adj;
    VertexInfo( ) : color( 0 ) { }
};

int Cover( int node, int parent, vector<VertexInfo>& tree, vector<int>& covers ) {
    //min( 1 + sum{on granchild}( Cover ), sum{on child}( Cover )}
    if( node >= tree.size( ) ) {
        return 0;
    } else if( covers[node] != -1 ) {
        return covers[node];
    } else if( tree[node].adj.size( ) <= 1 ) {
        covers[node] = 1;
        return 1;
    } else {
        int sumOnChildren = 0;
        for( int i = 0; i < tree[node].adj.size( ); i++ ) {
            int child = tree[node].adj[i];
            if( child != parent ) {
                sumOnChildren += Cover( 
                    child,
                    node,
                    tree,
                    covers );
            }
        }
        int sumOnGranChildren = 0;
        for( int i = 0; i < tree[node].adj.size( ); i++ ) {
            int child = tree[node].adj[i];
            if( child != parent ) {
                for( int j = 0; j < tree[child].adj.size( ); j++ ) {
                    int granchild = tree[child].adj[j];
                    if( granchild != node ) {
                        sumOnGranChildren += Cover(
                            granchild,
                            child,
                            tree,
                            covers );
                    }
                }
            }
        }
        covers[node] = min( 1 + sumOnGranChildren, sumOnChildren );
        return covers[node];
    }
}

int main( )
{
    ios::sync_with_stdio( false );
    int n;
    cin >> n;
    vector<VertexInfo> tree( n );
    vector<int> covers( n, -1 );
    for( int i = 0; i < n - 1; i++ ) {
        int u, v;
        cin >> u >> v;
        tree[u - 1].adj.push_back( v - 1 );
        tree[v - 1].adj.push_back( u - 1 );
    }
    cout << Cover( 0, -1, tree, covers ) << endl; 
}
