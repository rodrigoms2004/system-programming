# System programming - Jin-Jwei Chen


* System Programming Volume 1 - ISBN: 978-1-7361930-0-6

* System Programming Volume 2 - ISBN: 978-1-7361930-1-3


## Volume 01

### CAP02 - Software Development anf Engineering Processes


#### Make from volume01/cap02_softwareDevelopment/Makefile

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

#### Make from volume01/cap02_softwareDevelopment/Makefile.ex2

```
$ make -f Makefile.ex2
cc -c mylib.c
cc -c prog1.c
cc -c prog2.c
cc -o prog1 prog1.o mylib.o -lpthread
cc -o prog2 prog2.o mylib.o -lpthread
```


## Volume 02