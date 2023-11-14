EXEC = vm 
CXX = g++ 
CPPFLAGS = -MMD
CXXFLAGS = -std=c++11 -g -Wall

SRC = $(wildcard *.cc)
OBJECTS= $(SRC:.cc=.o)
DEPENDS = $(OBJECTS:.o=.d)

LDLIBS = -lncurses

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${CPPFLAGS} ${OBJECTS} ${LDLIBS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm *.o *.d ${EXEC}

