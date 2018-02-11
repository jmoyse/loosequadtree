// Julian Moyse
// CMSC 420 Fall 2007
// LooseQuadTree Project 4.3
//
#ifndef LOOSEQUADTREEDECODER_H
#define LOOSEQUADTREEDECODER_H
#include <iostream>
#include <math.h>

#include "LooseQuadTree.h"
#include "drawing_c.h"
#include "tName.h"

using namespace std;
class PriorityQueue;
class cNode;
class Quadtree {
public:
    Quadtree();
    void initLooseQuadTree();
    void initRectTree();
    void traceOn();
    void traceOff();

    void parse_command(tName *input);
    bool isFloatingPointNumber(tName *s);

    void INIT_QUADTREE(int width, double p);
    void DISPLAY();
    void LIST_RECTANGLES();
    void CREATE_RECTANGLE(tName name,int cx,int cy,int lx, int ly);
    void INSERT(tName n);
    void MOVE(tName name, int cx, int cy);
    void SEARCH_POINT(int px, int py);
    void DELETE_RECTANGLE(tName n);
    void DELETE_POINT(int px, int py);
    void REGION_SEARCH(tName n);
    void TOUCH(tName n);
    void WITHIN(tName n,int d);
    void VERT_NEIGHBOR(tName n);
    void HORIZ_NEIGHBOR(tName n);
    void NEAREST_RECTANGLE(int px, int py);
    void WINDOW(int llx, int lly, int lx, int ly);
    void CHANGE_EXPANSION_FACTOR(int p);
    void NEAREST_NEIGHBOR(tName n);
    void LEXICALLY_GREATER_NEAREST_NEIGHBOR(tName n);
    void RAYTRACE(int a, int b);
    
    
    LooseQuadTree looseQuadTree;
    bNode *rectTree;
};
#endif
