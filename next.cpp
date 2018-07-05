/*
    The program scans the array of the elements and
    inserts each one in a queue together with its
    position. Then it erases from the queue
    each element that has a value smaller than the 
    one added ( j ). For all these j will be 
    the next greater element in the array because not
    only it is greater than them but also is the first
    one since they are still in the queue.
    The program keeps an auxiliary array in which inserts
    the value j in the corrisponding position in the original
    array by the erased element.
    After scanning all the elements the one that remain in
    the queue are followed only by smaller elements and so in
    the corrisponding positions of the result array puts a -1.
    The program takes O( n ) time since it must scan one time
    the array, one time the queue that will be long at most
    O( n ) and the erasing of the elements in the queue is 
    ammortized with respect to the insertions.
    The program takes O( n ) additional space because it 
    stores the queue and two arrays of n elements.
    References: Hint from a collegue. He said this solution
    is similar to previous problem.
    
 */
#include <iostream>
#include <vector>
#include <deque>

using namespace std;

int main( )
{
    int notests;
    cin >> notests;

    for( int i = 0; i < notests; i++ ) {
        int size;
        cin >> size;

        vector<int> elements;
        for( int j = 0; j < size; j++ ) {
            int temp;
            cin >> temp;
            elements.push_back( temp );
        }

        deque< pair< int, int > > dq;
        vector<int> results = vector<int>( size );
        for( int j = 0; j < size; j++ ) {
            auto el = elements[j];
            dq.push_back( pair< int, int >( el, j ) );
            auto last = dq.end( ) - 1;
            auto it = last - 1;
            while( it >= dq.begin( ) && it->first < el ) {
                results[it->second] = el;
                it--;
            }
            dq.erase( it + 1, last );
        }
        for( auto it = dq.begin( ); it != dq.end( ); it++ ) {
            results[it->second] = -1;
        }
        for( auto it = results.begin( ); it != results.end( ); it++ ) {
            cout << *it << " ";
        }
        cout << endl;
    }
}
