/*
    To make the least number of changes we must change each number from
    1 to n. Otherwise each time we change something at position j < i
    the value at position i changes.
    Given k between [1, n] a[k] will be different from zero because it
    was modified by the previous operations. More precisely it will be equal to
    a[k - 1 ]. So we must increment or decrement depending if a[k - 1] less 
    than or greater than b[k] | b[k] - a[k - 1] | times. 
    Reference: none.
 */
#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

int main( )
{
    int n;
    cin >> n;
    vector<int> input( n );
    for( int i = 0; i < n; i++ ) {
        cin >> input[i];
    }
    long long steps = 0;
    int value = 0;
    for( int i = 0; i < n; i++ ) {
        long long diff = input[i] - value;
        steps += abs( diff );
        value = input[i];
    }
    cout << steps << endl;
}
