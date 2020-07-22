#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

//initializes a binary search tree
BStree bstree_ini(int size) {
    BStree tree = (BStree_struct*) malloc(sizeof(BStree_struct));
    tree->tree_nodes = (Node *) malloc((size + 1) * sizeof(Node));
    tree->free_nodes = (unsigned int *) malloc((size + 1) * sizeof(unsigned int));
    tree->size = size;
    tree->top = 1;
    tree->root = 0;

    //initializing free_nodes with i
    for(int i = 0; i < size+1; i++){
        tree->free_nodes[i] = i;
    }
    return tree;
}

//extra helper method to make a new node
static int new_node(BStree bst, Key *key, Data data){
    if(bst->root == 0) bst->root = bst->free_nodes[bst->top];

    //making node
    Node newNode;
    newNode.key = key;
    newNode.data = data;
    newNode.left = 0;
    newNode.right = 0;
    bst->tree_nodes[bst->free_nodes[bst->top]] = newNode;

    //setting top
    bst->free_nodes[bst->top] = -1;
    bst->top = bst->top+1;
    return bst->top-1;
}

//helper that recursively inserts a node with the given index, key and data
void bst_insert(BStree bst, int node_index, Key *key, Data data) {
    if(node_index > bst->size){
        printf("Invalid Index.\n");
        exit(0);
    }
    else if ( node_index == 0 ) {
        node_index = new_node(bst, key, data);
    }

    //if there is no right child and node should be on right
    else if(bst->tree_nodes[node_index].right == 0 && key_comp(key, bst->tree_nodes[node_index].key) > 0){
        bst->tree_nodes[node_index].right = new_node(bst, key, data);
    }
    //if there is no left child and node should be on left
    else if(bst->tree_nodes[node_index].left == 0 && key_comp(key, bst->tree_nodes[node_index].key) < 0){
        bst->tree_nodes[node_index].left = new_node(bst, key, data);
    }

    //recursive calls for left and right
    else {
        if ( key_comp(key, bst->tree_nodes[node_index].key) < 0 )
            bst_insert(bst, bst->tree_nodes[node_index].left, key, data);
        else if ( key_comp(key, bst->tree_nodes[node_index].key) > 0 )
            bst_insert(bst, bst->tree_nodes[node_index].right, key, data);
        //if there is no place for the node
        else {
            printf("No location for node.\n");
            free(key->name);
            free(key);
        }
    }
}

//uses other helper function to insert
void bstree_insert(BStree bst, Key *key, Data data) {
    bst_insert(bst, bst->root, key, data);
}

//helper that recursively prints all the nodes of the tree inorder
void trav_helper(BStree bst, int node_index){
    if(node_index == 0) return;
    else{
        trav_helper(bst, bst->tree_nodes[node_index].left);
        print_node(bst->tree_nodes[node_index]);
        trav_helper(bst, bst->tree_nodes[node_index].right);
    }
}

//uses above helper function to traverse inorder
void bstree_traversal(BStree bst) {
    trav_helper(bst, bst->root);
}

//helper to recursively traverse the tree for freeing all nodes
void free_helper(BStree bst, int node_index){
    if(node_index == 0) return;
    else{
        free_helper(bst, bst->tree_nodes[node_index].left);
        free(bst->tree_nodes[node_index].key->name);
        free(bst->tree_nodes[node_index].key);
        free_helper(bst, bst->tree_nodes[node_index].right);
    }
}

//function that uses the helper to free all nodes in the tree
//Then frees tree_nodes free_nodes and bst
void bstree_free(BStree bst) {
    free_helper(bst, bst->root);
    free(bst->tree_nodes);
    free(bst->free_nodes);
    free(bst);
}



