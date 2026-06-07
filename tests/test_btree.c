#include "trees.h"
#include <assert.h>
#include <stdio.h>

void test_insert_and_search()
{
    btreeNode* root = NULL;
    int t = 2;

    assert(btree_insert(&root, 10, t) == 1);
    assert(btree_insert(&root, 20, t) == 1);
    assert(btree_insert(&root, 30, t) == 1);

    assert(btree_search(root, 10) == 1);
    assert(btree_search(root, 20) == 1);
    assert(btree_search(root, 30) == 1);
    assert(btree_search(root, 99) == 0);

    btree_destroy(root);
    printf("btree insert and search test passed\n");
}

void test_duplicate_insert()
{
    btreeNode* root = NULL;
    int t = 2;

    assert(btree_insert(&root, 10, t) == 1);
    assert(btree_insert(&root, 10, t) == 0);

    btree_destroy(root);
    printf("btree duplicate insert test passed\n");
}

void test_empty_tree()
{
    btreeNode* root = NULL;

    assert(btree_search(root, 10) == 0);

    btree_destroy(root);
    printf("btree empty tree test passed\n");
}

void test_split()
{
    btreeNode* root = NULL;
    int t = 2;

    assert(btree_insert(&root, 10, t) == 1);
    assert(btree_insert(&root, 20, t) == 1);
    assert(btree_insert(&root, 30, t) == 1);
    assert(btree_insert(&root, 40, t) == 1);
    assert(btree_insert(&root, 50, t) == 1);

    assert(btree_search(root, 10) == 1);
    assert(btree_search(root, 30) == 1);
    assert(btree_search(root, 50) == 1);

    btree_destroy(root);
    printf("btree split test passed\n");
}

void test_delete_leaf_key()
{
    btreeNode* root = NULL;
    int t = 2;

    btree_insert(&root, 10, t);
    btree_insert(&root, 20, t);
    btree_insert(&root, 30, t);

    root = btree_delete(root, 20, t);

    assert(btree_search(root, 20) == 0);
    assert(btree_search(root, 10) == 1);
    assert(btree_search(root, 30) == 1);

    btree_destroy(root);
    printf("btree delete leaf key test passed\n");
}

void test_delete_nonexistent()
{
    btreeNode* root = NULL;
    int t = 2;

    btree_insert(&root, 10, t);
    btree_insert(&root, 20, t);

    root = btree_delete(root, 99, t);

    assert(btree_search(root, 10) == 1);
    assert(btree_search(root, 20) == 1);

    btree_destroy(root);
    printf("btree delete nonexistent key test passed\n");
}

void test_delete_internal_key()
{
    btreeNode* root = NULL;
    int t = 2;

    btree_insert(&root, 10, t);
    btree_insert(&root, 20, t);
    btree_insert(&root, 30, t);
    btree_insert(&root, 40, t);
    btree_insert(&root, 50, t);

    root = btree_delete(root, 20, t);

    assert(btree_search(root, 20) == 0);
    assert(btree_search(root, 10) == 1);
    assert(btree_search(root, 30) == 1);
    assert(btree_search(root, 40) == 1);
    assert(btree_search(root, 50) == 1);

    btree_destroy(root);
    printf("btree delete internal key test passed\n");
}

void test_traverse()
{
    btreeNode* root = NULL;
    int t = 2;

    btree_insert(&root, 10, t);
    btree_insert(&root, 20, t);
    btree_insert(&root, 30, t);

    printf("btree traversal output: ");
    btree_traverse(root);
    printf("\n");

    btree_destroy(root);
    printf("btree traverse test passed\n");
}

int main()
{
    test_insert_and_search();
    test_duplicate_insert();
    test_empty_tree();
    test_split();
    test_delete_leaf_key();
    test_delete_nonexistent();
    test_delete_internal_key();
    test_traverse();

    printf("All btree tests passed\n");
    return 0;
}