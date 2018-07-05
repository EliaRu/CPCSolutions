/*
    For a contiguous sub-array that has maximum sum two properties
    must hold: every prefix of the sub-array must have positive sum, 
    otherwise we could drop the negative prefix and have a
    differnt sub-array that is a better solution, and the previous
    value of the first element of the sub-array must not be positive,
    otherwise we could add it and have a better solution.
    For these reasons the program keeps two values: maxSum is the 
    current best sum it has found and currentSum is the sum of the 
    sub-array is evaluating. If currentSum is greater than maxSum we 
    have found a better sub-array, if it isn't we continue onto the 
    next sub-array. In case currentSum is less than zero the current 
    sub-array is dropped and the next one will start 
    from position i + 1.
    Also if currentSum is negative at the start of each loop the value
    is resetted and the previous sub-array is dropped.
    The program takes O( n ) time since it consists of a single scan of
    the array and takes O( n ) space for storing the n elements of the 
    input.
    References: We solved the same problem in other courses previously.
 */
#include <iostream>
#include <vector>

using namespace std;

int main( )
{
    int numberOfTests;
    cin >> numberOfTests;
    for( int i = 0; i < numberOfTests; i++ ) {
        int size;
        cin >> size;
        vector< int > elements( size );
        
        for( auto it = elements.begin( ); it != elements.end( ); it++ ) {
            cin >> *it;
        }

        int currentSum, maxSum;
        maxSum = elements[0];
        currentSum = 0;
        for( int i = 0; i < size; i++ ) {
            if( currentSum < 0 ) {
                currentSum = elements[i];
            } else {
                currentSum += elements[i];
            }
            if( currentSum > maxSum ) {
                maxSum = currentSum;
            } else if ( currentSum < 0 ) {
                currentSum = 0;
            }
        }
        cout << maxSum << endl;
    }
}
