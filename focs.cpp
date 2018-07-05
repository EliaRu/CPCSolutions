/*
    Given the input strings, the program compiles a graph with 
    a vertex for every letter and an egde ( u, v ) if:
    u = names[i-1][sp] and v = names[i][sp] for some i and sp
    and u and v are used to decide the lexographical order
    between the two strings ( i.e. if there aren't any characters
    before u and v that already impose a particular order ).
    This is done by the BuildGraph procedure. This procedure
    also verify that if one string is a prefix of another one
    this string must appear before the longer one.
    After this, the program makes a topological sorting of the
    graph and checks if the graph is a DAG at the same time. If
    it is not the program return "Impossible", as the dependecies
    between the characters have a loop, for example u->v->u so
    u must appear before v that in turn must appear before u in 
    the final order.
    If it is the topological order of the character give a correct 
    answer.
    The program runs in O( n ) time. The build graph procedure must
    look at each characater at most and these are n * 101.
    The result is a graph that has 26 nodes and n - 1 edges, one for 
    string minus the first one. For this reason the topological sort
    runs in O( 26 + n ) time.
    The program takes O( n ) space as it stores the input strings and 
    the graph.
    Reference: none.

 */
#include <vector>
#include <iostream>
#include <cstring>

using namespace std;

//0-white, 1-grey, 2-black
struct VertexInfo {
    char c;
    int color;
    int discovery;
    int completed;
    vector<char> adj;
    VertexInfo( ) {
        color = 0;
        discovery = -1;
        completed = -1;
    }
};

int GetPosition( char c ) {
    return ( int ) c - 97;
}

bool order = true;

void BuildGraph( 
    vector<VertexInfo>& graph,
    char** names,
    int L,
    int R,
    int sp ) 
{
    if( sp >= 101 ) {
        return;
    }
    int i = L + 1;
    while( i < R ) {
        if( names[i - 1][sp] == '\0' && names[i][sp] != '\0' 
            || names[i - 1][sp] == '\0' && names[i][sp] == '\0' ) {
            i++;
        } else if( names[i - 1][sp] != '\0' && names[i][sp] == '\0' ) {
            order = false;
            i++;
        } else if( names[i - 1][sp] != names[i][sp] ) {
            int j = GetPosition( names[i - 1][sp] );
            graph[j].adj.push_back( names[i][sp] );
            i++;
        } else {
            int j = i;
            while( j < R && names[j][sp] == names[i][sp] ) {
                j++;
            }
            BuildGraph( graph, names, i - 1, j, sp + 1 );
            i = j;
        }
    }
}

bool isDAG = true;
int time = 0;
vector<char> sortedGraph;

void DFSVisit( vector<VertexInfo>& graph, char s ) 
{
    time++;
    int node = GetPosition( s );
    graph[node].discovery = time;
    graph[node].color = 1;
    for( int i = 0; i < graph[node].adj.size( ); i++ ) {
        int next = graph[node].adj[i];
        int nextPos = GetPosition( next );
        if( graph[nextPos].color == 0 ) {
            DFSVisit( graph, next );
        } else if( graph[nextPos].color == 1 ) {
            isDAG = false;
        }
    }
    time++;
    graph[node].color = 2;
    graph[node].completed = time;
    sortedGraph.push_back( graph[node].c );
    
}

void DFS( vector<VertexInfo>& graph )
{
    time = 0;
    for( int i = 0; i < graph.size( ); i++ ) {
        if( graph[i].color == 0 ) {
            DFSVisit( graph, graph[i].c );
        }
    }
}

bool TopologicalSort( vector<VertexInfo>& graph ) {
    DFS( graph );
    if( isDAG && order ) {
        return true;
    } else {
        return false;
    }
}

int main( )
{
    ios::sync_with_stdio( false );
    cin.tie( nullptr );

    int noNames;
    cin >> noNames;
    char* names[100];
    memset( names, 0, sizeof( names ) );

    cin.ignore( 1, '\n' );
    for( int i = 0; i < noNames ; i++ ) {
        names[i] = new char[101];
        memset( names[i], '\0', sizeof( names[i] ) );
        cin.getline( names[i], 101 );
    }

    vector<VertexInfo> graph( 26 );
    for( int i = 0; i < 26; i++ ) {
        graph[i].c = ( int ) 'a' + i;
    }

    BuildGraph( graph, names, 0, noNames, 0 );

    if( TopologicalSort( graph ) ) {
        for( int i = 25; i >= 0; i-- ) {
            cout << sortedGraph[i] << "";
        }
        cout << endl;
    } else {
        cout << "Impossible" << endl;
    }
    
    return 0;
}
