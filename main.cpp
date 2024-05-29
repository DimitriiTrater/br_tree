#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "br_tree.hpp"

/*           10 B          */
TEST_CASE("insert1", "[root]") {
  BRTree tree;
  tree.insert(10);
  REQUIRE(tree.getLeft(10) == nullptr);
  REQUIRE(tree.getRight(10) == nullptr);
  REQUIRE(tree.getParent(10) == nullptr);
  REQUIRE(tree.getColor(10) == BRTree::Color::BLACK);
  REQUIRE(tree.getRoot() == tree.search(10));
}

/*        10 B
        /    \
      9 R     12 R
                              */
TEST_CASE("insert2", "[black parent]") {
  BRTree tree;
  tree.insert(10);
  tree.insert(9);
  tree.insert(12);
  REQUIRE(tree.getLeft(10) == tree.search(9));
  REQUIRE(tree.getRight(10) == tree.search(12));
  REQUIRE(tree.getParent(10) == nullptr);
  REQUIRE(tree.getParent(9) == tree.search(10));
  REQUIRE(tree.getParent(12) == tree.search(10));
  REQUIRE(tree.getColor(9) == BRTree::Color::RED);
  REQUIRE(tree.getColor(10) == BRTree::Color::BLACK);
  REQUIRE(tree.getColor(12) == BRTree::Color::RED);
  REQUIRE(tree.getRoot() == tree.search(10));
}
/*        10 B                  10 B
         /    \                /     \
       7 R     12 R   ->     7 B      12 B
         \                     \
           9 R                   9 R          */
TEST_CASE("insert3", "[red parent, red uncle]") {
  BRTree tree;
  tree.insert(10);
  tree.insert(7);
  tree.insert(12);
  tree.insert(9);
  REQUIRE(tree.getLeft(7) == nullptr);
  REQUIRE(tree.getRight(7) == tree.search(9));
  REQUIRE(tree.getLeft(10) == tree.search(7));
  REQUIRE(tree.getRight(10) == tree.search(12));
  REQUIRE(tree.getParent(10) == nullptr);
  REQUIRE(tree.getParent(7) == tree.search(10));
  REQUIRE(tree.getParent(9) == tree.search(7));
  REQUIRE(tree.getParent(12) == tree.search(10));
  REQUIRE(tree.getColor(7) == BRTree::Color::BLACK);
  REQUIRE(tree.getColor(9) == BRTree::Color::RED);
  REQUIRE(tree.getColor(10) == BRTree::Color::BLACK);
  REQUIRE(tree.getColor(12) == BRTree::Color::BLACK);
}

/*        10 B                  10 B
        /    \                /     \
      7 B     12 B   ->     8 B      12 B
        \                  /   \
          9 R             7 R   9 R
         /
        8 R
                                              */
TEST_CASE("insert4",
          "[red parent, black uncle || !uncle (turn right, turn left)]") {
  BRTree tree;
  tree.insert(10);
  tree.insert(7);
  tree.insert(12);
  tree.insert(9);
  tree.insert(8);
  REQUIRE(tree.getLeft(8) == tree.search(7));
  REQUIRE(tree.getRight(8) == tree.search(9));
  REQUIRE(tree.getLeft(10) == tree.search(8));
  REQUIRE(tree.getRight(10) == tree.search(12));
  REQUIRE(tree.getLeft(12) == nullptr);
  REQUIRE(tree.getRight(12) == nullptr);
  REQUIRE(tree.getParent(10) == nullptr);
  REQUIRE(tree.getParent(7) == tree.search(8));
  REQUIRE(tree.getParent(8) == tree.search(10));
  REQUIRE(tree.getParent(9) == tree.search(8));
  REQUIRE(tree.getParent(12) == tree.search(10));
  REQUIRE(tree.getColor(7) == BRTree::Color::RED);
  REQUIRE(tree.getColor(8) == BRTree::Color::BLACK);
  REQUIRE(tree.getColor(9) == BRTree::Color::RED);
  REQUIRE(tree.getColor(10) == BRTree::Color::BLACK);
  REQUIRE(tree.getColor(12) == BRTree::Color::BLACK);
  REQUIRE(tree.getRoot() == tree.search(10));
}

/*        10 B                  10 B
        /    \                /     \
      7 B     12 B   ->     8 B      12 B
        \                  /   \
          8 R             7 R   9 R
            \
             9 R
                                              */
