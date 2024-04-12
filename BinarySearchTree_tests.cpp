#include "BinarySearchTree.hpp"
#include "unit_test_framework.hpp"
#include <sstream>


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
TEST(empty_to_both_branches_full) {
 BinarySearchTree<int> bst;
 ASSERT_TRUE(bst.empty());
 ASSERT_EQUAL(bst.size(), 0);
 ASSERT_EQUAL(bst.height(), 0);
 ASSERT_EQUAL(bst.min_element(), bst.end());
 ASSERT_EQUAL(bst.max_element(), bst.end());

 bst.insert(8);
 ASSERT_EQUAL(bst.height(), 1u);
 ASSERT_EQUAL(bst.size(), 1u);
 ASSERT_EQUAL(*bst.min_element(), 8);
 ASSERT_EQUAL(*bst.max_element(), 8);

 bst.insert(10);
 bst.insert(12);
 bst.insert(14);
 ASSERT_EQUAL(bst.height(), 3u);

 bst.insert(6);
 bst.insert(4);
 bst.insert(2);
 ASSERT_EQUAL(bst.height(), 3u);
 ASSERT_EQUAL(bst.size(), 6u);
 ASSERT_EQUAL(*bst.min_element(), 2);
 ASSERT_EQUAL(*bst.max_element(), 14);
}
TEST(test_min_greater_than_n_find){
    BinarySearchTree<int> bst;
    ASSERT_EQUAL(bst.min_greater_than(21), bst.end());
    ASSERT_EQUAL(bst.min_element(), bst.end());
    bst.insert(2);
    bst.insert(4);
    bst.insert(6);
    ASSERT_EQUAL(*bst.min_greater_than(2), 4);
    ASSERT_EQUAL(*(bst.find(4)), 4)
    ASSERT_EQUAL(*bst.begin(), 2);
    ASSERT_EQUAL(*bst.end(), 6);

}
TEST(checking_sorting_invariant) {
    BinarySearchTree<int> bst;
    ASSERT_TRUE(bst.check_sorting_invariant());

    bst.insert(15);
    ASSERT_TRUE(bst.check_sorting_invariant());

    bst.insert(10);
    bst.insert(5);
    bst.insert(20);
    bst.insert(25);
    bst.insert(35);    
    bst.insert(20);
    ASSERT_TRUE(bst.check_sorting_invariant());

}
TEST(traverse_inorder) {
    BinarySearchTree<int> bst;
    ASSERT_TRUE(bst.check_sorting_invariant());

    bst.insert(15);
    ASSERT_TRUE(bst.check_sorting_invariant());
    
    bst.insert(10);
    bst.insert(5);
    bst.insert(20);
    bst.insert(25);
    bst.insert(35);    
    bst.insert(20);
    ASSERT_TRUE(bst.check_sorting_invariant());
}
TEST(traverse_preorder) {
    BinarySearchTree<int> bst;
    ASSERT_TRUE(bst.check_sorting_invariant());

    bst.insert(15);
    ASSERT_TRUE(bst.check_sorting_invariant());
    
    bst.insert(10);
    bst.insert(5);
    bst.insert(20);
    bst.insert(25);
    bst.insert(35);    
    bst.insert(20);
    ASSERT_TRUE(bst.check_sorting_invariant());

}
TEST_MAIN()
