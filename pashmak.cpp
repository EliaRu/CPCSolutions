#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class FenwickTree {
public:
    FenwickTree( int size ) : sz( size + 1 ), arr( size + 1, 0 ) { }

    int get( int pos ) {
        int sum = 0;
        for( int i = pos; i > 0; i -= i & ( -i ) ) {
            sum += arr[i];
        }
        return sum;
    }

    int get( int first, int last ) {
        return get( last ) - get( first );
    }

    void add( int value, int pos ) {
        for( int i = pos + 1; i < sz; i += i & ( -i ) ) {
            arr[i] += value;
        }
    }

private:
    vector<int> arr;
    int sz;
};

int main( ) 
{
    int n;
    cin >> n;
    vector<int> input( n );
    vector<int> aux( n );
    for( int i = 0; i < n; i++ ) {
        cin >> input[i];
        aux[i] = input[i];
    }

    sort( aux.begin( ), aux.end( ) );
    unique( aux.begin( ), aux.end( ) );
    for( int i = 0; i < n; i++ ) {
        input[i] = lower_bound( aux.begin( ), aux.end( ), input[i] ) - aux.begin( );
    }

    vector<int> counters( 1000001, 0 );
    vector<int> rem( 1000001, 0 );
    FenwickTree ft( 1000001 );
    for( int i = n - 1; i >= 0; i-- ) {
        counters[input[i]]++;
        ft.add( 1, counters[input[i]] );
        rem[i] = counters[input[i]];
    }
    counters = vector<int>( 1000001, 0 );
    long long res = 0;
    for( int i = 0; i < n; i++ ) {
        ft.add( -1 , rem[i] );
        counters[input[i]]++;
        res += ft.get( 1, counters[input[i]] );
    }
    cout << res << endl;
    return 0;
}
