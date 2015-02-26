
SRCDIR  = . 
SOURCES = $(wildcard $(addsuffix /*.c, $(SRCDIR)))
OBJECTS = $(SOURCES:.c=.o)
CC		= gcc
CFLAGS 	= -Wall -Werror 
LIBS 	= 
LDFLAGS = 
LIBDIRS = 
INCLUDE = 

%.o : %.c 
	$(CC) -o $@ -c $< $(CFLAGS) $(addprefix -I, $(INCLUDE))

checker: $(OBJECTS) 
	$(CC) -o $@ $(OBJECTS) $(LDFLAGS) $(addprefix -l, $(LIBS)) $(addprefix -I, $(INCLUDE)) $(addprefix -L, $(LIBDIRS)) 
