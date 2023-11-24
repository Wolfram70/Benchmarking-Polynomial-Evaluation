CC = hipcc
CFLAGS = -I/usr/lib/gcc/x86_64-linux-gnu/10/include
SOURCE = main.cpp polyeval_hip.cpp polyeval.cpp
TARGET = polyeval

all: build

build:
	$(CC) $(CFLAGS) $(SOURCE) -o $(TARGET)

