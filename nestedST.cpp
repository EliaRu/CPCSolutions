#include <algorithm>
#include <vector>
#include <iostream>
#include <tuple>

using namespace std;
using ll = long long;

class SegmentTree {
public:
    SegmentTree( int size ) :
    tree( 4 * size, 0 ),
    n( size )
    {
    }

    void update( ll value, int pos ) {
        update( value, pos, pos, 0, n - 1, 1 );
    }

    ll query( int pos ) {
        return query( 0, pos, 0, n - 1, 1 );
    }

private:
    int left( int node ) { return node << 1;}
    int right( int node ) { return ( node << 1 ) + 1; }

    ll build( vector<ll>& A, int L, int R, int node ) {
        if( L == R ) {
            tree[node] = A[L];
            return tree[node];
        } else {
            int mid = ( L + R ) / 2;
            ll leftSum = build( A, L, mid, left( node ) );
            ll rightSum = build( A, mid + 1, R, right( node ) );
            tree[node] = leftSum + rightSum;
            return tree[node];
        }
    }

    ll query( int L, int R, int i, int j, int node ) {
        if( R < i || L > j ) {
            return 0;
        } else if( L <= i && R >= j ) { 
            return tree[node];
        } else {
            int mid = ( i + j ) / 2;
            ll rightSum = query( L, R, i, mid, left( node ) );
            ll leftSum = query( L, R, mid + 1, j, right( node ) );
            return rightSum + leftSum;
        }
    }

    void update( ll value, int L, int R, int i, int j, int node ) {
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

    vector<ll> tree;
    int n;
};

int main( ) 
{
    ios::sync_with_stdio( false );
    cin.tie( nullptr );
    cout.tie( nullptr );
    int n;
    cin >> n;
    vector<tuple<ll, ll, ll>> input( n );
    for( int i = 0; i < n; i++ ) {
        cin >> get<0>( input[i] );
        cin >> get<1>( input[i] );
        get<2>( input[i] ) = i;
    }

    sort( input.begin( ), input.end( ),
        []( tuple<ll, ll, ll >& a, tuple<ll, ll, ll>& b ) {
            return get<1>( a ) < get<1>( b );
        }
    );

    for( int i = 0; i < n; i++ ) {
        get<1>( input[i] ) = i;
    }

    sort( input.begin( ), input.end( ),
        []( tuple<ll, ll, ll >& a, tuple<ll, ll, ll>& b ) {
            return get<0>( a ) > get<0>( b );
        }
    );

    SegmentTree st( n );
    vector<ll> res( n );
    for( int i = 0; i < n; i++ ) {
        st.update( 1, get<1>( input[i] ) );
        res[get<2>( input[i] )] = st.query( get<1>( input[i] ) ) - 1;
    }

    for( int i = 0; i < n; i++ ) {
        cout << res[i] << endl;
    }
}
