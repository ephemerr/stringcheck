#pragma once

typedef struct node_st * tree_t;
typedef unsigned int keyval_t;

int tree_new( tree_t* self, keyval_t key, tree_t parent ) ;
int tree_place(const tree_t self, keyval_t val, tree_t* nod, int* dir);
int tree_setleft(tree_t dad, tree_t son);
int tree_setright(tree_t dad, tree_t son); 
