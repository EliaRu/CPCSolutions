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
