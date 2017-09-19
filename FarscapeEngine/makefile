# OBJS specifies which files to compile as part of the project
OBJS = tests

OUTPUTDIR = build
EXECUTABLE = farscape_demo

# CC specifies which compiler we're using
CC = g++

# INCLUDE_PATHS specifies the additional include paths we'll need
# INCLUDE_PATHS = -I/Users/tanerselim/Dev/antons_opengl_tutorials_book/common/include -I/usr/local/include 
INCLUDE_PATHS =  -I/usr/local/include 

# LIBRARY_PATHS specifies the additional library paths we'll need
LIBRARY_PATHS = -L/usr/local/lib 
# LIB_P = /Users/tanerselim/Dev/antons_opengl_tutorials_book/common/osx_64/
LIB_P = /usr/local/lib/
LOC_LIB = $(LIB_P)libGLEW.a $(LIB_P)libglfw3.a

# COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -std=c++14 -DAPPLE -DUSE_GLM -Wall -pedantic -arch x86_64 -fmessage-length=0 -UGLFW_CDECL

# LINKER_FLAGS specifies the libraries we're linking against
# Cocoa, IOKit, and CoreVideo are needed for static GLFW3.
LINKER_FLAGS = -framework OpenGL -lpng -framework Cocoa -framework IOKit -framework CoreVideo

# OBJ_NAME specifies the name of our exectuable
OBJ_NAME = cgdisplay

#This is the target that compiles our executable
all : clean $(OBJS) 


tests: cgdisplay rawmodel loader renderer shader texture helpers entity cgcamera mesh cginput cgobj callbacks
	$(CC) tests.cpp $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OUTPUTDIR)/$(EXECUTABLE) $(OUTPUTDIR)/cgdisplay.o $(OUTPUTDIR)/cgrawmodel.o $(OUTPUTDIR)/cgloader.o $(OUTPUTDIR)/cgrenderer.o $(OUTPUTDIR)/cgshader.o $(OUTPUTDIR)/cgtexture.o $(OUTPUTDIR)/cghelper.o $(OUTPUTDIR)/cgentity.o $(OUTPUTDIR)/cgcamera.o $(OUTPUTDIR)/cgmesh.o $(OUTPUTDIR)/cginput.o $(OUTPUTDIR)/cgobj.o $(OUTPUTDIR)/cgcallback.o $(LOC_LIB)

cgcamera : cgcore.hpp cgcamera.hpp 
	$(CC) cgcamera.cpp $(INCLUDE_PATHS) $(COMPILER_FLAGS) -c -o $(OUTPUTDIR)/cgcamera.o

cgdisplay : callbacks cgdisplay.hpp
	$(CC) cgdisplay.cpp $(INCLUDE_PATHS) $(COMPILER_FLAGS) -c -o $(OUTPUTDIR)/cgdisplay.o

cginput : cgcamera cgdisplay cginput.hpp
	$(CC) cginput.cpp $(INCLUDE_PATHS) $(COMPILER_FLAGS) -c -o $(OUTPUTDIR)/cginput.o

callbacks : cgcallback.hpp
	$(CC) cgcallback.cpp $(INCLUDE_PATHS) $(COMPILER_FLAGS) -c -o $(OUTPUTDIR)/cgcallback.o

loader : rawmodel texture cgloader.hpp 
	$(CC) cgloader.cpp $(INCLUDE_PATHS) $(COMPILER_FLAGS) -c -o $(OUTPUTDIR)/cgloader.o

renderer : rawmodel cgrenderer.hpp 
	$(CC) cgrenderer.cpp $(INCLUDE_PATHS) $(COMPILER_FLAGS) -c -o $(OUTPUTDIR)/cgrenderer.o

rawmodel : cgrawmodel.hpp
	$(CC) cgrawmodel.cpp $(INCLUDE_PATHS) $(COMPILER_FLAGS) -c -o $(OUTPUTDIR)/cgrawmodel.o

shader : cgshader.hpp
	$(CC) cgshader.cpp $(INCLUDE_PATHS) $(COMPILER_FLAGS) -c -o $(OUTPUTDIR)/cgshader.o

entity : texture cgentity.hpp
	$(CC) cgentity.cpp $(INCLUDE_PATHS) $(COMPILER_FLAGS) -c -o $(OUTPUTDIR)/cgentity.o

texture : cgtransform.hpp cgtexture.hpp 
	$(CC) cgtexture.cpp $(INCLUDE_PATHS) $(COMPILER_FLAGS) -c -o $(OUTPUTDIR)/cgtexture.o

cgobj : mesh cgobj.hpp
	$(CC) cgobj.cpp $(INCLUDE_PATHS) $(COMPILER_FLAGS) -c -o $(OUTPUTDIR)/cgobj.o

helpers : cghelper.hpp
	$(CC) cghelper.cpp $(INCLUDE_PATHS) $(COMPILER_FLAGS) -c -o $(OUTPUTDIR)/cghelper.o

mesh : cgcore.hpp cgmesh.hpp
	$(CC) cgmesh.cpp $(INCLUDE_PATHS) $(COMPILER_FLAGS) -c -o $(OUTPUTDIR)/cgmesh.o

clean:
	- rm -rf $(OUTPUTDIR)
	- mkdir -p $(OUTPUTDIR)
