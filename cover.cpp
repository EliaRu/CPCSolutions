/*
    Given a node the program computes the least
    number of nodes that must be choosen in order to 
    respect the problem constraint in the subtree rooted in
    the given node both in case when this is included and
    when it is not. To do this it computes the same for 
    its children recursively. Then the first value is
    equal to 1 ( the given node ) plus for each child
    the minimum between its two values. In fact we 
    must choose at least one vertex given an edge,
    so choosing both of them is a valid option.
    The second value is equal to the sum of the 
    first value of each of its children.
    The solution to the problem is the minimum
    of the two values of the root.
    Note that the problem statement does not
    specify a root so the program search for
    a node that has more than one adjacent node
    and points this root. The case of a root
    with only two nodes is taken care by the
    final if statement.
    Since the program visits each node exactly once
    it runs in O( n ).
    Reference: none

 */
#include <vector>
#include <iostream>
#include <cassert>
#include <algorithm>

using namespace std;

struct VertexInfo{
    int tag;
    int color;
    int maxIfChosen;
    int maxIfNotChosen;
    vector<int> adj;
    VertexInfo( ) : color( 0 ) { }
};

void Visit( vector<VertexInfo>& graph, int node ) {
    if( graph[node].adj.size( ) == 1 ) {
        graph[node].maxIfChosen = 1;
        graph[node].maxIfNotChosen = 0;
        graph[node].color = 2;
    } else {
        int notChosen = 0;
        int chosen = 1;
        graph[node].color = 1;
        for( int i = 0; i < graph[node].adj.size( ); i++ ) {
            int next = graph[node].adj[i];
            if( graph[next].color == 0 ) {
                Visit( graph, next );
            }
            notChosen += graph[next].maxIfChosen;
            chosen += min( graph[next].maxIfChosen, graph[next].maxIfNotChosen );
        }
        graph[node].maxIfChosen = chosen;
        graph[node].maxIfNotChosen = notChosen;
        graph[node].color = 2;
    }
}

int main( )
{
    ios::sync_with_stdio( false );
    cin.tie( nullptr );
    cout.tie( nullptr );
    int N;
    cin >> N;
    vector<VertexInfo> graph( N );
    for( int i = 0; i < N; i++ ) {
        graph[i].tag = i;
    }
    for( int i = 0; i < N - 1; i++ ) {
        int u, v;
        cin >> u >> v;
        graph[u - 1].adj.push_back( v - 1 );
        graph[v - 1].adj.push_back( u - 1 );
    }
    int node;
    bool none = true;
    for( int i = 0; i < N; i++ ) {
        if( graph[i].adj.size( ) > 1 ) {
            node = i;
            none = false;
        }
    }
    if( none ) {
        cout << 1 << endl;
    } else {
        Visit( graph, node );
        cout << min( graph[node].maxIfNotChosen, graph[node].maxIfChosen ) << endl;
    }
}
