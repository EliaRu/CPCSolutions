/*
    The solution is divided into two parts: first it transform
    queries on a tree into queries on an array. Then it uses
    the Mo's algorithm to answer the queries efficiently.
    The first part  is done by a DFS that stores in the preordervisit
    array the tag of the nodes in the order that they are found
    for the first time and uses the time variable to compute
    the first and last position of its subtree in the array.
    The second part is done by substituting in the queries
    the node with the corrisponding positions computed by the DFS.
    Then these are ordered with respect to the Mo's algorithm
    criteria and answered one by one.
    To implement the add and remove operations the array counters
    and noEachColor are used. The latter contains at position i
    how many nodes in the range have color i, the former contains
    at position j how many colors have at least j nodes.
    When we add a node the number of nodes for that color is 
    incremented and the number of colors that have at least
    noEachColor[currentColor] is also incremented.
    When we remove a node first we decrement the number of color
    that has at least noEachColor[currentColor] then we decrement
    the number of nodes for the currentColor.
    The more expensive operation is Mo's algorithm so the program
    runs in O( ( n + q )sqrt( n ) ) time.
    Reference: Tutorial on Codeforces.
 */
#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

struct VertexInfo {
    int color;
    int tag;
    int state;
    int l;
    int r;
    vector<int> adj;
};

struct Query {
    int l;
    int r;
    int k;
    int pos;
};

int time;
int preordervisit[100010];
int i;

void Visit( vector<VertexInfo>& tree, int node )
{
    preordervisit[i] = node;
    i++;
    tree[node].l = time;
    tree[node].state = 1;
    for( int i = 0; i < tree[node].adj.size( ); i++ ) {
        int next = tree[node].adj[i];
        if( tree[next].state == 0 ) {
            time++;
            Visit( tree, next );
        }
    }
    tree[node].r = time;
    tree[node].state = 2;
}

void DFS( vector<VertexInfo>& tree )
{
    time = 0;
    for( int i = 0; i < tree.size( ); i++ ) {
        if( tree[i].state == 0 ) {
            Visit( tree, i );
        }
    }
}

int noEachColor[100010];
long long counters[100010];
long long results[100010];

int main( )
{
    ios::sync_with_stdio( false );
    cin.tie( nullptr );
    cout.tie( nullptr );
    int n, m;
    cin >> n >> m;
    vector<VertexInfo> tree( n );
    for( int i = 0; i < n; i++ ) {
        cin >> tree[i].color;
        tree[i].tag = i;
    }
    for( int i = 0; i < n - 1; i++ ) {
        int u, v;
        cin >> u >> v;
        tree[u - 1].adj.push_back( v - 1 );
        tree[v - 1].adj.push_back( u - 1 );
    }
    DFS( tree );
    vector<Query> queries( m );
    for( int i = 0; i < m; i++ ) {
        int node;
        cin >> node;
        queries[i].l = tree[node - 1].l;
        queries[i].r = tree[node - 1].r;
        cin >> queries[i].k;
        queries[i].pos = i;
    }
    sort( queries.begin( ), queries.end( ),
        [ n ]( Query& a, Query& b ) {
            if( ( a.l / ( int ) sqrt( n ) ) 
                == ( b.l / ( int ) sqrt( n ) ) ) {
                return a.r < b.r;
            } else {
                return a.l < b.l;
            }
        }
    );
    int currentL = 0;
    int currentR = 0;
    int node = preordervisit[currentL];
    int currentC = tree[node].color;
    noEachColor[currentC]++;
    counters[noEachColor[currentC]]++;
    for( int i = 0; i < m; i++ ) {
        int l = queries[i].l;
        int r = queries[i].r;
        int k = queries[i].k;
        int pos = queries[i].pos;
        while( currentL < l ) {
            //remove
            node = preordervisit[currentL];
            currentC = tree[node].color;
            counters[noEachColor[currentC]]--;
            noEachColor[currentC]--;
            currentL++;
        }
        while( currentL > l ) {
            //add
            currentL--;
            node = preordervisit[currentL];
            currentC = tree[node].color;
            noEachColor[currentC]++;
            counters[noEachColor[currentC]]++;
        }
        while( currentR < r ) {
            //add
            currentR++;
            node = preordervisit[currentR];
            currentC = tree[node].color;
            noEachColor[currentC]++;
            counters[noEachColor[currentC]]++;
        }
        while( currentR > r ) {
            //remove
            node = preordervisit[currentR];
            currentC = tree[node].color;
            counters[noEachColor[currentC]]--;
            noEachColor[currentC]--;
            currentR--;
        }
        results[pos] = counters[k];
    }
    for( int i = 0; i < m; i++ ) {
        cout << results[i] << endl;
    }
}
