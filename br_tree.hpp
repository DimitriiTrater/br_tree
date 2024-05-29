#pragma once
#include <iostream>
#include <ostream>
#include <ranges>

class BRTree {
public:
  enum class Color { BLACK, RED, BLACK_BLACK };

private:
  struct Node {
    Node(int value)
        : left(nullptr), right(nullptr), parent(nullptr), color(Color::RED), value(value) {}

    Node *parent;
    Node *left;
    Node *right;
    Color color;
    int value{};
  };

  Node *root;

  auto deleteNode(Node *node) -> void;

  auto changeColor(Node *node) -> void;

  Node *getSibling(Node *node) const {
    if (node and node->parent) {
      return node->parent->left == node ? node->parent->right
                                        : node->parent->left;
    }
    return nullptr;
  }

  auto rotateRight(Node *node) -> void;
  auto rotateLeft(Node *node) -> void;

  auto insert(Node *node, int value) -> void;
  auto insertBalance(Node *current) -> void;

  auto remove(Node *node, int value) -> void;
  auto removeBalance(Node *current) -> void;

  std::ostream &debugPrint(std::ostream &stream) const {
    debugPrint(root, stream, 0);
    return stream;
  }

  std::ostream &debugPrint(Node *node, std::ostream &stream, int level) const {
    Node *current = node;
    if (current != nullptr) {
      std::string a{};
      if (current->color == Color::RED) {
        a = "r";
      } else {
        a = "b";
      }
      debugPrint(current->right, stream, level + 1);
      for (int i : std::ranges::iota_view{0, level}) {
        stream << '-';
      }
      stream << current->value << " (" << a << ")"
             << "\n";
      debugPrint(current->left, stream, level + 1);
    }
    return stream;
  }

public:
  BRTree() : root(nullptr) {}
  ~BRTree() { deleteNode(root); }

  Node *getLeft(int value) {
    Node *node = search(value);
    return node->left;
  }

  Node *getRight(int value) {
    Node *node = search(value);
    return node->right;
  }

  Node *getParent(int value) {
    Node *node = search(value);
    return node->parent;
  }

  Color getColor(int value) {
    Node *node = search(value);
    return node->color;
  }

  Node *getRoot() { return root; }

  friend std::ostream &operator<<(std::ostream &stream, BRTree &tree) {
    return tree.debugPrint(std::cout);
  }

  Node *search(int value) const {
    Node *current = root;
    while (current != nullptr) {
      if (current->value == value) {
        break;
      } else {
        if (value > current->value) {
          current = current->right;
        } else {
          current = current->left;
        }
      }
    }
    return current;
  }

  auto insert(int value) -> void { insert(root, value); }
  auto remove(int value) -> void { remove(root, value); }
};
