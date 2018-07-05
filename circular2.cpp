/*
    The program checks whether the ranges of the updates
    and queries wrap around the end of the array or not.
    This is done by checking if L is greater than R or 
    not. In the first case the query ( or the update )
    is divided into two queries ( updates ) that don't
    wrap around the array.
    To solve the RMQ the program uses a segment tree
    with lazy updates as the segment tree by itself was
    not enough to pass the tests.
    Reference: none.
 */
#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <algorithm>

using namespace std;

using ll = long long;

class SegmentTree {
public:
    SegmentTree( const vector<ll>& A ) {
        vec = A;
        n = A.size( );
        st = vector<ll>( 4 * n, 0 );
        lazy = vector<ll>( 4 * n, 0 );
        build( 0, n - 1, 1 );
    }
    
    void update_range( ll L, ll R, ll inc ) {
        update_range( L, R, inc, 0, n - 1, 1 );
    }

    ll rmq( ll L, ll R ) {
        return rmq( L, R, 0, n - 1, 1 );
    }

private:
    ll left( ll node ) { return ( node << 1 ); }
    ll right( ll node ) { return ( node << 1 ) + 1; }

    void build( ll i, ll j, ll node ) {
        if( i == j ) {
            st[node] = vec[i];
        } else {
            ll mid = ( i + j ) / 2;
            build( i, mid, left( node ) );
            build( mid + 1, j, right( node ) );
            st[node] = min( st[left( node )], st[right( node )] );
        }
    }

    void update_range( ll L, ll R, ll inc, ll i, ll j, ll node ) {
        if( lazy[node] != 0 ) {
            st[node] += lazy[node];
            if( i != j ) {
                lazy[left( node )] += lazy[node];
                lazy[right( node )] += lazy[node];
            }
            lazy[node] = 0;
        }
        if( j < L || i > R ) {
            return;
        } else if( L <= i && R >= j ) {
            st[node] += inc;
            if( i != j ) {
                lazy[left( node )] += inc;
                lazy[right( node )] += inc;
            }
            return;
        } else if( i == j ) {
            st[node] += inc;
            return;
        } else {
            ll mid = ( i + j ) / 2;
            update_range( L, R, inc, i, mid, left( node ) );
            update_range( L, R, inc, mid + 1, j, right( node ) );
            st[node] = min( st[left( node )], st[right( node )] );
            return;
        }
    }

    ll rmq( ll L, ll R, ll i, ll j, ll node ) {
        if( lazy[node] != 0 ) {
            st[node] += lazy[node];
            if( i != j ) {
                lazy[left( node )] += lazy[node];
                lazy[right( node )] += lazy[node];
            }
            lazy[node] = 0;
        }
        if( j < L || i > R ) {
            return numeric_limits<ll>::max( );
        } else if( L <= i && R >= j ) { 
            return st[node];
        } else {
            ll mid = ( i + j ) / 2;
            ll minI = rmq( L, R, i, mid, left( node ) );
            ll minJ = rmq( L, R, mid + 1, j, right( node ) );
            return min( minI, minJ );
        }
    }

    vector<ll> st;
    vector<ll> lazy;
    vector<ll> vec;
    ll n;
};

int main( )
{
    ios::sync_with_stdio( false );
    cin.tie( NULL );
    long long n;
    cin >> n;
    vector<long long> input( n );
    for( long long i = 0; i < n; i++ ) {
        long long tmp;
        cin >> tmp;
        input[i] = tmp;
    }

    SegmentTree st( input );

    long long m;
    cin >> m;
    string query;
    query.reserve( 35 );
    char *queryStr = new char[35];
    getline( cin, query );

    vector<long long> q( 3 );
    while( m-- ) {
        getline( cin, query );
        strncpy( queryStr, query.c_str( ), query.size( ) + 1 );
        char *token = strtok( queryStr, " ");
        long long i = 0;
        while (token != NULL) {
            q[i] = atoll( token );
            i++;
            token = strtok(NULL, " ");
        }
        if( i == 2 ) {
            //rmq
            if( q[0] <= q[1] ) {
                cout << st.rmq( q[0], q[1] ) << "\n";
            } else if( q[0] > q[1] ) {
                long long minI = st.rmq( q[0], n - 1 );
                long long minJ = st.rmq( 0, q[1] );
                cout << ( ( minI < minJ ) ? minI : minJ ) << "\n";
            }
        } else if( i == 3 ) {
            //update
            if( q[0] <= q[1] ) {
                st.update_range( q[0], q[1], q[2] );
            } else if( q[0] > q[1] ) {
                st.update_range( q[0], n - 1, q[2] );
                st.update_range( 0, q[1], q[2]);
            }
        }
    }
    //
    delete[] queryStr;
    return 0;
}
