/*
    Fist the program construct an N-ary tree from the input.
    It scans the input array skipping every element that is already
    in the tree. Otherwise it puts the element in a stack and jumps
    to its senior employee. The same thing is repeated until one of 
    the these two conditions are met: either an element that is already
    in the tree or Ms. Alfred is found ( or both ). In the first case
    this element will be the senior of the employee on the top of the
    stack. This will be popped from it and the procedure repeated 
    until the stack is empty. In the second case first Ms. Alfred will
    become the root of the tree then it will resort to the first case.
    Each node will have a pointer to the parent, a pointer to the first
    element of the list of its child, a pointer to the next brother
    and a pointer to the first one of the list.
    Once the tree is built the program computes every prime number
    from 2 to 2 * N + 1. This is done in the event that the tree of
    employers is a list with the last one ( the only leaf ) having 
    rank equal to N.
    Then recursevely each node is checked against the condition given
    in the text and the acc global variable is incremented each
    time the condition is true.
    The building of the tree takes O( n ) time because each element
    is inserted in the tree only once and the insertion is constant.
    The execution of the EratosthenesSieve takes O( nloglogn ) as 
    written in http://research.cs.wisc.edu/techreports/1990/TR909.pdf.
    The final check done on the employees take O( n ) time since 
    each node is checked only once.
    The program takes O( n ) space since it stores an array and a
    tree of the all n employees.
    Reference: none.

 */
#include <iostream>
#include <vector>

std::vector<bool> EratosthenesSieve( int n )
{
    std::vector<bool> results( n + 1, true );
    results[1] = false;
    int p = 2;
    while( ( p * p ) <= n ) {
        for( int i = p; i <= ( n / p ); i++ ) {
            results[p * i] = false;
        }
        do {
            p++;
        } while( p < ( n + 1 ) && results[p] != true );
    }
    return results;
}

using namespace std;

struct node {
    int rank;
    node* parent;
    node* children;
    node* brothers;
    node* firstBrother;
    node* lastBrother;
};

void DeleteTree( node* t )
{
    if( t->children != nullptr ) {
        DeleteTree( t->children );
    }
    if( t->brothers != nullptr ) {
        DeleteTree( t->brothers );
    }
    delete t;
}

int acc;
vector<bool> primes;

void CountEmployeesToFire( node* t, int height )
{
    if( t->parent == nullptr ) {
        if( t->children != nullptr ) { 
            CountEmployeesToFire( t->children, 1 );
        }
    } else {
        acc += ( primes[t->rank + height] ? 1 : 0 );
        if( t->brothers != nullptr ) {
            CountEmployeesToFire( t->brothers, height );
        }
        if( t->children != nullptr ) {
            CountEmployeesToFire( t->children, height + 1 );
        }
    }
}

int main( )
{
    int noTests;
    cin >> noTests;
    vector< pair<int, node*> > employees;
    while( noTests-- ) {
        employees.clear( );
        int size;
        cin >> size;
        for( int i = 0; i < size; i++ ) {
            int tmp;
            cin >> tmp;
            employees.push_back( make_pair( tmp, nullptr ) ); 
        }
        node* alfred;
        vector<int> ranks;
        for( int i = 0; i < employees.size( ); i++ ) {
            ranks.clear( );
            int j = i;
            while( employees[j].first != 0 && employees[j].second == nullptr ) {
                ranks.push_back( j + 1 );
                j = employees[j].first - 1;
            } 
            node* parent = employees[j].second;
            if( parent != nullptr ) {
                for( auto it = ranks.rbegin( ); it != ranks.rend( ); it++ ) {
                    node* newNode = new node;
                    newNode->rank = *it;  
                    newNode->parent = parent;
                    newNode->children = nullptr;
                    newNode->brothers = nullptr;
                    if( parent->children == nullptr ) {
                        parent->children = newNode;
                        newNode->firstBrother = nullptr;
                        newNode->lastBrother = nullptr;
                    } else {
                        if( parent->children->lastBrother == nullptr ) {
                            parent->children->brothers = newNode;
                            parent->children->lastBrother = newNode;
                            newNode->firstBrother = parent->children;
                            newNode->lastBrother = nullptr;
                        } else {
                            parent->children->lastBrother->brothers = newNode;
                            parent->children->lastBrother = newNode;
                            newNode->firstBrother = parent->children;
                            newNode->lastBrother = nullptr;
                        }
                    }
                    parent = newNode;
                    employees[ newNode->rank - 1].second = newNode;
                }
            } else if( employees[j].first == 0 ) {
                node* root = new node;
                root->rank = j + 1;
                root->parent = nullptr;
                root->children = nullptr;
                root->brothers = nullptr;
                root->firstBrother = nullptr;
                root->lastBrother = nullptr;
                alfred = root;
                parent = root;
                employees[j].second = root;
                for( auto it = ranks.rbegin( ); it != ranks.rend( ); it++ ) {
                    node* newNode = new node;
                    newNode->rank = *it;  
                    newNode->parent = parent;
                    newNode->children = nullptr;
                    newNode->brothers = nullptr;
                    if( parent->children == nullptr ) {
                        parent->children = newNode;
                        newNode->firstBrother = nullptr;
                        newNode->lastBrother = nullptr;
                    } else {
                        if( parent->children->lastBrother == nullptr ) {
                            parent->children->brothers = newNode;
                            parent->children->lastBrother = newNode;
                        } else {
                            parent->children->lastBrother->brothers = newNode;
                            parent->children->lastBrother = newNode;
                        }
                    }
                    parent = newNode;
                    employees[ newNode->rank - 1].second = newNode;
                }
            }
        }
        primes = EratosthenesSieve( 2 * size + 1 );
        acc = 0;
        CountEmployeesToFire( alfred, 0 );
        cout << acc << endl;
        DeleteTree( alfred );
    }
}
