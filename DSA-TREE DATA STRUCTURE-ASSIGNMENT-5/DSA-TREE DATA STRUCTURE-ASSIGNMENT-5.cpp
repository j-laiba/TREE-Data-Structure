//Laiba Atta FOC-1071-BSIT-F23A
// DSA-TREE DATA STRUCTURE-ASSIGNMENT-5.cpp
// This program implements a Binary Search Tree (BST) with various operations such as:
// insertion, deletion, traversal, and finding minimum, maximum, height, successor, and predecessor of nodes.

#include <iostream>
#include <queue>
using namespace std;

class Node 
{
public:
    int data;
    Node* left;
    Node* right;

	// Constructor to initialize a new node
    Node(int val) 
    {
        data = val;
        left = right = nullptr;
    }
};

class BST 
{
private:
    Node* root;

	// Helper functions for various operations on the BST
    void inorder(Node* node) 
	{
        // Function to perform inorder traversal of the BST
        if (node == nullptr) return;
        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }

	// Function to perform preorder traversal of the BST
    void preorder(Node* node) 
    {
        if (node == nullptr) return;
        cout << node->data << " ";
        preorder(node->left);
        preorder(node->right);
    }

	// Function to perform postorder traversal of the BST
    void postorder(Node* node) 
    {
        if (node == nullptr) return;
        postorder(node->left);
        postorder(node->right);
        cout << node->data << " ";
    }

	// Function to insert a new node with a given value into the BST
    Node* insert(Node* node, int val) 
    {
        if (node == nullptr) return new Node(val);
        if (val < node->data)
            node->left = insert(node->left, val);
        else
            node->right = insert(node->right, val);
        return node;
    }

	// Function to find the minimum and maximum nodes in the BST
    Node* findMin(Node* node) 
    {
        while (node && node->left)
            node = node->left;
        return node;
    }

	// Function to find the maximum node in the BST
    Node* findMax(Node* node) 
    {
        while (node && node->right)
            node = node->right;
        return node;
    }

	// Function to calculate the height of the BST
    int height(Node* node) 
    {
        if (node == nullptr) return -1;
        int leftHeight = height(node->left);
        int rightHeight = height(node->right);
        return 1 + max(leftHeight, rightHeight);
    }

	// Function to delete a node with a given key from the BST
    Node* deleteNode(Node* node, int key) 
    {
        if (node == nullptr) return node;
        if (key < node->data)
            node->left = deleteNode(node->left, key);
        else if (key > node->data)
            node->right = deleteNode(node->right, key);
        else 
        {
			// Node with one child or no child
            if (node->left == nullptr) 
            {
				// Node with only right child or no child
                Node* temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr) 
            {
				// Node with only left child
                Node* temp = node->left;
                delete node;
                return temp;
            }

			// Node with two children: get the inorder successor (smallest in the right subtree)
            Node* temp = findMin(node->right);
			node->data = temp->data;// Copy the inorder successor's value to this node
			node->right = deleteNode(node->right, temp->data);// Delete the inorder successor
        }
        return node;
    }

	// Function to find a node with a given value in the BST
    Node* findNode(Node* node, int val) 
    {
        if (node == nullptr || node->data == val) return node;
        if (val < node->data) return findNode(node->left, val);
        return findNode(node->right, val);
    }

	// Function to find the successor and predecessor of a given node
    Node* successor(Node* root, Node* node) 
    {
        if (node->right)
            return findMin(node->right);
        Node* succ = nullptr;
        while (root) 
        {
			// If the node's value is less than the root's value, the successor is in the left subtree
            if (node->data < root->data) 
            {
				// Update successor to the current root and move left
                succ = root;
                root = root->left;
            }
			// If the node's value is greater than the root's value, move right
            else if (node->data > root->data)
				root = root->right;// If the node's value is equal to the root's value, we have found the node
            else
                break;
        }
        return succ;
    }

