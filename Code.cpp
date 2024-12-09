#include <iostream>
#include <vector>
#include <limits>

using namespace std;

// Node structure for Binary Tree and Binary Search Tree
struct TreeNode {
    int value; // Value of the node
    TreeNode* left; // Pointer to the left child node
    TreeNode* right; // Pointer to the right child node

    // Constructor to initialize a node with a value
    TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}
};

// Binary Tree Class
class BinaryTree {
protected:
    TreeNode* root; // Root of the binary tree

    // Recursive function to insert a value into the tree
    virtual void insert(TreeNode*& node, int value) {
        if (!node) {
            node = new TreeNode(value); // Insert a new node if current position is null
            return;
        }
        if (value < node->value) {
            insert(node->left, value); // Recursively insert to the left subtree
        } else {
            insert(node->right, value); // Recursively insert to the right subtree
        }
    }

    // Recursive function to delete a node with a specific value
    TreeNode* deleteNode(TreeNode* node, int value) {
        if (!node) return nullptr; // Return null if node is not found

        if (value < node->value) {
            node->left = deleteNode(node->left, value); // Search in the left subtree
        } else if (value > node->value) {
            node->right = deleteNode(node->right, value); // Search in the right subtree
        } else {
            // Node with one or no child
            if (!node->left) {
                TreeNode* temp = node->right; // If no left child, promote the right child
                delete node;
                return temp;
            } else if (!node->right) {
                TreeNode* temp = node->left; // If no right child, promote the left child
                delete node;
                return temp;
            }

            // Node with two children: Get the inorder successor
            TreeNode* temp = findMin(node->right); // Find the smallest value in the right subtree
            node->value = temp->value; // Replace the node's value with the inorder successor's value
            node->right = deleteNode(node->right, temp->value); // Delete the inorder successor
        }
        return node; // Return the updated node
    }

    // Function to find the minimum value node (leftmost node)
    TreeNode* findMin(TreeNode* node) {
        while (node && node->left) node = node->left; // Traverse to the leftmost node
        return node;
    }

    // Recursive function to search for a node with a specific value
    TreeNode* search(TreeNode* node, int value) {
        if (!node || node->value == value) return node; // Return null if node is not found
        if (value < node->value) return search(node->left, value); // Search left subtree
        return search(node->right, value); // Search right subtree
    }

    // Preorder traversal: Node -> Left -> Right
    void preorder(TreeNode* node) {
        if (node) {
            cout << node->value << " "; // Print node value
            preorder(node->left); // Recursively traverse the left subtree
            preorder(node->right); // Recursively traverse the right subtree
        }
    }

    // Inorder traversal: Left -> Node -> Right
    void inorder(TreeNode* node) {
        if (node) {
            inorder(node->left); // Recursively traverse the left subtree
            cout << node->value << " "; // Print node value
            inorder(node->right); // Recursively traverse the right subtree
        }
    }

    // Postorder traversal: Left -> Right -> Node
    void postorder(TreeNode* node) {
        if (node) {
            postorder(node->left); // Recursively traverse the left subtree
            postorder(node->right); // Recursively traverse the right subtree
            cout << node->value << " "; // Print node value
        }
    }

public:
    BinaryTree() : root(nullptr) {} // Constructor to initialize an empty tree

    // Public function to insert a value into the tree
    virtual void insert(int value) {
        insert(root, value); // Call the recursive insert function
    }

    // Public function to delete a value from the tree
    void deleteValue(int value) {
        root = deleteNode(root, value); // Call the recursive delete function
    }

    // Public function to search for a value in the tree
    void searchValue(int value) {
        TreeNode* result = search(root, value); // Call the recursive search function
        if (result) {
            cout << "Value " << value << " found in the tree." << endl;
        } else {
            cout << "Value " << value << " not found in the tree." << endl;
        }
    }

    // Function to display the preorder traversal of the tree
    void preorderTraversal() {
        cout << "Preorder Traversal: ";
        preorder(root); // Call the recursive preorder function
        cout << endl;
    }

    // Function to display the inorder traversal of the tree
    void inorderTraversal() {
        cout << "Inorder Traversal: ";
        inorder(root); // Call the recursive inorder function
        cout << endl;
    }

    // Function to display the postorder traversal of the tree
    void postorderTraversal() {
        cout << "Postorder Traversal: ";
        postorder(root); // Call the recursive postorder function
        cout << endl;
    }
};

