#Flags de compilacion
CFLAGS = -c -std=c++11

main: main.o AB.o nodoB.o
	g++  main.o nodoB.o AB.o -o main
	mv *.o ./objects
	mv main ./build


main.o: ./src/main.cpp
	g++ $(CFLAGS) ./src/main.cpp

nodoB.o: ./src/nodoB.cpp ./include/nodoB.h
	g++ $(CFLAGS) ./src/nodoB.cpp

AB.o: ./src/AB.cpp ./include/AB.h
	g++ $(CFLAGS) ./src/AB.cpp


.PHONY: clean
clean:
	rm -rf ./objects/*.o
	rm -rf ./build/main


run:
	./build/main 
