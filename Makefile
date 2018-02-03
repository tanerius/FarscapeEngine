CFILES=$(shell find FarscapeEngine -name '*.cpp')
OFILES=$(patsubst %.cpp,%.o,$(CFILES))
TARGET=Farscape

OUTPUTDIR = build
EXECUTABLE = farscape_demo

OS := $(shell uname)

FLAGS= -framework OpenGL -lpng -lpthread -lglfw -lglew 
CC_FLAGS=-std=c++1y -O3 -w -pipe -ffast-math -fno-inline -mfpmath=sse -flto -fno-omit-frame-pointer -march=native -mtune=native
LIBRARY_PATHS = -L/usr/local/lib -I/opt/X11/lib
INCLUDE_PATHS = -I/usr/local/include -I/opt/X11/include


$(TARGET): $(OFILES)
	g++ $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(CC_FLAGS) $(FLAGS) -o $(TARGET) $(OFILES) 

%.o: %.cpp
	g++ $(CC_FLAGS) -o $@ -c $<

clean:
	rm -rf $(TARGET) $(OFILES)
