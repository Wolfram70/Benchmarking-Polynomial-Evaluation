HCC = hipcc
CC = clang++
HCCFLAGS = -fopenmp
CCFLAGS = -I/usr/lib/gcc/x86_64-linux-gnu/10/include -fopenmp=libiomp5
SOURCE = main.cpp polyeval_hip.cpp polyeval.cpp
OBJECTS = main.o polyeval_hip.o polyeval.o
TARGET = polyeval

all: build cleanobj

build: $(OBJECTS)
	$(HCC) $(HCCFLAGS) $(OBJECTS) -o $(TARGET)

main.o: main.cpp
	$(CC) $(CCFLAGS) -c main.cpp -o main.o

polyeval_hip.o: polyeval_hip.cpp
	$(HCC) -c polyeval_hip.cpp -o polyeval_hip.o

polyeval.o: polyeval.cpp
	$(CC) $(CCFLAGS) -c polyeval.cpp -o polyeval.o

cleanobj:
	rm -f $(OBJECTS)

clean:
	rm -f $(OBJECTS) $(TARGET)