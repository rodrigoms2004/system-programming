# CAP02 - Software Development anf Engineering Processes

```
$< name of the file causing the action, e.g. mylib.o
$@ name of the current target
```

## Make from volume01/cap02_softwareDevelopment/Makefile


```
$ make
cc -c prog1.c
cc -c mylib.c
cc -o prog1 prog1.o mylib.o -lpthread
cc -c prog2.c
cc -o prog2 prog2.o mylib.o -lpthread
```

Result

```
$ ./prog1Hello, there!
$ ./prog2
Hello, there!!
```

## Make from volume01/cap02_softwareDevelopment/Makefile.ex2

```
$ make -f Makefile.ex2
cc -c mylib.c
cc -c prog1.c
cc -c prog2.c
cc -o prog1 prog1.o mylib.o -lpthread
cc -o prog2 prog2.o mylib.o -lpthread
```

## Make from volume01/cap02_softwareDevelopment/simpleProject

```
make
(cd lib; make)
make[1]: Entering directory '/home/eseye/system-programming/volume01/cap02_softwareDevelopment/simpleProject/lib'
cc -c file1.c -o file1.o
cc -c file2.c -o file2.o
ar rv mylib.a file1.o file2.o
ar: creating mylib.a
a - file1.o
a - file2.o
make[1]: Leaving directory '/home/eseye/system-programming/volume01/cap02_softwareDevelopment/simpleProject/lib'
(cd prog1; make)
make[1]: Entering directory '/home/eseye/system-programming/volume01/cap02_softwareDevelopment/simpleProject/prog1'
cc -c prog1.c -o prog1.o
cc  -o prog1 prog1.o ../lib/mylib.a
make[1]: Leaving directory '/home/eseye/system-programming/volume01/cap02_softwareDevelopment/simpleProject/prog1'
```

## References

* [Unix Makefile Tutorial](https://www.tutorialspoint.com/makefile/index.htm)