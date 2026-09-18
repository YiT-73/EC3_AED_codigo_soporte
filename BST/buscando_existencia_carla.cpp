#include <iostream>
#include <queue>
#include <stack>
#include <stdexcept>
#include <utility>

using namespace std;

// ============================================================
// ÁRBOL BINARIO DE BÚSQUEDA 
// ============================================================
template <typename T>
class BinarySearchTree {
public:
    struct Node {
        T value;
        Node* left;
        Node* right;

        explicit Node(const T& val)
            : value(val), left(nullptr), right(nullptr) {}
    };

    Node* root;
    size_t numElements;

    BinarySearchTree()
        : root(nullptr), numElements(0) {}

    ~BinarySearchTree() {
        clear();
    }

    BinarySearchTree(const BinarySearchTree&) = delete;
    BinarySearchTree& operator=(const BinarySearchTree&) = delete;

    // ========================================================
    // INSERTAR
    // ========================================================
    bool insert(const T& value) {
        Node* newNode = new Node(value);

        if (root == nullptr) {
            root = newNode;
            ++numElements;
            return true;
        }

        Node* current = root;
        Node* parent = nullptr;

        while (current != nullptr) {
            parent = current;

            if (value < current->value) {
                current = current->left;
            } else if (value > current->value) {
                current = current->right;
            } else {
                // El valor ya existe.
                delete newNode;
                return false;
            }
        }

        if (value < parent->value) {
            parent->left = newNode;
        } else {
            parent->right = newNode;
        }

        ++numElements;
        return true;
    }

    // ========================================================
    // BUSCAR
    // ========================================================
    bool search(const T& value) const {
        const Node* current = root;

        while (current != nullptr) {
            if (value < current->value) {
                current = current->left;
            } else if (value > current->value) {
                current = current->right;
            } else {
                return true;
            }
        }

        return false;
    }

    bool contains(const T& value) const {
        return search(value);
    }

    // ========================================================
    // BUSCAR EL NODO MENOR
    // ========================================================
    Node* findMinNode(Node* node) const {
        if (node == nullptr) {
            return nullptr;
        }

        while (node->left != nullptr) {
            node = node->left;
        }

        return node;
    }

    const Node* findMinNode(const Node* node) const {
        if (node == nullptr) {
            return nullptr;
        }

        while (node->left != nullptr) {
            node = node->left;
        }

        return node;
    }

    // ========================================================
    // ELIMINAR
    // ========================================================
    bool remove(const T& value) {
        Node* current = root;
        Node* parent = nullptr;

        // Buscar el nodo que se quiere eliminar.
        while (current != nullptr && current->value != value) {
            parent = current;

            if (value < current->value) {
                current = current->left;
            } else {
                current = current->right;
            }
        }

        // El valor no se encontró.
        if (current == nullptr) {
            return false;
        }

        // ----------------------------------------------------
        // Caso 3: el nodo tiene dos hijos.
        // Buscar el sucesor inorden.
        // ----------------------------------------------------
        if (current->left != nullptr &&
            current->right != nullptr) {

            Node* successorParent = current;
            Node* successor = current->right;

            while (successor->left != nullptr) {
                successorParent = successor;
                successor = successor->left;
            }

            // Copiar el valor del sucesor.
            current->value = successor->value;

            // Ahora se eliminará el sucesor.
            parent = successorParent;
            current = successor;
        }

        // ----------------------------------------------------
        // Casos 1 y 2:
        // - Nodo sin hijos.
        // - Nodo con un solo hijo.
        // ----------------------------------------------------
        Node* child;

        if (current->left != nullptr) {
            child = current->left;
        } else {
            child = current->right;
        }

        // Si se elimina la raíz.
        if (parent == nullptr) {
            root = child;
        }
        // Si current es hijo izquierdo.
        else if (parent->left == current) {
            parent->left = child;
        }
        // Si current es hijo derecho.
        else {
            parent->right = child;
        }

        delete current;
        --numElements;

        return true;
    }

    // ========================================================
    // ALTURA
    // Árbol vacío: -1
    // Árbol con solamente la raíz: 0
    // ========================================================
    int height(const Node* node) const {
        if (node == nullptr) {
            return -1;
        }

        queue<const Node*> pending;
        pending.push(node);

        int treeHeight = -1;

        while (!pending.empty()) {
            size_t nodesAtCurrentLevel = pending.size();
            ++treeHeight;

            for (size_t i = 0; i < nodesAtCurrentLevel; ++i) {
                const Node* current = pending.front();
                pending.pop();

                if (current->left != nullptr) {
                    pending.push(current->left);
                }

                if (current->right != nullptr) {
                    pending.push(current->right);
                }
            }
        }

        return treeHeight;
    }

    int getHeight() const {
        return height(root);
    }

    // ========================================================
    // RECORRIDO INORDEN
    // Izquierda - raíz - derecha
    // ========================================================
    void InOrder(const Node* node) const {
        stack<const Node*> pending;
        const Node* current = node;

        while (current != nullptr || !pending.empty()) {

            // Avanzar todo lo posible hacia la izquierda.
            while (current != nullptr) {
                pending.push(current);
                current = current->left;
            }

            current = pending.top();
            pending.pop();

            cout << current->value << " ";

            current = current->right;
        }
    }

