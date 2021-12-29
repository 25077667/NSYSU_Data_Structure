CC = g++
FLAGS = -std=c++17 -O3

all: dep
	$(CC) $(FLAGS)  -o huffman.elf main.cpp libs/huffman.so 
	
dep:
	$(CC) $(FLAGS) -fPIC -rdynamic -shared libs/tools.hpp libs/huffmanLib.cpp libs/huffmanLib.hpp -o libs/huffman.so

clean:
	rm -rf huffman.elf libs/huffman.so __pycache__