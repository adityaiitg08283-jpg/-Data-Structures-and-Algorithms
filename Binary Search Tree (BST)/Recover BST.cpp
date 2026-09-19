// FIRST APPROACH  ::  Using Inorder Traversal and Sorting , inorder fashion - O(n * log n) Time and O(n) Space :
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

// Node structure
class Node {
public:
    int data;
    Node* left;
    Node* right;

    Node(int x) {
        data = x;
        left = right = nullptr;
    }
};

// Print tree in level order array format
void printTree(Node* root) {
    if (root == nullptr) {
        cout << "[]\n";
        return;
    }

    vector<string> ans;
    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        Node* curr = q.front();
        q.pop();

        if (curr != nullptr) {
            ans.push_back(to_string(curr->data));
            q.push(curr->left);
            q.push(curr->right);
        } else {
            ans.push_back("N");
        }
    }

    while (!ans.empty() && ans.back() == "N")
        ans.pop_back();

    cout << "[";
    for (int i = 0; i < ans.size(); i++) {
        if (i)
            cout << ", ";
        cout << ans[i];
    }
    cout << "]\n";
}

// Store inorder traversal
void findInorder(Node* root, vector<int>& inorder) {
    if (root == nullptr)
        return;

    findInorder(root->left, inorder);
    inorder.push_back(root->data);
    findInorder(root->right, inorder);
}

// Replace node values using sorted inorder array
void correctBSTUtil(Node* root, vector<int>& inorder, int& index) {
    if (root == nullptr)
        return;

    correctBSTUtil(root->left, inorder, index);
    root->data = inorder[index++];
    correctBSTUtil(root->right, inorder, index);
}

// Function to restore the BST
Node* correctBST(Node* root) {
    vector<int> inorder;

    findInorder(root, inorder);

    sort(inorder.begin(), inorder.end());

    int index = 0;
    correctBSTUtil(root, inorder, index);

    return root;
}

int main() {

    // Constructing the tree with swapped nodes
    //       6
    //     /  \
    //    10   2
    //   / \  / \
    //  1  3 7  12

    Node* root = new Node(6);
    root->left = new Node(10);
    root->right = new Node(2);
    root->left->left = new Node(1);
    root->left->right = new Node(3);
    root->right->left = new Node(7);
    root->right->right = new Node(12);

    root = correctBST(root);

    printTree(root);

    return 0;
}

// SECOND APPROACH :: [Expected Approach] Using One Traversal - O(n) Time and O(h) Space

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

// Node structure
class Node {
public:
    int data;
    Node* left;
    Node* right;

    Node(int x) {
        data = x;
        left = right = nullptr;
    }
};

// Print tree in level order array format
void printTree(Node* root) {
    if (root == nullptr) {
        cout << "[]\n";
        return;
    }

    vector<string> ans;
    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        Node* curr = q.front();
        q.pop();

        if (curr != nullptr) {
            ans.push_back(to_string(curr->data));
            q.push(curr->left);
            q.push(curr->right);
        } else {
            ans.push_back("N");
        }
    }

    while (!ans.empty() && ans.back() == "N")
        ans.pop_back();

    cout << "[";
    for (int i = 0; i < ans.size(); i++) {
        if (i)
            cout << ", ";
        cout << ans[i];
    }
    cout << "]\n";
}

    // Performs inorder traversal to find the misplaced nodes.
    void correctBSTUtil(Node* root, Node*& first, Node*& middle, Node*& last,
                        Node*& prev) {
        if (root == nullptr)
            return;

        // Traverse left subtree
        correctBSTUtil(root->left, first, middle, last, prev);

        // Detect violation of BST property
        if (prev != nullptr && root->data < prev->data) {

            // First violation
            if (first == nullptr) {
                first = prev;
                middle = root;
            }
            // Second violation
            else {
                last = root;
            }
        }

        prev = root;

        // Traverse right subtree
        correctBSTUtil(root->right, first, middle, last, prev);
    }

    Node* correctBST(Node* root) {

        Node *first = nullptr, *middle = nullptr;
        Node *last = nullptr, *prev = nullptr;

        correctBSTUtil(root, first, middle, last, prev);

        // If the swapped nodes are non-adjacent
        if (first != nullptr && last != nullptr)
            swap(first->data, last->data);

        // If the swapped nodes are adjacent
        else if (first != nullptr && middle != nullptr)
            swap(first->data, middle->data);

        return root;
    }
int main() {

    // Constructing the tree with swapped nodes
    //       6
    //     /  \
    //    10   2
    //   / \  / \
    //  1  3 7  12

    Node* root = new Node(6);
    root->left = new Node(10);
    root->right = new Node(2);
    root->left->left = new Node(1);
    root->left->right = new Node(3);
    root->right->left = new Node(7);
    root->right->right = new Node(12);

    root = correctBST(root);

    printTree(root);

    return 0;
}



































