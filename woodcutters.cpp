/*
    For each tree the program checks if it can be
    placed to the left by comparing the last position
    occupied by the previous tree and its height.
    If this cannot be done it checks if the tree can
    be place to the right in a similar way.
    The first tree can alway be placed to its left.
    This works since by choosing the left segment over
    the right one we have more chances to cut also the
    next tree. Also if we prevent a tree to be cut
    by cutting the previous one this won't affect the
    final number of trees that can be cut.
    Then the program scans once the array so it takes
    O( n ) time.
    Reference:none
 */
#include <vector>
#include <iostream>

using namespace std;

struct Tree {
    int position;
    int height;
};

int main( )
{
    int n;
    cin >> n;
    vector<Tree> road( n );
    for( int i = 0; i < n; i++ ) {
        cin >> road[i].position >> road[i].height;
    }
    int noCuttedTrees = 1;
    int lastUsedPosition = road[0].position;
    for( int i = 1; i < n; i++ ) {
        if( ( road[i].position - road[i].height ) > lastUsedPosition ) {
            noCuttedTrees++;
            lastUsedPosition = road[i].position;
        } else if( i + 1 >= n ) {
            noCuttedTrees++;
        } else if( ( road[i].position + road[i].height ) < road[i + 1].position ) {
            noCuttedTrees++;
            lastUsedPosition = road[i].position + road[i].height;
        } else {
            lastUsedPosition = road[i].position;
        }
    }
    cout << noCuttedTrees << endl;
}
