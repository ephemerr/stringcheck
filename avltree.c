#include "avltree.h"

#include <stdio.h>
#include <stdlib.h>


#define SELF 0
#define LEFT 1
#define RIGHT -1 



struct node_st {
    keyval_t key;
    tree_t parent;
    tree_t left;
    tree_t right;
    int balance;        
};

//  ------------------------------------------------------
int tree_new( tree_t* self, keyval_t key, tree_t parent ) {
    *self = (tree_t)calloc(1, sizeof (struct node_st));
    
    int err =  (*self != NULL) ? 0 : -1;
    if (err) return err;

    (*self)->key = key;
    (*self)->parent = parent;

    return err;
}

//  ------------------------------------------------------
int tree_place(const tree_t self, keyval_t val, tree_t* nod, int* dir) {
    int err = self != NULL && nod != NULL ? 0 : -1;
    if (err) return err;

    if (self->key == val) {
        *nod = self;
        *dir = SELF;
        return 0;
    }
    
    if (val < self->key) {
       if (self->left == NULL) {
        *nod = self;
        *dir = LEFT;
        return 0;
       } else {
          return tree_place(self->left, val, nod, dir);
       }
    } else {
       if (self->right == NULL) {
        *nod = self;
        *dir = RIGHT;
        return 0;
       } else {
          return tree_place(self->right, val, nod, dir);
       }

    }
    return -2; // shouldn't be there 
}

//  ------------------------------------------------------
int tree_setleft(tree_t dad, tree_t son) {
    int err = dad != NULL && son != NULL ? 0 : -1;
    if (err) return err;

    dad->left = son;
    son->parent = dad;

    return 0;
}


//  ------------------------------------------------------
int tree_setright(tree_t dad, tree_t son) {
    int err = dad != NULL && son != NULL ? 0 : -1;
    if (err) return err;

    dad->right = son;
    son->parent = dad;

    return 0;
}


