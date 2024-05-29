#include "br_tree.hpp"

auto BRTree::deleteNode(Node *node) -> void {
  if (node) {
    deleteNode(node->left);
    deleteNode(node->right);
    delete node;
  }
}

auto BRTree::changeColor(Node *node) -> void {
  node->parent->parent->left->color = node->parent->parent->right->color =
      Color::BLACK;
  node->parent->parent->color = Color::RED;
}

auto BRTree::rotateRight(Node *node) -> void {
  Node *a = node->left;
  node->left = a->right;
  if (a->right) {
    a->right->parent = node;
  }
  a->parent = node->parent;
  if (node->parent == nullptr) {
    root = a;

  } else if (node == node->parent->right) {
    node->parent->right = a;

  } else {
    node->parent->left = a;
  }
  a->right = node;
  node->parent = a;
}

auto BRTree::rotateLeft(Node *node) -> void {
  Node *a = node->right;
  node->right = a->left;
  if (a->left) {
    a->left->parent = node;
  }
  a->parent = node->parent;
  if (node->parent == nullptr) {
    root = a;
  } else if (node == node->parent->left) {
    node->parent->left = a;
  } else {
    node->parent->right = a;
  }
  a->left = node;
  node->parent = a;
}

auto BRTree::insert(Node *node, int value) -> void {
  Node *parent = nullptr;
  Node *current = node;
  while (current) {
    parent = current;
    if (value == current->value) {
      return;
    }
    if (value < current->value) {
      current = current->left;
    }
    else /* (value > current->value) */ {
      current = current->right;
    }
  }
  current = new Node(value);
  current->parent = parent;
  if (current->parent == nullptr) {
    root = current;
    root->color = Color::BLACK;
  } else {
    if (value < parent->value) {
      parent->left = current;
    } else {
      parent->right = current;
    }
    insertBalance(current);
  }
}

auto BRTree::insertBalance(Node *current) -> void {
  while (
      current != root
  and current->parent->color == Color::RED
  and current->color == Color::RED) {
    Node *uncle = nullptr;
    if (current->parent->parent->left == current->parent) {
      uncle = current->parent->parent->right;
    } else {
      uncle = current->parent->parent->left;
    }

    if (uncle == nullptr or uncle->color == Color::BLACK) {
      if (current->parent->parent->left == current->parent and
          current->parent->left == current) {

        current->parent->color = Color::BLACK;
        current->parent->parent->color = Color::RED;

        rotateRight(current->parent->parent);

      } else if (current->parent->parent->right == current->parent and
                 current->parent->right == current) {

        current->parent->color = Color::BLACK;
        current->parent->parent->color = Color::RED;
        rotateLeft(current->parent->parent);
      } else if (current->parent->parent->left == current->parent and
                 current->parent->right == current) {
        current->color = Color::BLACK;
        current->parent->parent->color = Color::RED;
        rotateLeft(current->parent);
        rotateRight(current->parent);
      } else if (current->parent->parent->right == current->parent and
                 current->parent->left == current) {
        current->color = Color::BLACK;
        current->parent->parent->color = Color::RED;
        rotateRight(current->parent);
        rotateLeft(current->parent);
      }
    } else if (uncle->color == Color::RED) {
      changeColor(current);
      current = current->parent->parent;
      root->color = Color::BLACK;
    }
  }
}

auto BRTree::remove(Node *node, int value) -> void {
  if (node) {
    if (value < node->value) {
      remove(node->left, value);
    } else if (value > node->value) {
      remove(node->right, value);
    } else if (value == node->value) {
      Node *parent = node->parent;
      if (node == root and not node->left and not node->right) {
        delete node;
        root = nullptr;
      } else if (node->left == nullptr and node->right == nullptr) {
        if (node->parent->left == node) {
          delete node;
          parent->left = nullptr;
        } else /* node->parent-right == node */ {
          delete node;
          parent->right = nullptr;
        }
      } else if (node->left != nullptr and node->right == nullptr) {
        Node *left = node->left;
        if (node->color == Color::RED) {
          if (parent->left == node) {
            delete node;
            parent->left = left;
          } else {
            delete node;
            parent->right = left;
          }
        } else {
          if (node->left->color == Color::RED) {
            if (parent->left == node) {
              delete node;
              parent->left = left;
              parent->left->color = Color::BLACK;
            } else {
              delete node;
              parent->right = left;
              parent->right->color = Color::BLACK;
            }
          } else {
            if (parent->left == node) {
              delete node;
              parent->left = left;
              parent->left->color = Color::BLACK_BLACK;
              removeBalance(parent->left);
            } else {
              delete node;
              parent->right = left;
              parent->right->color = Color::BLACK_BLACK;
              removeBalance(parent->right);
            }
          }
        }
        left->parent = parent;
      } else {
        Node *min = node->right;
        while (min->left) {
          min = min->left;
        }
        int a = min->value;
        remove(min->value);
        node->value = a;
      }
    }
  }
}

auto BRTree::removeBalance(Node *node) -> void {
  Node *current = node;

  while (current->color == Color::BLACK_BLACK) {
    Node *brother = getSibling(current);
    if ((brother->left && brother->left->color == Color::RED) ||
        (brother->right && brother->right->color == Color::RED)) {
      if (current->parent->left == current) {
        if (!brother->right || brother->right->color == Color::BLACK) {
          brother->left->color = Color::BLACK;
          brother->color = Color::RED;
          rotateRight(brother);
        } else {
          brother->right->color = Color::BLACK;
          brother->color = current->parent->color;
          current->parent->color = Color::BLACK;
          current->color = Color::BLACK;
          rotateLeft(current->parent);
        }
      } else {
        if (brother->right && brother->left->color == Color::BLACK) {
          brother->right->color = Color::BLACK;
          brother->color = Color::RED;
          rotateLeft(brother);
        } else {
          brother->left->color = Color::BLACK;
          brother->color = current->parent->color;
          current->parent->color = Color::BLACK;
          current->color = Color::BLACK;
          rotateRight(current->parent);
        }
      }
    } else {
      if (current->parent->color == Color::RED) {
        current->parent->color = Color::BLACK;
        brother->color = Color::RED;
        current->color = Color::BLACK;
      } else {
        if (brother->color == Color::BLACK) {
          current->parent->color = Color::BLACK_BLACK;
          brother->color = Color::RED;
          current->color = Color::BLACK;
          current = current->parent;
        } else if (brother->color == Color::RED) {
          if (current->parent->left == current) {
            brother->color = Color::BLACK;
            current->parent->color = Color::RED;
            rotateLeft(current->parent);
          } else {
            brother->color = Color::BLACK;
            current->parent->color = Color::RED;
            rotateRight(current->parent);
          }
        }
      }
    }
  }
}
