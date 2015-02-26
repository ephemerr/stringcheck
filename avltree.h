#pragma once

#include <stdint.h>

typedef struct node_st * tree_t;
typedef uint32_t keyval_t;

struct node_st {
    keyval_t key;
    tree_t parent;
    tree_t left;
    tree_t right;
    int balance;        
};

int tree_new( tree_t* self, keyval_t key) ;
int tree_place(const tree_t self, keyval_t val, tree_t* nod, int* dir);
int tree_setleft(tree_t dad, tree_t son);
int tree_setright(tree_t dad, tree_t son); 
int tree_insert(tree_t root, keyval_t val);
int tree_rotleft(tree_t nod);
int tree_rotright(tree_t nod);


/// tools

typedef int (*tree_method)(tree_t);

int tree_printnod(tree_t nod);
int tree_min(const tree_t root, tree_t* min); 
int tree_next(const tree_t nod, tree_t* next);
int tree_forearch(tree_t root, tree_method method);   
int tree_print(const tree_t root); 
tree_t tree_getroot(const tree_t node);
