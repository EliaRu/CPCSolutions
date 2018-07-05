/*
    The program doesn't generate all the pairs explicitly
    but it finds the k-th pair from the sorted input array.
    The idea behind it is based on first dividing k by n.
    The quotient of this division points out the first element
    of the pair while the remainder points out the second one.
    This solution is extended to take care of the possibility
    of repeated elements in the input array.
    First the program counts the number of occurrences of each
    distinct element in the input sequence.
    Then it starts subtracting from k the number of occurrences
    of element[i] * n. This is done to discard the pairs ( i, 0 ), 
    ..., ( i, 0 ), ( i, 1 ), ..., ( i, 1 ),( i, 2 ), ... ( i, n - 1 ).
    and is repeated until k is greater than zero. The program has found
    in this way the first element of the pair. Now it searches for
    the second one but in this case it has occurrences[i] times
    each pair. For this reason dividing k by occurrences[i] gives an
    index in the sequence ( i, 0 ), ( i, 1 ), ( i, 2 ), ( i, n - 1 ) 
    and it has found the index of the second element of the pair.
    The program takes O( n ) time because it scans the input array 
    once for computing the occurrences of the elements and it update
    the index k once for each elements of the array occurrences. 
    Moreover the size of this array is O( n ).
    The program takes O( n ) space for storing the input sequence and
    the occurrences.
    Reference: none
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>

using namespace std;

int main( ){
    uint64_t n;
    uint64_t k;
    cin >> n;
    cin >> k;
    vector<int64_t> elements( n );
    for( uint64_t i = 0; i < n; i++ ) {
        cin >> elements[i];
    }

    sort( elements.begin( ), elements.end( ) );

    vector<uint64_t> occurrences( n );
    int64_t current = elements[0];
    uint64_t j = 0;
    occurrences[j] = 1;
    for( uint64_t i = 1; i < n; i ++ ) {
        if( elements[i] == current ) {
            occurrences[j] += 1;
        } else {
            j++;
            current = elements[i];
            occurrences[j] = 1;
        }
    }

    bool found = false;
    uint64_t i = 0;
    uint64_t first = 0;
    uint64_t second;
    k--;
    while( !found && i < n ) {
        if( occurrences[i] * n > k ) {
            //cerca la coppia
            second = ( k / occurrences[i] );
            found = true;
        } else {
            first += occurrences[i];
            k -= occurrences[i] * n;
            i++;
        }
    }

    cout << elements[first] << " " 
        << elements[second] << endl;

    return 0;
}
