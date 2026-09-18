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

    // Helper recursivo para insertar (puntero pasado por referencia)
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

    // Helper recursivo para buscar
    bool searchHelper(TreeNode* node, T key) const {
        if (node == nullptr) return false;
        if (node->Key == key) return true;

        if (key < node->Key) {
            return searchHelper(node->left, key);
        } else {
            return searchHelper(node->right, key);
        }
    }

    // Helpers DFS
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

    // Libera memoria para evitar Memory Leaks
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

    // Interfaz pública
    void insert(T key) {
        insertHelper(root, key);
    }

    bool search(T key) const {
        return searchHelper(root, key);
    }

    // --- Recorrido BFS (Breadth-First Search) ---
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

    // --- Recorridos DFS (Depth-First Search) ---
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


