#include <stdlib.h>
#include <stdio.h>

#include "myHeader.h"

int arrCounter = 0;

rbtree* new_rbtree(void) {
    rbtree* p = (rbtree*) calloc(1, sizeof(rbtree));

    p->nil = makeNilNode();
    p->root = p->nil;

    return p;
}

node_t* rbtree_insert(rbtree* t, const key_t key) {
    node_t* searchNodeParent = t->nil;
    node_t* searchNode = t->root;

    while (searchNode != t->nil) {
        searchNodeParent = searchNode;

        if (key < searchNode->key) {
            searchNode = searchNode->left;
        } else {
            searchNode = searchNode->right;
        }
    }

    node_t* p_newInsertNode = makeNewNode(t, key);
    p_newInsertNode->parent = searchNodeParent;

    if (searchNodeParent == t->nil) {
        t->root = p_newInsertNode;
    } else {
        if (key < searchNodeParent->key) {
            searchNodeParent->left = p_newInsertNode;
        } else {
            searchNodeParent->right = p_newInsertNode;
        }
    }

    tree_insert_fixup(t, p_newInsertNode);

    return t->root;
}

node_t* rbtree_find(const rbtree* t, const key_t key) {
    node_t* searchNode = t->root;

    while (searchNode != t->nil && searchNode->key != key) {
        if (key < searchNode->key) {
            searchNode = searchNode->left;
        } else {
            searchNode = searchNode->right;
        }
    }

    if (searchNode == t->nil) {
        return NULL;
    } else {
        return searchNode;
    }
}

node_t* rbtree_min(const rbtree* t) {
    node_t* searchNode = find_min_in_subtree(t->nil, t->root);

    if (searchNode == t->nil) {
        return t->nil;
    }

    return searchNode;
}

node_t* find_min_in_subtree(node_t* p_nil, node_t* subTreeRootNode) {
    if (subTreeRootNode == p_nil) {
        return p_nil;
    }

    while (subTreeRootNode->left != p_nil) {
        subTreeRootNode = subTreeRootNode->left;
    }

    return subTreeRootNode;
}

node_t* rbtree_max(const rbtree* t) {
    node_t* searchNode = find_max_in_subtree(t->nil, t->root);

    if (searchNode == t->nil) {
        return t->nil;
    }

    return searchNode;
}

node_t* find_max_in_subtree(node_t* p_nil, node_t* subTreeRootNode) {
    if (subTreeRootNode == p_nil) {
        return p_nil;
    }

    while (subTreeRootNode->right != p_nil) {
        subTreeRootNode = subTreeRootNode->right;
    }

    return subTreeRootNode;
}

node_t* makeNilNode() {
    node_t* p_newNilNode = (node_t*) calloc(1, sizeof(node_t));
    p_newNilNode->key = 0;
    p_newNilNode->color = RBTREE_BLACK;
    p_newNilNode->left = NULL;
    p_newNilNode->right = NULL;
    p_newNilNode->parent = NULL;

    return p_newNilNode;
}

node_t* makeNewNode(rbtree* t, const key_t key) {
    node_t* p_newNode = (node_t*) calloc(1, sizeof(node_t));
    p_newNode->key = key;
    p_newNode->color = RBTREE_RED;
    p_newNode->left = t->nil;
    p_newNode->right = t->nil;
    p_newNode->parent = t->nil;

    return p_newNode;
}

void print_node_inorder(rbtree* t, node_t* curNode) {
    if (curNode == t->nil) {
        return;
    }

    print_node_inorder(t, curNode->left);
    printf("%d %c // ", curNode->key, curNode->color == RED ? 'R' : 'B');
    print_node_inorder(t, curNode->right);
}

void print_tree_inorder(rbtree* t) {
    printf("RootValue : %d \n", t->root->key);
    print_node_inorder(t, t->root);
    printf("\n");
}

void tree_insert_fixup(rbtree* t, node_t* targetNode) {
    while (targetNode->parent->color == RBTREE_RED) {
        if (targetNode->parent->parent->left == targetNode->parent) {
            targetNode = insert_fixupLeftCase(t, targetNode);
        } else {
            targetNode = insert_fixupRightCase(t, targetNode);
        }
    }

    t->root->color = RBTREE_BLACK;
}

node_t* insert_fixupLeftCase(rbtree* t, node_t* targetNode) {
    node_t* uncle = targetNode->parent->parent->right;

    if (uncle->color == RBTREE_RED) {
        targetNode = insert_fixupLeftCase_1(targetNode, uncle);
    } else {
        if (targetNode->parent->right == targetNode) {
            targetNode = insert_fixupLeftCase_2(t, targetNode);
        }

        targetNode = insert_fixupLeftCase_3(t, targetNode);
    }

    return targetNode;
}

node_t* insert_fixupLeftCase_1(node_t* targetNode, node_t* uncle) {
    targetNode->parent->color = RBTREE_BLACK;
    uncle->color = RBTREE_BLACK;

    targetNode->parent->parent->color = RBTREE_RED;
    targetNode = targetNode->parent->parent;

    return targetNode;
}

