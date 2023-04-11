PROG1SRC = useload.c 
PROG1OBJ = useload.o 
PROG1 = useload
DLIBS = ../../lib/libmath1.so

CC = cc
GCC = gcc
LD = ld
RM = rm

CFLAGS = -fPIC 
LDLIBS = -lc -ldl 

all: $(PROG1) $(PROG2)

$(PROG1): $(PROG1OBJ)
	$(CC) -o $(PROG1) $(PROG1OBJ) $(LDLIBS)

.c.o:
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	$(RM) -fr $(PROG1) $(PROG1OBJ)
