/*
    The solution consists of divinding the cubes into two groups:
    the first one is made up by the cubes that don't share their
    numbers with anyone else while the second one is made up by
    the cubes that share their number with at least another 
    cube.
    The program does this by inserting the cubes by their numbers
    in the dictionary dic and then split them by the length of 
    the corrisponding dic[cube] array.
    Then starting from the ones that share their number it assigns
    one to a heap and the other one to the other heap until all the
    cubes are assigned. If the number
    of cubes sharing a single number is odd the next set of cubes that
    share a different number will start from the heap that has less
    cubes. After that, it starts with the cubes that don't share 
    their numbers with anyone else. Half of these are put in one
    heap and the other one half are put in the other heap.
    In case the two sets were odd, it will put half minus one to the
    heap with one more cube and it will put half plus one to the heap
    with a cube less.
    This will ensure that each heap will have the maximum number
    of ditinct cubes possible and the two will differ at most by one.
    The program takes O( n ) because it insersts each cube in dic
    once, splits them by scanning the elements in dic, then assigns
    each one to the heap and finally counts the distinct number in
    each heap.
    It takes O( n ) space because it store each cube first in dic,
    then in the two sets and finally in the two heaps 
    Reference: none
    

 */
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

enum class Heap {
    first, second
};

int main( )
{
    int n;
    cin >> n;
    vector<vector<pair<int, int>>> dic( 101 );

    for( int i = 0; i < 2*n; i++ ) {
        int cube;
        cin >> cube;
        dic[cube].push_back( make_pair( cube, i ) );
    }

    vector< pair<int, int> > distinctEls;
    vector< pair<int, int> > sameEls;
    //Separare gli elementi in distinti e non
    for( auto it = dic.begin( ); it != dic.end( ); it++ ) {
        if( it->size( ) == 1 ) {
            distinctEls.push_back( *( it->begin( ) ) );
        } else if( it->size( ) > 1 ) {
            for( auto jt = it->begin( ); jt != it->end( ); jt++ ) {
                sameEls.push_back( *jt );
            }
        }
    }

    vector<int> results( 2 * n );
    vector< vector<int> > heaps( 2 );
    int heap = 0;
    //Assegnare i non
    for( auto it = sameEls.begin( ); it != sameEls.end( ); it++ ) {
        results[it->second] = heap + 1;
        heaps[heap].push_back( it->first );
        heap = ( heap + 1 ) % 2;
    }

    //Assegnare i distinti
    if( heaps[0].size( ) == heaps[1].size( ) ) {
        int i = 0;
        for( ; i < distinctEls.size( ) / 2; i++ ) {
            heaps[0].push_back( distinctEls[i].first );
            results[distinctEls[i].second] = 1;
        }
        for( ; i < distinctEls.size( ); i++ ) {
            heaps[1].push_back( distinctEls[i].first );
            results[distinctEls[i].second] = 2;
        }
    } else if( heaps[0].size( ) > heaps[1].size( ) ) {
        int i = 0;
        while( heaps[0].size( ) > heaps[1].size( ) ) {
            heaps[1].push_back( distinctEls[i].first );
            results[distinctEls[i].second] = 2;
            i++;
        }
        int noAssignedEls = i;
        for( ; i <= ( distinctEls.size( ) - noAssignedEls ) / 2; i++ ) {
            heaps[0].push_back( distinctEls[i].first );
            results[distinctEls[i].second] = 1;
        }
        for( ; i < distinctEls.size( ); i++ ) {
            heaps[1].push_back( distinctEls[i].first );
            results[distinctEls[i].second] = 2;
        }
    } else if( heaps[0].size( ) < heaps[1].size( ) ) {
        int i = 0;
        while( heaps[0].size( ) < heaps[1].size( ) ) {
            heaps[0].push_back( distinctEls[i].first );
            results[distinctEls[i].second] = 1;
            i++;
        }
        int noAssignedEls = i;
        for( ; i <= ( distinctEls.size( ) - noAssignedEls ) / 2; i++ ) {
            heaps[0].push_back( distinctEls[i].first );
            results[distinctEls[i].second] = 1;
        }
        for( ; i < distinctEls.size( ); i++ ) {
            heaps[1].push_back( distinctEls[i].first );
            results[distinctEls[i].second] = 2;
        }
    }

    int first = 1;
    int second = 1;
    for( int i = 1; i < heaps[0].size( ); i++ ) {
        if( heaps[0][i-1] != heaps[0][i] ) 
            first++;
    }
    for( int i = 1; i < heaps[1].size( ); i++ ) {
        if( heaps[1][i-1] != heaps[1][i] ) 
            second++;
    }
    cout << first * second << endl;
    for( auto it = results.begin( ); it != results.end( ); it++ ) {
        cout << *it << " ";
    }
    cout << endl;
}
