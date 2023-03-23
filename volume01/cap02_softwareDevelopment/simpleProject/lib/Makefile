# Build the library from source files.

OBJS = file1.o file2.o
LIB1 = mylib.a
CC = cc
CFLAGS = -c

all: $(OBJS)
	ar rv $(LIB1) $(OBJS)


# $< name of the file causing the action, e.g. mylib.o
# $@ name of the current target
.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -fr $(OBJS) $(LIB1)

