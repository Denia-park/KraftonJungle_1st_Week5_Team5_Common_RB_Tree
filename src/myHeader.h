
#ifndef _MY_HEADER_H_
#define _MY_HEADER_H_

#include "rbtree.h"

void print_node_inorder(rbtree* t, node_t* curNode);
void print_tree_inorder(rbtree* t);

void tree_insert_fixup(rbtree* t, node_t* p);

node_t* insert_fixupLeftCase(rbtree* t, node_t* z);
node_t* insert_fixupRightCase(rbtree* t, node_t* z);

node_t* insert_fixupLeftCase_1(node_t* targetNode, node_t* uncle);
node_t* insert_fixupLeftCase_2(rbtree* t, node_t* targetNode);
node_t* insert_fixupLeftCase_3(rbtree* t, node_t* targetNode);

node_t* insert_fixupRightCase_1(node_t* targetNode, node_t* uncle);
node_t* insert_fixupRightCase_2(rbtree* t, node_t* targetNode);
node_t* insert_fixupRightCase_3(rbtree* t, node_t* targetNode);

node_t* makeNilNode();
node_t* makeNewNode(rbtree* t, const key_t key);

void left_rotate(rbtree* t, node_t* targetNode);
void right_rotate(rbtree* t, node_t* targetNode);

void findTest(rbtree* t, int testValue);
void find_max_test(rbtree* t, int testValue);
void find_min_test(rbtree* t, int testValue);

int rbtree_delete_node(rbtree* t, const key_t key);
node_t* findTreeSuccessor(rbtree* t, node_t* targetNode);
node_t* find_min_in_subtree(node_t* p_nil, node_t* subTreeRootNode);
node_t* find_max_in_subtree(node_t* p_nil, node_t* subTreeRootNode);
void rbtree_delete_fixup(rbtree* t, node_t* childNode);
node_t* delete_fixupLeftCase(rbtree* t, node_t* targetNode);
node_t* delete_fixupRightCase(rbtree* t, node_t* targetNode);

node_t* delete_fixupLeftCase_1(rbtree* t, node_t* targetNode, node_t* sibling);
node_t* delete_fixupRightCase_1(rbtree* t, node_t* targetNode, node_t* sibling);
node_t* delete_fixupLeftCase_2(node_t* targetNode, node_t* sibling);
node_t* delete_fixupRightCase_2(node_t* targetNode, node_t* sibling);
node_t* delete_fixupLeftCase_3(rbtree* t, node_t* targetNode, node_t* sibling);
node_t* delete_fixupRightCase_3(rbtree* t, node_t* targetNode, node_t* sibling);
node_t* delete_fixupLeftCase_4(rbtree* t, node_t* targetNode, node_t* sibling);
node_t* delete_fixupRightCase_4(rbtree* t, node_t* targetNode, node_t* sibling);


int rbtree_to_array(const rbtree* t, key_t* arr, const size_t n);

void freeMemoryByPostorder(rbtree* t, node_t* curNode);

rbtree* testMakeRbTree();
void testMaxValueInEmptyRbTree(rbtree* t);
void testMinValueInEmptyRbTree(rbtree* t);
void testInsertValueToRbTree(rbtree* t);
void testFindValueInRbTree(rbtree* t);
void testFindMaxMinValueInRbTree(rbtree* t);
void testDeleteValueInRbTree(rbtree* t);
void testRbTreeToArr(rbtree* t);

#define RED 0
#define BLACK 1

#define SUCCESS 1
#define FAIL 0

#define TRUE 1
#define FALSE 0 

#endif  // _MY_HEADER_H_