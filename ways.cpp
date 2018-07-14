/*
    The program first checks if the sum of the elements
    is divisible by 3. In the case it is not there is no
    solution to the problem.
    Then starting from the last element it checks if the
    suffix starting from j sums to a third of the whole
    elemnents and put the result in an array and it 
    computes the suffix sums on this array.
    Finally for each element i starting from the first it
    check if the prefix that has i has last element sums
    to a third of the whole array. If it does it checks
    the other array to see how many suffixes starting 
    from i + 2 do the same.
    Since the program scans the array once for computing
    the sum, once for computing the suffixes, once for
    computing the suffix sums on that array and once
    for finding the solution it runs in O( n ) and
    takes O( n ) space.
    Reference: Tutorial on Codeforces
 */
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
