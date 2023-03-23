# Makefile for building multiple executables
# Authorized by Mr. Jin-Jwei Chen.
# Copyright (c) 1991, 2012-2016, 2020 Mr. Jin-Jwei Chen. All rights reserved.
#

CFLAGS = -c
CC = cc
LD = cc

LDLIBS = -lpthread
MYLIBS = mylib.o

all: prog1 prog2

# This rule builds *.o from *.c. This rule is optional because it is implicit.
# Both rules work.
.c.o:
#	$(CC) $(CFLAGS) $<
	$(CC) $(CFLAGS) $*.c

prog1: prog1.o $(MYLIBS)
	$(CC) -o $@ $(@).o $(MYLIBS) $(LDLIBS)

prog2: prog2.o $(MYLIBS)
	$(CC) -o $@ $(@).o $(MYLIBS) $(LDLIBS)

clean:
	rm -fr prog1 prog1.o prog2 prog2.o $(MYLIBS)