TEST_CASE("insert5", "[red parent, black uncle || !uncle (turn left)]") {
  BRTree tree;
  tree.insert(10);
  tree.insert(7);
  tree.insert(12);
  tree.insert(8);
  tree.insert(9);
  REQUIRE(tree.getLeft(8) == tree.search(7));
  REQUIRE(tree.getRight(8) == tree.search(9));
  REQUIRE(tree.getLeft(10) == tree.search(8));
  REQUIRE(tree.getRight(10) == tree.search(12));
  REQUIRE(tree.getParent(10) == nullptr);
  REQUIRE(tree.getParent(7) == tree.search(8));
  REQUIRE(tree.getParent(8) == tree.search(10));
  REQUIRE(tree.getParent(9) == tree.search(8));
  REQUIRE(tree.getParent(12) == tree.search(10));
  REQUIRE(tree.getColor(7) == BRTree::Color::RED);
  REQUIRE(tree.getColor(8) == BRTree::Color::BLACK);
  REQUIRE(tree.getColor(9) == BRTree::Color::RED);
  REQUIRE(tree.getColor(10) == BRTree::Color::BLACK);
  REQUIRE(tree.getColor(12) == BRTree::Color::BLACK);
  REQUIRE(tree.getRoot() == tree.search(10));
}

/*        10 B                  10 B
        /    \                /     \
      7 B     13 B   ->     7 B      12 B
             /                      /   \
          11 R                    11 R   13 R
            \
             12 R
                                              */
TEST_CASE("insert6",
          "[red parent, black uncle || !uncle (turn left, turn right)]") {
  BRTree tree;
  tree.insert(10);
  tree.insert(7);
  tree.insert(13);
  tree.insert(11);
  tree.insert(12);
  REQUIRE(tree.getLeft(10) == tree.search(7));
  REQUIRE(tree.getRight(10) == tree.search(12));
  REQUIRE(tree.getLeft(12) == tree.search(11));
  REQUIRE(tree.getRight(12) == tree.search(13));
  REQUIRE(tree.getParent(10) == nullptr);
  REQUIRE(tree.getParent(7) == tree.search(10));
  REQUIRE(tree.getParent(11) == tree.search(12));
  REQUIRE(tree.getParent(12) == tree.search(10));
  REQUIRE(tree.getParent(13) == tree.search(12));
  REQUIRE(tree.getColor(7) == BRTree::Color::BLACK);
  REQUIRE(tree.getColor(10) == BRTree::Color::BLACK);
  REQUIRE(tree.getColor(11) == BRTree::Color::RED);
  REQUIRE(tree.getColor(12) == BRTree::Color::BLACK);
  REQUIRE(tree.getColor(13) == BRTree::Color::RED);
  REQUIRE(tree.getRoot() == tree.search(10));
}

/*        10 B                  10 B
        /    \                /     \
      7 B     13 B   ->     7 B      12 B
             /                      /   \
          12 R                    11 R   13 R
         /
        11 R
                                              */
TEST_CASE("insert7", "[red parent, black uncle || !uncle (turn right)]") {
  BRTree tree;
  tree.insert(10);
  tree.insert(7);
  tree.insert(13);
  tree.insert(12);
  tree.insert(11);
  REQUIRE(tree.getLeft(10) == tree.search(7));
  REQUIRE(tree.getRight(10) == tree.search(12));
  REQUIRE(tree.getLeft(12) == tree.search(11));
  REQUIRE(tree.getRight(12) == tree.search(13));
  REQUIRE(tree.getParent(10) == nullptr);
  REQUIRE(tree.getParent(7) == tree.search(10));
  REQUIRE(tree.getParent(11) == tree.search(12));
  REQUIRE(tree.getParent(12) == tree.search(10));
  REQUIRE(tree.getParent(13) == tree.search(12));
  REQUIRE(tree.getColor(7) == BRTree::Color::BLACK);
  REQUIRE(tree.getColor(10) == BRTree::Color::BLACK);
  REQUIRE(tree.getColor(11) == BRTree::Color::RED);
  REQUIRE(tree.getColor(12) == BRTree::Color::BLACK);
  REQUIRE(tree.getColor(13) == BRTree::Color::RED);
  REQUIRE(tree.getRoot() == tree.search(10));
}

/*           10 B
           /     \
         7 B      12 B
                 /   \
               11 R   13 R      */
