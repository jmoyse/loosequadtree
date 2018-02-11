// Julian Moyse
// CMSC 420 Fall 2007
// LooseQuadTree Project 4.3
//
#ifndef BNODE_H
#define BNODE_H
#include <iostream>

#include "Rectangle.h"

class bNode {
public:
    bNode();
    bNode(Rectangle *r);
    void insertNode(Rectangle *data);
    void removeNode(Rectangle *data);
    bNode* searchNode(tName name);
    Rectangle * getNode(int position);

    Rectangle* getRectangle();
    void printNodes();
    void listNodes();
    int length;
    bNode* findNode(Rectangle *data);
    bNode* findNode(tName s);
    ~bNode();
    bNode * prev;
    bNode * next;
    Rectangle *Rect;
};
#endif
