UNAME = $(shell uname)
ARCH = $(shell uname -m)

CXXFLAGS = -std=c++1y -g3 $(shell ./link_graphics --cflags) $(shell freetype-config --cflags) $(shell pkg-config --cflags glm)
LIBS = $(shell ./link_graphics --libs) $(shell pkg-config --libs glm) $(shell freetype-config --libs)
OBJECTS = $(wildcard *.cpp)
BINARY = planetarium

$(shell mkdir -p build)

all:;$(MAKE) glsl;$(MAKE) $(BINARY) -j$(shell getconf _NPROCESSORS_ONLN)

glsl:
	glslangValidator plntclr.vert plntclr.geom plntclr.frag
	glslangValidator planet.vert planet.geom planet.frag
	glslangValidator labels.vert labels.frag

$(BINARY) : $(notdir $(patsubst %.cpp, %.o, $(OBJECTS)))
	$(CXX) $(wildcard build/*.o) $(CXXFLAGS) $(LIBS) -o $(BINARY)

%.o : %.cpp
	$(CXX) -c $(CXXFLAGS) -o "build/$@" "$<"

clean :
	rm -rvf build
	rm -vf $(BINARY)
