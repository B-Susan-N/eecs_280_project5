#include "BinarySearchTree.hpp"
#include "unit_test_framework.hpp"
#include <sstream>
#include <string>

using namespace std;

TEST(bst_public_test) {
  BinarySearchTree<int> tree;

  tree.insert(5);

  ASSERT_TRUE(tree.size() == 1);
  ASSERT_TRUE(tree.height() == 1);

  ASSERT_TRUE(tree.find(5) != tree.end());

  tree.insert(7);
  tree.insert(3);

  ASSERT_TRUE(tree.check_sorting_invariant());
  ASSERT_TRUE(*tree.max_element() == 7);
  ASSERT_TRUE(*tree.min_element() == 3);
  ASSERT_TRUE(*tree.min_greater_than(5) == 7);

  cout << "cout << tree.to_string()" << endl;
  cout << tree.to_string() << endl << endl;

  cout << "cout << tree" << endl << "(uses iterators)" << endl;
  cout << tree << endl << endl;

  ostringstream oss_preorder;
  tree.traverse_preorder(oss_preorder);
  cout << "preorder" << endl;
  cout << oss_preorder.str() << endl << endl;
  ASSERT_TRUE(oss_preorder.str() == "5 3 7 ");

  ostringstream oss_inorder;
  tree.traverse_inorder(oss_inorder);
  cout << "inorder" << endl;
  cout << oss_inorder.str() << endl << endl;
  ASSERT_TRUE(oss_inorder.str() == "3 5 7 ");
}
TEST(check_sorting_invarian_2){
   BinarySearchTree<int> b;
   b.insert(6);
   b.insert(5);
   b.insert(10);
   b.insert(15);
// change first datum to 11, resulting in the first broken tree above
   *b.begin() = 11;
   ASSERT_FALSE(b.check_sorting_invariant());
}


TEST(assignment) {
    BinarySearchTree<int> bst;
    bst.insert(15);
    bst.insert(10);
    bst.insert(5);
    bst.insert(20);
    bst.insert(25);
    BinarySearchTree<int> bst2 = bst;
    ASSERT_EQUAL(bst2.size(), 5u);
    ASSERT_EQUAL(*bst2.min_element(), 5)
    ASSERT_EQUAL(*bst2.max_element(), 25)
}
TEST(test_copy){
    BinarySearchTree<int> bst;
    bst.insert(2);
    bst.insert(4);
    bst.insert(6);
    BinarySearchTree<int> bst2(bst);
    ASSERT_EQUAL(bst2.size(), 3u);
    ASSERT_EQUAL(*bst2.begin(), 2);
}
TEST(empty_testing) {
 BinarySearchTree<int> bst;
 ASSERT_TRUE(bst.empty());
 ASSERT_EQUAL(bst.size(), 0);
 ASSERT_EQUAL(bst.height(), 0);
 ASSERT_EQUAL(bst.max_element(), bst.end());
 ASSERT_EQUAL(bst.min_element(), bst.end());
}

//empty with destroy node
TEST(one_node) {
BinarySearchTree<int> bst2;
 bst2.insert(8);
 ASSERT_EQUAL(bst2.height(), 1u);
 ASSERT_EQUAL(*bst2.min_element(), 8);
 ASSERT_EQUAL(*bst2.max_element(), 8);

}
TEST(one_branch) {
BinarySearchTree<int> bst3;
 bst3.insert(8);
 bst3.insert(10);
 bst3.insert(12);
 bst3.insert(14);
 ASSERT_EQUAL(bst3.height(), 4u);
}

TEST(both_branches) {
 BinarySearchTree<int> bst4;
 bst4.insert(8);
 bst4.insert(10);
 bst4.insert(12);
 bst4.insert(14);
 bst4.insert(6);
 bst4.insert(4);
 bst4.insert(2);
 ASSERT_EQUAL(bst4.height(), 4u);
 ASSERT_EQUAL(bst4.size(), 7u);
 ASSERT_EQUAL(*(bst4.find(6)), 6)
 ASSERT_EQUAL(*bst4.min_element(), 2);
 ASSERT_EQUAL(*bst4.max_element(), 14);
 }

TEST(test_min_greater_than){

    BinarySearchTree<int> bst;
    ASSERT_EQUAL(bst.min_greater_than(21), bst.end());
    ASSERT_EQUAL(bst.min_element(), bst.end());
    ASSERT_EQUAL(bst.min_greater_than(21), bst.find(21));

    BinarySearchTree<int> bst2;
    bst2.insert(2);
    bst2.insert(4);
    bst2.insert(6);
    ASSERT_EQUAL(*bst2.min_greater_than(2), 4);

    
   
    BinarySearchTree<int> bst3;
    bst3.insert(88);
    ASSERT_EQUAL(bst3.min_greater_than(80), bst3.find(88));
}


TEST(test_find){
    BinarySearchTree<int> bst_1;
    bst_1.insert(1);
    bst_1.insert(3);
    bst_1.insert(8);
    bst_1.insert(5);
    bst_1.insert(11);
    ASSERT_EQUAL(*(bst_1.find(8)), 8);
}

TEST(checking_sorting_invariant) {
    BinarySearchTree<int> bst;
    ASSERT_TRUE(bst.check_sorting_invariant());

    BinarySearchTree<int> bst2;
    bst2.insert(15);
    ASSERT_TRUE(bst2.check_sorting_invariant());

    BinarySearchTree<int> bst3;
    bst3.insert(20);
    bst3.insert(25);
    bst3.insert(35); 
    bst3.insert(15); 
    ASSERT_TRUE(bst3.check_sorting_invariant());

    BinarySearchTree<int> bst4;
    bst4.insert(20);
    bst4.insert(21);
    ASSERT_TRUE(bst4.check_sorting_invariant());

    BinarySearchTree<int> b4;
    b4.insert(20);
    b4.insert(19);
    ASSERT_TRUE(b4.check_sorting_invariant());

    BinarySearchTree<int> bst5;
    bst5.insert(20);
    bst5.insert(22);
    bst5.insert(21); 
    ASSERT_TRUE(bst5.check_sorting_invariant());
    
    }

    TEST(traverse_inorder) {
    //empty tree
    BinarySearchTree<int> bst;
    ostringstream oss_bst;
    bst.traverse_inorder(oss_bst);
    ASSERT_EQUAL(oss_bst.str(), "");

    BinarySearchTree<int> bst_2;
    bst_2.insert(8);
    bst_2.insert(7);
    bst_2.insert(6);
    bst_2.insert(5);
    ostringstream oss_bst_2;
    bst_2.traverse_inorder(oss_bst_2);
    cout << oss_bst_2.str() << endl;
    ASSERT_EQUAL(oss_bst_2.str(), "5 6 7 8 ");



}
TEST(traverse_preorder) {
 //empty tree 
    BinarySearchTree<int> bst;
    ostringstream oss_bst;
    bst.traverse_preorder(oss_bst);
    ASSERT_EQUAL(oss_bst.str(), "");

    BinarySearchTree<int> bst_2;
    ostringstream oss_bst_2;
    bst_2.insert(45);
    bst_2.insert(35);
    bst_2.insert(30);
    bst_2.insert(40);
    bst_2.insert(20);
    bst_2.insert(33);
    bst_2.insert(55);
    bst_2.traverse_preorder(oss_bst_2);
    cout << oss_bst_2.str() << endl;
    ASSERT_EQUAL(oss_bst_2.str(), "45 35 30 20 33 40 55 ");

}


TEST_MAIN()