	// Function to find the predecessor of a given node
    Node* predecessor(Node* root, Node* node) 
    {
		// If the node has a left child, the predecessor is the maximum in the left subtree
        if (node->left)
            return findMax(node->left);

		// Otherwise, traverse the tree to find the predecessor
        Node* pred = nullptr;
        while (root) 
        {
			// If the node's value is greater than the root's value, the predecessor is in the right subtree
            if (node->data > root->data) 
            {
				// Update predecessor to the current root and move right
                pred = root;
                root = root->right;
            }

			// If the node's value is less than the root's value, move left
            else if (node->data < root->data)
                root = root->left;

			// If the node's value is equal to the root's value, we have found the node
            else
                break;
        }
        return pred;
    }

public:
    BST() 
    {
		// Initialize the BST with an empty root
        root = nullptr; 
    }

    void insert(int val) 
    {
		// Insert the value into the BST by calling the helper function
        root = insert(root, val); 
    }

    void deleteNode(int val) 
    {
		// Delete a node with the given value from the BST
        root = deleteNode(root, val); 
    }

    void inorder() 
    {
		// Perform inorder traversal and print the values
        inorder(root); 
    }

    void preorder() 
    {
		// Perform preorder traversal and print the values
        preorder(root); 
    }

    void postorder() 
    {
		// Perform postorder traversal and print the values
        postorder(root); 
    }

    void findMin() 
    {
		// Find the minimum node in the BST
        Node* minNode = findMin(root);

		// If a minimum node is found, print its value
        if (minNode) cout << "Min: " << minNode->data << endl;
    }

    void findMax() 
    {
		// Find the maximum node in the BST
        Node* maxNode = findMax(root);

		// If a maximum node is found, print its value
        if (maxNode) cout << "Max: " << maxNode->data << endl;
    }

    void findHeight() 
    {
		// Calculate the height of the BST
        cout << "Height: " << height(root) << endl;
    }

    void findSuccessor(int val) 
    {
		// Find the successor of a node with the given value
        Node* node = findNode(root, val);

		// If the node is found, find its successor
        if (!node) cout << "Node not found.\n";
        else 
        {
			// Call the successor function and print the result
            Node* succ = successor(root, node);

			// If a successor is found, print its value
            if (succ) cout << "Successor: " << succ->data << endl;

			// If no successor is found, print a message
            else cout << "No Successor found.\n";
        }
    }

    void findPredecessor(int val) 
    {
		// Find the predecessor of a node with the given value
        Node* node = findNode(root, val);

		// If the node is found, find its predecessor
        if (!node) cout << "Node not found.\n";
        else 
        {
			// Call the predecessor function and print the result
            Node* pred = predecessor(root, node);

			// If a predecessor is found, print its value
            if (pred) cout << "Predecessor: " << pred->data << endl;
            else cout << "No Predecessor found.\n";
        }
    }
};

int main()
{	// Main function to demonstrate the BST operations
    BST tree;
    int choice, val;

    do 
	{// Display the menu for BST operations
        cout << "\n--- BST Operations Menu ---\n";
        cout << "1. Insert Node\n2. Delete Node\n3. Inorder Traversal\n4. Preorder Traversal\n5. Postorder Traversal\n";
        cout << "6. Find Min\n7. Find Max\n8. Find Height\n9. Find Successor\n10. Find Predecessor\n0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) 
		{// Switch case to handle user choices
        case 1:
            cout << "Enter value to insert: ";
            cin >> val;
            tree.insert(val);
            break;
        case 2:
            cout << "Enter value to delete: ";
            cin >> val;
            tree.deleteNode(val);
            break;
        case 3:
            cout << "Inorder: ";
            tree.inorder();
            cout << endl;
            break;
        case 4:
            cout << "Preorder: ";
            tree.preorder();
            cout << endl;
            break;
        case 5:
            cout << "Postorder: ";
            tree.postorder();
            cout << endl;
            break;
        case 6:
            tree.findMin();
            break;
        case 7:
            tree.findMax();
            break;
        case 8:
            tree.findHeight();
            break;
        case 9:
            cout << "Enter node to find successor: ";
            cin >> val;
            tree.findSuccessor(val);
            break;
        case 10:
            cout << "Enter node to find predecessor: ";
            cin >> val;
            tree.findPredecessor(val);
            break;
        case 0:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice!\n";
        }
    } while (choice != 0);

    return 0;
}
//End of the program