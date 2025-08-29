CFLAGS = -std=c++17 -O2
CFLAGS += -I includes
LDFLAGS = -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl

all : MandelBrot

MandelBrot : mandelbrot.o glad.o shaders.o
	g++ $(CFLAGS) mandelbrot.o glad.o shaders.o -o Mandelbrot $(LDFLAGS)

mandelbrot.o : mandelbrot.cpp
	g++ $(CFLAGS) -c mandelbrot.cpp -o mandelbrot.o $(LDFLAGS)

shaders.o : shaders.cpp
	g++ $(CFLAGS) -c shaders.cpp -o shaders.o $(LDFLAGS)

glad.o : glad.c
	g++ $(CFLAGS) -c glad.c -o glad.o $(LDFLAGS)


mb:
	./Mandelbrot

clean:
	rm -f GLTest shaders.o glad.o mandelbrot.o
