PROG1SRC = uselink.c 
PROG1OBJ = uselink.o 
PROG1 = uselink

CC = cc
LD = cc
RM = rm

CFLAGS = -c -fPIC
LDFLAGS = -dynamic 
LDLIBS = ../../lib/libmath1.so

all: $(PROG1) 

$(PROG1): $(PROG1OBJ)
	$(LD) $(LDFLAGS) -o $(PROG1) $(PROG1OBJ) $(LDLIBS)

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	$(RM) -fr $(PROG1OBJ) $(PROG1)
