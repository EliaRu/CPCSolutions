/*
    The idea behind the solution is to find where the queries 
    overlap. In this way the program can assign to these regions
    the bigger elements in ordere to maximize the total sum.
    To do this the program uses an array that is initialized to
    zero. Then for each query ( l, r ) it adds a one at position
    l and it subtracts a one at position r + 1 if it is inside 
    the array. Then it computes the prefix sum. In this way
    at each position we have how many queries uses it.
    Then it assigns each element to each position depending on
    the values of the two arrays as previously said.
    This is done by ordering both of them in descending order and
    then sorting back to the original order.
    In this way the programs have in overlappingQueries the 
    permutation of the input elements that yields the best sum
    on that queries.
    The rest of the program is dedicated to find this sum.
    First it computes the prefix sum of the array and then
    adds up the value given by each query.
    The program takes O( nlogn + n + q ) time since it sorts
    three times an array of length n and scans multiple times
    the overlappingQueries and queries arrays.
    The program takes O( n + q ) space for storing the input
    elements and the queries.
    Reference: none.
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main( )
{
    int n;
    cin >> n;
    int q;
    cin >> q;
    vector<int> elements( n );
    for( int i = 0; i < n; i++ ) {
        int tmp;
        cin >> tmp;
        elements[i] = tmp;
    }
    vector<pair<int, int>> queries( q );
    for( int i = 0; i < q; i++ ) {
        int l, r;
        cin >> l;
        cin >> r;
        queries[i] = make_pair( l, r );
    }
    vector<pair<long long, int>> overlappingQueries( n + 1 );
    for( int i = 0; i < n + 1; i++ ) {
        overlappingQueries[i] = make_pair( 0, i );
    }
    for( int i = 0; i < q; i++ ) {
        int l = queries[i].first;
        int r = queries[i].second;
        overlappingQueries[l].first += 1;
        if( r + 1 < n + 1 ) {
            overlappingQueries[r + 1].first -= 1;
        }
    }
    for( int i = 1; i < n + 1; i++ ) {
        overlappingQueries[i].first += overlappingQueries[i - 1].first;
    }
    sort( elements.begin( ), elements.end( ),
        []( int a, int b ) {
            return a > b;
        }
    );
    sort( overlappingQueries.begin( ), overlappingQueries.end( ),
        []( pair< long long , int> a, pair< long long, int> b ) {
            return a.first > b.first;
        }
    );
    for( int i = 0; i < n; i++ ) {
        overlappingQueries[i].first = elements[i];
    }
    sort( overlappingQueries.begin( ), overlappingQueries.end( ),
        []( pair<long long, int> a, pair<long long, int> b ) {
            return a.second < b.second;
        }
    );
    for( int i = 1; i < n + 1; i++ ) {
        overlappingQueries[i].first += overlappingQueries[i - 1].first;
    }
    long long sum = 0;
    for( int i = 0; i < q; i++ ) {
        int l = queries[i].first;
        int r = queries[i].second;
        sum += overlappingQueries[r].first - overlappingQueries[l - 1].first;
    }
    cout << sum << endl;
}
