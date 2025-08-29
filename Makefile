CFLAGS = -std=c++17 -O2
CFLAGS += -I includes
LDFLAGS = -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl

all : GLTest

GLTest : main.cpp glad.c
	g++ $(CFLAGS) main.cpp glad.c -o GLTest $(LDFLAGS)

test:
	./GLTest

clean:
	rm -f GLTest
