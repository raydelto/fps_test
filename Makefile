SRC=src/Texture2d.cpp \
	src/ShaderProgram.cpp \
	src/MeshInterface.cpp \
	src/Mesh_Loading.cpp \
	src/Md2Model.cpp \
	src/RayMesh.cpp \
	src/Mesh.cpp \
	src/Camera.cpp \
	third-party-source-code/glad.c \

OBJ=bin/Texture2d.o \
	bin/ShaderProgram.o \
	bin/MeshInterface.o \
	bin/Mesh_Loading.o \
	bin/Md2Model.o \
	bin/RayMesh.o \
	bin/Mesh.o \
	bin/Camera.o \
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
INCLUDES=-I./includes
endif

WARNINGS=-Wall

all:
	g++ -c $(SRC) $(INCLUDES) $(WARNINGS)
	ls bin>/dev/null||mkdir bin
	mv *.o ./bin
	g++ $(OBJ) $(FRAMEWORKS) $(LIBS) $(INCLUDES) -o bin/main $(WARNINGS)
