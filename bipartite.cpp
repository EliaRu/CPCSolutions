/*
    The function divides each node into two groups. Each one must
    contain only nodes that are linked by an edge. This is done by
    a BFS. Given a node in group A its adjacency list will be scaned
    and the group B will be assigned to each undiscovered node
    ( viceversa in case the node is in group B ). 
    Instead already discovered nodes will already have a group and
    these must be consistent. In case they are not the graph is not
    bipartite. If the BFS stops before 
    every node is found, a new BFS will start but the group
    assigned to the first node must be chosen to be the opposite
    of the group of one of the node that is linked to this one but has
    been already discovered.
    The program takes O( V + E ) since it executes a BFS on all the nodes
    and it takes O( V * V ) space as it stores the graph as a matrix.
    Reference: none.
 */

// C++ program to find out whether a given graph is Bipartite or not.
// It works for disconnected graph also.
#include <iostream>
using namespace std;
const int MAX = 100;
bool isBipartite(int G[][MAX],int V);
int main()
{
    int t;
	cin>>t;
	int g[MAX][MAX];
	while(t--)
	{
		memset(g,0,sizeof (g));
		int n;
		cin>>n;
	
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<n;j++)
			{
				cin>>g[i][j];
			}
		}
		
		cout<<isBipartite(g,n)<<endl;
	}
	return 0;
}

/*Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function is mentioned above.*/

/*The function takes an adjacency matrix representation of the graph (g)
and an integer(v) denoting the no of vertices as its arguments.
You are required to complete below method */
struct NodeInfo {
    int group;
    int explored;
    NodeInfo( ) {
        group = 0;
        explored = 0;
    }
};

#include <deque>

int incMod2( int i ) {
    return ( i + 1 ) % 2;
}

bool isBipartite(int G[][MAX],int V)
{
    NodeInfo nodes[16];
    deque<int> q;
    bool isBipartite = true;
    for( int i = 0; i < V; i++ ) {
        int j = 0;
        while( j < V ){
            if( G[i][j] == 1 && nodes[j].explored == 1 ) {
                break;
            }
            j++;
        }
        if( j < V ) {
            nodes[i].group = incMod2( nodes[j].group );
        }
        q.push_back( i );
        while( !q.empty( ) ) {
            int node = q.front( );
            q.pop_front( );
            if( nodes[node].explored == 0 ) {
                nodes[node].explored = 1;
                for( int j = 0; j < V; j++ ) {
                    if( G[node][j] == 1 ) {
                        if( nodes[j].explored == 1 ) {
                            if( nodes[node].group == nodes[j].group ) {
                                isBipartite = false;
                            }
                        } else {
                            nodes[j].group = incMod2( nodes[node].group );
                            q.push_back( j );
                        }
                    }
                }
            }
        }
    }
    return isBipartite;
}
