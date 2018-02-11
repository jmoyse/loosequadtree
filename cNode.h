// Julian Moyse
// CMSC 420 Fall 2007
// LooseQuadTree Project 4.3
//
#ifndef CNODE_H
#define CNODE_H

#define NDIR_2D 4
#include "bNode.h"

class PriorityQueue;
class CompareField;

class cNode {
public:
    typedef enum {NW,NE,SW,SE} quadrant;
    cNode();
    cNode(int quadrant, Rectangle *r);

    ~cNode();
    void drawQuadrants(cNode *quadTreeNode,int cx,int cy,int lx,int ly, int position);
    void drawQuadrantsList(cNode *quadTreeNode,int cx,int cy,int lx,int ly, int position, bNode **list);
    void drawAxis(cNode *quadTreeNode,int rect_llx, int rect_lly, int rect_lx, int rect_ly, int cx,int cy,int lx,int ly, int position);
    
    void printQuadrants(cNode *quadTreeNode);
    void printQuadrants(cNode *quadTreeNode, int depth);
    void insertRectangle(int quadrant, Rectangle *r);
    void deleteRectangle(cNode **quadTreeNode, Rectangle * rect, int cx, int cy, int lx, int ly, int position, float p,bNode ** list);
    void deletePoint(cNode **quadTreeNode,int findX, int findY, int cx, int cy, int lx, int ly, int position, float p, bNode ** list);
    void insertcNodeRectangle(Rectangle *r, cNode *tree, int worldX, int worldY, int centerX, int centerY, int position, float p);
    void moveInsert(Rectangle *r, cNode **tree, int worldX, int worldY, int centerX, int centerY, int position, int p);
    void moveRectangle(cNode **quadTreeNode, Rectangle * rect, int offsetx, int offsety, int cx, int cy, int lx, int ly, float expansion,  int position,  bNode ** list);
    void searchPoint(cNode **quadTreeNode,int findX, int findY, int cx, int cy, int lx, int ly, int position, float p, bNode ** list);
    void regionNodeSearch(cNode **quadTreeNode, Rectangle * rect, int cx, int cy, int lx, int ly, int position, float p, bNode ** list);
    void touch(cNode **quadTreeNode, Rectangle * rect, int cx, int cy, int lx, int ly, int position, float p, bNode ** list);
    void within(cNode **quadTreeNode, Rectangle * q,Rectangle *n, int cx, int cy, int lx, int ly, int position, float p, bNode ** list);
    bool intersects(int sRight,  int sLeft, int sTop, int sBottom, int rRight, int rLeft, int rTop, int rBottom);
    bool contains(int sRight,  int sLeft, int sTop, int sBottom, int rRight, int rLeft, int rTop, int rBottom);
    bool intersectionIsZero(int sRight,  int sLeft, int sTop, int sBottom, int rRight, int rLeft, int rTop, int rBottom);
    bool horizontalNeighbor(int sRight,  int sLeft, int sTop, int sBottom, int rRight, int rLeft, int rTop, int rBottom);
   
    void insert(Rectangle *r);
    void searchPoint(cNode *quadTreeNode, int px, int py, int position,  bNode ** list);
    Rectangle * verticalNeighbor(cNode **quadTreeNode, Rectangle * n, int cx, int cy, int lx, int ly, int position, float p);
    int vertDistance(CompareField r, CompareField s, double p);
    
    void vertAddChildrenNodes(PriorityQueue **queue, cNode *quadrant, CompareField point, CompareField quad, double p, int position);
    Rectangle * horizontalNeighbor(cNode **quadTreeNode, Rectangle * n, int cx, int cy, int lx, int ly, int position, float p);
    int horDistance(CompareField r, CompareField s, double p);
    void horAddChildrenNodes(PriorityQueue **queue, cNode *quadrant, CompareField point, CompareField quad, double p, int position);
    Rectangle * nearestRectangle(cNode **quadTreeNode, int findX, int findY, int cx, int cy, int lx, int ly, int position, float p);
    void nearestAddChildrenNodes(PriorityQueue **queue, cNode *quadrant, CompareField compareQuad, CompareField field, double p, int position);
    void window(cNode **quadTreeNode, int rect_llx, int rect_lly, int rect_lx, int rect_ly, int cx, int cy, int lx, int ly, int position, float p, bNode ** list);
    void changeExpansion(cNode **quadTreeNode,int ocx, int ocy, int olx, int oly, int cx, int cy, int lx, int ly, float old_expansion,float new_expansion, int position,  bNode ** list);
    bool canFit(Rectangle *r, int cx, int cy, int lx, int ly, int p, int quadrant);

    Rectangle * nearestNeighbor(cNode **quadTreeNode, Rectangle * n, int cx, int cy, int lx, int ly, int position, float p);
    Rectangle * lexicallyNearestNeighbor(cNode **quadTreeNode, Rectangle * n, int cx, int cy, int lx, int ly, int position, float p);
    bool rayIntersect(double rox,double roy,double roz,double rdx,double rdy,double rdz,double bminx, double bminy,double bminz,double bmaxx, double bmaxy, double bmaxz);
    Rectangle * rayTrace(cNode **quadTreeNode, int a, int b, int cx, int cy, int lx, int ly, int position, float p);
    void raytraceAddChildrenNodes(PriorityQueue **queue, cNode *quadrant, CompareField point, CompareField quad, double p, int position, int a, int b, int top);
    
    void traceOn();
    void traceOff();

    cNode* getNW();
    cNode* getSW();
    cNode* getNE();
    cNode* getSE();
    bool trace;
    cNode *spcSon[NDIR_2D];
    bNode *binSon;
};
#endif
