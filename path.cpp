/*
    Note: the program contains the driver code used to read the input
    given by the GeekForGeeks.com exercise.
    The program searches for the best path in the right subtree and
    in the left subtree recursevely. Then first it compares the two
    path to choose the best among them, then it compares this path
    with the best one that includes the root. This is done by 
    returning the best path from one of the leaf of the subtree
    to the root of the subtree and then summing up the received 
    value from the right subtree, the received value from the left
    one and the value of the root. Finally this one is compared
    with the previously chosen best path and it is returned, together 
    with the best path from one of the leaf of the tree to the root, 
    to the caller.
    The program runs in O( n ) time since the function Solve is 
    called once for each node and makes O( c ) operations.
    The program takes O( n ) space since it must store the whole
    tree.
    Reference: none.
 */
#include <iostream>
#include <limits>

using namespace std;
struct Node{
	int data;
	Node *left, *right;
};
Node *newNode(int data)
{
    Node *node = new Node;
    node->data = data;
    node->left = node->right = NULL;
    return (node);
}
int maxPathSum(struct Node *root);
void insert(Node *root, int a1,int a2, char lr){
	if(root==NULL)
		return ;
	if(root->data==a1){
		switch(lr){
			case 'L':root->left=newNode(a2);
					break;
			case 'R':root->right=newNode(a2);
					break;
		}
	}
	insert(root->left,a1,a2,lr);
	insert(root->right,a1,a2,lr);
}
void inorder(Node *root){
    if(root==NULL){
        return;
    }
    inorder(root->left);
    cout<<root->data<<" ";
    inorder(root->right)
;}
int main(){
	int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		Node *root=NULL;
		while(n--){
			int a1,a2;
			char lr;
			cin>>a1>>a2>>lr;
			if(root==NULL){
				root=newNode(a1);
				switch(lr){
					case 'L':root->left=newNode(a2);
							break;
					case 'R':root->right=newNode(a2);
							break;
				}
			}
			else
				insert(root,a1,a2,lr);
		}
		//inorder(root);
		//cout<<endl;
		cout<<maxPathSum(root)<<endl;		
	}
}

/*Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function is mentioned above.*/

/*Complete the function below
Node is as follows
struct Node{
	int data;
	Node *left, *right;
};
*/
struct Result {
    int maxPathToLeaf;
    int maxPathToRoot;
};

Result Solve( struct Node* root ) 
{
    if( root == nullptr ) {
        int min = numeric_limits<int>::min( );
        Result r = { min, min };
        return r;
    } else { 
        auto resultL = Solve( root->left );
        auto resultR = Solve( root->right );
        int pathR = resultR.maxPathToLeaf;
        int pathL = resultL.maxPathToLeaf;
        int bestPathToLeaf = ( pathR > pathL ) ? pathR : pathL;
        int newPath = resultR.maxPathToRoot + resultL.maxPathToRoot + root->data;
        Result r = { 
            ( bestPathToLeaf > newPath ) ? bestPathToLeaf : newPath, 
            ( resultL.maxPathToRoot > resultR.maxPathToRoot ) ?
                resultL.maxPathToRoot + root->data :
                resultR.maxPathToRoot + root->data
        };
        return r;
    }
}

int maxPathSum(struct Node *root)
{
    return Solve( root ).maxPathToLeaf;
}
