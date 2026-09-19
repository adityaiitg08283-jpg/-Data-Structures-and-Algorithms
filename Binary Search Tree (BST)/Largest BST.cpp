#include <iostream>
#include <algorithm>
#include <climits>

using namespace std;

// Node structure for Binary Tree
struct Node {
    int data;
    Node* left;
    Node* right;
    
    Node(int val) {
        data = val;
        left = NULL;
        right = NULL;
    }
};

// Info class to store min, max, and size for each subtree
class Info {
public:
    int min, max, sz;
    
    Info(int mi, int ma, int size) {
        min = mi;
        max = ma;
        sz = size;
    }
};

// Helper function to return Info for the current node
Info helper(Node* root) {
    // Base case: empty tree is a BST of size 0
    if (root == NULL) {
        return Info(INT_MAX, INT_MIN, 0);
    }
    
    Info left = helper(root->left);
    Info right = helper(root->right);
    
    // Check if the current subtree is a BST
    if (root->data > left.max && root->data < right.min) {
        int curMin = min(root->data, left.min);
        int curMax = max(root->data, right.max);
        int currSz = left.sz + right.sz + 1;
        
        return Info(curMin, curMax, currSz);
    }
    
    // If not a BST, return max size found so far in left or right subtrees
    return Info(INT_MIN, INT_MAX, max(left.sz, right.sz));
}

// Function to find the size of the largest BST
int largestBST(Node* root) {
    Info info = helper(root);
    return info.sz; // max BST size
}

int main() {
    Node* root = new Node(10);
    root->left = new Node(5);
    root->right = new Node(15);
    root->left->left = new Node(1);
    root->left->right = new Node(8);
    root->right->right = new Node(7);
    
    cout << "Largest BST Size: " << largestBST(root) << endl;
    
    return 0;
}














