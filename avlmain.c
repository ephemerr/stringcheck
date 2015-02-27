#include "avltree.h"
#include "hash.h"

#include <stdio.h>
#include <string.h>

#define MAXSTR 1024
#define MAXCYCLS 30000 

void perchar(char *str) {
  int len = strlen (str);
  int i;
  printf("%s ",str);
  for (i=0;i<len;i++) {
    printf("%3d ",str[i]);
  }
  puts("");
}

// ------------------------------------------------------
// Read string without insignificant chars
int readstr(char *str, int max, FILE* from) {
  int err = from != NULL && str != NULL ? 0 : 1;
  if (err) return err;

  char c;
  do {
    c = getc(from);
  } while (c != EOF && (c >= 127 || c <= 32) );

  if (c == EOF) return 2;

  str[0] = c;

  int i;  
  for (i=1; i<max; i++) {
    c = getc(from);
    if (c >= 127 || c < 32) break;
    
    str[i] = c;    
  }
  if (i < max) str[i] = '\0';
  
  return err; 
}

// ------------------------------------------------------
int main(int argc, char **argv) {
  int err=0;
  int res=0;
  FILE* store = NULL;
  char buf[MAXSTR+1]="";
  tree_t t = NULL;

  err = argc == 2 ? 0 : 1;
  if (err) goto FINISH;
  
  store = fopen(argv[1], "r");
  err = (store != NULL ) ? 0 : 2;
  if (err) goto FINISH;
  
  err = tree_new(&t,0) == 0 ? 0 : 3;
  if (err) goto FINISH;

  int i=0;
  while (readstr(buf, MAXSTR, store) == 0) {
    int len = strlen(buf);
    keyval_t hashcode = jenkins_one_at_a_time_hash(buf, len);
    //perchar(buf);

    res = tree_insert(t, hashcode);
    if (res == -1) continue; // found

    err = res == 0 ? 0 : 5; // error    
    if (err) goto FINISH;
    
    t = tree_getroot(t);

    i++;
    err = i < MAXCYCLS ? 0 : 8;
    if (err) goto FINISH;
  }
  
  err = i > 0 ? 0 : 9;
  if (err) goto FINISH;

  puts("Input:");
  
  do {
    err = gets(buf) != NULL ? 0 : 7; 
    //perchar(buf);

    if (err) goto FINISH;
    
    int exitsig = strcmp("exit", buf);
    if (exitsig == 0) goto FINISH;

    int len = strlen(buf);
    keyval_t hashcode = jenkins_one_at_a_time_hash(buf, len);
    int found = tree_has(t, hashcode);
    printf("%s\n", found ? "YES" : "NO");
  } while(1);

FINISH:
  tree_destroy(t);

  if (store != NULL) {
    fclose(store);
  }


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
    case 7: {
      printf("Couldn't read stdin\n");
      break;
    }
    case 8: {
      printf("Eternal loop somehow\n");
      break;
    }
    case 9: {
      printf("No correct data\n");
      break;
    }
    default: {
      printf ("Unknown error: %d\n",err);
    }  
  }

  return err; 
}

