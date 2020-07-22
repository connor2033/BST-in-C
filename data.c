#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"

//Constructs a key for a node
//allocates memory for key and name
Key *key_construct(char *in_name, int in_id) {

    Key *pKey;
    pKey = malloc(sizeof(Key));
    pKey->id = in_id;

    pKey->name = (char *)malloc( (strlen(in_name)+1)* sizeof(char) );
    strcpy(pKey->name, in_name);

    return pKey;
}

//Compares keys based on the name, if name is equal it compares the IDs.
int key_comp(Key *key1, Key *key2) {
    if(strcmp(key1->name, key2->name) < 0) return -1;
    else if(strcmp(key1->name, key2->name) > 0) return 1;
    else if(strcmp(key1->name, key2->name) == 0){
        if(key1->id > key2->id) return  1;
        else if(key1->id < key2->id) return  -1;
        else return 0;
    }
}

//Prints the name and ID of a given key to screen
void print_key(Key *key) {
    printf("( %-15s%4d )\t", key->name,key->id);
}

//prints the contents of a given node
void print_node(Node node) {
    print_key(node.key);
    printf(" %d\n", node.data);
}

