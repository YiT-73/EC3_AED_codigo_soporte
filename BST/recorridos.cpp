#include <iostream>
#include <queue>
using namespace std;

template<typename  T>
class Tree {
private:
    struct TreeNode {
        T Key;
        TreeNode *left;
        TreeNode *right;
        TreeNode(T key) : Key(key), left(nullptr), right(nullptr) {}
    };

    TreeNode *root = nullptr;


    void insertHelper(TreeNode*& node, T key) {
        if (node == nullptr) {
            node = new TreeNode(key);
            return;
        }
        if (key < node->Key) {
            insertHelper(node->left, key);
        } else if (key > node->Key) {
            insertHelper(node->right, key);
        }
    }


    bool searchHelper(TreeNode* node, T key) const {
        if (node == nullptr) return false;
        if (node->Key == key) return true;

        if (key < node->Key) {
            return searchHelper(node->left, key);
        } else {
            return searchHelper(node->right, key);
        }
    }


    void inorderHelper(TreeNode* node) const {
        if (node == nullptr) return;
        inorderHelper(node->left);
        cout << node->Key << " ";
        inorderHelper(node->right);
    }

    void preorderHelper(TreeNode* node) const {
        if (node == nullptr) return;
        cout << node->Key << " ";
        preorderHelper(node->left);
        preorderHelper(node->right);
    }

    void postorderHelper(TreeNode* node) const {
        if (node == nullptr) return;
        postorderHelper(node->left);
        postorderHelper(node->right);
        cout << node->Key << " ";
    }


    void destroyTree(TreeNode* node) {
        if (node != nullptr) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

public:
    ~Tree() {
        destroyTree(root);
    }


    void insert(T key) {
        insertHelper(root, key);
    }

    bool search(T key) const {
        return searchHelper(root, key);
    }


    void bfs() const {
        if (root == nullptr) return;

        queue<T> q;
        q.push(root);

        while (!q.empty()) {
            TreeNode* current = q.front();
            q.pop();

            cout << current->Key << " ";

            if (current->left != nullptr)  q.push(current->left);
            if (current->right != nullptr) q.push(current->right);
        }
        cout << endl;
    }

    void dfsInorder() const {
        inorderHelper(root);
        cout << endl;
    }

    void dfsPreorder() const {
        preorderHelper(root);
        cout << endl;
    }

    void dfsPostorder() const {
        postorderHelper(root);
        cout << endl;
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin>> n;
    Tree<int> T;

    int val;
    for (int i = 0; i < n; i++) {
        cin>>val;
        T.insert(val);
    }

    T.dfsPreorder();
    T.dfsInorder();
    T.dfsPostorder();


}