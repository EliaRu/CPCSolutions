/*
    The program uses the formula ( n * ( n + 1 ) ) / 2 to find
    the sum of the first n elements starting from 1.
    It then subtracts to this value the sum of the input 
    elements. The difference is the missing element.
    This solution takes O( n ) time for adding up all the elements
    received and it takes O( 1 ) space for the variables only.
    Reference: none
 */
#include <iostream>

using namespace std;

int main( ) {
    int numberOfTests;
    cin >> numberOfTests;

    for( int i = 0; i < numberOfTests; i++ ) {
        int size;
        cin >> size;
        int sum = 0;
        for( int j = 0; j < size - 1; j++ ) {
            int element;
            cin >> element;
            sum += element;
        }
        int diff = ( size * ( size + 1 ) ) / 2 - sum;
        cout << diff << endl;
    }
}
