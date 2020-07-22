#include <stdio.h>
#include "bst.h"

//main method to take tree nodes from standard input
int main(void) {
    //creating the tree
    BStree bst;
    bst = bstree_ini(256);

    //making variables to be scanned in
    char name[10];
    int id;
    int data;

    printf("Enter a triple (Name, ID, Data) to be inserted.\n");

    //loops through
    while (scanf(" %s %d %d", &name, &id, &data) != EOF){
        //inserting the scanned node into the tree
        bstree_insert(bst, key_construct(name, id), data);
    }

    //traversing the tree and printing it, then freeing all nodes
    bstree_traversal(bst);
    bstree_free(bst);
}
