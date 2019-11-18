all: rasterizer.o 
	g++ -g -o rasterizer rasterizer.o

rasterizer.o: rasterizer.cpp
	g++ -c rasterizer.cpp

clean:
	rm *.o 