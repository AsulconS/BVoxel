CC=g++
CC2=gcc

all: stb_image.o display.o shader.o mesh.o texture.o transform.o main.o
	$(CC) stb_image.o display.o shader.o mesh.o texture.o transform.o main.o -lSDL2 -lGL -lGLU -lGLEW -o main

stb_image.o: stb_image.c
	$(CC2) -c stb_image.c

display.o: display.cpp
	$(CC) -c display.cpp

shader.o: shader.cpp
	$(CC) -c shader.cpp

mesh.o: mesh.cpp
	$(CC) -c mesh.cpp

texture.o: texture.cpp
	$(CC) -c texture.cpp

transform.o: transform.cpp
	$(CC) -c transform.cpp

main.o: main.cpp
	$(CC) -c main.cpp

clean:
	rm -rf *.o main
