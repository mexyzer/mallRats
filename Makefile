CC = g++
CFLAGS = -c -std=c++11 -Wall

all: main.o player.o splashMenu.o level.o
	$(CC) main.o player.o splashMenu.o level.o -o mallRats -lsfml-graphics -lsfml-window -lsfml-system

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

player.o: player.cpp
	$(CC) $(CFLAGS) player.cpp common.h

splashMenu.o: splashMenu.cpp
	$(CC) $(CFLAGS) splashMenu.cpp common.h

level.o: level.cpp
	$(CC) $(CFLAGS) level.cpp common.h

clean:
	rm -rf *o mallRats
