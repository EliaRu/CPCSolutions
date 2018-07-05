/*
    Suppose the program has evaluated the m-th subarray and wants
    to evaluate the next one. The new element j is also the maximum
    elements of the m+1-th subarray. In this case it can "forget"
    what elements are to the left of j because for sure would not
    be the maxima of the next k subarrays, i.e. until j is in the 
    window. Now it goes into evaluating the next subarrays. Each
    time it can drop the elements before j but it has to check
    if the new elements are greater than j but also to store in 
    some way these in case the program doesn't find an element 
    greater than j. It stores these in a queue in order of arrival
    but, in a similar way it did with j, each time it adds a new 
    element i it can "forget" some of the elements to the left of
    this, in particular the ones that have a smaller value, because
    in each new subarray will be chosen always i instead of them.
    After adding the new element the program must also delete the
    element that is not in the current subarray anymore. This 
    may have been eliminated from the queue, but if not it would
    be the first one. So it checks if the first element of the
    queue doesn't belong to the subarray. If it does it is also
    the maximum of the subarray, beacuse is the greater of the 
    following elements in the queue for it is built.
    The program runs in O( n ) time because to delete k elements
    from the queue we must have had at least k insertion without
    deleting anythin so the cost is amoritized;
    The program takes O( n ) space for the array of elements,
    the queue may have at most size k.
    Reference: professor's hint about using the queue and his
    solution

 */

#include <iostream>
#include <vector>
#include <deque>

using namespace std;

void Erase( deque< pair<int, int>>& dq, int el ) 
{
    auto last = dq.end( ) - 1;
    auto it = last - 1;
    while( it >= dq.begin( ) && it->first < el ) {
        it--;
    }
    dq.erase( it + 1, last );
}

int main( )
{
    int noTests;
    cin >> noTests;
    for( int i = 0; i < noTests; i++ ) {
        int size;
        int k;
        cin >> size;
        cin >> k;

        vector<int> elements;
        for( int j = 0; j < size; j++ ) {
            int temp;
            cin >> temp;
            elements.push_back( temp );
        }

        deque<pair< int, int >> dq;
        for( int j = 0; j < k; j++ ) {
            dq.push_back( pair<int, int>( elements[j], j ) );
            Erase( dq, elements[j] );
        }
        cout << dq.front( ).first << " ";

        for( int j = k; j < size; j++ ) {
            dq.push_back( pair<int, int>( elements[j], j ) );
            Erase( dq, elements[j] );
            auto head = dq.front( );
            if( head.second <= j - k ) {
                dq.pop_front( );
                head = dq.front( );
            }
            cout << head.first << " ";
        }
        cout << endl;
    }
}
