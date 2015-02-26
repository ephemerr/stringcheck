#include "avltree.h"
#include "hash.h"

#include <stdio.h>

#define MAXSTR 1024

char buf[MAXSTR+1]="";
tree_t t;

int main(int argc, char **argv) {
    int err=0;
    int res=0;
    FILE* store = NULL;

    err = argc == 2 ? 0 : 1;
    if (err) goto FINISH;
    
    store = fopen(argv[1], "r");
    err = (store != NULL ) ? 0 : 2;
    if (err) goto FINISH;
    
    err = tree_new(&t,0) == 0 ? 0 : 3;
    if (err) goto FINISH;

    err = fgets(buf, MAXSTR, store) != NULL ? 0 : 4;     
    while (!err) {
        keyval_t hashcode = jenkins_one_at_a_time_hash(buf, MAXSTR);
        
        res = tree_insert(t, hashcode);
        if (res == -1) continue; // found

        err = res == 0 ? 0 : 5; // error        
        if (err) goto FINISH;
        
        t = tree_getroot(t);

        err = fgets(buf, MAXSTR, store) != NULL ? 0 : 6;     
    }

  

//  tree_insert(t, 100);
//  tree_insert(t, 5);
//  tree_insert(t, -5);
//  tree_insert(t, 6);
//  tree_print(t);
  

FINISH:

  fclose(store);

  t = tree_getroot(t);
  tree_print(t);
  

    switch (err) {
        case 1: {
            puts("Wrong arguments");
            puts("Usage: ./checker \"file.name\" ");
            break;
        }
        case 2: {
            printf("Couldn't open file: %s\n",argv[1]);
            break;
        }
        case 3: {
            printf("Couldn't allocate memory\n");
            break;
        }
        case 4: {
            printf("File %s is empty or read error\n",argv[1]);
            break;
        }
        case 5: {
            printf("Tree insert failure\n");
            break;
        }
        case 6: {
            break;
        }
        default: {
            printf ("EROOR: %d\n",err);
        }  
    }

  return err; 
}

