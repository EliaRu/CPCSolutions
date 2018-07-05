/*
    The program how many strongly connected components
    there are in the graph. In each one we must put 
    a checkpost. The checkpost must be placed in one
    of the nodes that has the lowest cost among the others
    in the same component. Than taking the product of
    how many nodes in the same component have the lowest
    cost gives how many solution with the same cost we have.
    The program does a DFS to compute the finishing time of
    each node. Than starting from the node that has the highest
    finishing time it does another DFS on the transpose of 
    the graph. Each time this DFS starts over will visit a 
    different component. Each time it visits a component will
    search for the minimum cost and how many node have the 
    same value. So the program takes O( V + E ) time.
    Reference: none.
 */
#include <vector>
#include <iostream>
#include <algorithm>
#include <utility>

using namespace std;

struct VertexInfo {
    int color;
    int dTime;
    int fTime;
    unsigned int cost;
    vector<int> adj;
    vector<int> invertedAdj;
    VertexInfo( ) :
        color( 0 )
    { }
};

int time;

void Visit( vector<VertexInfo>& graph, int node ) {
    time++;
    graph[node].color = 1;
    graph[node].dTime = time;
    for( int i = 0; i < graph[node].adj.size( ); i++ ) {
        int next = graph[node].adj[i];
        if( graph[next].color == 0 ) {
            Visit( graph, next );
        }
    }
    time++;
    graph[node].color = 2;
    graph[node].fTime = time;
}

void DFS( vector<VertexInfo>& graph ) {
    time = 0;
    for( int i = 0; i < graph.size( ); i++ ) {
        if( graph[i].color == 0 ) {
            Visit( graph, i );
        }
    }
}

unsigned int minCost = -1;
int noMins = 0;

void InvertedVisit( vector<VertexInfo>& graph, int node ) {
    if( minCost == -1 || graph[node].cost < minCost ) {
        minCost = graph[node].cost;
        noMins = 1;
    } else if( minCost == graph[node].cost ) {
        noMins++;
    }
    graph[node].color = 1;
    for( int i = 0; i < graph[node].invertedAdj.size( ); i++ ) {
        int next = graph[node].invertedAdj[i];
        if( graph[next].color == 0 ) {
            InvertedVisit( graph, next );
        }
    }
    graph[node].color = 2;
}

pair<long long, long long> InvertedDFS( vector<VertexInfo>& graph, vector<pair<int, int>>& sortedGraph ) {
    long long wholeCost = 0;
    long long noPossibleWays = 1;
    for( int i = 0; i < graph.size( ); i++ ) {
        graph[i].color = 0;
    }
    for( int i = 0; i < graph.size( ); i++ ) {
        int node = sortedGraph[i].first;
        if( graph[node].color == 0 ) {
            minCost = -1;
            noMins = 0;
            InvertedVisit( graph, node );
            wholeCost += minCost;
            noPossibleWays = ( noPossibleWays * noMins ) % 1000000007;
        }
    }
    return make_pair( wholeCost, noPossibleWays ) ;
}

void FindStronglyConnectedComponents( vector<VertexInfo>& graph ) {
    DFS( graph );
    vector<pair<int, int>> sortedGraph( graph.size( ) );
    for( int i = 0; i < graph.size( ); i++ ) {
        sortedGraph[i] = make_pair( i, graph[i].fTime );
    }
    sort( sortedGraph.begin( ), sortedGraph.end( ),
        []( pair<int, int>& a, pair<int, int>& b ) {
            return a.second > b.second;
        }
    );
    
    auto res = InvertedDFS( graph, sortedGraph ); 
    cout << res.first << " " << res.second << endl;
}

int main( )
{
    int noJunction;
    cin >> noJunction;
    vector<VertexInfo> graph( noJunction );
    for( int i = 0; i < noJunction; i++ ) {
        cin >> graph[i].cost;
    }
    int noRoads;
    cin >> noRoads;
    for( int i = 0; i < noRoads; i++ ) {
        int u, v;
        cin >> u >> v;
        graph[u - 1].adj.push_back( v - 1 );
        graph[v - 1].invertedAdj.push_back( u - 1 );
    }
    FindStronglyConnectedComponents( graph );
    return 0;
}
