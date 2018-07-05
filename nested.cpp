/*
    Since we want to use a Fenwick tree over the right ends
    of the queries we must map these into a shorter range than
    10^9. This is done by sorting the query by the right ends
    and then replace them by their ranks.
    After that we sort the queries by their left ends in 
    descending order. When the program will process a query
    it will have already processed all the ones that may
    be nested inside them. In particular there will be
    as many queries as right ends between 0 and the current
    query right end and this information is maintained in
    the Fenwick tree. Then the tree is updated adding a one
    at position q.r.
    Since the program must sort the input array twice and 
    update a BIT the program takes O( nlogn ) time while
    it takes O( n ) space for storing the input sequence and 
    the BIT.
    Reference: professor's notes
 */
#include <algorithm>
#include <vector>
#include <iostream>
#include <tuple>

using namespace std;
using ll = long long;

class FenwickTree {
public:
    FenwickTree( size_t sz ) :
        tree( sz + 1, 0 ) { }

    void add( ll value, size_t pos ) {
        pos++;
        while( pos < tree.size( ) ) {
            tree[pos] += value;
            pos += ( pos & ( -pos ) );
        }
    }

    ll query( size_t pos ) {
        size_t i = pos + 1;
        ll sum = 0;
        while( i ) {
            sum += tree[i];
            i -= ( i & ( -i ) );
        }
        return sum;
    }

private:
    vector<ll> tree;
};

int main( ) 
{
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

    FenwickTree ft( n );
    vector<ll> res( n );
    for( int i = 0; i < n; i++ ) {
        ft.add( 1, get<1>( input[i] ) );
        res[get<2>( input[i] )] = ft.query( get<1>( input[i] ) ) - 1;
    }

    for( int i = 0; i < n; i++ ) {
        cout << res[i] << endl;
    }
}
