/*
    In a preordered traversal of a BST given the root of a subtree 
    at position i in the array, first we will have all the elements 
    of the left subtree and after that possibly the elements of the 
    right subtree. While telling apart the first is easy, we scan 
    the array until an element that is greater than the root is 
    found, once we find that is harder to tell if the node is the
    child of the current root or of one of its ancestor.
    We must check if the node respect the property of the BST
    as the child of the current root, otherwise we will check
    each ancestor until we discarded the root, too. In this case
    we can say that the array is not a preordered traversal of a 
    BST, otherwise will restart doing the same thing as before
    in a different subtree.
    In the program this is done by using a stack that keeps track
    of the ancestors of the current node and the constraints that
    the value of the current node must follow to respect the BST
    properties. When the following node in the array is greater 
    than its parent but it's out of range than the stacked is 
    popped until a proper parent is found or the stack is empty.
    In the first case the program resumes, in the second one
    the array is not a preordered traversal of a BST tree.
    The program takes O( n ) time since it checks each node only 
    once and each node may be discarded at most once.
    The program takes O( n ) space since it stores all the 
    elements in an array and at most n elements in the stack.
    Reference: none
 */
#include <vector>
#include <iostream>
#include <cstdio>

using namespace std;

struct node {
    int data;
    int left;
    int right;
};

struct limit {
    int pos;
    int min;
    int max;
};

int main( ) 
{
    int noTests;
    cin >> noTests;
    while( noTests-- ) {
        int size;
        cin >> size;
        vector<node> tree;
        for( int i = 0; i < size; i++ ) {
            node tmp;
            cin >> tmp.data;
            tmp.left = -1;
            tmp.right = -1;
            tree.push_back( tmp );
        }
        vector<limit> stack;
        limit root = { 0, -1, -1 };
        stack.push_back( root );
        bool exit = false;
        for( int i = 1; i < size && !exit; i++ ) {
            auto currentLimit = stack.back( );
            auto parent = tree[currentLimit.pos];
            if( tree[i].data <= parent.data ) {
                if( currentLimit.min == -1 || tree[i].data >= currentLimit.min ) {
                    limit l = { i, currentLimit.min, parent.data };
                    tree[currentLimit.pos].left = i;
                    stack.push_back( l );
                } else {
                    cout << 0 << endl;
                    exit = true;
                }
            } else if( tree[i].data > parent.data ) {
                if( currentLimit.max == -1 || tree[i].data <= currentLimit.max ) {
                    limit l = { i, parent.data, currentLimit.max };
                    tree[currentLimit.pos].right = i;
                    stack.push_back( l );
                } else {
                    stack.pop_back( );
                    while( !stack.empty( ) ) {
                        auto l = stack.back( );
                        if( tree[l.pos].right == -1 && tree[l.pos].data <= tree[i].data ) {
                            if( l.max == -1 || tree[i].data <= l.max ) {
                                limit iLimit = { i, parent.data, l.max };
                                tree[l.pos].right = i;
                                stack.push_back( iLimit );
                                break;
                            }
                        }
                        stack.pop_back( );
                    }
                    if( stack.empty( ) ) {
                        cout << 0 << endl;
                        exit = true;
                    }
                }
            }
        }
        if( !exit ) {
            cout << 1 << endl;
        }
    }
    return 0;
}
