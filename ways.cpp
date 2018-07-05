#include <vector>
#include <iostream>

using namespace std;

int main( ) 
{
    int n;
    cin >> n;
    vector<long long> input( n );
    for( int i = 0; i < n; i++ ) {
        cin >> input[i];
    }
    long long sum = 0;
    for( int i = 0; i < n; i++ ) {
        sum += input[i];
    }
    if( sum % 3 != 0 ) {
        cout << 0 << endl;
        return 0;
    }
    sum /= 3;
    vector<long long> suffixes( n + 1, 0 );
    long long suffixSum = 0;
    for( int i = n - 1; i >= 0; i-- ) {
        suffixSum += input[i];
        if( suffixSum == sum ) {
            suffixes[i] = 1;
        }
    }
    for( int i = n - 1; i >= 0; i-- ) {
        suffixes[i] += suffixes[i + 1];
    }
    long long res = 0;
    long long prefixSum = 0;
    for( int i = 0; i < n - 2; i++ ) {
        prefixSum += input[i];
        if( prefixSum == sum ) {
            res += suffixes[i + 2];
        }
    }
    cout << res << endl;
}
