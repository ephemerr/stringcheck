#include "avltree.h"

#include <stdio.h>

int main() {
    tree_t n1,n10,n100;
    tree_new(&n10,10,NULL);
    tree_new(&n1,1,n10);
    tree_new(&n100,100,n10);

    tree_setright(n10, n100);
    tree_setleft(n10, n1);
    
    return 0;
}

