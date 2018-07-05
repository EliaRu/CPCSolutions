/*
    The program implements Prim's algorithm using priority_queue
    from std.
 */
#include <vector>
#include <limits>
#include <queue>
#include <iostream>

using namespace std;

struct EdgeInfo {
    int u;
    int v;
    long long w;
};

struct VertexInfo {
    bool discovered;
    vector<EdgeInfo> adj;
    VertexInfo( ) : discovered( false ) { }
};

long long SpanningTree( vector<VertexInfo>& graph )
{
    long long cost = 0;
    auto cmp = []( EdgeInfo a, EdgeInfo b ) {
        return a.w > b.w;
    };

    priority_queue<
        EdgeInfo,
        vector<EdgeInfo>,
        decltype( cmp )> edges( cmp );
        for( int i = 0; i < graph[0].adj.size( ); i++ ) {
            edges.push( graph[0].adj[i] );
        }
        graph[0].discovered = true;
        while( !edges.empty( ) ) {
            EdgeInfo edge = edges.top( );
            edges.pop( );
            int u, v;
            u = edge.u;
            v = edge.v;
            if( !graph[v].discovered ) {
                graph[v].discovered = true;
                cost += edge.w;
                auto adj = graph[v].adj;
                for( int i = 0; i < adj.size( ); i++ ) {
                    edges.push( adj[i] );
                }
            }
    }
    return cost;
}


int main( )
{
    int n, m;
    cin >> n;
    cin >> m;
    vector<VertexInfo> graph( n );
    for( int r = 0; r < m; r++ ) {
        int i, j, k;
        cin >> i >> j >> k;
        EdgeInfo edge = { i - 1, j - 1, k };
        graph[i - 1].adj.push_back( edge );
        graph[j - 1].adj.push_back( { j - 1, i - 1, k } );
    }
    cout << SpanningTree( graph ) << endl;
}
