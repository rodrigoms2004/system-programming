# CAP03 - Building Programs and Libraries

## Types of libraries

* Archive library or static library
* Shared library or dynamic library

## Build your own static library (libtst1.a/libtst1.lib)

1. Compile all of the library source files into object code. (cc -c)
2. Put all of the library object files into a single *archive library*.

### Linux

```
cc -c tripleIt.c echoMsg.c
ar rv libtst1.a tripleIt.o echoMsg.o
```
#### ar command exit

```
ar: creating libtst1.a
a - tripleIt.o
a - echoMsg.o
```


## Build your own dynamic library (libtst.so/libtst1.dll)

1. Compile all of the library source files into object code. (cc -c)
2. Put all of the library object files into a single *shared library*.

### Linux

The *-shared* liker option produces a shared library. Whether you specify the -fPIC on the ld command 
or not does not seem to matter. 

```
cc -fPIC -c tripleIt.c echoMsg.c
ld -shared -o libtst1.so tripleIt.o echoMsg.o
```

or 

```
gcc -fPIC -c tripleIt.c echoMsg.c
gcc -shared -o -W1,-soname,libtst1.so -o libtst1.so tripleIt.o echoMsg.o -lc

```

## The Makefile to generate the libraries

[Makefile for libtst1](volume01/cap03_buildingProgLib/src/libtst1/Makefile)

### Variables

```
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

```

### Executes LIBA and LIBSO
```
all: $(LIBA) $(LIBSO)		
```

### ar rv libtst1.a tripletIt.o echoMsg.o
```
$(LIBA): $(LIBOBJFILES)	
	$(AR) $(ARFLAGS) $(LIBA) $(LIBOBJFILES)				

```

### ld -shared -o libtst1.so tripletIt.o echoMsg.o

```
$(LIBSO): $(LIBOBJFILES)
	$(LD) $(LDFLAGS) -o $(LIBSO) $(LIBOBJFILES)
```


###  Compiler

Applies to all *.c files. It tells te make command how to build a xxx.o object file from a xxx.c source file.
Where $< is file.c and $@ is file.o.


```
.c.o:
	$(CC) $(CFLAGS) $< -o $@
```


#### Exit:

```
cc       -c -fPIC  tripleIt.c -o tripleIt.o
cc       -c -fPIC  echoMsg.c -o echoMsg.o
```


### Clean 

```
clean:
	rm -fr *.o lib*.a lib*.so
```

## Develop an aaplication using your own library

### The code

```
#include <stdio.h>
#include <errno.h>

int main(int argc, char **argv)
{
  int  ret;
  int  x = 22;
  char *mymsg = "Hello, there!";

  /* Pass in an integer and get back another */
  ret = tripleIt(x);
  printf("Triple of %d is %d.\n", x, ret);

  /* Pass in a string and get back an integer */
  ret = echoMsg(mymsg);
  printf("There are %d characters in the string '%s'.\n", ret, mymsg);

  return(0);
}
```

### Exit

```
The library function tripleIt() was called.
Triple of 22 is 66.
The library function echoMsg() was called.
The library function echoMsg2() was called.
*** Your message is: Hello, there!
There are 13 characters in the string 'Hello, there!'.
```

## Build an application that links with your own statc library

volume01/cap03_buildingProgLib/src/app/slink

### Linux

```
cc -c uselink.c -o uselink.o
cc -static -o uselink uselink.o ../../libtst1/libtst1.a
```

or 

```
gcc -static -o uselink uselink.c ../../libtst1/libtst1.a
```


## Build an application that links with your own dynamic library 

volume01/cap03_buildingProgLib/src/app/dlink

### Linux

```
cc -fPIC -c uselink.c -o uselink.o
cc -dynamic -o uselink uselink.o ../../libtst1/libtst1.so
```

or 

```
gcc -dynamic -o uselink uselink.c ../../libtst1/libtst1.so
```