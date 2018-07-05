#include <fstream>

using namespace std;

//3
//0 0 0
//100
//1 1 0
//0 0 -1
//0 1 0
//2 0
//2 2
//0 1
//0 0 1
//1 1
//2 2
//2 0 1
//0 1
//1 2

int main( )
{
    ofstream ofs( "input" );
    int n = 200000;
    ofs << n << endl;
    int i = n;
    while( i-- ) {
        if( i == 1 ) {
            ofs << rand( ) << endl;
        } else {
            ofs << rand( ) << " ";
        }
    }
    int m = 200000;
    ofs << m << endl;
    i = m;
    while( i-- ) {
        int k = rand( ) % 2;
        if( k == 0 ) {
            ofs << ( rand( ) % n ) << " " << ( rand( ) % n ) << endl;
        } else {
            ofs << ( rand( ) % n ) << " " << ( rand( ) % n ) << " " << rand( ) << endl;
        }
    }

}
