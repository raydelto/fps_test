SRC=Texture2d.cpp \
	ShaderProgram.cpp \
	Mesh.cpp \
	Camera.cpp \
	Mesh_Loading.cpp \
	glad.c

OBJ=bin/Texture2d.o \
	bin/ShaderProgram.o \
	bin/Mesh.o \
	bin/Camera.o \
	bin/Mesh_Loading.o \
	bin/glad.o


UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	LIBS = -lGL -lGLU -lglfw -ldl
	INCLUDES=-I ./include \
		-I /usr/include	
endif
ifeq ($(UNAME_S),Darwin)
FRAMEWORKS=-framework OpenGL

LIBS= -L/System/Library/Frameworks \
	  -lglfw
INCLUDES=-I/Users/raydelto/git/fps-test/common/includes


	
endif


WARNINGS=-w

all:
	g++ -c $(SRC) $(FRAMEWORKS) $(LIBS) $(INCLUDES) $(WARNINGS)
	mv *.o ./bin
	g++ $(OBJ) $(FRAMEWORKS) $(LIBS) $(INCLUDES) -o bin/main $(WARNINGS)