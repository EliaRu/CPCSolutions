/*
    If we think about the various animals as 
    vertices of a graph, we can assign at each
    edge a value: 1 if x can eat y, 0 if x and
    y share kind or -1 if y can eat x. In this
    way, if we want to find the kind of some 
    animal r, we start from a vertex v which
    we know the value of and follow a path from
    r and v. The sum of edges and the value fo v
    will tell us if v eats r, viceversa or share
    kind.
    However we have to build the graph first.
    We start by having as many vertices as animals.
    At first each vertex will be its own connected 
    component. For each connected component will have
    one node which will be used to compute the values
    of every other node in the component.
    To do this we will use the "quick union" algorithm.
    This is similar to the union-find DS based on the tree
    but instead of pointers it uses positions in the
    array input and the path compression algorithm also
    computes the sum of the values from its node to the
    root.
    Each time the program merges two connected components
    into one will choose one of the two "roots" as the new
    one and will compute the new value R( r, s ) bases on the fact 
    that R( r, s ) = R( x, y ) - R( x, r ) + R( y, s ) mod 3
    where r is the "root" of x, s, is the "root" of y and also
    the new root.
    Instead, when the program gets an information that involves
    two vertices in the same connected component it will check if
    this is coherent with the informations that already have, i.e.
    it will compute the value of the two against the same "root",
    find which eats which and check it against what the info 
    asserts.
    The program runs in O( m ) time, where m is the number of info.
    In fact in the worst case scenario the program invokes the
    find operation each query and the union-find disjoint sets
    based on forest and path compression runs in O( m * alpha( n ) )
    where m is the number of find, join, make_set operation
    and n is the number of make_set ones.
    Reference: solution on Quora.
 */
#include <iostream>

using namespace std;

int input[50000];
int dist[50000];

int find( int x ) {
    if( input[x] == x ) {
        return x;
    } else {
        int oldRoot = input[x];
        input[x] = find( input[x] );
        dist[x] = dist[oldRoot] + dist[x];
        return input[x];
    }
}

int main( )
{
    int noTests;
    cin >> noTests;
    while( noTests-- ) {
        int n, k;
        cin >> n >> k;
        for( int i = 0; i < n; i++ ) {
            input[i] = i;
            dist[i] = 0;
        }
        int noFalseInfo = 0;
        while( k-- ) {
            int op, x, y;
            cin >> op >> x >> y;
            if( x > n || y > n ) {
                noFalseInfo++;
            } else {
                x--, y--, op--;
                auto rootX = find( x );
                auto rootY = find( y );
                if( rootX == rootY ) {
                    int res = ( dist[x] - dist[y] ) % 3;
                    res = ( res + 3 ) % 3;
                    if( op != res ) {
                        noFalseInfo++;
                    }
                } else {
                    input[rootX] = rootY;
                    int tmp = ( dist[x] - dist[y] - op ) % 3;
                    dist[rootX] = ( tmp < 0 ) ? -tmp: 3 - tmp;
                }
            }
        cout << noFalseInfo << endl;
        }
    }
}
