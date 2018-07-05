/*
    The solution is based on the divide&conquer technique.
    First the program splits the array into two halves and
    resolves the problem invoking recursevely the function
    InversionCoutn. 
    This returns a pair consisting of the subarray in 
    decreasing ordered and the number of inversions between
    its elements. Given f and s the solutions to the two
    halves, the program counts the number of inversion
    between the two subarrays f.first and s.second in this way:
    it compares f.first[0] with s.first[0]. If the first one 
    is greater than we have one inversion for all the elements
    in s.first because the elements are in decreasing order and
    stores that in the array orderedSeq. If the first one is less
    or equal to the second one there won't be no inversion with
    this element so the program just stores it in orderedSeq.
    It goes on until one of the two subarrays is empty.
    When this happens it stores the remaining elements in 
    orderedSeq.
    The result of the function invocation is then the 
    ordered array and the number of found inversions plus
    the number of inversions that were found in the two
    subarrays.
    For arrays of size 1 and 0 the program resolves the program
    directly by returning the array and zero as the number of
    inversions.
    The program takes O( nlogn ) since it is an augmented version
    of MergeSort.
    The program takes O( nlogn ) of space since it uses an additional
    array of size n each call.
    Reference: solution given in class.
 */

#include <iostream>
#include <vector>
#include <cstdint>

using namespace std;

using i64 = int64_t;

pair<vector<i64>, i64 > InversionCount( vector<i64> v )
{
    if( v.size( ) >= 2 ) {
        vector<i64> fHalf( v.begin( ), v.begin( ) + v.size( ) / 2 );
        vector<i64> sHalf( v.begin( ) + v.size( ) / 2, v.end( ) );
        auto f = InversionCount( fHalf );
        auto s = InversionCount( sHalf);
        i64 i = 0;
        i64 j = 0;
        i64 noInversions = 0;
        vector<i64> orderedSeq;
        while( i < f.first.size( ) && j < s.first.size( ) ) {
            if( f.first[i] > s.first[j] ) {
                noInversions += s.first.size( ) - j;
                orderedSeq.push_back( f.first[i] );
                i++;
            } else {
                orderedSeq.push_back( s.first[j] );
                j++;
            }
        }
        while( i < f.first.size( ) ) {
            orderedSeq.push_back( f.first[i] );
            i++;
        }
        while( j < s.first.size( ) ) {
            orderedSeq.push_back( s.first[j] );
            j++;
        }

        return make_pair( move( orderedSeq ), noInversions + f.second +s.second );
    } else if( v.size( ) == 1 ) {
        return make_pair( move( v ), 0 );
    } else if( v.size( ) == 0 ) {
        return make_pair( move( v ), 0 );
    }
}

int main( )
{
    i64 noTests;
    cin >> noTests;
    vector<i64> results;
    while( noTests-- ) {
        i64 size;
        cin >> size;
        vector<i64> els;
        while( size-- ) {
            i64 temp;
            cin >> temp;
            els.push_back( temp );
        }
        results.push_back( InversionCount( els ).second );
        //cout << InversionCount( els ).second << endl;
        //int noInversions = 0;
        //for( int i = 0; i < els.size( ); i ++ ) 
            //for( int j = i; j < els.size( ); j++ ) {
                //if( els[i] > els[j] ) {
                    //noInversions++;
                //}
            //}
    }
    for( auto i = results.begin( ); i != results.end( ); i++ ) {
        cout << *i << endl;
    }
}
