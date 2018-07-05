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
