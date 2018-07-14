#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class SegmentTree {
public:
    SegmentTree( int size ) :
    tree( 4 * size, 0 ),
    n( size )
    {
    }

    void update( long long value, int pos ) {
        update( value, pos, pos, 0, n - 1, 1 );
    }

    long long query( int pos ) {
        return query( 0, pos, 0, n - 1, 1 );
    }

private:
    int left( int node ) { return node << 1;}
    int right( int node ) { return ( node << 1 ) + 1; }

    long long build( vector<long long>& A, int L, int R, int node ) {
        if( L == R ) {
            tree[node] = A[L];
            return tree[node];
        } else {
            int mid = ( L + R ) / 2;
            long long leftSum = build( A, L, mid, left( node ) );
            long long rightSum = build( A, mid + 1, R, right( node ) );
            tree[node] = leftSum + rightSum;
            return tree[node];
        }
    }

    long long query( int L, int R, int i, int j, int node ) {
        if( R < i || L > j ) {
            return 0;
        } else if( L <= i && R >= j ) { 
            return tree[node];
        } else {
            int mid = ( i + j ) / 2;
            long long rightSum = query( L, R, i, mid, left( node ) );
            long long leftSum = query( L, R, mid + 1, j, right( node ) );
            return rightSum + leftSum;
        }
    }

    void update( long long value, int L, int R, int i, int j, int node ) {
        if( R < i || L > j ) {
            return;
        } else if( i == j ) {
            tree[node] += value;
        } else {
            int mid = ( i + j ) / 2;
            update( value, L, R, i, mid, left( node ) );
            update( value, L, R, mid + 1, j, right( node ) );
            tree[node] = tree[left( node )] + tree[right( node )];
        }
    }

    vector<long long> tree;
    int n;
};


int main( )
{
    ios::sync_with_stdio( false );
    cin.tie( nullptr );
    int n;
    cin >> n;
    vector<pair<int, int>> input( n );
    for( int i = 0; i < n; i++ ) {
        cin >> input[i].first;
        input[i].second = i;
    }

    sort( input.begin( ), input.end( ),
        []( pair< int, int >& a, pair<int, int>& b ) {
            if( a.first == b.first ) {
                return a.second < b.second;
            } else {
                return a.first < b.first;
            }
        }
    );
    
    vector<int> fromOne( n );
    int counter = 1;
    fromOne[input[0].second] = counter;
    for( int i = 1; i < n; i++ ) {
        if( input[i].first == input[i - 1].first ) {
            counter++;
        } else {
            counter = 1;
        }
        fromOne[input[i].second] = counter;
    }

    vector<int> fromN( n );
    counter = 1;
    fromN[input[n - 1].second] = counter;
    for( int i = n - 2; i >= 0; i-- ) {
        if( input[i].first == input[i + 1].first ) {
            counter++;
        } else {
            counter = 1;
        }
        fromN[input[i].second] = counter;
    }

    SegmentTree st( n );
    for( int i = 0; i < n; i++ ) {
        st.update( 1, fromN[i] );
    }

    long long sum = 0;
    for( int i = 0; i < n - 1; i++ ) {
        st.update( -1, fromN[i] );
        sum += st.query( fromOne[i] - 1 );
    }
    cout << sum << endl;

    return 0;
}
