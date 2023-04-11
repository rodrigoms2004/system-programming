# Makefile
# Authored by Mr. Jin-Jwei Chen.
# Copyright (c) 2012-2016, 2020 Mr. Jin-Jwei Chen. All rights reserved.

PROG1SRC = useload.c 
PROG1OBJ = useload.o 
PROG1 = useload
DLIBS = ../../libtst1/libtst1.so

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
