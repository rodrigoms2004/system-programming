# Makefile for building fs example programs (Linux)
# Authored by Mr. Jin-Jwei Chen.
# Copyright (c) 1991-2016, 2020 Mr. Jin-Jwei Chen. All rights reserved.
# SOLARIS requires -lsocket while AIX does not have that library.
# In Apple MacOS, there is no need to specify libnsl and libsocket on linker line.

# Compiler flags
CFLAGS = -c

# Compiler
#ifdef sun
CC = gcc
LD = gcc
#else
CC = cc
LD = cc
#endif

# Libraries to link with
LOCALLIBS=
#ifdef sun
LDLIBS = -lnsl -lsocket -lpthread 
#else
LDLIBS = -lnsl -lpthread -lrt
#endif

# Programs to be built
PROGS=gendataf

# Generic build rules.
# This rule builds each executable target, single or multiple.
# It works in Linux, Solaris and MacOS.
%: %.c
	$(CC) -o $@ $< $(LOCALLIBS) $(LDLIBS)

.c.o:
	$(CC) $(CFLAGS) $<

all: $(LOCALLIBS) $(PROGS)

clean:
	rm -fr $(PROGS) $(OBJS) $(LOCALLIBS)

