
SRCDIR  = . 
SOURCES = avlmain.c avltree.c hash.c  
OBJECTS = $(SOURCES:.c=.o)
CC		= gcc
CFLAGS 	= -Wall -Werror 
LIBS 	= 
LDFLAGS = 
LIBDIRS = 
INCLUDE = 

all: checker

%.o : %.c 
	$(CC) -o $@ -c $< $(CFLAGS) $(addprefix -I, $(INCLUDE))

clean :
	rm -rf  $(OBJECTS) 

checker: $(OBJECTS) 
	ctags $(SOURCES)
	$(CC) -o $@ $(OBJECTS) $(LDFLAGS) $(addprefix -l, $(LIBS)) $(addprefix -I, $(INCLUDE)) $(addprefix -L, $(LIBDIRS)) 

new:
	ctags $(SOURCES) $(SOURCES_TEST)
	make clean
	make all
