# Build the executable program named prog1.

PROG1 = prog1
PROG1OBJ = prog1.o
LIB1 = ../lib/mylib.a

CFLAGS = -c
CC = cc
LD = cc

$(PROG1): $(PROG1OBJ) $(LIB1)
	$(LD) $(LDFLAGS) -o $(PROG1) $(PROG1OBJ) $(LIB1)

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(PROG1) $(PROG1OBJ)