    // ========================================================
    // RECORRIDO PREORDEN
    // Raíz - izquierda - derecha
    // ========================================================
    void PreOrder(const Node* node) const {
        if (node == nullptr) {
            return;
        }

        stack<const Node*> pending;
        pending.push(node);

        while (!pending.empty()) {
            const Node* current = pending.top();
            pending.pop();

            cout << current->value << " ";

            /*
             * Se agrega primero el hijo derecho porque una pila
             * procesa primero el último elemento agregado.
             */
            if (current->right != nullptr) {
                pending.push(current->right);
            }

            if (current->left != nullptr) {
                pending.push(current->left);
            }
        }
    }

    // ========================================================
    // RECORRIDO POSTORDEN
    // Izquierda - derecha - raíz
    // ========================================================
    void PostOrder(const Node* node) const {
        if (node == nullptr) {
            return;
        }

        stack<pair<const Node*, bool>> pending;
        pending.push({node, false});

        while (!pending.empty()) {
            const Node* current = pending.top().first;
            bool visited = pending.top().second;

            pending.pop();

            if (visited) {
                cout << current->value << " ";
            } else {
                /*
                 * El nodo se vuelve a guardar como visitado.
                 * Después se guardan sus hijos.
                 */
                pending.push({current, true});

                if (current->right != nullptr) {
                    pending.push({current->right, false});
                }

                if (current->left != nullptr) {
                    pending.push({current->left, false});
                }
            }
        }
    }

    // ========================================================
    // RECORRIDO POR NIVELES
    // ========================================================
    void levelOrder() const {
        cout << "Por niveles: ";

        if (root == nullptr) {
            cout << "árbol vacío\n";
            return;
        }

        queue<const Node*> pending;
        pending.push(root);

        while (!pending.empty()) {
            const Node* current = pending.front();
            pending.pop();

            cout << current->value << " ";

            if (current->left != nullptr) {
                pending.push(current->left);
            }

            if (current->right != nullptr) {
                pending.push(current->right);
            }
        }

        cout << "\n";
    }

    // ========================================================
    // IMPRIMIR ÁRBOL
    // ========================================================
    void printTree(const Node* node, int initialLevel) const {
        if (node == nullptr) {
            return;
        }

        stack<pair<const Node*, int>> pending;

        const Node* current = node;
        int currentLevel = initialLevel;

        /*
         * Se realiza un inorden inverso:
         * derecha - raíz - izquierda.
         */
        while (current != nullptr || !pending.empty()) {

            while (current != nullptr) {
                pending.push({current, currentLevel});
                current = current->right;
                ++currentLevel;
            }

            current = pending.top().first;
            currentLevel = pending.top().second;
            pending.pop();

            for (int i = 0; i < currentLevel; ++i) {
                cout << "    ";
            }

            cout << current->value << "\n";

            current = current->left;
            ++currentLevel;
        }
    }

    void print() const {
        cout << "-----------------------------------------\n";
        cout << "Elements : " << numElements << "\n";
        cout << "Height   : " << getHeight() << "\n";
        cout << "-----------------------------------------\n";

        if (root == nullptr) {
            cout << "Árbol vacío\n";
        } else {
            printTree(root, 0);
        }

        cout << "-----------------------------------------\n";
    }

    // ========================================================
    // VALOR MÍNIMO
    // ========================================================
    const T& minValue() const {
        const Node* node = findMinNode(root);

        if (node == nullptr) {
            throw runtime_error("El árbol está vacío");
        }

        return node->value;
    }

    // ========================================================
    // VALOR MÁXIMO
    // ========================================================
    const T& maxValue() const {
        if (root == nullptr) {
            throw runtime_error("El árbol está vacío");
        }

        const Node* current = root;

        while (current->right != nullptr) {
            current = current->right;
        }

        return current->value;
    }

    // ========================================================
    // ELIMINAR TODOS LOS NODOS
    // ========================================================
    void clear() {
        if (root == nullptr) {
            return;
        }

        stack<Node*> pending;
        pending.push(root);

        while (!pending.empty()) {
            Node* current = pending.top();
            pending.pop();

            if (current->left != nullptr) {
                pending.push(current->left);
            }

            if (current->right != nullptr) {
                pending.push(current->right);
            }

            delete current;
        }

        root = nullptr;
        numElements = 0;
    }

    size_t size() const {
        return numElements;
    }

    bool empty() const {
        return root == nullptr;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    BinarySearchTree<int> arbol;
    int n;
    cin >> n;
    int consultas;
    cin >> consultas;
    int valor;
    for (int i = 0; i < n; ++i) {
        cin >> valor;
        arbol.insert(valor);
    }
    int buscar;
    for (int i = 0; i < consultas; ++i) {
        cin >> buscar;
        if (arbol.search(buscar) == true){
            cout << "SI" << "\n";
        }
        else {
            cout << "NO" << "\n";
        }
    }
    return 0;

}