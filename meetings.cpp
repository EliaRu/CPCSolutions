/*
    The program sorts the meetings in ascending order
    of finishing times.
    Then the first meeting, the one with the lowest 
    finishing times, is selected.
    The program searches for the next meeting that
    has the lowest finishing time but has a start
    time that is greater than the finishing time
    of the previous meeting.
    The program takes O( nlogn ) time as it must
    sort the input array, while it takes O( n )
    space since it must store just the input 
    sequence.
    Reference: job scheduling seen in class.
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Meeting{
    int start;
    int finish;
    int pos;
};

int main( )
{
    int noTests;
    cin >> noTests;
    while( noTests-- ) {
        int n;
        cin >> n;
        vector<Meeting> meetings( n );
        for( int i = 0; i < n; i++ ) {
            cin >> meetings[i].start;
            meetings[i].pos = i + 1;
        }
        for( int i = 0; i < n; i++ ) {
            cin >> meetings[i].finish;
        }
        sort( meetings.begin( ), meetings.end( ),
            []( Meeting& a, Meeting& b ) {
                return a.finish < b.finish;
            }
        );
        int f = meetings[0].finish;
        cout << meetings[0].pos << " ";
        for( int i = 1; i < n; i++ ) {
            if( meetings[i].start > f ) {
                f = meetings[i].finish;
                cout << meetings[i].pos << " ";
            }
        }
        cout << endl;
    }
}


