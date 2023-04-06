
# -lnsl tells to the linker to use libnsl.a 
all:
	cc -o myprog myprog.c -lnsl 

linker:
	cc -c myprog.c
	ld -o myprog myprog.o -lnsl

clean:
	rm -rf *.o myprog


