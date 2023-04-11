# Makefile for building library libtst1
# Authored by Mr. Jin-Jwei Chen.
# Copyright (c) 2012-2016, 2020 Mr. Jin-Jwei Chen. All rights reserved.
#
LIBSRCFILES = tripleIt.c echoMsg.c
LIBOBJFILES = tripleIt.o echoMsg.o
LIBA = libtst1.a		# static library (archive library)
LIBSO = libtst1.so		# dynamic library (shared library)

CC = cc 	# compiler
LD = ld		# linker
AR = ar		# archive, ar - create, modify, and extract from archives

CFLAGS = -c -fPIC 
LDFLAGS = -shared
ARFLAGS = rv

all: $(LIBA) $(LIBSO)		# executes LIBA and LIBSO


# ar rv libtst1.a tripletIt.o echoMsg.o
$(LIBA): $(LIBOBJFILES)	
	$(AR) $(ARFLAGS) $(LIBA) $(LIBOBJFILES)				

# ld -shared -o libtst1.so tripletIt.o echoMsg.o
$(LIBSO): $(LIBOBJFILES)
	$(LD) $(LDFLAGS) -o $(LIBSO) $(LIBOBJFILES)

# Applies to all *.c files. It tells te make command how to build a xxx.o object file from a xxx.c source file
# cc       -c -fPIC  tripleIt.c -o tripleIt.o
# cc       -c -fPIC  echoMsg.c -o echoMsg.o
# $< is file.c and $@ is file.o
.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -fr *.o lib*.a lib*.so