TEST_CASE("remove1", "[]") {
  BRTree tree;
  tree.insert(10);
  tree.insert(7);
  tree.insert(13);
  tree.insert(12);
  tree.insert(11);
  tree.remove(15);
  REQUIRE(tree.getLeft(10) == tree.search(7));
  REQUIRE(tree.getRight(10) == tree.search(12));
  REQUIRE(tree.getLeft(12) == tree.search(11));
  REQUIRE(tree.getRight(12) == tree.search(13));
  REQUIRE(tree.getParent(10) == nullptr);
  REQUIRE(tree.getParent(7) == tree.search(10));
  REQUIRE(tree.getParent(11) == tree.search(12));
  REQUIRE(tree.getParent(12) == tree.search(10));
  REQUIRE(tree.getParent(13) == tree.search(12));
  REQUIRE(tree.getColor(7) == BRTree::Color::BLACK);
  REQUIRE(tree.getColor(10) == BRTree::Color::BLACK);
  REQUIRE(tree.getColor(11) == BRTree::Color::RED);
  REQUIRE(tree.getColor(12) == BRTree::Color::BLACK);
  REQUIRE(tree.getColor(13) == BRTree::Color::RED);
  REQUIRE(tree.getRoot() == tree.search(10));
}

/*           10 B                         11 B
           /     \                      /     \
         7 B      13 R          ->    7 B      13 R
                 /   \                        /   \
               12 B   14 B                  12 B   14 B
              /
            11 R                                              */
TEST_CASE("remove2", "[root || node->right]") {
  BRTree tree;
  tree.insert(10);
  tree.insert(7);
  tree.insert(14);
  tree.insert(12);
  tree.insert(13);
  tree.insert(11);
  tree.remove(10);
  REQUIRE(tree.getLeft(11) == tree.search(7));
  REQUIRE(tree.getRight(11) == tree.search(13));
  REQUIRE(tree.getLeft(13) == tree.search(12));
  REQUIRE(tree.getRight(13) == tree.search(14));
  REQUIRE(tree.getParent(11) == nullptr);
  REQUIRE(tree.getParent(7) == tree.search(11));
  REQUIRE(tree.getParent(13) == tree.search(11));
  REQUIRE(tree.getParent(12) == tree.search(13));
  REQUIRE(tree.getParent(14) == tree.search(13));
  REQUIRE(tree.getColor(7) == BRTree::Color::BLACK);
  REQUIRE(tree.getColor(11) == BRTree::Color::BLACK);
  REQUIRE(tree.getColor(12) == BRTree::Color::BLACK);
  REQUIRE(tree.getColor(13) == BRTree::Color::RED);
  REQUIRE(tree.getColor(14) == BRTree::Color::BLACK);
  REQUIRE(tree.getRoot() == tree.search(11));
}

/*        10 B                  10 B
        /    \                /     \
      7 B     12 B   ->     7 B      12 B
             /   \                      \
          11 R    13 R                   13 R
                                              */
TEST_CASE("remove3", "[leaf]") {
  BRTree tree;
  tree.insert(10);
  tree.insert(7);
  tree.insert(12);
  tree.insert(13);
  tree.insert(11);
  tree.remove(11);
  REQUIRE(tree.getLeft(10) == tree.search(7));
  REQUIRE(tree.getRight(10) == tree.search(12));
  REQUIRE(tree.getLeft(12) == nullptr);
  REQUIRE(tree.getRight(12) == tree.search(13));
  REQUIRE(tree.getParent(10) == nullptr);
  REQUIRE(tree.getParent(7) == tree.search(10));
  REQUIRE(tree.getParent(12) == tree.search(10));
  REQUIRE(tree.getParent(13) == tree.search(12));
  REQUIRE(tree.getColor(7) == BRTree::Color::BLACK);
  REQUIRE(tree.getColor(10) == BRTree::Color::BLACK);
  REQUIRE(tree.getColor(12) == BRTree::Color::BLACK);
  REQUIRE(tree.getColor(13) == BRTree::Color::RED);
  REQUIRE(tree.getRoot() == tree.search(10));
}

/*        10 B                  10 B
        /    \                /     \
      7 B     12 B   ->     7 B      11 B
             /
          11 R                                 */
TEST_CASE("remove4", "[node->left]") {
  BRTree tree;
  tree.insert(10);
  tree.insert(7);
  tree.insert(12);
  tree.insert(11);
  tree.remove(12);
  REQUIRE(tree.getLeft(10) == tree.search(7));
  REQUIRE(tree.getRight(10) == tree.search(11));
  REQUIRE(tree.getParent(10) == nullptr);
  REQUIRE(tree.getParent(7) == tree.search(10));
  REQUIRE(tree.getParent(11) == tree.search(10));
  REQUIRE(tree.getColor(7) == BRTree::Color::BLACK);
  REQUIRE(tree.getColor(10) == BRTree::Color::BLACK);
  REQUIRE(tree.getColor(11) == BRTree::Color::BLACK);
  REQUIRE(tree.getRoot() == tree.search(10));
}
