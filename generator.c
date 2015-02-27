#include <stdio.h>
#include <stdlib.h> 

#define MAXL 1024
char buf[MAXL+1]={};

int main (int argc, char **argv) {
  FILE* store = fopen("store.dat","w");
  int err = store != NULL ? 0 : 1;
  if (err) goto FINISH;
  
  err = argc == 2 ? 0 : 1;
  if (err) goto FINISH;

  int lim = atoi(argv[1]);
  err = lim < MAXL && lim > 0 ? 0 : 3;
  if (err) goto FINISH;
  

  int i,j,k;
  for (k=33;k<127;k++) {
    for (i=1; i<=lim; i++) {
      for (j=0; j<i; j++) {
        buf[j] = k; 
      }
      buf[i]='\n';
      buf[i+1]='\0';
      err = fputs(buf, store) != EOF ? 0 : 2;
      if (err) goto FINISH;
    }
}

FINISH: 
  if (store != NULL) {
    fclose(store);
  }
  printf("%s() err: %d\n", __func__, err);

  return err;
}
