CC = g++
CFLAGS = -c -std=c++11 -Wall

testCharacter: testCharacter.o Character.o
	$(CC) testCharacter.o Character.o -o testCharacter -lsfml-graphics -lsfml-window -lsfml-system

testCharacter.o: testCharacter.cpp
	$(CC) $(CFLAGS) testCharacter.cpp Character.h

Character.o: Character.cpp
	$(CC) $(CFLAGS) Character.cpp Character.h

clean:
	rm -rf *gch *o testCharacter mallRats
