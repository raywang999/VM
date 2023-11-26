EXEC =  a.out
CXX = g++ 

SOURCES := $(shell find ./ ../../lib -name "*.cc") 
OBJECTS= $(SOURCES:.cc=.o) 
DEPENDS = $(OBJECTS:.o=.d)

LDLIBS = -lncurses

INCLUDE=$(shell cd ../../; pwd)/include $(shell cd ../..; pwd)
INCLUDE_PARAMS=$(INCLUDE:%=-I%)

CPPFLAGS = -MMD ${INCLUDE_PARAMS}
CXXFLAGS = -std=c++20 -g -Wall 

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${CPPFLAGS} ${INCLUDE_PARAMS} ${OBJECTS} ${LDLIBS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm *.o *.d ${EXEC}

.PHONY: check

check: 
	valgrind --leak-check=full ./${EXEC} < input.txt 2> memtext.out 


