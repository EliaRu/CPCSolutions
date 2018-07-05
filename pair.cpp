/*
    The program stores in the array teams
    all the information received an all the possible
    team composition. It sorts the teams by their
    strength from stronger to weaker and assign to
    each partecipants the best team they can.
    The program takes O( n^2*logn^2 ) because the
    longest task is to sort all the ( ( 2n - 1)*2n ) / 2
    teams by their strength.
    The program takes O( n^2*logn^2 ) space because
    it stores the teams in an array.
    Reference: none
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Team {
    int i;
    int j;
    int power;
};

int main( )
{
    int noPeople;
    cin >> noPeople;
    noPeople *= 2;

    vector<Team> teams;
    for( int i = 0; i < noPeople; i++ ) {
        for( int j = 0; j < i; j++ ) {
            Team t;
            t.i = i;
            t.j = j;
            cin >> t.power;
            teams.push_back( t );
        }
    }

    sort( teams.begin( ), teams.end( ),
        []( const Team& a, const Team& b ) {
            if( a.power > b.power ) 
                return true;
            else
                return false;
        }
    );

    vector<bool> partecipants( noPeople, false);
    vector<Team> finalTeams( noPeople );
    int noPeopleAssigned = 0;
    int i = 0;
    while( i < teams.size( ) && noPeopleAssigned < noPeople ) {
        if( partecipants[teams[i].i] || partecipants[teams[i].j] ) {
            i++;
        } else {
            partecipants[teams[i].i] = true;
            finalTeams[teams[i].i] = teams[i];

            partecipants[teams[i].j] = true;
            finalTeams[teams[i].j] = Team{ teams[i].j, teams[i].i, 0 };
            noPeopleAssigned += 2;
            i++;
        }
    }
    for( auto it = finalTeams.begin( ); it != finalTeams.end( ); it ++ ) {
        cout << it->j + 1 << " ";
    }
    cout << endl;
}