// Binary Search Tree Class (inherits from BinaryTree)
class BinarySearchTree : public BinaryTree {
protected:
    // Override insert function to ensure Binary Search Tree property (not necessary in this case as insert is identical)
    void insert(TreeNode*& node, int value) override {
        if (!node) {
            node = new TreeNode(value); // Insert new node
            return;
        }
        if (value < node->value) {
            insert(node->left, value); // Recursively insert to the left subtree
        } else {
            insert(node->right, value); // Recursively insert to the right subtree
        }
    }

public:
    // Public insert function (inherits functionality from BinaryTree)
    void insert(int value) {
        BinaryTree::insert(value); // Call the parent insert function
    }
};

// Heap Class
class Heap {
private:
    vector<int> heap; // Vector to store heap elements
    bool isMinHeap; // Boolean to track whether it's a Min-Heap or Max-Heap

    // Heapify up: Ensure the heap property is maintained when a new element is inserted
    void heapifyUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            // Compare with parent depending on heap type (Min or Max)
            if ((isMinHeap && heap[parent] > heap[index]) || (!isMinHeap && heap[parent] < heap[index])) {
                swap(heap[parent], heap[index]); // Swap if the heap property is violated
                index = parent; // Move to the parent node
            } else {
                break; // Stop if no further swaps are needed
            }
        }
    }

    // Heapify down: Ensure the heap property is maintained after removing the root
    void heapifyDown(int index) {
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
        int largestOrSmallest = index;

        // Check if left child exists and is in the correct position
        if (leftChild < heap.size() &&
                ((isMinHeap && heap[leftChild] < heap[largestOrSmallest]) ||
                 (!isMinHeap && heap[leftChild] > heap[largestOrSmallest]))) {
            largestOrSmallest = leftChild;
        }

        // Check if right child exists and is in the correct position
        if (rightChild < heap.size() &&
                ((isMinHeap && heap[rightChild] < heap[largestOrSmallest]) ||
                 (!isMinHeap && heap[rightChild] > heap[largestOrSmallest]))) {
            largestOrSmallest = rightChild;
        }

        // If heap property is violated, swap and continue heapifying
        if (largestOrSmallest != index) {
            swap(heap[index], heap[largestOrSmallest]);
            heapifyDown(largestOrSmallest);
        }
    }

public:
    // Constructor to initialize the heap with a flag for Min or Max Heap
    Heap(bool minHeap) : isMinHeap(minHeap) {}

    // Insert a value into the heap and maintain the heap property
    void insert(int value) {
        heap.push_back(value); // Add the new element
        heapifyUp(heap.size() - 1); // Restore the heap property by heapifying up
    }

    // Rebuild the heap from the last non-leaf node to maintain the heap property
    void heapify() {
        for (int i = (heap.size() / 2) - 1; i >= 0; --i) {
            heapifyDown(i); // Heapify down from each node
        }
    }

    // Traverse and display all elements in the heap
    void traverse() {
        if (heap.empty()) {
            cout << "Heap is empty." << endl;
            return;
        }
        cout << "Heap: ";
        for (int val : heap) {
            cout << val << " "; // Print each element
        }
        cout << endl;
    }

    // Delete the root element and reheapify the heap
    void deleteRoot() {
        if (heap.empty()) {
            cout << "Heap is empty, nothing to delete." << endl;
            return;
        }

        if (heap.size() == 1) {
            heap.pop_back(); // If only one element, remove it
            return;
        }

        // Move the last element to the root and heapify down
        heap[0] = heap.back();
        heap.pop_back();
        heapifyDown(0);
    }

    // Toggle between Min-Heap and Max-Heap
    void toggleHeapType() {
        isMinHeap = !isMinHeap; // Flip the heap type
        heapify(); // Rebuild the heap with the new property
        cout << (isMinHeap ? "Heap converted to Min-Heap.\n" : "Heap converted to Max-Heap.\n");
    }
};

// Function to handle user input dynamically
int getInput() {
    int choice;
    while (true) {
        cout << "Enter your choice: ";
        cin >> choice;
        if (cin.fail()) {
            cin.clear(); // Clear the fail state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "Invalid input, please enter a number.\n";
        } else {
            return choice; // Return valid input
        }
    }
}

