/*
    The program builds a graph where each vertex may be an 
    employee or a language. Each employee is linked to 
    each language that he knows. The graph is undirected.
    Then it performs a DFS on the graph starting from
    an employee. This will find every employee that he can
    communicate with and mark them as black. Every
    time the DFS must restart the program has found a 
    group of vertices that can communicate with each
    other but cannot do the same with the other nodes
    of the graph. Once all employees have been found the
    DFS will stop.
    Given noComponents groups, to let them communicate with
    every other node of the graph we have to build a tree
    on these groups with noComponents - 1 edges, so the 
    company must spend noComponents - 1 credits.
    Note in case nobody knows a language every node must learn a 
    new language and so the company must spend n credits.
    The program takes O( n + m + v ) time, where n is the number
    of employees and v is the sum for each employees of how many
    languages he knows. In fact first the program must parse the 
    input and this takes v time, then it must build the graph
    and perform a DFS, both of them takes O( n + m + v ) time. In total
    it takes O( n + m + v ).
    The program takes O( n + m + v ) space since it stores the
    whole graph.
    Reference: none
 */
#include <iostream>
#include <vector>

using namespace std;

struct VertexInfo{
    int discovered;
    int completed;
    int state; //0-white, 1-grey, 2-black
    vector<int> adj;
    VertexInfo( ) :
        discovered( 0 ),
        completed( 0 ),
        state( 0 ),
        adj( )
    { }
};

int noComponents = 0;
int time;
int n, m;

void Visit( vector<VertexInfo>& graph, int i ) {
    time++;
    graph[i].discovered = time;
    graph[i].state = 1;
    for( int j = 0; j < graph[i].adj.size( ); j++ ) {
        if( graph[graph[i].adj[j]].state == 0 ) {
            Visit( graph, graph[i].adj[j] );
        }
    }
    time++;
    graph[i].completed = time;
    graph[i].state = 2;
}

void DFS( vector<VertexInfo>& graph ) {
    time = 0;
    for( int i = 0; i < n; i++ ) {
        if( graph[i].state == 0 ) {
            Visit( graph, i );
            noComponents++;
        }
    }
}

int main( )
{
    ios::sync_with_stdio( false );
    cin >> n;
    cin >> m;
    vector<VertexInfo> graph( n + m );
    bool nobody = true;
    for( int i = 0; i < n; i++ ) {
        int noLang;
        cin >> noLang;
        for( int j = 0; j < noLang; j++ ) {
            int lang;
            if( lang != 0 ) nobody = false;
            cin >> lang;
            graph[i].adj.push_back( n + lang - 1 );
            graph[n + lang - 1].adj.push_back( i );
        }
    }
    if( nobody ) {
        cout << n << endl;
    } else {
        DFS( graph );
        cout << noComponents - 1 << endl;
    }
}
