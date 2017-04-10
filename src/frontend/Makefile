UNAME = $(shell uname)
ARCH = $(shell uname -m)

OPTFLAGS = -g3
# OPTFLAGS = -DNDEBUG -O3 -march=native -m64
CXXFLAGS = -std=c++1y $(OPTFLAGS) $(shell ./link_graphics --cflags) $(shell pkg-config --cflags glm openal freealut) $(shell freetype-config --cflags)
LIBS = $(shell ./link_graphics --libs) $(shell pkg-config --libs glm openal freealut) $(shell freetype-config --libs)
OBJECTS = $(wildcard *.cpp)
COBJECTS = $(notdir $(patsubst %.cpp, %.o, $(OBJECTS)))
BINARY = planetarium

all:;$(MAKE) glsl;$(MAKE) $(BINARY) -j$(shell getconf _NPROCESSORS_ONLN)

glsl:
	glslangValidator -t triangle.vert triangle.geom triangle.frag
	glslangValidator -t plntclr.vert plntclr.geom plntclr.frag
	glslangValidator -t planet.vert planet.geom planet.frag
	glslangValidator -t planet.vert planet_skeleton.geom planet.frag
	glslangValidator -t planet.vert pglow.geom planet.frag
	glslangValidator -t ptext.vert ptext.frag
	glslangValidator -t pquad.vert pquad.frag

$(BINARY) : $(COBJECTS)
	$(CXX) $(COBJECTS) $(CXXFLAGS) $(LIBS) -o $(BINARY)

clean :
	rm -rvf $(BINARY) $(wildcard *.o) *.dSYM
