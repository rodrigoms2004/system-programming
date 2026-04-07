	ifdef SOLARIS
	CC = gcc
	else
	CC = cc
	endif
	ifeq ($(CC),gcc)
	LDLIBS = -lnsl -lsocket -lpthread 
	else
	LDLIBS = -lnsl -lpthread
	endif

test:
	@echo "CC = " $(CC)
	@echo "LDLIBS = " $(LDLIBS)

# make SOLARIS=1

# ifdef LINUX
# OS = Linux
# else
# OS = Unknown
# endif	

# # special:
# # 	@echo "	A command starts with @ sign"
# # 	+echo "	A command starts with + sign"
# # 	-echo "	A command starts with - sign
# # 	echo "	A command after an error"

# include my.mk

# test:
# 	@echo "Testing ..."
# 	@echo "MACRO1 =" $(MACRO1)

# 	@echo "OS =" $(OS)

# system:
	