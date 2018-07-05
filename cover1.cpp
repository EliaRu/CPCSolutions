#include <vector>
#include <deque>
#include <iostream>
#include <algorithm>

using namespace std;

struct VertexInfo{
    int color;
    int distance;
    vector<int> adj;
    VertexInfo( ) : color( 0 ) { }
};

void BFS( vector<VertexInfo>& tree, int node, vector<int>& arr ) {
    tree[node].color = 1;
    tree[node].distance = 0;
    arr[tree[node].distance]++;
    deque<int> q;
    q.push_back( node );
    while( !q.empty( ) ) {
        int current = q.front( );
        q.pop_front( );
        for( int i = 0; i < tree[current].adj.size( ); i++ ) {
            int next = tree[current].adj[i];
            if( tree[next].color == 0 ) {
                tree[next].color = 1;
                tree[next].distance = tree[current].distance + 1;
                arr[tree[next].distance]++;
                q.push_back( next );
            }
        }
        tree[current].color = 2;
    }
}

int Cover( int i, vector<int>& arr ) {
    if( i < arr.size( ) ) {
        return min( Cover( i + 1, arr ), arr[i] + Cover( i + 2, arr ) );
    } else {
        return 0;
    }
}

int main( )
{
    int n;
    cin >> n;
    vector<VertexInfo> tree( n );
    for( int i = 0; i < n - 1; i++ ) {
        int u, v;
        cin >> u >> v;
        tree[u - 1].adj.push_back( v - 1 );
        tree[v - 1].adj.push_back( u - 1 );
    }
    vector<int> noVertexPerLevel( n );
    BFS( tree, 0, noVertexPerLevel );
    int sum1 = 0;
    for( int i = 0; i < n; i += 2 ) {
        sum1 += noVertexPerLevel[i];
    }
    int sum2 = 0;
    for( int i = 1; i < n; i += 2 ) {
        sum2 += noVertexPerLevel[i];
    }
    cout << min( sum1, sum2 ) << endl;
}
