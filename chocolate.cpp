/*
    The program computes the times needed to eat
    each bar up to the i-th one for both Alice and Bobs.
    In this way for each bar we can see whether Bob or
    Alice first starts eating it.
    The program runs in O( n ) since it computes two 
    prefix arrays and it compares Bob's and Alice's
    times for each bar;
    The program takes O( n ) space for storing the
    prefix sums and the input.
    Reference: none
 */
#include <iostream>
#include <vector>

using namespace std;

int main( )
{
    int noBars;
    cin >> noBars;
    vector<int> times;
    while( noBars-- ) {
        int tmp;
        cin >> tmp;
        times.push_back( tmp );
    }
    noBars = times.size( );
    vector<int> alicesTimes( noBars + 1, 0 );
    vector<int> bobsTimes( noBars + 1, 0 );
    for( int i = 1; i < noBars + 1; i++ ) {
        alicesTimes[i] = alicesTimes[i - 1] + times[i - 1];
    }
    for( int i = noBars - 1; i >= 0; i-- ) {
        bobsTimes[i] = bobsTimes[i + 1] + times[i];
    }
    int noEatenByAlice = 0;
    int noEatenByBob = 0;
    for( int i = 0; i < noBars; i++ ) {
        ( alicesTimes[i] <= bobsTimes[i + 1] ) ? noEatenByAlice++ : noEatenByBob++;
    }
    cout << noEatenByAlice << " " << noEatenByBob << endl;
}
