
# cc       -c -fPIC  libmath1.c -o libmath1.o
# ar               rv libmath1.a libmath1.o
# ar: creating libmath1.a
# a - libmath1.o
# ld               -shared -o libmath1.so libmath1.o

LIBSRCFILES = libmath1.c
LIBOBJFILES = libmath1.o
LIBA = libmath1.a
LIBSO = libmath1.so

CC = cc 	# compiler
LD = ld		# linker
AR = ar		# archive, ar - create, modify, and extract from archives

CFLAGS = -c -fPIC 
LDFLAGS = -shared
ARFLAGS = rv

all: $(LIBA) $(LIBSO)


$(LIBA): $(LIBOBJFILES)	
	$(AR) $(ARFLAGS) $(LIBA) $(LIBOBJFILES)				

$(LIBSO): $(LIBOBJFILES)
	$(LD) $(LDFLAGS) -o $(LIBSO) $(LIBOBJFILES)

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -fr *.o lib*.a lib*.so