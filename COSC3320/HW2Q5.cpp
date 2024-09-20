#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

class BinarySearchTree {
private:
    static const int LARGE_SIZE = 1 << 20; // 2^20
    static const int MEDIUM_SIZE = (1 << 19) + (1 << 20); // 2^19 + 2^20
    static const int SMALL_SIZE = (1 << 18) + (1 << 17); // 2^18 + 2^17

    struct TreeNode {
        int value;
        int* array;
        TreeNode *left, *right;
        int depth;

        TreeNode(int val) : value(val), array(nullptr), left(nullptr), right(nullptr), depth(0) {
            int residue = val % 3;
            if (residue == 0) array = new int[LARGE_SIZE]();
            else if (residue == 1) array = new int[MEDIUM_SIZE]();
            else array = new int[SMALL_SIZE]();
        }

        ~TreeNode() {
            delete[] array;
        }
    };

    TreeNode *root;
    int totalNodes;
    int additions;
    int removals;

    int nodeDepth(TreeNode* node) {
        return node ? node->depth : -1;
    }

    TreeNode* rightRotate(TreeNode* y) {
        TreeNode* x = y->left;
        y->left = x->right;
        x->right = y;
        y->depth = std::max(nodeDepth(y->left), nodeDepth(y->right)) + 1;
        x->depth = std::max(nodeDepth(x->left), nodeDepth(x->right)) + 1;
        return x;
    }

    TreeNode* leftRotate(TreeNode* x) {
        TreeNode* y = x->right;
        x->right = y->left;
        y->left = x;
        x->depth = std::max(nodeDepth(x->left), nodeDepth(x->right)) + 1;
        y->depth = std::max(nodeDepth(y->left), nodeDepth(y->right)) + 1;
        return y;
    }

    TreeNode* balanceTree(TreeNode* node, int val) {
        if (!node) return NULL;

        if (nodeDepth(node->left) - nodeDepth(node->right) > 1) {
            if (val < node->left->value) {
                node = rightRotate(node);
            } else {
                node->left = leftRotate(node->left);
                node = rightRotate(node);
            }
        } else if (nodeDepth(node->right) - nodeDepth(node->left) > 1) {
            if (val > node->right->value) {
                node = leftRotate(node);
            } else {
                node->right = rightRotate(node->right);
                node = leftRotate(node);
            }
        }
        return node;
    }

    TreeNode* addNode(int val, TreeNode* node) {
        if (!node) {
            additions++;
            return new TreeNode(val);
        }

        if (val < node->value) {
            node->left = addNode(val, node->left);
        } else if (val > node->value) {
            node->right = addNode(val, node->right);
        }

        node->depth = std::max(nodeDepth(node->left), nodeDepth(node->right)) + 1;
        return balanceTree(node, val);
    }

    TreeNode* removeNode(int val, TreeNode* node) {
        if (!node) return nullptr;

        if (val < node->value) {
            node->left = removeNode(val, node->left);
        } else if (val > node->value) {
            node->right = removeNode(val, node->right);
        } else {
            if (node->left == nullptr || node->right == nullptr) {
                TreeNode* temp = node->left ? node->left : node->right;
                if (temp == nullptr) {
                    delete node;
                    node = nullptr;
                } else {
                    TreeNode* toDelete = node;
                    node = temp;
                    toDelete->left = toDelete->right = nullptr;
                    delete toDelete;
                }
            } else {
                TreeNode* temp = node->right;
                while (temp->left != nullptr) {
                    temp = temp->left;
                }
                node->value = temp->value;
                node->array = temp->array;
                temp->array = nullptr; // Prevent array from being deleted by removeNode
                node->right = removeNode(temp->value, node->right);
            }
            removals++;
        }

        if (node == nullptr) return nullptr;

        node->depth = std::max(nodeDepth(node->left), nodeDepth(node->right)) + 1;
        return balanceTree(node, val);
    }

    void inorder(TreeNode* node) {
        if (!node) return;
        inorder(node->left);
        std::cout << node->value << " ";
        inorder(node->right);
    }

public:
    BinarySearchTree() : root(NULL), totalNodes(0), additions(0), removals(0) {}

    ~BinarySearchTree() {
        while (root) {
            removeNode(root->value, root);
        }
    }

    void insert(int val) {
        root = addNode(val, root);
    }

    void remove(int val) {
        root = removeNode(val, root);
        if (root != nullptr) {
            totalNodes--;
        }
    }

    void display() {
        inorder(root);
        std::cout << std::endl;
    }

    int getNodeCount() const {
        return totalNodes;
    }

    int getAdditionCount() const {
        return additions;
    }

    int getRemovalCount() const {
        return removals;
    }
};

int main() {
    BinarySearchTree bst;
    srand(static_cast<unsigned int>(time(NULL)));
    std::vector<int> numArray(100000);
    for (size_t i = 0; i < numArray.size(); ++i) {
        numArray[i] = rand() % 300;
    }

    clock_t startTime, endTime;
    double insertTimeTotal = 0, deleteTimeTotal = 0;
    int insertCount = 0, deleteCount = 0;

    // Initial insert until the tree has 50 nodes
    while (bst.getNodeCount() < 50) {
        int val = numArray[insertCount];
        startTime = clock();
        bst.insert(val);
        endTime = clock();
        insertTimeTotal += static_cast<double>(endTime - startTime);
        insertCount++;
    }
    double initialInsertTime = (insertTimeTotal / insertCount) / CLOCKS_PER_SEC * 1000;

    // Continue with the rest of insertions and deletions
    for (size_t i = insertCount; i < numArray.size(); ++i) {
        if (bst.getNodeCount() < 50) {
            startTime = clock();
            bst.insert(numArray[i]);
            endTime = clock();
            insertTimeTotal += static_cast<double>(endTime - startTime);
            insertCount++;
        }
        if (bst.getNodeCount() >= 50) {
            startTime = clock();
            bst.remove(numArray[rand() % bst.getNodeCount()]);
            endTime = clock();
            deleteTimeTotal += static_cast<double>(endTime - startTime);
            deleteCount++;
        }
    }

    // Calculate average times
    double avgInsertTime = (insertTimeTotal / insertCount) / CLOCKS_PER_SEC * 1000;
    double avgDeleteTime = deleteCount > 0 ? (deleteTimeTotal / deleteCount) / CLOCKS_PER_SEC * 1000 : 0;

    std::cout << "Average Initial Insertion time: " << initialInsertTime << " milliseconds.\n";
    std::cout << "Average Insertion time: " << avgInsertTime << " milliseconds.\n";
    std::cout << "Average Deletion time: " << avgDeleteTime << " milliseconds.\n";

    return 0;
}
