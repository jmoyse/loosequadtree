// Julian Moyse
// CMSC 420 Fall 2007
// LooseQuadTree Project 4.3
//
#ifndef LOOSEQUADTREE_H
#define LOOSEQUADTREE_H

#ifndef RECTANGLE_H
#include "Rectangle.h"
#endif

#ifndef CNODE_H
#include "cNode.h"
#endif

using namespace std;
class LooseQuadTree {
public:
    LooseQuadTree();
    LooseQuadTree(tName name, int centerX, int centerY, int lengthX, int lengthY, float p);
    void AddRectangle(Rectangle *r);
    void traceOn();
    void traceOff();

    cNode *looseQuadRoot;
    Rectangle World;
    float p;
    bool trace;
    ~LooseQuadTree();
};
#endif
