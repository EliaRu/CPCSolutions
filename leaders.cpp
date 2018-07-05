/*
 *  Starting from the last element of the array, the next leader
 *  must be greater than all the elements to its right side, the
 *  last leader the program has found too. So it compares each 
 *  element with the last found leader. If the element is greater 
 *  then it is a leader because is greater than the last leader and,
 *  for the definition of leader, is also greater than all the 
 *  elements to the right and is also greater than the elements 
 *  between the two because otherwise one of them would be the
 *  last leader.
 *  For this reason the algorithm is correct and it runs in O( n )
 *  time with O( n ) space because it uses an elements array, 
 *  which has size equals to n, and a leaders array, which in the
 *  worst case scenario has size equals to n.
 *  Reference: none
 */

#include <iostream>
#include <vector>

using namespace std;

int main( )
{
    int nTests;
    cin >> nTests;
    for( int i = 0; i < nTests; i++ ) {
        vector<int> elements;
        vector<int> leaders;
        //Input
        int size;
        cin >> size;
        for( int i = 0; i < size; i++ ) {
            int tmp;
            cin >> tmp;
            elements.push_back( tmp );
        }
        //Search of the leaders
        int currentLeader = elements.back( );
        leaders.push_back( elements.back( ) );
        for( int j = size - 1; j >= 0; j-- ) {
            if( elements[j] > currentLeader ) {
                currentLeader = elements[j];
                leaders.push_back( elements[j] );
            }
        }
        //Output
        for( int j = leaders.size( ) - 1; j >= 0; j-- ) {
            cout << leaders[j] << " ";
        }
        cout << endl;
    }
}
