#include "BinarySearchTree.hpp"
#include "unit_test_framework.hpp"
#include <sstream>
#include <string>

using namespace std;

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

 //ASSERT_NOT_EQUAL(bst.max_element(), bst);
 //ASSERT_NOT_EQUAL(bst.min_element(), bst);
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
/*
TEST(test_min_greater_than){
    BinarySearchTree<int> bst;
    ASSERT_EQUAL(bst.min_greater_than(21), bst.end());
    ASSERT_EQUAL(bst.min_element(), bst.end());

    BinarySearchTree<int> bst2;
    bst2.insert(2);
    bst2.insert(4);
    bst2.insert(6);
    ASSERT_EQUAL(*bst2.min_greater_than(2), 4);
    ASSERT_EQUAL(*bst2.begin(), 2);
    ASSERT_EQUAL(*bst2.end(), 6);

}
*/

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
/*
BinarySearchTree<int> bst4;
    bst4.insert(20);
    bst4.insert(25);
    bst4.insert(35); 
    bst4.insert(15);
    bst4.insert(15);
    ASSERT_FALSE(bst4.check_sorting_invariant());
*/
    
    }

    TEST(traverse_inorder) {
    //empty tree
    BinarySearchTree<int> bst;
    ostringstream oss_bst;
    bst.traverse_inorder(oss_bst);
    ASSERT_EQUAL(oss_bst.str(), "");
}
TEST(traverse_preorder) {
 //empty tree 
    BinarySearchTree<int> bst;
    ostringstream oss_bst;
    bst.traverse_preorder(oss_bst);
    ASSERT_EQUAL(oss_bst.str(), "");
}


TEST_MAIN()