// Main Menu Function
int main() {
    int choice;
    do {
        cout << "\n--- Main Menu ---\n";
        cout << "1. Binary Search Tree\n";
        cout << "2. Binary Tree\n";
        cout << "3. Heaps\n";
        cout << "4. Exit\n";
        choice = getInput(); // Get user input

        // Handle different menu options
        switch (choice) {
        case 1: {
            BinarySearchTree bst; // Create a Binary Search Tree
            int subChoice;
            do {
                cout << "\nBinary Search Tree Menu\n";
                cout << "1. Insert\n";
                cout << "2. Delete\n";
                cout << "3. Search\n";
                cout << "4. Display Traversals\n";
                cout << "5. Back to Main Menu\n";
                subChoice = getInput(); // Get user input

                if (subChoice == 1) {
                    int value;
                    cout << "Enter value to insert: ";
                    cin >> value;
                    bst.insert(value); // Insert value into BST
                } else if (subChoice == 2) {
                    int value;
                    cout << "Enter value to delete: ";
                    cin >> value;
                    bst.deleteValue(value); // Delete value from BST
                } else if (subChoice == 3) {
                    int value;
                    cout << "Enter value to search: ";
                    cin >> value;
                    bst.searchValue(value); // Search for value in BST
                } else if (subChoice == 4) {
                    bst.preorderTraversal(); // Display traversals
                    bst.inorderTraversal();
                    bst.postorderTraversal();
                }
            } while (subChoice != 5); // Repeat until user chooses to go back
            break;
        }
        case 2: {
            BinaryTree bt; // Create a Binary Tree
            int subChoice;
            do {
                cout << "\nBinary Tree Menu\n";
                cout << "1. Insert\n";
                cout << "2. Delete\n";
                cout << "3. Search\n";
                cout << "4. Display Traversals\n";
                cout << "5. Back to Main Menu\n";
                subChoice = getInput(); // Get user input

                if (subChoice == 1) {
                    int value;
                    cout << "Enter value to insert: ";
                    cin >> value;
                    bt.insert(value); // Insert value into Binary Tree
                } else if (subChoice == 2) {
                    int value;
                    cout << "Enter value to delete: ";
                    cin >> value;
                    bt.deleteValue(value); // Delete value from Binary Tree
                } else if (subChoice == 3) {
                    int value;
                    cout << "Enter value to search: ";
                    cin >> value;
                    bt.searchValue(value); // Search for value in Binary Tree
                } else if (subChoice == 4) {
                    bt.preorderTraversal(); // Display traversals
                    bt.inorderTraversal();
                    bt.postorderTraversal();
                }
            } while (subChoice != 5); // Repeat until user chooses to go back
            break;
        }
        case 3: {
            int subChoice;
            Heap* currentHeap = nullptr;

            do {
                cout << "\n--- Heaps Menu ---\n";
                cout << "1. Insert into Heap\n";
                cout << "2. Rebuild Heap (Heapify)\n";
                cout << "3. Delete Root\n";
                cout << "4. Toggle Heap Type (Min ↔ Max)\n";
                cout << "5. Back to Main Menu\n";
                subChoice = getInput(); // Get user input

                if (subChoice == 1) {
                    if (!currentHeap) {
                        int heapType;
                        do {
                            cout << "Choose heap type (1 for Min-Heap, 2 for Max-Heap): ";
                            cin >> heapType; // Choose heap type
                            if (heapType != 1 && heapType != 2) {
                                cout << "Invalid choice. Please enter 1 for Min-Heap or 2 for Max-Heap.\n";
                            }
                        } while (heapType != 1 && heapType != 2);

                        currentHeap = (heapType == 1) ? new Heap(true) : new Heap(false); // Create heap
                        cout << (heapType == 1 ? "Min-Heap created.\n" : "Max-Heap created.\n");
                    }

                    int value;
                    cout << "Enter value to insert in Heap: ";
                    cin >> value;
                    currentHeap->insert(value); // Insert value into heap
                    cout << "Value inserted successfully.\n";
                    currentHeap->traverse(); // Display the heap
                } else if (subChoice == 2) {
                    if (currentHeap) {
                        currentHeap->heapify(); // Rebuild the heap
                        cout << "Heap rebuilt successfully:\n";
                        currentHeap->traverse(); // Display the heap
                    } else {
                        cout << "No heap exists. Please create a heap first.\n";
                    }
                } else if (subChoice == 3) {
                    if (currentHeap) {
                        currentHeap->deleteRoot(); // Delete root of heap
                        cout << "Root deleted successfully.\n";
                        currentHeap->traverse(); // Display the heap
                    } else {
                        cout << "No heap exists. Please create a heap first.\n";
                    }
                } else if (subChoice == 4) { // Toggle between Min-Heap ↔ Max-Heap
                    if (currentHeap) {
                        currentHeap->toggleHeapType(); // Toggle heap type
                        currentHeap->traverse(); // Display the heap
                    } else {
                        cout << "No heap exists. Please create a heap first.\n";
                    }
                }
            } while (subChoice != 5); // Repeat until user chooses to go back

            delete currentHeap; // Clean up heap
            break;
        }
        case 4:
            cout << "Exiting program...\n"; // Exit the program
            break;
        default:
            cout << "Invalid choice, please try again.\n"; // Invalid option
        }
    } while (choice != 4); // Repeat until user chooses to exit

    return 0;
}
