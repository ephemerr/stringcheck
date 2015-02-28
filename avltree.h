#pragma once

#include <stdint.h>

typedef struct node_st * tree_t;
typedef uint32_t keyval_t;
typedef struct list_st {
    char* data;
    struct list_st* next;
} * list_t;
struct node_st {
    keyval_t key;
    tree_t parent;
    tree_t left;
    tree_t right;
    int balance;        
    struct list_st list;
};

typedef int (*tree_method)(tree_t);

int tree_new( tree_t* self, keyval_t key, char* dat) ;
int tree_place(const tree_t self, keyval_t val, tree_t* nod, int* dir);
int tree_setleft(tree_t dad, tree_t son);
int tree_setright(tree_t dad, tree_t son); 
int tree_insert(tree_t root, keyval_t val, char* str);
int tree_rotleft(tree_t nod);
int tree_rotright(tree_t nod);
int tree_has(const tree_t tree, keyval_t val);
int tree_printnod(tree_t nod);
int tree_min(const tree_t root, tree_t* min); 
int tree_next(const tree_t nod, tree_t* next);
int tree_foreach(tree_t root, tree_method method);   
int tree_foreach_s(tree_t root, tree_method method);   
int tree_print(const tree_t root); 
tree_t tree_getroot(const tree_t node);
int tree_destroy( tree_t root ); 
