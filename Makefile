TARGET		:= billc
SRCDIR  	:= src/
BUILDDIR	:= build/
NAMES	    := lexer

SRCS		:= $(patsubst %,$(SRCDIR)%.c, $(NAMES))
OBJS    	:= $(patsubst %,$(BUILDDIR)%.o, $(NAMES))

CC = g++

IFLAGS = 
CCFLAGS = -O3 -Wall -Werror -Wno-implicit -ggdb ${IFLAGS} -Wno-unused-label
LDFLAGS = 
LIBS    = -lstdc++ 

.PHONY: all clean distclean 
	all:: ${TARGET} 

${TARGET}: ${OBJS} 
	${CC} ${LDFLAGS} -o $@ $^ ${LIBS} 

${BUILDDIR}%.o: ${SRCDIR}%.cpp 
	${CC} ${CCFLAGS} -o $@ -c $< 

clean:: 
	-rm -f *~ ${BUILDDIR}*.o ${TARGET} 

distclean:: clean

