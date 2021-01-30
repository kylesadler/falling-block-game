# define libraries
ifeq ($(shell uname),Darwin)
LIB = -DMAC -framework OPENGL -framework GLUT
else
LIB = -lGL -lGLU -lglut
endif

# define makefile targets
CC = g++ -std=c++11 -Wall -Wno-deprecated-declarations -O3

all: $(LIB2) $(BIN)


clean: 
	/bin/rm -f homework

homework: homework1.cpp
	$(CC) -o homework homework1.cpp $(LIB)

