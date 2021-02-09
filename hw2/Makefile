# define libraries
ifeq ($(shell uname),Darwin)
LIB = -DMAC -framework OPENGL -framework GLUT
else
LIB = -lGL -lGLU -lglut
endif

# define makefile targets
CC = g++ -std=c++11 -Wall -Wno-deprecated-declarations -O3

homework2: homework2.cpp util.cpp piece.cpp
	$(CC) -o $@ homework2.cpp piece.cpp util.cpp $(LIB)

clean: 
	/bin/rm -f homework2
