#include "catch2/catch_test_macros.hpp"
#include <fstream>
#include <iostream>
#include <vector>

namespace binary_tree {
struct Node {
  int val;
  Node* left = nullptr;
  Node* right = nullptr;
};

// Free allocated memory
void free(Node* root) {
  if (!root)
    return;

  free(root->left);
  free(root->right);
}

// Function to insert a new node into the BST
Node* insert(Node* root, int val) {
  if (root == nullptr) {
    return new Node(val);
  }

  if (val < root->val) {
    root->left = insert(root->left, val);
  } else if (val > root->val) {
    root->right = insert(root->right, val);
  }
  return root;
}

// Insert multiple values to the binary search tree.
Node* insert(Node* root, std::vector<int> values) {
  for (const auto val : values) {
    root = insert(root, val);
  }
  return root;
}

// Function to search for a node in the BST
Node* search(Node* root, int val) {
  if (root == nullptr || root->val == val) {
    return root;
  }

  return (val < root->val) ? search(root->left, val) : search(root->right, val);
}

// Function to traverse the BST in inorder
void inorder_traversal(const Node* root) {
  if (root == nullptr) {
    return;
  }

  inorder_traversal(root->left);
  std::cout << root->val << " ";
  inorder_traversal(root->right);
}

void preorder_traversal(const Node* root) {
  if (!root)
    return;

  std::cout << root->val << " ";
  preorder_traversal(root->left);
  preorder_traversal(root->right);
}

void postorder_traversal(const Node* root) {
  if (!root)
    return;

  postorder_traversal(root->left);
  postorder_traversal(root->right);
  std::cout << root->val << " ";
}

void write_dot(const Node* root, std::ofstream& os) {
  if (root == nullptr) {
    return;
  }

  os << root->val << " [label=\"" << root->val << "\"];\n";

  if (root->left) {
    write_dot(root->left, os);
    os << root->val << " -> " << root->left->val << ";\n";
  }

  if (root->right) {
    write_dot(root->right, os);
    os << root->val << " -> " << root->right->val << ";\n";
  }
}

void write_dot(const Node* root, const std::string& dot_file) {
  std::ofstream out(dot_file);
  out << "digraph G {\n";
  write_dot(root, out);
  out << "}";
}
}  // namespace binary_tree

namespace {
auto create_test_graph_1() {
  return binary_tree::insert(nullptr, {5, 3, 7, 2, 4, 6, 8});
}

}  // namespace

TEST_CASE("Write dot file") {
  write_dot(create_test_graph_1(), "binary-tree.dot");
}

TEST_CASE("traversal algorithms") {
  auto* root = create_test_graph_1();
  REQUIRE(root);

  SECTION("inorder") {
    std::cout << "Inorder traversal: ";
    inorder_traversal(root);
    std::cout << std::endl;
  }

  SECTION("pre-order traversal") {
    std::cout << "Pre-order traversal: ";
    preorder_traversal(root);
    std::cout << std::endl;
  }

  SECTION("post-order") {
    std::cout << "Post-order traversal: ";
    postorder_traversal(root);
    std::cout << std::endl;
  }

  CHECK(binary_tree::search(root, 7));
  CHECK_FALSE(binary_tree::search(root, 9));
}
