# define libraries
ifeq ($(shell uname),Darwin)
LIB = -DMAC -framework OPENGL -framework GLUT
else
LIB = -lGL -lGLU -lglut
endif

# define makefile targets
CC = g++ -std=c++11 -Wall -Wno-deprecated-declarations -O3

homework2: homework2.cpp
	$(CC) -o $@ homework2.cpp block.cpp $(LIB)

homework1: homework1.cpp
	$(CC) -o $@ homework1.cpp $(LIB)

clean: 
	/bin/rm -f homework1 homework2
