// Julian Moyse
// CMSC 420 Fall 2007
// LooseQuadTree Project 4.3
//
#include "LooseQuadTree.h"
using namespace std;

LooseQuadTree::LooseQuadTree() {
    looseQuadRoot = NULL;
    trace = false;
}
LooseQuadTree::LooseQuadTree(tName name, int centerX, int centerY, int lengthX, int lengthY, float expansion) {
    looseQuadRoot = NULL;
    looseQuadRoot = new cNode();
    World = Rectangle(name,centerX,centerY,lengthX,lengthY);
    p = expansion;
    trace = false;
}
void LooseQuadTree::traceOn() {
    trace = true;
    looseQuadRoot->trace = true;
}
void LooseQuadTree::traceOff() {
    trace = false;
    looseQuadRoot->trace = false;
}

void LooseQuadTree::AddRectangle(Rectangle *r) {
    looseQuadRoot->insertcNodeRectangle(r,looseQuadRoot,World.getLengthX(),World.getLengthY(),World.getCenterX(),World.getCenterY(), 0, p);
}

LooseQuadTree::~LooseQuadTree() {}
