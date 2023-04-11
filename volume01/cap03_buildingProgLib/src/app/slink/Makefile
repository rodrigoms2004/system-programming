# Makefile
# Authored by Mr. Jin-Jwei Chen.
# Copyright (c) 2012-2016, Mr. Jin-Jwei Chen. All rights reserved.

PROG1SRC = uselink.c 
PROG1OBJ = uselink.o 
PROG1 = uselink

CC = cc
LD = cc
RM = rm

CFLAGS = 
LDFLAGS = -static 
# Both absolute and relative paths work.
#LDLIBS = -L/home/oracle/mybk1/lib/lin/libtst1 -ltst1
LDLIBS = ../../libtst1/libtst1.a

all: $(PROG1) 

$(PROG1): $(PROG1OBJ)
	$(LD) $(LDFLAGS) -o $(PROG1) $(PROG1OBJ) $(LDLIBS)

.c.o:
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	$(RM) -fr $(PROG1OBJ) $(PROG1)