node_t* insert_fixupLeftCase_2(rbtree* t, node_t* targetNode) {
    targetNode = targetNode->parent;
    left_rotate(t, targetNode);

    return targetNode;
}

node_t* insert_fixupLeftCase_3(rbtree* t, node_t* targetNode) {
    targetNode->parent->color = RBTREE_BLACK;
    targetNode->parent->parent->color = RBTREE_RED;

    right_rotate(t, targetNode->parent->parent);

    return targetNode;
}

node_t* insert_fixupRightCase(rbtree* t, node_t* targetNode) {
    node_t* uncle = targetNode->parent->parent->left;

    if (uncle->color == RBTREE_RED) {
        targetNode = insert_fixupRightCase_1(targetNode, uncle);
    } else {
        if (targetNode->parent->left == targetNode) {
            targetNode = insert_fixupRightCase_2(t, targetNode);
        }

        targetNode = insert_fixupRightCase_3(t, targetNode);
    }

    return targetNode;
}

node_t* insert_fixupRightCase_1(node_t* targetNode, node_t* uncle) {
    targetNode->parent->color = RBTREE_BLACK;
    uncle->color = RBTREE_BLACK;

    targetNode->parent->parent->color = RBTREE_RED;
    targetNode = targetNode->parent->parent;

    return targetNode;
}

node_t* insert_fixupRightCase_2(rbtree* t, node_t* targetNode) {
    targetNode = targetNode->parent;
    right_rotate(t, targetNode);

    return targetNode;
}

node_t* insert_fixupRightCase_3(rbtree* t, node_t* targetNode) {
    targetNode->parent->color = RBTREE_BLACK;
    targetNode->parent->parent->color = RBTREE_RED;

    left_rotate(t, targetNode->parent->parent);

    return targetNode;
}

void left_rotate(rbtree* t, node_t* targetNode) {
    node_t* toRootNode = targetNode->right;
    targetNode->right = toRootNode->left;
    if (toRootNode->left != t->nil) {
        toRootNode->left->parent = targetNode;
    }
    toRootNode->parent = targetNode->parent;

    if (targetNode->parent == t->nil) {
        t->root = toRootNode;
    } else if (targetNode->parent->left == targetNode) {
        targetNode->parent->left = toRootNode;
    } else {
        targetNode->parent->right = toRootNode;
    }

    toRootNode->left = targetNode;

    targetNode->parent = toRootNode;
}

void right_rotate(rbtree* t, node_t* targetNode) {
    node_t* toRootNode = targetNode->left;
    targetNode->left = toRootNode->right;
    if (toRootNode->right != t->nil) {
        toRootNode->right->parent = targetNode;
    }
    toRootNode->parent = targetNode->parent;

    if (targetNode->parent == t->nil) {
        t->root = toRootNode;
    } else if (targetNode->parent->right == targetNode) {
        targetNode->parent->right = toRootNode;
    } else {
        targetNode->parent->left = toRootNode;
    }

    toRootNode->right = targetNode;

    targetNode->parent = toRootNode;
}

int rbtree_delete_node(rbtree* t, const key_t key) {
    node_t* searchNode = rbtree_find(t, key);

    if (searchNode == NULL) {
        return FAIL;
    } else {
        printf("find delete node : %d \n", key);

        rbtree_erase(t, searchNode);
        return SUCCESS;
    }
}

node_t* findTreeSuccessor(rbtree* t, node_t* targetNode) {
    if (targetNode->right != t->nil) {
        return find_min_in_subtree(t->nil, targetNode->right);
    }

    node_t* parentNode = targetNode->parent;

    while (parentNode != t->nil && targetNode == parentNode->right) {
        targetNode = parentNode;
        parentNode = parentNode->parent;
    }

    return parentNode;
}


int rbtree_erase(rbtree* t, node_t* targetNode) {
    node_t* realDeleteNode = t->nil;
    node_t* childNode = t->nil;

    if (targetNode->left == t->nil || targetNode->right == t->nil) {
        realDeleteNode = targetNode;
    } else {
        realDeleteNode = findTreeSuccessor(t, targetNode);
    }

    if (realDeleteNode->left != t->nil) {
        childNode = realDeleteNode->left;
    } else {
        childNode = realDeleteNode->right;
    }
    childNode->parent = realDeleteNode->parent;

    if (realDeleteNode->parent == t->nil) {
        t->root = childNode;
    } else if (realDeleteNode == realDeleteNode->parent->left) {
        realDeleteNode->parent->left = childNode;
    } else {
        realDeleteNode->parent->right = childNode;
    }

    if (realDeleteNode != targetNode) {
        targetNode->key = realDeleteNode->key;
    }

    if (realDeleteNode->color == RBTREE_BLACK) {
        rbtree_delete_fixup(t, childNode);
    }

    free(realDeleteNode);
    realDeleteNode = NULL;

    return SUCCESS;
}

