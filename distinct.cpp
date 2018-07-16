/*
    The set of the prefixes of each suffixes of a string
    is equal to the set of all substrings of a prefix.
    To compute how many of these substrings are distinct
    given a suffix a program computes how many prefixes
    it has, the lentgth of the string minus the position
    of the suffix ( i.e. SA[i] ). From this it removes
    each prefix that shares with the previous suffix in 
    the suffix array, since those are not distinct.
    The algorithm used to compute the suffix array and
    lcp array are taken from the book Competitive Programming
    3 since the ones found in the notes of the Standford 
    course and Codechef didn't work for me.
    The construction of the suffix array is based on the
    same procedure as the algorithm explained on the notes.
    The construction of the lcp array is based on the Kasai's
    algorithm.
    The program runs in O( n*logn ). In fact the construction
    of the suffix array uses a kind of radix sort so is O( n )
    and the total cost is O( n*logn ). The lcp array is built
    in O( n ) time.
    Reference: yuting-zhang.github.io
 */
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAXLEN = 50010;

char st[MAXLEN];

int SA[MAXLEN], RA[MAXLEN];
int tempSA[MAXLEN], tempRA[MAXLEN];
int counting[MAXLEN];
int n;

void countingSort( int k )
{
    int maxRange = max( 300, n );
    memset( counting, 0, sizeof counting );
    for( int i = 0; i < n; i++ )
        counting[i + k < n ? RA[i + k] : 0]++;

    int sum = 0;
    for( int i = 0; i < maxRange; i++ ) {
        int temp = counting[i];
        counting[i] = sum;
        sum += temp;
    }

    for( int i = 0 ; i < n; i++ )
        tempSA[counting[SA[i] + k < n ? RA[SA[i] + k] : 0]++] = SA[i];
    for( int i = 0; i < n; i++ )
        SA[i] = tempSA[i];
}

void constructSA( )
{
    for( int i = 0; i < n; i++ ) {
        SA[i] = i;
        RA[i] = st[i];
    }

    for( int k = 1; k < n; k <<= 1 ) {
        countingSort( k );
        countingSort( 0 );
        int rank;
        tempRA[SA[0]] = rank = 0;
        for( int i = 1; i < n; i++ )
            tempRA[SA[i]] = 
                ( RA[SA[i - 1]] == RA[SA[i]] 
                && RA[SA[i - 1] + k] == RA[SA[i] + k] ) 
                ? rank : ++rank;
        for( int i = 0; i < n; i++ )
            RA[i] = tempRA[i];
        if( RA[SA[n - 1]] == n - 1 )
            break;
    }
}

int LCP[MAXLEN], PLCP[MAXLEN], Phi[MAXLEN];

void computeLCP()
{
    Phi[SA[0]] = -1;
    for( int i = 1; i < n; i++ )
        Phi[SA[i]] = SA[i - 1];
    int L = 0;
    for( int i = 0; i < n; i++ ) {
        if (Phi[i] == -1){
            PLCP[i] = 0;
            continue;
        }
        while( st[i + L] == st[Phi[i] + L] )
            L++;
        PLCP[i] = L;
        L = max( L - 1, 0 );
    }
    for( int i = 0; i < n; i++ )
        LCP[i] = PLCP[SA[i]];
}

int main()
{
    ios::sync_with_stdio( false );
    cin.tie( nullptr );
    cout.tie( nullptr );
    int noTests;
    cin >> noTests;
    cin.getline( st, sizeof st );
    while( noTests-- ) {
        cin.getline( st, sizeof st );
        n = strlen( st );
        st[n++] = '$';
        st[n] = '\0';
        constructSA( );
        computeLCP( );
        int res = 0;
        for( int i = 0; i < n; i++ ) {
            res += n - 1 - SA[i];
            res -= LCP[i];
        }
        cout << res << endl;
    }
    
    return 0;
}
