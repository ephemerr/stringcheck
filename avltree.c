#include "avltree.h"

#include <stdio.h>
#include <stdlib.h>

#define SELF 0
#define LEFT 1
#define RIGHT -1 

// ------------------------------------------------------
int tree_new( tree_t* self, keyval_t key ) {
  *self = (tree_t)calloc(1, sizeof (struct node_st));
  
  int err = (*self != NULL) ? 0 : -1;
  if (err) return err;

  (*self)->key = key;

  return err;
}

// ------------------------------------------------------
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

// ------------------------------------------------------
int tree_has(const tree_t tree, keyval_t val) {
  tree_t tmp=NULL;
  int dir=0;
  int err = tree_place(tree, val, &tmp, &dir);
  if (err || dir != SELF) return 0;  
  return 1;
}

// ------------------------------------------------------
int tree_setleft(tree_t dad, tree_t son) {
  int err = dad != NULL ? 0 : -1;
  if (err) return err;

  dad->left = son;
  if (son != NULL) {
    son->parent = dad;
  }

  return 0;
}


// ------------------------------------------------------
int tree_setright(tree_t dad, tree_t son) {
  int err = dad != NULL ? 0 : -1;
  if (err) return err;

  dad->right = son;
  if (son != NULL) {
    son->parent = dad;
  }

  return 0;
}

// ------------------------------------------------------
int tree_rotleft(tree_t nod) {
  int err = nod != NULL ? 0 : -1;
  if (err) return err;

  tree_t dad = nod->parent;
  tree_t bigson = nod->right;

  err = bigson != NULL ? 0 : -2;
  if (err) return err;
  
  tree_setright(nod, bigson->left);

  tree_setleft(bigson, nod);

  if (dad != NULL) {
    if (dad->left == nod) {
      tree_setleft(dad, bigson);
    } else {
      tree_setright(dad, bigson);
    }
  } else {
      bigson->parent = NULL;
  }

  return err;
}

// ------------------------------------------------------
int tree_rotright(tree_t nod) {
  int err = nod != NULL ? 0 : -1;
  if (err) return err;

  tree_t dad = nod->parent;
  tree_t bigson = nod->left;

  err = bigson != NULL ? 0 : -2;
  if (err) return err;
  
  tree_setleft(nod, bigson->right);

  tree_setright(bigson, nod);

  if (dad != NULL) {
    if (dad->left == nod) {
      tree_setleft(dad, bigson);
    } else {
      tree_setright(dad, bigson);
    }
  } else {
      bigson->parent = NULL;
  }

  return err;
}

// ------------------------------------------------------
int tree_rebalance(tree_t node, int dir) {
    int err = dir == RIGHT || dir == LEFT ? 0 : -1; 
    if (err) return err;
    
    err = node != NULL ? 0 : -2;
    if (err) return err;
    
    if (node->left != NULL && node->right != NULL) {
        node->balance = 0;
        return 0;
    }

    tree_t dad = node->parent;
    node->balance = dir == RIGHT ? -1 : 1;

    while (dad != NULL) {
      if (node == dad->left) {
        if (dad->balance == 1) { 
          if (node->balance == -1) { 
              // Left Right Case
             tree_rotleft(node); 
          }
          // Left Left Case
          tree_rotright(dad);
          break; 
        }

        if (dad->balance == -1) {
          dad->balance = 0; 
          break; 
        }

        dad->balance = 1; 
      } else { // node == dad->right

        if (dad->balance == -1) { 
          if (node->balance == 1) { 
             // Right Left Case
             tree_rotright(node); 
          }
          // Right Right Case
          tree_rotleft(dad);
          break; 
        }

        if (dad->balance == 1) {
          dad->balance = 0; 
          break; 
        }

        dad->balance = -1; 
      }
      node = dad;
      dad = node->parent;
    } 
    return err;
}

// ------------------------------------------------------
int tree_insert( tree_t root, keyval_t val) {
  tree_t newnode;
  tree_t place;
  int dir=0;

  int err = tree_new( &newnode, val ) == 0 ? 0 : 1;
  if (err) goto FINISH;

  err = tree_place(root, val, &place, &dir) == 0 ? 0 : 2;
  if (err) goto FINISH;

  if (dir == LEFT) {
    tree_setleft(place, newnode);
  } else if (dir == RIGHT) {
    tree_setright(place, newnode);
  } else {
    return -1; // elem found
  }
  
  err = tree_rebalance(place, dir) == 0 ? 0 : 3;

FINISH:

  if (err) {
      //printf ("%s err: %d\n",__func__, err);
  }
  return err;
}


// ------------------------------------------------------
int tree_printnod(tree_t nod) {
  int err = nod != NULL ? 0 : -1;
  if (err) return err;

  printf("%s() parent: %p self: %p key: %x b: %d lr: %p %p \n",__func__, 
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
// successive traverse
int tree_foreach_s(tree_t root, tree_method method) {
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
int tree_foreach(tree_t root, tree_method method) {
    if (root == NULL) return 0;
    
    tree_foreach(root->left, method);
    tree_foreach(root->right, method);

    method(root);
        
    return 0;
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
   return tree_foreach(root, tree_printnod);
}

// ------------------------------------------------------
int tree_free(tree_t tree) {
  free(tree);
  return 0;
}

// ------------------------------------------------------
int tree_destroy( tree_t root ) {
  return tree_foreach(root, tree_free);
}
