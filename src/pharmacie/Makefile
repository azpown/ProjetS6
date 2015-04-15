CXX = g++
EXEC = TestParseurSiSi
CXXFLAGS = -std=gnu++11 -O2
SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)

all : ${EXEC}

${EXEC} : depend $(OBJ)
	${CXX} ${CXXFLAGS} -o $@ ${OBJ}

.PHONY : clean

clean :
	rm $(OBJ)
depend :
	$(CXX) ${CXXFLAGS} -MM $(SRC) > depends.txt
