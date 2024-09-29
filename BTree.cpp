#include <iostream>
#include <cstdlib> // Include this header for rand() and srand()
using namespace std;
 
// B-Tree node structure
struct BTreeNode {
  int keys[4];               // Array of keys
  BTreeNode* children[5];    // Array of child pointers
  int numKeys;               // Current number of keys
  bool isLeaf;               // True if node is leaf
 
  BTreeNode(bool leaf) : isLeaf(leaf), numKeys(0) {}
};
 
// B-Tree class
class BTree {
  BTreeNode* root;           // Pointer to root node
  int t;                     // Minimum degree (t=3 for order 5)
 
public:
  BTree() : root(NULL), t(3) {}
 
  // Function to search for a key in the tree
  BTreeNode* search(int k) {
      return root ? search(root, k) : NULL;
  }
 
  // Function to insert a new key
  void insert(int k);
 
  // Function to delete a key
  void remove(int k);
 
private:
  // Helper functions
  BTreeNode* search(BTreeNode* node, int k);
  void insertNonFull(BTreeNode* node, int k);
  void splitChild(BTreeNode* node, int i);
  void remove(BTreeNode* node, int k);
  void merge(BTreeNode* node, int idx);
};
 
// Search a key in the subtree rooted with this node
BTreeNode* BTree::search(BTreeNode* node, int k) {
  int i = 0;
  while (i < node->numKeys && k > node->keys[i])
      i++;
  if (i < node->numKeys && node->keys[i] == k)
      return node;
  if (node->isLeaf)
      return NULL;
  return search(node->children[i], k);
}
 
// Insert a new key in the B-Tree
void BTree::insert(int k) {
  if (!root) {
      root = new BTreeNode(true);
      root->keys[0] = k;
      root->numKeys = 1;
  } else {
      if (root->numKeys == 4) {
          BTreeNode* s = new BTreeNode(false);
          s->children[0] = root;
          splitChild(s, 0);
          root = s;
      }
      insertNonFull(root, k);
  }
}
 
// Insert a key into a non-full node
void BTree::insertNonFull(BTreeNode* node, int k) {
  int i = node->numKeys - 1;
  if (node->isLeaf) {
      while (i >= 0 && node->keys[i] > k) {
          node->keys[i + 1] = node->keys[i];
          i--;
      }
      node->keys[i + 1] = k;
      node->numKeys++;
  } else {
      while (i >= 0 && node->keys[i] > k)
          i--;
      if (node->children[i + 1]->numKeys == 4) {
          splitChild(node, i + 1);
          if (node->keys[i + 1] < k)
              i++;
      }
      insertNonFull(node->children[i + 1], k);
  }
}
 
// Split the child y of node at index i
void BTree::splitChild(BTreeNode* node, int i) {
  BTreeNode* y = node->children[i];
  BTreeNode* z = new BTreeNode(y->isLeaf);
  z->numKeys = 2;
 
  for (int j = 0; j < 2; j++)
      z->keys[j] = y->keys[j + 3];
  if (!y->isLeaf) {
      for (int j = 0; j < 3; j++)
          z->children[j] = y->children[j + 3];
  }
 
  y->numKeys = 2;
 
  for (int j = node->numKeys; j >= i + 1; j--)
      node->children[j + 1] = node->children[j];
  node->children[i + 1] = z;
 
  for (int j = node->numKeys - 1; j >= i; j--)
      node->keys[j + 1] = node->keys[j];
  node->keys[i] = y->keys[2];
  node->numKeys++;
}
 
// Delete a key from the B-Tree
void BTree::remove(int k) {
  if (!root) return;
  remove(root, k);
  if (root->numKeys == 0) {
      BTreeNode* tmp = root;
      root = root->isLeaf ? NULL : root->children[0];
      delete tmp;
  }
}
 
// Remove a key from the subtree rooted with this node
void BTree::remove(BTreeNode* node, int k) {
  int i = 0;
  while (i < node->numKeys && node->keys[i] < k)
      i++;
  if (i < node->numKeys && node->keys[i] == k) {
      // Key found
      if (node->isLeaf) {
          for (int j = i + 1; j < node->numKeys; j++)
              node->keys[j - 1] = node->keys[j];
          node->numKeys--;
      } else {
          // Complex removal in non-leaf nodes omitted for brevity
          cout << "Deletion in internal nodes is not implemented in this simplified version.\n";
      }
  } else {
      // Key not found, handle children
      if (node->isLeaf) {
          cout << "The key " << k << " is not present in the tree.\n";
          return;
      }
      remove(node->children[i], k);
  }
}
 
int main() {
  BTree tree;
 
  // Insert 100 random elements and display them
  cout << "Inserting random elements:\n";
  for (int i = 0; i < 100; i++) {
      int key = rand() % 1000; // Random keys between 0 and 999
      cout << key << " "; // Display the random key
      tree.insert(key);
  }
  cout << "\n\n";
 
  // Search for a key
  int keyToSearch = 500; // Change this key to test search
  if (tree.search(keyToSearch) != NULL) {
      cout << "Key " << keyToSearch << " found in the tree.\n";
  } else {
      cout << "Key " << keyToSearch << " not found in the tree.\n";
  }
 
  // Delete a key
  int keyToDelete = 500; // Change this key to test delete
  tree.remove(keyToDelete);
  cout << "Attempted to delete " << keyToDelete << " from the tree.\n";
 
  return 0;
}