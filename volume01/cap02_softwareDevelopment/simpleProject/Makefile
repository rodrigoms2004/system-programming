# Top-level Makefile to build all.

DEPEND1 = lib
DEPEND2 = prog1

all: $(DEPEND1) $(DEPEND2)
	(cd $(DEPEND1); make)
	(cd $(DEPEND2); make)

clean:
	(cd $(DEPEND1); make clean)
	(cd $(DEPEND2); make clean)
