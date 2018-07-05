#pragma once

#include <vector>

std::vector<bool> EratosthenesSieve( int n )
{
    std::vector<bool> results( n + 1, true );
    results[1] = false;
    int p = 2;
    while( ( p * p ) <= n ) {
        for( int i = p; i <= n / p; i++ ) {
            results[p * i] = false;
        }
        do {
            p++;
        } while( p < n + 1 && results[p] == true );
    }
    return results;
}