void rbtree_delete_fixup(rbtree* t, node_t* targetNode) {
    while (targetNode != t->root && targetNode->color == RBTREE_BLACK) {
        if (targetNode == targetNode->parent->left) {
            targetNode = delete_fixupLeftCase(t, targetNode);
        } else {
            targetNode = delete_fixupRightCase(t, targetNode);
        }
    }

    targetNode->color = RBTREE_BLACK;
}

node_t* delete_fixupLeftCase(rbtree* t, node_t* targetNode) {
    node_t* sibling = targetNode->parent->right;

    if (sibling->color == RBTREE_RED) {
        sibling = delete_fixupLeftCase_1(t, targetNode, sibling);
    }

    if (sibling->left->color == RBTREE_BLACK && sibling->right->color == RBTREE_BLACK) {
        targetNode = delete_fixupLeftCase_2(targetNode, sibling);
    } else {
        if (sibling->right->color == RBTREE_BLACK) {
            sibling = delete_fixupLeftCase_3(t, targetNode, sibling);
        }

        targetNode = delete_fixupLeftCase_4(t, targetNode, sibling);
    }

    return targetNode;
}

node_t* delete_fixupLeftCase_1(rbtree* t, node_t* targetNode, node_t* sibling) {
    sibling->color = RBTREE_BLACK;
    targetNode->parent->color = RBTREE_RED;
    left_rotate(t, targetNode->parent);
    sibling = targetNode->parent->right;

    return sibling;
}

node_t* delete_fixupLeftCase_2(node_t* targetNode, node_t* sibling) {
    sibling->color = RBTREE_RED;
    targetNode = targetNode->parent;

    return targetNode;
}

node_t* delete_fixupLeftCase_3(rbtree* t, node_t* targetNode, node_t* sibling) {
    sibling->left->color = RBTREE_BLACK;
    sibling->color = RBTREE_RED;
    right_rotate(t, sibling);
    sibling = targetNode->parent->right;

    return sibling;
}

node_t* delete_fixupLeftCase_4(rbtree* t, node_t* targetNode, node_t* sibling) {
    sibling->color = targetNode->parent->color;
    targetNode->parent->color = RBTREE_BLACK;
    sibling->right->color = RBTREE_BLACK;
    left_rotate(t, targetNode->parent);
    targetNode = t->root;

    return targetNode;
}

node_t* delete_fixupRightCase(rbtree* t, node_t* targetNode) {
    node_t* sibling = targetNode->parent->left;

    if (sibling->color == RBTREE_RED) {
        sibling = delete_fixupRightCase_1(t, targetNode, sibling);
    }

    if (sibling->right->color == RBTREE_BLACK && sibling->left->color == RBTREE_BLACK) {
        targetNode = delete_fixupRightCase_2(targetNode, sibling);
    } else {
        if (sibling->left->color == RBTREE_BLACK) {
            sibling = delete_fixupRightCase_3(t, targetNode, sibling);
        }

        targetNode = delete_fixupRightCase_4(t, targetNode, sibling);
    }

    return targetNode;
}

node_t* delete_fixupRightCase_1(rbtree* t, node_t* targetNode, node_t* sibling) {
    sibling->color = RBTREE_BLACK;
    targetNode->parent->color = RBTREE_RED;
    right_rotate(t, targetNode->parent);
    sibling = targetNode->parent->left;

    return sibling;
}

node_t* delete_fixupRightCase_2(node_t* targetNode, node_t* sibling) {
    sibling->color = RBTREE_RED;
    targetNode = targetNode->parent;

    return targetNode;
}

node_t* delete_fixupRightCase_3(rbtree* t, node_t* targetNode, node_t* sibling) {
    sibling->right->color = RBTREE_BLACK;
    sibling->color = RBTREE_RED;
    left_rotate(t, sibling);
    sibling = targetNode->parent->left;

    return sibling;
}

node_t* delete_fixupRightCase_4(rbtree* t, node_t* targetNode, node_t* sibling) {
    sibling->color = targetNode->parent->color;
    targetNode->parent->color = RBTREE_BLACK;
    sibling->left->color = RBTREE_BLACK;
    right_rotate(t, targetNode->parent);
    targetNode = t->root;

    return targetNode;
}

void searchValueByInorder(const rbtree* t, const node_t* curNode, key_t* arr, const size_t n) {
    if (curNode == t->nil) {
        return;
    }

    if (arrCounter == n) {
        return;
    }

    searchValueByInorder(t, curNode->left, arr, n);
    arr[arrCounter++] = curNode->key;
    searchValueByInorder(t, curNode->right, arr, n);
}

int rbtree_to_array(const rbtree* t, key_t* arr, const size_t n) {
    arrCounter = 0;

    searchValueByInorder(t, t->root, arr, n);
    return SUCCESS;
}

void delete_rbtree(rbtree* t) {
    freeMemoryByPostorder(t, t->root);

    free(t->nil);
    free(t);
    t = NULL;
}

void freeMemoryByPostorder(rbtree* t, node_t* curNode) {
    if (curNode == t->nil) {
        return;
    }

    freeMemoryByPostorder(t, curNode->left);
    freeMemoryByPostorder(t, curNode->right);
    free(curNode);
    curNode = NULL;
}
