#include <iostream>
#include <tuple>
#include <vector>
using namespace std;

class BinaryTree;

class TreeNode {
public:
  TreeNode(int _value) {
    this->value = _value;
    this->right = this->left = nullptr;
  }
  friend class BinaryTree;
  TreeNode *getSuccessor() {
    TreeNode *current = this->right, *preverious = current;
    while (current && current->left) {
      preverious = current;
      current = current->left;
    }
    preverious->left = nullptr;
    return current;
  }

private:
  int value;
  TreeNode *left, *right;
};

class BinaryTree {
public:
  BinaryTree(int _value) { root = new TreeNode(_value); }
  void clearTree(TreeNode *current) {
    if (!current)
      return;
    clearTree(current->left);
    clearTree(current->right);
    delete current;
  }
  ~BinaryTree() { clearTree(root); }

  TreeNode *find(int _value, TreeNode *current) {
    if (current == nullptr)
      return nullptr;
    else if (_value == current->value)
      return current;
    else if (_value > current->value)
      return find(_value, current->right);
    else
      return find(_value, current->left);
  }

  TreeNode *deleteNode(TreeNode *current, TreeNode *toBeDeleted) {
    if (current) {
      if (toBeDeleted->value > current->value)
        current->right = deleteNode(current->right, toBeDeleted);
      else if (toBeDeleted->value < current->value)
        current->left = deleteNode(current->left, toBeDeleted);
      else {
        if (current->left == nullptr)
          return current->right;
        else if (current->right == nullptr)
          return current->left;

        TreeNode *successor = toBeDeleted->getSuccessor();
        current->value = successor->value;
        current->right = deleteNode(current->right, successor);
        delete successor;
      }
      return current;
    } else
      return nullptr;
  }

  TreeNode *insertNode(TreeNode *current, int _value) {
    if (current == nullptr)
      return new TreeNode(_value);
    else if (_value < current->value)
      current->left = insertNode(current->left, _value);
    else
      current->right = insertNode(current->right, _value);
    return current;
  }

  void addNode(int _value) {
    TreeNode *isInTree = find(_value, root);
    root = ((isInTree) ? deleteNode(root, isInTree) : insertNode(root, _value));
  }

  void inorderRecord(vector<tuple<int, int, int>> &recorder) {
    inorderRecord(recorder, root);
  }
  void inorderRecord(vector<tuple<int, int, int>> &recorder,
                     const TreeNode *current) {
    if (current) {
      inorderRecord(recorder, current->left);
      int left = ((current->left) ? current->left->value : 0),
          right = ((current->right) ? current->right->value : 0);
      recorder.push_back(make_tuple(current->value, left, right));
      inorderRecord(recorder, current->right);
    }
  }

private:
  TreeNode *root;
};

int main() {
  int n;
  while (cin >> n) {
    BinaryTree *tree = new BinaryTree(n);
    vector<tuple<int, int, int>> recorder;
    while (cin >> n && n != -1)
      tree->addNode(n);
    tree->inorderRecord(recorder);
    cout << "node: ";
    for (auto i : recorder)
      cout << get<0>(i) << " ";
    cout << "\nleft: ";
    for (auto i : recorder)
      cout << get<1>(i) << " ";
    cout << "\nright: ";
    for (auto i : recorder)
      cout << get<2>(i) << " ";
    cout << "\n\n";
    recorder.clear();
    tree->~BinaryTree();
  }
}