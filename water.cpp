/*
    The program is pretty simple: if the first part of the elevation
    map is flat than it cannot trap any water so is discarded and
    finds the first element whose height is greater than zero, called
    startingHeight. From this element until it finds another one
    whose height is greater than startingHeight it counts the trapped 
    water as the difference between the its height and 
    startingHeight. When a new element whose height is greater than
    startingHeight is found we set startingHeight to the height of 
    this element. The program does this until the max of the array
    is found. Because this reasoning cannot be applied for the 
    maximum element we stop and it does the same thing starting from
    the end of the elevation map.
    The last loop accounts for the case in which there are multiple
    maximum elements in the elevation map.
    The program consists of three scan, two for finding the maximum 
    elements of the array and one for counting the water so it takes
    O( n ) time. It uses only one array for storing the elements so 
    it takes O( n ) space.
    Reference: none
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

int main( )
{
    int numberOfTests;
    cin >> numberOfTests;
    for( int i = 0; i < numberOfTests; i++ ) {
        int size;
        cin >> size;
        vector<int> elements( size );
        for( int j = 0; j < elements.size( ); j++ ) {
            cin >> elements[j];
        }

        int trappedWater = 0;
        auto max = max_element( elements.begin( ), elements.end( ) );
        auto it = elements.begin( );
        int position = 0;
        while( *it == 0 ) {
            it++;
            position++;
        }
        int startingHeight = *it;
        for( ; it != max; it++ ) {
            if( *it <= startingHeight ) {
                trappedWater += startingHeight - *it;
            } else if( *it > startingHeight ) {
                startingHeight = *it;
            }
            position++;
        }

        auto rit = elements.rbegin( );
        auto rmax = max_element( elements.rbegin( ), elements.rend( ) );
        int rposition = elements.size( ) - 1;
        while( *rit == 0 ) {
            rit++;
            rposition--;
        }
        startingHeight = *rit;
        for( ; rit != rmax; rit++ ) {
            if( *rit <= startingHeight ) {
                trappedWater += startingHeight - *rit;
            } else if( *rit > startingHeight ) {
                startingHeight = *rit;
            }
            rposition--;
        }
        if( position != rposition ) {
            startingHeight = elements[rposition];
           for( int i = rposition; i >= position; i-- ) {
                if( elements[i] <= startingHeight ) {
                    trappedWater += startingHeight - elements[i];
                } else if( elements[i] > startingHeight ) {
                    startingHeight = elements[i];
               }
           }
        }
        cout << trappedWater << endl;
    }
}
