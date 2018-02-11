// Julian Moyse
// CMSC 420 Fall 2007
// LooseQuadTree Project 4.3
//
#ifndef RECTANGLE_H
#define RECTANGLE_H
#define NDIR_1D 2
#include <iostream>
#include "tName.h"

class bNode;
using namespace std;

class Rectangle {
public:
    typedef enum {LEFT, RIGHT, BOTH} direction;
    typedef enum {X,Y} dimension;
    Rectangle();
    Rectangle(tName name, int centerX, int centerY, int lengthX,int lengthY);

    int getCenterX();
    int getCenterY();
    int getLengthX();
    int getLengthY();

    Rectangle* getLeft();
    Rectangle* getRight();

    void setCenter(int x, int y);
    void setLength(int x,int y);

    void setName(tName name);
    tName getName();
    void removeNode(tName r);
    void insertNode(Rectangle *r);
    void removeReference(Rectangle *r);
    Rectangle* search(tName r);
    Rectangle* findNode(tName r);
    Rectangle* findPredessor(Rectangle * tree);
    ~Rectangle();
private:
    tName Name;
    Rectangle *binSon[NDIR_1D];
    int Center[NDIR_1D];
    int Length[NDIR_1D];
};
#endif
