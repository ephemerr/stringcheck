#include "avltree.h"

#include <stdio.h>



// ------------------------------------------------------
int tree_printnod(tree_t nod) {
  int err = nod != NULL ? 0 : -1;
  if (err) return err;

  printf("%s() parent: %p self: %p key: %d b: %d lr: %p %p \n",__func__, 
      (void*)nod->parent, 
      (void*)nod, 
      nod->key, 
      nod->balance, 
      (void*)nod->left,
      (void*)nod->right 
      );
  return 0;
}


// ------------------------------------------------------
// leftmost 
int tree_min(const tree_t root, tree_t* min) {
  int err = root != NULL ? 0 : -1;
  if (err) return err;

  if (root-> left == NULL ) {
    *min = root;
    return 0;
  } else {
    return tree_min(root->left, min);
  }
  return err;  
}

// ------------------------------------------------------
// next value
int tree_next(const tree_t nod, tree_t* next) {
  int err = nod != NULL ? 0 : -1;
  if (err) return err;

  if (nod->right != NULL) {
    return tree_min(nod->right, next);
  }

  tree_t dad = nod->parent;
  tree_t son = nod;
  while(dad != NULL && son == dad->right) {
    son = dad;
    dad = dad->parent;
  }
  *next = dad;

  return 0; 
}

// ------------------------------------------------------
int tree_forearch(tree_t root, tree_method method) {
    tree_t victim; 
    int err = tree_min(root, &victim);
    if (err) return err;

    while ( victim != NULL ) {        
        err = method(victim);
        if (err) return err;

        err = tree_next(victim, &victim);
        if (err) return err;
    }
    return err;
} 


// ------------------------------------------------------
tree_t tree_getroot(const tree_t node) {
    tree_t root = node;
    while (root != NULL && root->parent != NULL) {
        root = root->parent;
    }
    return root;
}

// ------------------------------------------------------
int tree_print( const tree_t root ) {
   puts(__func__);
   return tree_forearch(root, tree_printnod);
}
