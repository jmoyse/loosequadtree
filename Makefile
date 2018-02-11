CC= g++
CFLAGS=-Wl,-rpath,/usr/local/gcc/lib64

all: part4

part4: LooseQuadTree.h LooseQuadTree.cpp LooseQuadTreeDecoder.cpp LooseQuadTreeDecoder.h cNode.cpp cNode.h bNode.cpp bNode.h drawing_c.h drawing.c Rectangle.cpp Rectangle.h tName.h tName.cpp PriorityQueue.h temp.cpp
	$(CC) $(CFLAGS) -o part4 LooseQuadTree.h LooseQuadTree.cpp LooseQuadTreeDecoder.cpp LooseQuadTreeDecoder.h cNode.cpp cNode.h bNode.cpp bNode.h drawing_c.h drawing.c Rectangle.cpp Rectangle.h tName.cpp tName.h PriorityQueue.h

temp: LooseQuadTree.h LooseQuadTree.cpp LooseQuadTreeDecoder.cpp LooseQuadTreeDecoder.h cNode.cpp cNode.h bNode.cpp bNode.h drawing_c.h drawing.c Rectangle.cpp Rectangle.h tName.h tName.cpp PriorityQueue.h
	$(CC) $(CFLAGS) -o temp  bNode.cpp bNode.h  Rectangle.cpp Rectangle.h tName.cpp tName.h PriorityQueue.h temp.cpp

clean: 
	rm -rf part4 priorityqueue temp