/*
    The solution is very similar to the "Subset Sum" in
    the lecture notes. 
    First the program computes the sum of the element
    in the set. If the sum is not divisible by 2 is 
    impossible to divide the set into two such that
    the sum of each is the same. If the sum is zero,
    since all the elements are greater or equal to 
    zero, they must be all equal to zero and is 
    possible to make up to subset with sum equal to
    zero.
    If the sum is divisible by zero the problem
    is resolved with the same recurrence equation
    used for the Subset Sum problem of the notes.
    The only difference is the final value, that must 
    be half of the whole sum and the starting conditions.
    In fact we cannot choose the empty set or the
    whole set as a valid solution to the problem.
    The program must fill the whole table so it runs
    in O( n * sum ) time and takes O( n * sum ) space.
    Reference: none
 */
#include <vector>
#include <iostream>
#include <cstring>

using namespace std;

int input[100];
bool table[101 * 100001];

int main( )
{
    ios::sync_with_stdio( false );
    cin.tie( nullptr );
    int noTests;
    cin >> noTests;
    while( noTests-- ) {
        int n;
        cin >> n;
        int sum = 0;
        memset( input, 0, sizeof table  );
        memset( table, 0, sizeof input );
        for( int i = 0; i < n; i++ ) {
            cin >> input[i];
            sum += input[i];
        }
        if( sum % 2 != 0 ) {
            cout << "NO" << endl;
        } else if( sum == 0 ) {
            cout << "YES" << endl;
        } else {
            sum /= 2;
            int N = n + 1;
            int M = sum + 1;
            for( int j = 0; j < M; j++ ) {
                table[j] = false;
            }
            for( int i = 1; i < N - 1; i++ ) {
                table[i * M] = true;
            }
            table[M * ( N - 1 )] = false;
            for( int i = 1; i < N; i++ ) {
                for( int j = 1; j < M; j++ ) {
                    if( j - input[i - 1] < 0 ) {
                        table[i * M + j] = 
                            table[( i - 1 ) * M + j];
                    } else {
                        table[i * M + j] = 
                            table[( i - 1 ) * M + j] ||
                            table[( i - 1 ) * M + j - input[i - 1]];
                    }
                }
            }
            if( ( table[ M * N - 1] ) ) {
                cout << "YES" << endl;
            } else {
                cout << "NO" << endl;
            }
        }
    }
    return 0;
}
