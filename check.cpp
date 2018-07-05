/*
    Note: the file contains also the driver code used for parsing the 
    input on the GeekForGeeks site.
    The function CheckBST checks recursively if each subtree is a BST.
    In particular null pointers are assumed to be BST and each 
    invocation of the function returns whether that subtree is BST and
    what are the value of its minimum and maximum elements. Each element
    calls the function depending whether it has a left child, a right 
    child or both. Then it checks if the subtree are all BST. If not
    it returns false. Otherwise if the node has only a left child it 
    checks if the maximum element of the left subtree is less than
    its value, if the node has only a left child it checks if 
    the minimum element of the right subtree is greater than its value
    and if has both it checks both the above conditions.
    If these hold the node returns true and the new minimum and 
    maximum elements. Specifically if the node has no left child
    its value will become the minimum, if the node has no right child
    its value will become the maximum and if it has both the minimum
    will become the minimum of its left subtree and the maximum will
    be the maximum of its right subtree.
    The program takes O( n ) since it carries out the above procedure
    once for each node of the tree.
    Reference: none.
 */

#include <cstdio>
#include <cstdlib>
#include <map>
#include <iostream>
using namespace std;
/* A binary tree node has data, pointer to left child
   and a pointer to right child */
struct Node
{
    int data;
    struct Node* left;
    struct Node* right;
};
/* Returns true if the given tree is a binary search tree
 (efficient version). */
bool isBST(struct Node* node);
int isBSTUtil(struct Node* node, int min, int max);
/* Helper function that allocates a new node with the
   given data and NULL left and right pointers. */
struct Node* newNode(int data)
{
  struct Node* node = (struct Node*)
                       malloc(sizeof(struct Node));
  node->data = data;
  node->left = NULL;
  node->right = NULL;
  return(node);
}
/* Driver program to test size function*/
int main()
{
  int t;
  struct Node *child;
  scanf("%d\n", &t);
  while (t--)
  {
     map<int, Node*> m;
     int n;
     scanf("%d\n",&n);
     struct Node *root = NULL;
     while (n--)
     {
        Node *parent;
        char lr;
        int n1, n2;
        scanf("%d %d %c", &n1, &n2, &lr);
      //  cout << n1 << " " << n2 << " " << (char)lr << endl;
        if (m.find(n1) == m.end())
        {
           parent = newNode(n1);
           m[n1] = parent;
           if (root == NULL)
             root = parent;
        }
        else
           parent = m[n1];
        child = newNode(n2);
        if (lr == 'L')
          parent->left = child;
        else
          parent->right = child;
        m[n2]  = child;
     }
     cout << isBST(root) << endl;
  }
  return 0;
}

#include <vector>

using namespace std;

using ii = pair<int, int>;

pair<bool, ii> CheckBST( Node* root ) {
    if( root == NULL ) {
        return make_pair( true, make_pair( 0, 0 ) );
    }
    if( root->left == NULL && root->right == NULL ) {
        return make_pair( true, make_pair( root->data ,root->data ) );
    } else if( root->left == NULL && root->right != NULL ) {
        auto resultR = CheckBST( root->right );
        if( resultR.first == true && resultR.second.first >= root->data ) {
            return make_pair( true, make_pair( root->data, resultR.second.second ) );
        } else {
            return make_pair( false, make_pair( 0, 0 ) );
        }
    } else if( root->right == NULL && root->left != NULL ) {
        auto resultL = CheckBST( root->left );
        if( resultL.first == true && resultL.second.second <= root->data ) {
            return make_pair( true, make_pair( resultL.second.first, root->data ) );
        } else {
            return make_pair( false, make_pair( 0, 0 ) );
        }
    } else if( root->right != NULL && root->left != NULL ) {
        auto resultR = CheckBST( root->right );
        auto resultL = CheckBST( root->left );
        if( resultL.first == true && resultR.first == true && resultL.second.second <= root->data
            && resultR.second.first >= root->data ) {
            return make_pair( true, make_pair( resultL.second.first, resultR.second.second ) );
        } else {
            return make_pair( false, make_pair( 0, 0 ) );
        }
    }
}

bool isBST( struct Node* node ) {
    return CheckBST( node ).first;
}
