/*
    The program sorts the locations on their distance from
    the city. Then starting from the nearest one it adds
    cities to Tomsk until its population is greater than 
    one milion. If it can reach this value the program
    prints -1 else the distance of the latest added city.
    The program runs in O( nlogn ) because it sorts the
    locations by the standard library sorting algorithm
    and the following scan of the array takes at most
    O( n ) time
    The program takes O( n ) additional space because it
    stores the locations in an array.
    Reference: none
 */
#include <iostream>
#include <iomanip>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <cmath>

using namespace std;

const int targetPopulation = 1000000;

struct City {
    int x;
    int y;
    int population;
};

int main( )
{
    int noLocations;
    cin >> noLocations;
    
    int populationTomsk;
    cin >> populationTomsk;

    vector<City> locations( noLocations );
    for( int i = 0; i < noLocations; i++ ) {
        City newCity;
        cin >> newCity.x;
        cin >> newCity.y;
        cin >> newCity.population;
        locations[i] = newCity;
    }
    
    sort( locations.begin( ), locations.end( ), 
        []( const City& a, const City& b ) {
            if( ( a.x * a.x + a.y * a.y ) < ( b.x * b.x + b.y * b.y ) ) {
                return true;
            } else {
                return false;
            }
        }
    );
    
    int i = -1;
    while( populationTomsk < targetPopulation && i < noLocations - 1 ) {
        i++;
        populationTomsk += locations[i].population;
    }
    if( populationTomsk < targetPopulation ) {
        cout << -1 << endl;
    } else if( i == -1 ) {
        cout << 0 << endl;
    } else {
        cout << setprecision( 10 );
        cout << fixed;
        cout << hypot( locations[i].x, locations[i].y ) << endl;
    }
}
