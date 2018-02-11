// Julian Moyse
// CMSC 420 Fall 2007
// LooseQuadTree Project 4.3
//
#include "cNode.h"
#include "drawing_c.h"
#include <math.h>
#include <sstream>

#include "PriorityQueue.h"
using namespace std;

cNode::cNode() {
    spcSon[NW] = NULL;
    spcSon[NE] = NULL;
    spcSon[SW] = NULL;
    spcSon[SE] = NULL;
    binSon = NULL;
    binSon = new bNode();
    trace = false;
}

cNode::cNode(int quadrant, Rectangle *r) {
    spcSon[NW] = NULL;
    spcSon[NE] = NULL;
    spcSon[SW] = NULL;
    spcSon[SE] = NULL;
    spcSon[quadrant] = new cNode();
    binSon = new bNode();
    spcSon[quadrant]->binSon = new bNode(r);
}

void cNode::insert(Rectangle *r) {
    if (binSon->length == 0) {
        binSon = new bNode(r);
    } else {
        binSon->insertNode(r);
    }
}

void cNode::traceOn() {
    trace = true;
}

void cNode::traceOff() {
    trace = false;
}

void cNode::insertRectangle(int quadrant, Rectangle *r) {
    if (spcSon[quadrant] == NULL) {
        spcSon[quadrant] = new cNode();
    }

    if (spcSon[quadrant]->binSon->length == 0) {
        spcSon[quadrant]->binSon = new bNode(r);
    } else {
        spcSon[quadrant]->binSon->insertNode(r);
    }
}

void cNode::printQuadrants(cNode *quadTreeNode) {
    if(quadTreeNode != NULL) {
        printQuadrants(quadTreeNode->spcSon[NW]);
        printQuadrants(quadTreeNode->spcSon[NE]);
        quadTreeNode->binSon->printNodes();
        cout << endl;
        printQuadrants(quadTreeNode->spcSon[SW]);
        printQuadrants(quadTreeNode->spcSon[SE]);
    }
}

void cNode::drawQuadrants(cNode *quadTreeNode,int cx,int cy,int lx,int ly, int position) {
    if(quadTreeNode != NULL) {
        if (quadTreeNode->binSon!= NULL) {
            SetLineDash(3,2);
              DrawLine(cx-(lx/2),cy,cx+(lx/2),cy);
              SetLineDash(3,2);
              DrawLine(cx,cy-(ly/2),cx,cy+(ly/2));
              
            for (int i = 0; i<quadTreeNode->binSon->length; i++) {
                int minX = quadTreeNode->binSon->getNode(i)->getCenterX() - quadTreeNode->binSon->getNode(i)->getLengthX()/2;
                int minY = quadTreeNode->binSon->getNode(i)->getCenterY() - quadTreeNode->binSon->getNode(i)->getLengthY()/2;
                int maxX = quadTreeNode->binSon->getNode(i)->getCenterX() + quadTreeNode->binSon->getNode(i)->getLengthX()/2;
                int maxY = quadTreeNode->binSon->getNode(i)->getCenterY() + quadTreeNode->binSon->getNode(i)->getLengthY()/2;

                SetLineDash(1,1);
                DrawRect(minX,minY,maxX,maxY);

                char * temp;
                temp = new char[quadTreeNode->binSon->getNode(i)->getName().length() + 1];
                strcpy(temp, quadTreeNode->binSon->getNode(i)->getName().toString());	              
                string c;
                

                string str;
                stringstream out;
                out << position;
                str = out.str();                
                tName * strin = new tName(str.c_str());
                
                DrawName(strin->toString(), minX+5, minY+5);
                DrawName(temp, minX,minY);
            }
        }	
        if (quadTreeNode->spcSon[NW] == NULL && quadTreeNode->spcSon[NE] == NULL && quadTreeNode->spcSon[SW] == NULL && quadTreeNode->spcSon[SE] == NULL){

            return;
        }

  

        drawQuadrants(quadTreeNode->spcSon[NW], cx-(lx/4), cy+(ly/4), lx/2,ly/2, 4*position+1);
        drawQuadrants(quadTreeNode->spcSon[NE], cx+(lx/4), cy+(ly/4), lx/2,ly/2, 4*position+2);
        drawQuadrants(quadTreeNode->spcSon[SW], cx-(lx/4), cy-(ly/4), lx/2,ly/2, 4*position+3);
        drawQuadrants(quadTreeNode->spcSon[SE], cx+(lx/4), cy-(ly/4), lx/2,ly/2, 4*position+4);
    }
	string str;
	                stringstream out;
	                out << position;
	                str = out.str();                
	                tName * strin = new tName(str.c_str());
	DrawName(strin->toString(),cx,cy);
}


void cNode::drawQuadrantsList(cNode *quadTreeNode,int cx,int cy,int lx,int ly, int position,bNode ** list) {
    if(quadTreeNode != NULL) {
        if (quadTreeNode->binSon!= NULL) {
            for (int i = 0; i<quadTreeNode->binSon->length; i++) {
                int minX = quadTreeNode->binSon->getNode(i)->getCenterX() - quadTreeNode->binSon->getNode(i)->getLengthX()/2;
                int minY = quadTreeNode->binSon->getNode(i)->getCenterY() - quadTreeNode->binSon->getNode(i)->getLengthY()/2;
                int maxX = quadTreeNode->binSon->getNode(i)->getCenterX() + quadTreeNode->binSon->getNode(i)->getLengthX()/2;
                int maxY = quadTreeNode->binSon->getNode(i)->getCenterY() + quadTreeNode->binSon->getNode(i)->getLengthY()/2;
                Rectangle *rect = quadTreeNode->binSon->getNode(i);

                if ((*list)->searchNode(rect->getName())!=NULL) {
                    SetLineDash(1,1);
                    DrawRect(minX,minY,maxX,maxY);
                    char * temp;
                    temp = new char[quadTreeNode->binSon->getNode(i)->getName().length()+1];
                    strcpy(temp, quadTreeNode->binSon->getNode(i)->getName().toString());
                    DrawName(temp, minX,minY);
                }
            }
        }
        if (quadTreeNode->spcSon[NW] == NULL && quadTreeNode->spcSon[NE] == NULL && quadTreeNode->spcSon[SW] == NULL && quadTreeNode->spcSon[SE] == NULL)
            return;

        drawQuadrantsList(quadTreeNode->spcSon[NW], cx-(lx/4), cy+(ly/4), lx/2,ly/2, 4*position+1, &(*list));
        drawQuadrantsList(quadTreeNode->spcSon[NE], cx+(lx/4), cy+(ly/4), lx/2,ly/2, 4*position+2,&(*list));
        drawQuadrantsList(quadTreeNode->spcSon[SW], cx-(lx/4), cy-(ly/4), lx/2,ly/2, 4*position+3,&(*list));
        drawQuadrantsList(quadTreeNode->spcSon[SE], cx+(lx/4), cy-(ly/4), lx/2,ly/2, 4*position+4,&(*list));
    }
}

// TODO: Fix move so its insert point actually is the right size
void cNode::moveRectangle(cNode **quadTreeNode, Rectangle * rect, int offsetx, int offsety, int cx, int cy, int lx, int ly, float p, int position, bNode ** list) {
    int quadrant = 0;
    if((*quadTreeNode) != NULL) {
        if (trace == true)
            cout << position << " ";
        if ((*quadTreeNode)->binSon != NULL) {
            bNode *temp = (*quadTreeNode)->binSon->searchNode(rect->getName());
            if (temp != NULL) {
                if ((*quadTreeNode)->binSon->length == 1) {
                    (*quadTreeNode)->binSon = new bNode();
                } else {
                    (*quadTreeNode)->binSon->removeNode(temp->Rect);
                }
            }
        }

        int rRight = rect->getCenterX()+(rect->getLengthX()/2);
        int rLeft = rect->getCenterX()-(rect->getLengthX()/2);
        int rTop = rect->getCenterY()+(rect->getLengthY()/2);
        int rBottom = rect->getCenterY()-(rect->getLengthY()/2);

        int newX = (lx/2*(1+p))/2;
        int newY = (ly/2*(1+p))/2;

        if (rect->getCenterX() >= cx && rLeft >= ((cx+(lx/4))-newX) && rRight <= ((cx+(lx/4))+newX)) { // EASTERN QUADRANT
            if (rect->getCenterY() >= cy && rTop <= ((cy+(ly/4))+newY) && rBottom >= ((cy+(ly/4))-newY)) {// NE
                newX = cx+(lx/4);
                newY = cy+(ly/4);
                quadrant = NE;
                moveRectangle(&(*quadTreeNode)->spcSon[NE], rect, offsetx, offsety, newX,newY,lx/2,ly/2, p,4*position+2,&(*list));
            } else if (rect->getCenterY() < cy && rTop <= ((cy-(ly/4))+newY) && rBottom >= ((cy-(ly/4))-newY)) { // SE
                newX = cx+(lx/4);
                newY = cy-(ly/4);
                quadrant = SE;
                moveRectangle(&(*quadTreeNode)->spcSon[SE], rect, offsetx, offsety, newX,newY,lx/2,ly/2, p,4*position+4,&(*list));
            }
        } else if (rect->getCenterX() < cx && rLeft >=((cx-(lx/4))-newX) && rRight <= ((cx-(lx/4))+newX)) {
            if(rect->getCenterY() >= cy && rTop <= ((cy+(ly/4))+newY) && rBottom>= ((cy+(ly/4))-newY)) { 	// NW
                newX = cx-(lx/4);
                newY = cy+(ly/4);
                quadrant =NW;
                moveRectangle(&(*quadTreeNode)->spcSon[NW], rect, offsetx, offsety, newX,newY,lx/2,ly/2, p,4*position+1,&(*list));
            } else if (rect->getCenterY() < cy && rTop <= ((cy-(ly/4))+newY) && rBottom >= ((cy-(ly/4))-newY)) { // SW
                newX = cx-(lx/4);
                newY = cy-(ly/4);
                quadrant = SW;
                moveRectangle(&(*quadTreeNode)->spcSon[SW], rect, offsetx, offsety, newX,newY,lx/2,ly/2, p, 4*position+3,&(*list));
            }
        }

        rRight = rect->getCenterX()+(rect->getLengthX()/2)+offsetx;
        rLeft = rect->getCenterX()-(rect->getLengthX()/2)+offsetx;
        rTop = rect->getCenterY()+(rect->getLengthY()/2)+offsety;
        rBottom = rect->getCenterY()-(rect->getLengthY()/2)+offsety;

        int wRight = cx+(lx/2)*(1+p);
        int wLeft = cx-(lx/2)*(1+p);
        int wTop = cy+(ly/2)*(1+p);
        int wBottom = cy-(ly/2)*(1+p);

        // make sure it fits
        if (rRight <= wRight && rLeft>=wLeft && rTop<=wTop && rBottom >= wBottom && (*list)->length == 0) {
            //set a new X,Y point
            rect->setCenter((rect->getCenterX())+offsetx, (rect->getCenterY())+offsety);
            if (rect->getCenterX() >= cx && rLeft >= ((cx+(lx/4))-newX) && rRight <= ((cx+(lx/4))+newX)) { // EASTERN QUADRANT
                if (rect->getCenterY() >= cy && rTop <= ((cy+(ly/4))+newY) && rBottom >= ((cy+(ly/4))-newY)) {// NE
                    if ((*quadTreeNode)->spcSon[(*quadTreeNode)->NE] == NULL)
                        (*quadTreeNode)->spcSon[(*quadTreeNode)->NE] = new cNode();
                    insertcNodeRectangle(rect,(*quadTreeNode)->getNE(),lx/2,ly/2, cx+(lx/4),cy+(ly/4),4*(position)+2,p);
                } else if (rect->getCenterY() < cy && rTop <= ((cy-(ly/4))+newY) && rBottom >= ((cy-(ly/4))-newY)) { // SE
                    if ((*quadTreeNode)->spcSon[(*quadTreeNode)->SE] == NULL)
                        (*quadTreeNode)->spcSon[(*quadTreeNode)->SE] = new cNode();
                    insertcNodeRectangle(rect,(*quadTreeNode)->getSE(),lx/2,ly/2,  cx+(lx/4),cy-(ly/4), 4*(position)+4,p);
                } else { // add here
                    if ((*quadTreeNode)->binSon->length == 0)
                        (*quadTreeNode)->binSon= new bNode(rect);
                    else
                        (*quadTreeNode)->insert(rect);
                    return;
                }
            } else if (rect->getCenterX() < cx && rLeft >= ((cx-(lx/4))-newX) && rRight <= ((cx-(lx/4))+newX)) {
                if(rect->getCenterY() >= cy && rTop <= ((cy+(ly/4))+newY) && rBottom >= ((cy+(ly/4))-newY)) { 	// NW
                    if ((*quadTreeNode)->spcSon[(*quadTreeNode)->NW] == NULL)
                        (*quadTreeNode)->spcSon[(*quadTreeNode)->NW] = new cNode();
                    insertcNodeRectangle(rect,(*quadTreeNode)->getNW(),lx/2,ly/2, cx-(lx/4),cy+(ly/4), 4*(position)+1,p);
                } else if (rect->getCenterY() < cy && rTop <= ((cy-(ly/4))+newY) && rBottom >= ((cy-(ly/4))-newY)) { // SW
                    if ((*quadTreeNode)->spcSon[(*quadTreeNode)->SW] == NULL)
                        (*quadTreeNode)->spcSon[(*quadTreeNode)->SW] = new cNode();
                    insertcNodeRectangle(rect,(*quadTreeNode)->getSW(),lx/2,ly/2, cx-(lx/4),cy-(ly/4),4*(position)+3,p);
                } else { // add here
                    if ((*quadTreeNode)->binSon->length == 0)
                        (*quadTreeNode)->binSon= new bNode(rect);
                    else
                        (*quadTreeNode)->insert(rect);
                    return;
                }
            } else {// add here
                if ((*quadTreeNode)->binSon->length == 0)
                    (*quadTreeNode)->binSon= new bNode(rect);
                else
                    (*quadTreeNode)->insert(rect);
                return;
            }

            if ((*list)->length == 0)
                (*list) = new bNode(rect);
            else
                (*list)->insertNode(rect);
            return;
        }
        if ((*quadTreeNode)->spcSon[NW] == NULL && (*quadTreeNode)->spcSon[NE] == NULL && (*quadTreeNode)->spcSon[SW] == NULL && (*quadTreeNode)->spcSon[SE] == NULL && ((*quadTreeNode)->binSon == NULL || (*quadTreeNode)->binSon->length == 0) && (*quadTreeNode)!=this) {
            (*quadTreeNode) = NULL;
        }
    }
}

void cNode::deleteRectangle(cNode **quadTreeNode, Rectangle * rect, int cx, int cy, int lx, int ly, int position, float p,  bNode ** list) {
    int quadrant = 0;
    if((*quadTreeNode) != NULL) {
        if (trace == true)
            cout << position << " ";
        if ((*quadTreeNode)->binSon != NULL) {
            bNode *temp = (*quadTreeNode)->binSon->searchNode(rect->getName());
            if (temp != NULL) {
                if ((*quadTreeNode)->binSon->length == 1) {
                    (*quadTreeNode)->binSon = new bNode();
                } else {
                    (*quadTreeNode)->binSon->removeNode(temp->Rect);
                }
                if ((*list)->length == 0)
                    (*list) = new bNode(rect);
                else
                    (*list)->insertNode(rect);

                if ((*quadTreeNode)->spcSon[NW] == NULL && (*quadTreeNode)->spcSon[NE] == NULL && (*quadTreeNode)->spcSon[SW] == NULL && (*quadTreeNode)->spcSon[SE] == NULL && ((*quadTreeNode)->binSon == NULL || (*quadTreeNode)->binSon->length == 0) && (*quadTreeNode)!=this) {
                    (*quadTreeNode) = NULL;
                }
                return;
            }
        }

        int rRight = rect->getCenterX()+(rect->getLengthX()/2);
        int rLeft = rect->getCenterX()-(rect->getLengthX()/2);
        int rTop = rect->getCenterY()+(rect->getLengthY()/2);
        int rBottom = rect->getCenterY()-(rect->getLengthY()/2);

        int newX = (lx/2*(1+p))/2;
        int newY = (ly/2*(1+p))/2;

        if (rect->getCenterX() >= cx && rLeft >= ((cx+(lx/4))-newX) && rRight <= ((cx+(lx/4))+newX)) { // EASTERN QUADRANT
            if (rect->getCenterY() >= cy && rTop <= ((cy+(ly/4))+newY) && rBottom >= ((cy+(ly/4))-newY)) {// NE
                newX = cx+(lx/4);
                newY = cy+(ly/4);
                quadrant = NE;
                deleteRectangle(&(*quadTreeNode)->spcSon[NE], rect,newX,newY,lx/2,ly/2,4*position+2,p,&(*list));
            } else if (rect->getCenterY() < cy && rTop <= ((cy-(ly/4))+newY) && rBottom >= ((cy-(ly/4))-newY)) { // SE
                newX = cx+(lx/4);
                newY = cy-(ly/4);
                quadrant = SE;
                deleteRectangle(&(*quadTreeNode)->spcSon[SE], rect,newX,newY,lx/2,ly/2,4*position+4,p,&(*list));
            }
        } else if (rect->getCenterX() < cx && rLeft >= ((cx-(lx/4))-newX) && rRight <= ((cx-(lx/4))+newX)) {
            if(rect->getCenterY() >= cy && rTop <= ((cy+(ly/4))+newY) && rBottom>= ((cy+(ly/4))-newY)) { 	// NW
                newX = cx-(lx/4);
                newY = cy+(ly/4);
                quadrant =NW;
                deleteRectangle(&(*quadTreeNode)->spcSon[NW], rect, newX,newY,lx/2,ly/2,4*position+1,p,&(*list));
            } else if (rect->getCenterY() <cy && rTop <= ((cy-(ly/4))+newY) && rBottom >= ((cy-(ly/4))-newY)) { // SW
                newX = cx-(lx/4);
                newY = cy-(ly/4);
                quadrant = SW;
                deleteRectangle(&(*quadTreeNode)->spcSon[SW], rect, newX,newY,lx/2,ly/2, 4*position+3,p,&(*list));
            }
        }

        if ((*quadTreeNode)->spcSon[NW] == NULL && (*quadTreeNode)->spcSon[NE] == NULL && (*quadTreeNode)->spcSon[SW] == NULL && (*quadTreeNode)->spcSon[SE] == NULL && ((*quadTreeNode)->binSon == NULL || (*quadTreeNode)->binSon->length == 0) && (*quadTreeNode)!=this) {
            (*quadTreeNode) = NULL;
        }
        return;
    }
}

void cNode::insertcNodeRectangle(Rectangle *r, cNode *tree, int worldX, int worldY, int centerX, int centerY, int position, float p) {
    int rRight = r->getCenterX()+(r->getLengthX()/2);
    int rLeft = r->getCenterX()-(r->getLengthX()/2);
    int rTop = r->getCenterY()+(r->getLengthY()/2);
    int rBottom = r->getCenterY()-(r->getLengthY()/2);

    int worldX4 = worldX/4;
    int worldY4 = worldY/4;

    int newX = (worldX4)*(p+1);
    int newY = (worldY4)*(p+1);

    if (trace == true)
        cout << position << " " ;
    if (r->getCenterX() >= centerX && rLeft >= ((centerX+(worldX4))-newX) && rRight <= ((centerX+(worldX4))+newX)) { // EASTERN QUADRANT
        if (r->getCenterY() >= centerY && rTop <= ((centerY+(worldY4))+newY) && rBottom >= ((centerY+(worldY4))-newY)) {// NE
            if (tree->spcSon[tree->NE] == NULL)
                tree->spcSon[tree->NE] = new cNode();
            insertcNodeRectangle(r,tree->getNE(),worldX/2,worldY/2, centerX+(worldX4),centerY+(worldY4),4*(position)+2,p);
        } else if (r->getCenterY() < centerY && rTop <= ((centerY-(worldY4))+newY) && rBottom >=((centerY-(worldY4))-newY)) { // SE
            if (tree->spcSon[tree->SE] == NULL)
                tree->spcSon[tree->SE] = new cNode();
            insertcNodeRectangle(r,tree->getSE(),worldX/2,worldY/2,  centerX+(worldX4),centerY-(worldY4), 4*(position)+4,p);
        } else { // add here
            if (tree->binSon->length == 0)
                tree->binSon= new bNode(r);
            else
                tree->insert(r);
            return;
        }
    } else if (r->getCenterX() < centerX && rLeft >=((centerX-(worldX4))-newX) && rRight <= ((centerX-(worldX4))+newX)) {
        if(r->getCenterY() >= centerY && rTop <= ((centerY+(worldY4))+newY) && rBottom >= ((centerY+(worldY4))-newY)) { 	// NW
            if (tree->spcSon[tree->NW] == NULL)
                tree->spcSon[tree->NW] = new cNode();
            insertcNodeRectangle(r,tree->getNW(),worldX/2,worldY/2, centerX-(worldX4),centerY+(worldY4), 4*(position)+1,p);
        } else if (r->getCenterY() < centerY && rTop <= ((centerY-(worldY4))+newY) && rBottom >= ((centerY-(worldY4))-newY)) { // SW
            if (tree->spcSon[tree->SW] == NULL)
                tree->spcSon[tree->SW] = new cNode();
            insertcNodeRectangle(r,tree->getSW(),worldX/2,worldY/2, centerX-(worldX4),centerY-(worldY4),4*(position)+3,p);
        } else { // add here
            if (tree->binSon->length == 0)
                tree->binSon= new bNode(r);
            else
                tree->insert(r);

            return;
        }
    } else {// add here
        if (tree->binSon->length == 0)
            tree->binSon= new bNode(r);
        else
            tree->insert(r);

        return;
    }
}
void cNode::deletePoint(cNode **quadTreeNode,int findX, int findY, int cx, int cy, int lx, int ly, int position, float p, bNode ** list) {
    if((*quadTreeNode) != NULL) {
        if (trace == true)
            cout << position << " ";

        if ((*quadTreeNode)->binSon != NULL && (*quadTreeNode)->binSon->length > 0) {
            for(int i=(*quadTreeNode)->binSon->length-1; i>=0; i--) {
                Rectangle * nodeToDelete = (*quadTreeNode)->binSon->getNode(i);

                int SRectMaxX = nodeToDelete->getCenterX()+(nodeToDelete->getLengthX()/2);
                int SRectMinX = nodeToDelete->getCenterX()-(nodeToDelete->getLengthX()/2);
                int SRectMaxY = nodeToDelete->getCenterY()+(nodeToDelete->getLengthY()/2);
                int SRectMinY = nodeToDelete->getCenterY()-(nodeToDelete->getLengthY()/2);

                if (SRectMaxX >=findX && SRectMinX<=findX) {
                    if(	SRectMaxY>=findX && SRectMinY<=findY) {
                        if ((*quadTreeNode)->binSon->length == 1) {
                            (*quadTreeNode)->binSon = new bNode();
                        } else {
                            (*quadTreeNode)->binSon->removeNode(nodeToDelete);
                        }

                        if ((*list)->length == 0)
                            (*list) = new bNode(nodeToDelete);
                        else
                            (*list)->insertNode(nodeToDelete);
                    }
                }
            }
        }

        int newX = (lx/4)*(p+1);
        int newY = (ly/4)*(p+1);

        if (findX <= ((cx-(lx/4))+newX)) {
            if(findY>= ((cy+(ly/4))-newY)) { 	// NW
                deletePoint(&(*quadTreeNode)->spcSon[NW], findX, findY, cx-(lx/4),cy+(ly/4),lx/2,ly/2,4*position+1,p,&(*list));
            }
        }
        if (findX >= ((cx+(lx/4))-newX)) { // EASTERN QUADRANT
            if (findY >= ((cy+(ly/4))-newY))	 {// NE
                deletePoint(&(*quadTreeNode)->spcSon[NE], findX, findY ,cx+(lx/4),cy+(ly/4),lx/2,ly/2,4*position+2,p,&(*list));
            }
        }

        if (findX <= ((cx-(lx/4))+newX)) {
            if (findY <= ((cy-(ly/4))+newY)) { // SW
                deletePoint(&(*quadTreeNode)->spcSon[SW], findX, findY, cx-(lx/4),cy-(ly/4),lx/2,ly/2, 4*position+3,p,&(*list));
            }
        }

        if (findX >= ((cx+(lx/4))-newX)) { // EASTERN QUADRANT
            if (findY <= ((cy-(ly/4))+newY)) { // SE
                deletePoint(&(*quadTreeNode)->spcSon[SE], findX, findY, cx+(lx/4),cy-(ly/4),lx/2,ly/2,4*position+4,p,&(*list));
            }
        }

        if ((*quadTreeNode)->spcSon[NW] == NULL && (*quadTreeNode)->spcSon[NE] == NULL && (*quadTreeNode)->spcSon[SW] == NULL && (*quadTreeNode)->spcSon[SE] == NULL && ((*quadTreeNode)->binSon == NULL || (*quadTreeNode)->binSon->length == 0) && (*quadTreeNode)!=this) {
            (*quadTreeNode) = NULL;
        }
    }
}

void cNode::regionNodeSearch(cNode **quadTreeNode, Rectangle * rect, int cx, int cy, int lx, int ly, int position, float p, bNode ** list) {
    if((*quadTreeNode) != NULL) {
        if (trace == true)
            cout << position << " ";

        if ((*quadTreeNode)->binSon != NULL && (*quadTreeNode)->binSon->length > 0) {
            for(int i=0; i<(*quadTreeNode)->binSon->length; i++) {
                Rectangle * s = (*quadTreeNode)->binSon->getNode(i);

                int sRight = s->getCenterX()+(s->getLengthX()/2);
                int sLeft = s->getCenterX()-(s->getLengthX()/2);
                int sTop = s->getCenterY()+(s->getLengthY()/2);
                int sBottom = s->getCenterY()-(s->getLengthY()/2);

                int rRight = rect->getCenterX()+(rect->getLengthX()/2);
                int rLeft = rect->getCenterX()-(rect->getLengthX()/2);
                int rTop = rect->getCenterY()+(rect->getLengthY()/2);
                int rBottom = rect->getCenterY()-(rect->getLengthY()/2);

                //http://www.tekpool.com/?p=23
                if (!(rLeft > sRight || rRight < sLeft || rTop < sBottom || rBottom > sTop)) {
                    if ((*list)->length == 0)
                        (*list) = new bNode(s);
                    else
                        (*list)->insertNode(s);
                }
            }
        }

        int rRight = rect->getCenterX()+(rect->getLengthX()/2);
        int rLeft = rect->getCenterX()-(rect->getLengthX()/2);
        int rTop = rect->getCenterY()+(rect->getLengthY()/2);
        int rBottom = rect->getCenterY()-(rect->getLengthY()/2);

        int newX = (lx/2*(1+p))/2;
        int newY = (ly/2*(1+p))/2;


        if (rRight >= ((cx-(lx/4))-newX) && rLeft <= ((cx-(lx/4))+newX)) {
            if(rBottom <= ((cy+(ly/4))+newY) && rTop>= ((cy+(ly/4))-newY)) { 	// NW
                regionNodeSearch(&(*quadTreeNode)->spcSon[NW], rect, cx-(lx/4),cy+(ly/4),lx/2,ly/2,4*position+1,p,&(*list));
            }
        }

        if (rRight >= ((cx+(lx/4))-newX) &&  rLeft <= ((cx+(lx/4))+newX)) {
            if (rBottom <= ((cy+(ly/4))+newY) && rTop >= ((cy+(ly/4))-newY)) {// NE
                regionNodeSearch(&(*quadTreeNode)->spcSon[NE], rect,cx+(lx/4),cy+(ly/4),lx/2,ly/2,4*position+2,p,&(*list));
            }
        }

        if (rRight >= ((cx-(lx/4))-newX) && rLeft <= ((cx-(lx/4))+newX)) {
            if (rBottom <= ((cy-(ly/4))+newY) && rTop >= ((cy-(ly/4))-newY)) { // SW
                regionNodeSearch(&(*quadTreeNode)->spcSon[SW], rect, cx-(lx/4),cy-(ly/4),lx/2,ly/2, 4*position+3,p,&(*list));

            }
        }
        if (rRight >= ((cx+(lx/4))-newX) &&  rLeft <= ((cx+(lx/4))+newX)) {
            if (rBottom <= ((cy-(ly/4))+newY) && rTop >= ((cy-(ly/4))-newY)) { // SE
                regionNodeSearch(&(*quadTreeNode)->spcSon[SE], rect,cx+(lx/4),cy-(ly/4),lx/2,ly/2,4*position+4,p,&(*list));
            }
        }
    }
}

void cNode::searchPoint(cNode **quadTreeNode,int findX, int findY, int cx, int cy, int lx, int ly, int position, float p, bNode ** list) {
    if((*quadTreeNode) != NULL) {
        if (trace == true)
            cout << position << " ";
        if ((*quadTreeNode)->binSon != NULL && (*quadTreeNode)->binSon->length > 0) {
            for(int i=0; i<(*quadTreeNode)->binSon->length; i++) {
                Rectangle * s = (*quadTreeNode)->binSon->getNode(i);

                int SRectMaxX = s->getCenterX()+(s->getLengthX()/2);
                int SRectMinX = s->getCenterX()-(s->getLengthX()/2);
                int SRectMaxY = s->getCenterY()+(s->getLengthY()/2);
                int SRectMinY = s->getCenterY()-(s->getLengthY()/2);

                if (SRectMaxX >=findX && SRectMinX<=findX) {
                    if(	SRectMaxY>=findX && SRectMinY<=findY) {
                        if ((*list)->length == 0)
                            (*list) = new bNode(s);
                        else
                            (*list)->insertNode(s);
                    }
                }
            }
        }
        int newX = (lx/4)*(p+1);
        int newY = (ly/4)*(p+1);


        if (findX <= ((cx-(lx/4))+newX)) {
            if(findY>= ((cy+(ly/4))-newY)) { 	// NW
                searchPoint(&(*quadTreeNode)->spcSon[NW], findX, findY, cx-(lx/4),cy+(ly/4),lx/2,ly/2,4*position+1,p,&(*list));
            }
        }
        if (findX >= ((cx+(lx/4))-newX)) { // EASTERN QUADRANT
            if (findY >= ((cy+(ly/4))-newY))	 {// NE
                searchPoint(&(*quadTreeNode)->spcSon[NE], findX, findY ,cx+(lx/4),cy+(ly/4),lx/2,ly/2,4*position+2,p,&(*list));
            }
        }

        if (findX <= ((cx-(lx/4))+newX)) {
            if (findY <= ((cy-(ly/4))+newY)) { // SW
                searchPoint(&(*quadTreeNode)->spcSon[SW], findX, findY, cx-(lx/4),cy-(ly/4),lx/2,ly/2, 4*position+3,p,&(*list));
            }
        }

        if (findX >= ((cx+(lx/4))-newX)) { // EASTERN QUADRANT
            if (findY <= ((cy-(ly/4))+newY)) { // SE
                searchPoint(&(*quadTreeNode)->spcSon[SE], findX, findY,cx+(lx/4),cy-(ly/4),lx/2,ly/2,4*position+4,p,&(*list));
            }
        }
    }
}
cNode* cNode::getNW() {
    return spcSon[NW];
}
cNode* cNode::getSW() {
    return spcSon[SW];
}
cNode* cNode::getNE() {
    return spcSon[NE];
}
cNode* cNode::getSE() {
    return spcSon[SE];
}
cNode::~cNode() {}

// IF S INTERSECTS R
bool cNode::intersects(int sRight,  int sLeft, int sTop, int sBottom, int rRight, int rLeft, int rTop, int rBottom) {
    if (!(rLeft > sRight || rRight < sLeft || rTop < sBottom || rBottom > sTop)) {
        return true;
    }
    return false;
}

//http://dotnetjunkies.com/WebLog/chris.taylor/
// IF S INTERSECTS R
// TODO: Find a better algorithm for if two rectangles touch
bool cNode::intersectionIsZero(int sRight,  int sLeft, int sTop, int sBottom, int rRight, int rLeft, int rTop, int rBottom) {
    if (abs(rLeft - sRight) == 0 || abs(sLeft - rRight)  == 0 || abs(rRight-sLeft)==0 || abs(sRight-rLeft)==0	) {
        if ((rLeft < sRight  && sRight < rRight) || (rLeft < sRight  && sRight < rRight) )
            return true;
    }
    if (abs(rTop - sBottom) == 0 || abs(sTop - rBottom) || abs(sBottom-rTop) == 0 || abs(rBottom-sTop) ==0) {
        return true;
    }
    return false;
}

// IF S CONTAINS R
bool cNode::contains(int sRight,  int sLeft, int sTop, int sBottom, int rRight, int rLeft, int rTop, int rBottom) {
    if (sRight>=rRight && sLeft <=rLeft && sTop>=rTop && sBottom<=rBottom) {
        return true;
    } else {
        return false;
    }
}

void cNode::touch(cNode **quadTreeNode, Rectangle * rect, int cx, int cy, int lx, int ly, int position, float p, bNode ** list) {
    if((*quadTreeNode) != NULL) {
        if (trace == true)
            cout << position << " ";
        if ((*quadTreeNode)->binSon != NULL && (*quadTreeNode)->binSon->length > 0) {
            for(int i=0; i<(*quadTreeNode)->binSon->length; i++) {
                Rectangle * s = (*quadTreeNode)->binSon->getNode(i);

                int sRight = s->getCenterX()+(s->getLengthX()/2);
                int sLeft = s->getCenterX()-(s->getLengthX()/2);
                int sTop = s->getCenterY()+(s->getLengthY()/2);
                int sBottom = s->getCenterY()-(s->getLengthY()/2);

                int rRight = rect->getCenterX()+(rect->getLengthX()/2);
                int rLeft = rect->getCenterX()-(rect->getLengthX()/2);
                int rTop = rect->getCenterY()+(rect->getLengthY()/2);
                int rBottom = rect->getCenterY()-(rect->getLengthY()/2);
                CompareField r1;
                r1.type = r1.Rectangle_Type;
                r1.cx  = rect->getCenterX();
                r1.cy = rect->getCenterY();
                r1.lx  = rect->getLengthX();
                r1.ly  = rect->getLengthY();

                CompareField r2;
                r2.type = r2.Rectangle_Type;
                r2.cx  = s->getCenterX();
                r2.cy  = s->getCenterY();
                r2.lx  = s->getLengthX();
                r2.ly  = s->getLengthY();

                if (horDistance(r1,r2,0) == 0 && vertDistance(r1,r2,0)==0){
                    if ((*list)->length == 0)
                        (*list) = new bNode(s);
                    else
                        (*list)->insertNode(s);
                }
            }
        }

        int rRight = rect->getCenterX()+(rect->getLengthX()/2);
        int rLeft = rect->getCenterX()-(rect->getLengthX()/2);
        int rTop = rect->getCenterY()+(rect->getLengthY()/2);
        int rBottom = rect->getCenterY()-(rect->getLengthY()/2);

        int newX = (lx/2*(1+p))/2;
        int newY = (ly/2*(1+p))/2;


        if (rRight >= ((cx-(lx/4))-newX) && rLeft <= ((cx-(lx/4))+newX)) {
            if(rBottom <= ((cy+(ly/4))+newY) && rTop>= ((cy+(ly/4))-newY)) { 	// NW
                touch(&(*quadTreeNode)->spcSon[NW], rect, cx-(lx/4),cy+(ly/4),lx/2,ly/2,4*position+1,p,&(*list));
            }
        }

        if (rRight >= ((cx+(lx/4))-newX) &&  rLeft <= ((cx+(lx/4))+newX)) {
            if (rBottom <= ((cy+(ly/4))+newY) && rTop >= ((cy+(ly/4))-newY)) {// NE
                touch(&(*quadTreeNode)->spcSon[NE], rect,cx+(lx/4),cy+(ly/4),lx/2,ly/2,4*position+2,p,&(*list));
            }
        }

        if (rRight >= ((cx-(lx/4))-newX) && rLeft <= ((cx-(lx/4))+newX)) {
            if (rBottom <= ((cy-(ly/4))+newY) && rTop >= ((cy-(ly/4))-newY)) { // SW
                touch(&(*quadTreeNode)->spcSon[SW], rect, cx-(lx/4),cy-(ly/4),lx/2,ly/2, 4*position+3,p,&(*list));

            }
        }
        if (rRight >= ((cx+(lx/4))-newX) &&  rLeft <= ((cx+(lx/4))+newX)) {
            if (rBottom <= ((cy-(ly/4))+newY) && rTop >= ((cy-(ly/4))-newY)) { // SE
                touch(&(*quadTreeNode)->spcSon[SE], rect,cx+(lx/4),cy-(ly/4),lx/2,ly/2,4*position+4,p,&(*list));
            }
        }

    }
}

void cNode::within(cNode **quadTreeNode, Rectangle * n,Rectangle *q, int cx, int cy, int lx, int ly, int position, float p, bNode ** list) {
    if((*quadTreeNode) != NULL) {
        if (trace == true)
            cout << position << " ";
        if ((*quadTreeNode)->binSon != NULL && (*quadTreeNode)->binSon->length > 0) {
            for(int i=0; i<(*quadTreeNode)->binSon->length; i++) {
                Rectangle * s = (*quadTreeNode)->binSon->getNode(i);

                int sRight = s->getCenterX()+(s->getLengthX()/2);
                int sLeft = s->getCenterX()-(s->getLengthX()/2);
                int sTop = s->getCenterY()+(s->getLengthY()/2);
                int sBottom = s->getCenterY()-(s->getLengthY()/2);

                int qRight = q->getCenterX()+(q->getLengthX()/2);
                int qLeft = q->getCenterX()-(q->getLengthX()/2);
                int qTop = q->getCenterY()+(q->getLengthY()/2);
                int qBottom = q->getCenterY()-(q->getLengthY()/2);

                int nRight = n->getCenterX()+(n->getLengthX()/2);
                int nLeft = n->getCenterX()-(n->getLengthX()/2);
                int nTop = n->getCenterY()+(n->getLengthY()/2);
                int nBottom = n->getCenterY()-(n->getLengthY()/2);

                if (intersects(sRight,sLeft,sTop, sBottom,qRight,qLeft,qTop,qBottom)  ) {
                    if (!contains(nRight,nLeft,nTop,nBottom,sRight,sLeft,sTop,sBottom)) {
                        if ((*list)->length == 0)
                            (*list) = new bNode(s);
                        else
                            (*list)->insertNode(s);
                    }
                }
            }
        }

        int rRight = q->getCenterX()+(q->getLengthX()/2);
        int rLeft = q->getCenterX()-(q->getLengthX()/2);
        int rTop = q->getCenterY()+(q->getLengthY()/2);
        int rBottom = q->getCenterY()-(q->getLengthY()/2);

        int newX = (lx/2*(1+p))/2;
        int newY = (ly/2*(1+p))/2;

        //TODO: Make sure you only goto the nodes that intersect the region Q-N.  Trace is off
        if (rRight >= ((cx-(lx/4))-newX) && rLeft <= ((cx-(lx/4))+newX)) {
            if(rBottom <= ((cy+(ly/4))+newY) && rTop>= ((cy+(ly/4))-newY)) { 	// NW
                within(&(*quadTreeNode)->spcSon[NW], n,q, cx-(lx/4),cy+(ly/4),lx/2,ly/2,4*position+1,p,&(*list));
            }
        }

        if (rRight >= ((cx+(lx/4))-newX) &&  rLeft <= ((cx+(lx/4))+newX)) {
            if (rBottom <= ((cy+(ly/4))+newY) && rTop >= ((cy+(ly/4))-newY)) {// NE
                within(&(*quadTreeNode)->spcSon[NE], n,q,cx+(lx/4),cy+(ly/4),lx/2,ly/2,4*position+2,p,&(*list));
            }
        }

        if (rRight >= ((cx-(lx/4))-newX) && rLeft <= ((cx-(lx/4))+newX)) {
            if (rBottom <= ((cy-(ly/4))+newY) && rTop >= ((cy-(ly/4))-newY)) { // SW
                within(&(*quadTreeNode)->spcSon[SW], n,q, cx-(lx/4),cy-(ly/4),lx/2,ly/2, 4*position+3,p,&(*list));

            }
        }
        if (rRight >= ((cx+(lx/4))-newX) &&  rLeft <= ((cx+(lx/4))+newX)) {
            if (rBottom <= ((cy-(ly/4))+newY) && rTop >= ((cy-(ly/4))-newY)) { // SE
                within(&(*quadTreeNode)->spcSon[SE], n,q,cx+(lx/4),cy-(ly/4),lx/2,ly/2,4*position+4,p,&(*list));
            }
        }
    }
}

//http://www.cs.umd.edu/~brabec/quadtree/pubs/incnear.pdf
// Page 494 in the textbookexpansion
int cNode::vertDistance(CompareField r, CompareField q, double p) {
    if ((r.rect== NULL && r.node == NULL) || (q.rect== NULL && q.node == NULL))
        return -1;

    int distance = 9999;

    int rRight = r.cx + (r.lx);
    int rLeft = r.cx - (r.lx);
    int rTop = r.cy + (r.ly);
    int rBottom = r.cy - (r.ly);

    if(r.type == r.Quadrant_Type) {
        rRight = r.cx + (r.lx*(1+p));
        rLeft = r.cx - (r.lx*(1+p));
        rTop = r.cy + (r.ly*(1+p));
        rBottom = r.cy - (r.ly*(1+p));
    }

    int qRight = q.cx + (q.lx);
    int qLeft = q.cx - (q.lx);
    int qTop = q.cy + (q.ly);
    int qBottom = q.cy - (q.ly);

    if (q.type == q.Quadrant_Type) {
        qRight = q.cx +  (q.lx*(1+p));
        qLeft = q.cx - (q.lx*(1+p));
        qTop = q.cy + (q.ly*(1+p));
        qBottom = q.cy - (q.ly*(1+p));
    }

    if (r.type != r.Rectangle_Type && !( rTop < qBottom || rBottom > qTop)) {
        return 0;
    }

    int set1_1= abs(rBottom - qBottom);
    int set1_2 = abs(rBottom - qTop);
    int set2_1 = abs(rTop - qBottom);
    int set2_2 = abs(rTop - qTop);
    int set3_1 = abs(qBottom - rBottom);
    int set3_2 = abs(qBottom - rTop);
    int set4_1 =abs(qTop - rBottom);
    int set4_2 =abs(qTop - rTop);

    if (set1_1 < distance && set1_1 >=0)
        distance = set1_1;
    if (set1_2 < distance && set1_2 >=0)
        distance = set1_2;

    if (set2_1 < distance && set2_1 >=0)
        distance = set2_1;
    if (set2_2 < distance && set2_2 >=0)
        distance = set2_2;

    if (set3_1 < distance && set3_1 >=0)
        distance = set3_1;
    if (set3_2 < distance && set3_2 >=0)
        distance = set3_2;

    if (set4_1 < distance && set4_1 >=0)
        distance = set4_1;
    if (set4_2 < distance && set4_2 >=0)
        distance = set4_2;

    return distance;
}

Rectangle *cNode::horizontalNeighbor(cNode **quadTreeNode, Rectangle * n, int cx, int cy, int lx, int ly, int position, float p) {
    CompareField checkNode;
    checkNode.rect = n;
    checkNode.setCords(n->getCenterX(),n->getCenterY(),n->getLengthX()/2, n->getLengthY()/2);
    checkNode.isQuad = false;
    checkNode.type = checkNode.Rectangle_Type;

    PriorityQueue *queue = new PriorityQueue();
    queue->Enqueue(*quadTreeNode,0,cx,cy,lx/2,ly/2, 0,0);
    while(!queue->IsEmpty()) {
        CompareField currentQueue = queue->Dequeue();
        if (trace == true) {
            if (currentQueue.position!=9999)
                cout << currentQueue.position << " " ;
        }
        if(currentQueue.isQuadrant()) {
            cNode *quadrant = currentQueue.node;
            for(int i=0; i<quadrant->binSon->length;i++) {  // check all the rectangles in the node
                Rectangle *currentRectangle = quadrant->binSon->getNode(i);
                CompareField tempRect;
                tempRect.rect = currentRectangle;
                tempRect.setCords(currentRectangle->getCenterX(),currentRectangle->getCenterY(),currentRectangle->getLengthX()/2, currentRectangle->getLengthY()/2);
                if (currentRectangle->getName().compare(n->getName()) != 0) { // dont add itself{
                   

            		   int left  = max(tempRect.cx-tempRect.lx,checkNode.cx-checkNode.lx);
            		   int top = min(tempRect.cy+tempRect.ly,checkNode.cy+checkNode.ly);
            		   int right = min(tempRect.cx+tempRect.lx ,checkNode.cx+checkNode.lx);
            		   int bottom = max(tempRect.cy-tempRect.ly,checkNode.cy-checkNode.ly);
            		   
            		   if ( (left-right)>= 0){
            			   queue->Enqueue(currentRectangle,left-right);
            		   }

                }
            }
            horAddChildrenNodes(&queue,quadrant,checkNode,currentQueue,p,currentQueue.position);
        } 
        else { // we have a rectangle element
            //cout << "Rectangle: " << currentQueue.rect->getName() << endl;
        	 cout << "Rectangle: " << currentQueue.rect->getName()  << currentQueue.distance << endl;
            //return (currentQueue.rect);
        }
    }
}

Rectangle *cNode::verticalNeighbor(cNode **quadTreeNode, Rectangle * n, int cx, int cy, int lx, int ly, int position, float p) {
    CompareField checkNode;
    checkNode.rect = n;
    checkNode.setCords(n->getCenterX(),n->getCenterY(),n->getLengthX()/2, n->getLengthY()/2);
    checkNode.isQuad = false;
    checkNode.type = checkNode.Rectangle_Type;

    PriorityQueue *queue = new PriorityQueue();
    queue->Enqueue(*quadTreeNode,0,cx,cy,lx/2,ly/2, 0,0);
    while(!queue->IsEmpty()) {
        CompareField currentQueue = queue->Dequeue();
        if (trace == true) {
            if (currentQueue.position!=9999)
                cout << currentQueue.position << " " ;
        }
        if(currentQueue.isQuadrant()) {
            cNode *quadrant = currentQueue.node;
            for(int i=0; i<quadrant->binSon->length;i++) {  // check all the rectangles in the node
                Rectangle *currentRectangle = quadrant->binSon->getNode(i);
                CompareField tempRect;
                tempRect.rect = currentRectangle;
                tempRect.setCords(currentRectangle->getCenterX(),currentRectangle->getCenterY(),currentRectangle->getLengthX()/2, currentRectangle->getLengthY()/2);
                if (currentRectangle->getName().compare(n->getName()) != 0) { // dont add itself{
            		   int left  = max(tempRect.cx-tempRect.lx,checkNode.cx-checkNode.lx);
            		   int top = min(tempRect.cy+tempRect.ly,checkNode.cy+checkNode.ly);
            		   int right = min(tempRect.cx+tempRect.lx ,checkNode.cx+checkNode.lx);
            		   int bottom = max(tempRect.cy-tempRect.ly,checkNode.cy-checkNode.ly);
            		  // cout << "Rectangle: " << currentRectangle->getName() << " " << left << " " << right << " " << top << " " << bottom << endl;
            		   if ( (bottom-top)>= 0){
             			   int distance = vertDistance(tempRect,checkNode,p);
                			   queue->Enqueue(currentRectangle,bottom-top);
            		   }
                }
            }
            vertAddChildrenNodes(&queue,quadrant,checkNode,currentQueue,p,currentQueue.position);
        } else { // we have a rectangle element
           cout << "Rectangle: " << currentQueue.rect->getName()  << currentQueue.distance << endl;
            //return (currentQueue.rect);
        }
    }
}

void cNode::vertAddChildrenNodes(PriorityQueue **queue, cNode *quadrant, CompareField point, CompareField quad, double p, int position) {
    double distance;
    if (quadrant->spcSon!=NULL ) {
        if(quadrant->spcSon[NW]!=NULL) {
            CompareField tempNode;
            tempNode.type = tempNode.Quadrant_Type;
            tempNode.setCords(quad.cx-(quad.lx/2),quad.cy+(quad.ly/2),quad.lx/2,quad.ly/2);
            tempNode.quadrant = NW;
            distance = vertDistance(tempNode,point,p);
            (*queue)->Enqueue(quadrant->spcSon[NW],distance,tempNode.cx,tempNode.cy,tempNode.lx,tempNode.ly, NW, 4*position+1);
            //vertAddChildrenNodes(queue,quadrant->spcSon[NW],point,tempNode,p,4*position+1);
        }
        if(quadrant->spcSon[NE]!=NULL) {
            CompareField tempNode;
            tempNode.type = tempNode.Quadrant_Type;
            tempNode.setCords(quad.cx+(quad.lx/2),quad.cy+(quad.ly/2),quad.lx/2,quad.ly/2);
            tempNode.quadrant = NE;
            distance = vertDistance(tempNode,point,p);
            (*queue)->Enqueue(quadrant->spcSon[NE],distance, tempNode.cx,tempNode.cy,tempNode.lx,tempNode.ly, NE, 4*position+2);
            //vertAddChildrenNodes(queue,quadrant->spcSon[NE],point,tempNode, p,4*position+2);
        }
        if(quadrant->spcSon[SW]!=NULL) {
            CompareField tempNode;
            tempNode.type = tempNode.Quadrant_Type;
            tempNode.setCords(quad.cx-(quad.lx/2),quad.cy-(quad.ly/2),quad.lx/2,quad.ly/2);
            tempNode.quadrant = SW;
            distance = vertDistance(tempNode,point,p);
            (*queue)->Enqueue(quadrant->spcSon[SW],distance,tempNode.cx,tempNode.cy,tempNode.lx,tempNode.ly, SW,  4*position+3);
            //vertAddChildrenNodes(queue,quadrant->spcSon[SW],point,tempNode,p,4*position+3);
        }
        if(quadrant->spcSon[SE]!=NULL) {
            CompareField tempNode;
            tempNode.type = tempNode.Quadrant_Type;
            tempNode.setCords(quad.cx+(quad.lx/2),quad.cy-(quad.ly/2),quad.lx/2,quad.ly/2);
            tempNode.quadrant = SE;
            distance = vertDistance(tempNode,point,p);
            (*queue)->Enqueue(quadrant->spcSon[SE],distance,tempNode.cx,tempNode.cy,tempNode.lx,tempNode.ly, SE, 4*position+4);
            //vertAddChildrenNodes(queue,quadrant->spcSon[SE],point,tempNode,p,4*position+4);
        }
    }
}

void cNode::horAddChildrenNodes(PriorityQueue **queue, cNode *quadrant, CompareField point, CompareField quad, double p, int position) {
    double distance;
    if (quadrant->spcSon!=NULL ) {
        if(quadrant->spcSon[NW]!=NULL) {
            CompareField tempNode;
            tempNode.type = tempNode.Quadrant_Type;
            tempNode.setCords(quad.cx-(quad.lx/2),quad.cy+(quad.ly/2),quad.lx/2,quad.ly/2);
            tempNode.quadrant = NW;
            distance = horDistance(tempNode,point,p);
            (*queue)->Enqueue(quadrant->spcSon[NW],distance,tempNode.cx,tempNode.cy,tempNode.lx,tempNode.ly, NW, 4*position+1);
            //horAddChildrenNodes(queue,quadrant->spcSon[NW],point,tempNode,p,4*position+1);
        }
        if(quadrant->spcSon[NE]!=NULL) {
            CompareField tempNode;
            tempNode.type = tempNode.Quadrant_Type;
            tempNode.setCords(quad.cx+(quad.lx/2),quad.cy+(quad.ly/2),quad.lx/2,quad.ly/2);
            tempNode.quadrant = NE;
            distance = horDistance(tempNode,point,p);
            (*queue)->Enqueue(quadrant->spcSon[NE],distance, tempNode.cx,tempNode.cy,tempNode.lx,tempNode.ly, NE, 4*position+2);
            //horAddChildrenNodes(queue,quadrant->spcSon[NE],point,tempNode, p,4*position+2);
        }
        if(quadrant->spcSon[SW]!=NULL) {
            CompareField tempNode;
            tempNode.type = tempNode.Quadrant_Type;
            tempNode.setCords(quad.cx-(quad.lx/2),quad.cy-(quad.ly/2),quad.lx/2,quad.ly/2);
            tempNode.quadrant = SW;
            distance = horDistance(tempNode,point,p);
            (*queue)->Enqueue(quadrant->spcSon[SW],distance,tempNode.cx,tempNode.cy,tempNode.lx,tempNode.ly, SW,  4*position+3);
            //horAddChildrenNodes(queue,quadrant->spcSon[SW],point,tempNode,p,4*position+3);
        }
        if(quadrant->spcSon[SE]!=NULL) {
            CompareField tempNode;
            tempNode.type = tempNode.Quadrant_Type;
            tempNode.setCords(quad.cx+(quad.lx/2),quad.cy-(quad.ly/2),quad.lx/2,quad.ly/2);
            tempNode.quadrant = SE;
            distance = horDistance(tempNode,point,p);
            (*queue)->Enqueue(quadrant->spcSon[SE],distance,tempNode.cx,tempNode.cy,tempNode.lx,tempNode.ly, SE, 4*position+4);
            //horAddChildrenNodes(queue,quadrant->spcSon[SE],point,tempNode,p,4*position+4);
        }
    }
}

int cNode::horDistance(CompareField r, CompareField q, double p) {
    if ((r.rect== NULL && r.node == NULL) || (q.rect== NULL && q.node == NULL))
        return -1;
    int distance = 9999;

    int rRight = r.cx + (r.lx);
    int rLeft = r.cx - (r.lx);
    int rTop = r.cy + (r.ly);
    int rBottom = r.cy - (r.ly);

    if(r.type == r.Quadrant_Type) {
        rRight = r.cx + (r.lx*(1+p));
        rLeft = r.cx - (r.lx*(1+p));
        rTop = r.cy + (r.ly*(1+p));
        rBottom = r.cy - (r.ly*(1+p));
    }

    int qRight = q.cx + (q.lx);
    int qLeft = q.cx - (q.lx);
    int qTop = q.cy + (q.ly);
    int qBottom = q.cy - (q.ly);

    if (q.type == q.Quadrant_Type) {
        qRight = q.cx +  (q.lx*(1+p));
        qLeft = q.cx - (q.lx*(1+p));
        qTop = q.cy + (q.ly*(1+p));
        qBottom = q.cy - (q.ly*(1+p));
    }

    if (r.type != r.Rectangle_Type && !(rLeft >qRight || rRight < qLeft )) {
        return 0;
    }

    int set1_1= abs(rLeft - qLeft);
    int set1_2 = abs(rLeft - qRight);
    int set2_1 = abs(rRight - qLeft);
    int set2_2 = abs(rRight - qRight);
    int set3_1 = abs(qLeft - rLeft);
    int set3_2 = abs(qLeft - rRight);
    int set4_1 =abs(qRight - rLeft);
    int set4_2 =abs(qRight - rRight);

    if (set1_1 < distance && set1_1 >=0)
        distance = set1_1;
    if (set1_2 < distance && set1_2 >=0)
        distance = set1_2;

    if (set2_1 < distance && set2_1 >=0)
        distance = set2_1;
    if (set2_2 < distance && set2_2 >=0)
        distance = set2_2;

    if (set3_1 < distance && set3_1 >=0)
        distance = set3_1;
    if (set3_2 < distance && set3_2 >=0)
        distance = set3_2;

    if (set4_1 < distance && set4_1 >=0)
        distance = set4_1;
    if (set4_2 < distance && set4_2 >=0)
        distance = set4_2;

    return distance;
}

Rectangle *cNode::nearestRectangle(cNode **quadTreeNode, int findX, int findY, int cx, int cy, int lx, int ly, int position, float p) {
    CompareField checkPoint;
    checkPoint.type = checkPoint.Point_Type;

    Rectangle *checkRect = new Rectangle("TEMP_RECTANGLE", findX,findY,0,0);
    checkPoint.rect = checkRect;
    checkPoint.setCords(findX,findY,0,0);
    checkPoint.isQuad = false;

    PriorityQueue *queue = new PriorityQueue();
    queue->Enqueue(*quadTreeNode,0,cx,cy,lx/2,ly/2,0,0);
    while(!queue->IsEmpty()) {
        CompareField currentQueue = queue->Dequeue();
        if(currentQueue.isQuadrant()) {
            cNode *quadrant = currentQueue.node;
            if (trace == true) {
                cout << currentQueue.position << " " ;
            }
            for(int i=0; i<quadrant->binSon->length;i++) {  // check all the rectangles in the node
                Rectangle *currentRectangle = quadrant->binSon->getNode(i);
                CompareField tempRect;
                tempRect.rect = currentRectangle;
                tempRect.setCords(currentRectangle->getCenterX(),currentRectangle->getCenterY(),currentRectangle->getLengthX()/2, currentRectangle->getLengthY()/2);

                int distanceHorizontal = horDistance(tempRect,checkPoint,p);
                int distanceVertical = vertDistance(tempRect,checkPoint,p);
                double totalDistance = sqrt(distanceHorizontal*distanceHorizontal+distanceVertical*distanceVertical);
                //cout << "Rectangle " << currentRectangle->getName() << " distanceHorizontal: " << distanceHorizontal << " distanceVertical: " << distanceVertical << " distance: " << totalDistance << endl;
                queue->Enqueue(currentRectangle,totalDistance);
            }
            // determine which node is the closest.  then add its all children
            nearestAddChildrenNodes(&queue,quadrant,checkPoint,currentQueue,p,currentQueue.position);
        } else { // we have a rectangle element
            //cout << "Rectangle: " << currentQueue.rect->getName() << endl;
            return (currentQueue.rect);
        }
    }
    Rectangle * temp = new Rectangle("NOT_FOUND",0,0,0,0);
    cout << "Not found " << endl;
    return (temp);
}

void cNode::nearestAddChildrenNodes(PriorityQueue **queue, cNode *quadrant, CompareField point, CompareField quad, double p, int position) {
    double distance;
    int distanceHorizontal, distanceVertical;

    if (quadrant->spcSon!=NULL ) {
        if(quadrant->spcSon[NW]!=NULL) {
            CompareField tempNode;
            tempNode.type = tempNode.Quadrant_Type;
            tempNode.setCords(quad.cx-(quad.lx/2),quad.cy+(quad.ly/2),quad.lx/2,quad.ly/2);
            tempNode.quadrant = NW;
            distanceHorizontal = horDistance(tempNode,point,p);
            distanceVertical = vertDistance(tempNode,point,p);
            distance = sqrt(distanceHorizontal*distanceHorizontal+distanceVertical*distanceVertical);
            (*queue)->Enqueue(quadrant->spcSon[NW],distance,tempNode.cx,tempNode.cy,tempNode.lx,tempNode.ly, NW, 4*position+1);
            //nearestAddChildrenNodes(queue,quadrant->spcSon[NW],point,tempNode,p,4*position+1);
        }
        if(quadrant->spcSon[NE]!=NULL) {
            CompareField tempNode;
            tempNode.type = tempNode.Quadrant_Type;
            tempNode.setCords(quad.cx+(quad.lx/2),quad.cy+(quad.ly/2),quad.lx/2,quad.ly/2);
            tempNode.quadrant = NE;
            distanceHorizontal = horDistance(tempNode,point,p);
            distanceVertical = vertDistance(tempNode,point,p);
            distance = sqrt(distanceHorizontal*distanceHorizontal+distanceVertical*distanceVertical);
            (*queue)->Enqueue(quadrant->spcSon[NE],distance, tempNode.cx,tempNode.cy,tempNode.lx,tempNode.ly, NE, 4*position+2);
            //nearestAddChildrenNodes(queue,quadrant->spcSon[NE],point,tempNode, p,4*position+2);
        }
        if(quadrant->spcSon[SW]!=NULL) {
            CompareField tempNode;
            tempNode.type = tempNode.Quadrant_Type;
            tempNode.setCords(quad.cx-(quad.lx/2),quad.cy-(quad.ly/2),quad.lx/2,quad.ly/2);
            tempNode.quadrant = SW;
            distanceHorizontal = horDistance(tempNode,point,p);
            distanceVertical = vertDistance(tempNode,point,p);
            distance = sqrt(distanceHorizontal*distanceHorizontal+distanceVertical*distanceVertical);
            (*queue)->Enqueue(quadrant->spcSon[SW],distance,tempNode.cx,tempNode.cy,tempNode.lx,tempNode.ly, SW,  4*position+3);
            //nearestAddChildrenNodes(queue,quadrant->spcSon[SW],point,tempNode,p,4*position+3);
        }
        if(quadrant->spcSon[SE]!=NULL) {
            CompareField tempNode;
            tempNode.type = tempNode.Quadrant_Type;
            tempNode.setCords(quad.cx+(quad.lx/2),quad.cy-(quad.ly/2),quad.lx/2,quad.ly/2);
            tempNode.quadrant = SE;
            distanceHorizontal = horDistance(tempNode,point,p);
            distanceVertical = vertDistance(tempNode,point,p);
            distance = sqrt(distanceHorizontal*distanceHorizontal+distanceVertical*distanceVertical);
            (*queue)->Enqueue(quadrant->spcSon[SE],distance,tempNode.cx,tempNode.cy,tempNode.lx,tempNode.ly, SE, 4*position+4);
            //nearestAddChildrenNodes(queue,quadrant->spcSon[SE],point,tempNode,p,4*position+4);
        }
    }
}

//TODO: Make sure you only goto the nodes that intersect the region Q-N.  Trace is off
void cNode::window(cNode **quadTreeNode, int rect_llx, int rect_lly, int rect_lx, int rect_ly, int cx, int cy, int lx, int ly, int position, float p, bNode ** list) {
    if((*quadTreeNode) != NULL) {
        if (trace == true)
            cout << position << " ";

        int rRight = rect_llx+rect_lx;
        int rLeft = rect_llx;
        int rTop = rect_lly+rect_ly;
        int rBottom = rect_lly;

        if ((*quadTreeNode)->binSon != NULL && (*quadTreeNode)->binSon->length > 0) {
            for(int i=0; i<(*quadTreeNode)->binSon->length; i++) {
                Rectangle * s = (*quadTreeNode)->binSon->getNode(i);
                int sRight = s->getCenterX()+(s->getLengthX()/2);
                int sLeft = s->getCenterX()-(s->getLengthX()/2);
                int sTop = s->getCenterY()+(s->getLengthY()/2);
                int sBottom = s->getCenterY()-(s->getLengthY()/2);

                if(contains(rRight,rLeft,rTop,rBottom,sRight,sLeft,sTop,sBottom)) {
                    if ((*list)->length == 0)
                        (*list) = new bNode(s);
                    else
                        (*list)->insertNode(s);
                }
            }
        }

        int nRight = rect_llx+rect_lx;
        int nLeft = rect_llx;
        int nTop = rect_lly+rect_ly;
        int nBottom = rect_lly;

        int newX = (lx/2*(1+p))/2;
        int newY = (ly/2*(1+p))/2;

		if(intersects(rRight,rLeft,rTop,rBottom,((cx-(lx/4))+newX),((cx-(lx/4))-newX),((cy+(ly/4))+newY),((cy+(ly/4))-newY))) {
			window(&(*quadTreeNode)->spcSon[NW], rect_llx, rect_lly, rect_lx, rect_ly, cx-(lx/4),cy+(ly/4),lx/2,ly/2,4*position+1,p,&(*list));
		}	
		if(intersects(rRight,rLeft,rTop,rBottom,((cx-(lx/4))+newX),((cx+(lx/4))-newX),((cy+(ly/4))+newY),((cy+(ly/4))-newY))) {			
			window(&(*quadTreeNode)->spcSon[NE], rect_llx, rect_lly, rect_lx, rect_ly,cx+(lx/4),cy+(ly/4),lx/2,ly/2,4*position+2,p,&(*list));
		}
        if(intersects(rRight,rLeft,rTop,rBottom,((cx-(lx/4))+newX),((cx-(lx/4))-newX),((cy-(ly/4))+newY),((cy-(ly/4))-newY))) {
        	window(&(*quadTreeNode)->spcSon[SW], rect_llx, rect_lly, rect_lx, rect_ly, cx-(lx/4),cy-(ly/4),lx/2,ly/2, 4*position+3,p,&(*list));
        }
		if(intersects(rRight,rLeft,rTop,rBottom,((cx+(lx/4))+newX),((cx+(lx/4))-newX),((cy-(ly/4))+newY),((cy-(ly/4))-newY))) {
			window(&(*quadTreeNode)->spcSon[SE], rect_llx, rect_lly, rect_lx, rect_ly,cx+(lx/4),cy-(ly/4),lx/2,ly/2,4*position+4,p,&(*list));
		}
    }
}

void cNode::drawAxis(cNode *quadTreeNode,int rect_llx, int rect_lly, int rect_lx, int rect_ly, int cx,int cy,int lx,int ly, int position) {
    if(quadTreeNode != NULL) {
        if (quadTreeNode->spcSon[NW] == NULL && quadTreeNode->spcSon[NE] == NULL && quadTreeNode->spcSon[SW] == NULL && quadTreeNode->spcSon[SE] == NULL)
            return;

        int verticalLeft = cx;
        int verticalRight = cx;
        int verticalBottom = cy-(ly/2);
        int verticalTop = cy+(ly/2);

        int horizontalLeft = cx-(lx/2);
        int horizontalRight = cx+(lx/2);
        int horizontalBottom = cy;
        int horizontalTop = cy;

        int windowLeft = rect_llx;
        int windowRight = rect_llx+rect_lx;
        int windowBottom = rect_lly;
        int windowTop = rect_lly+rect_ly;

        if (windowRight>=horizontalRight && windowLeft <=horizontalLeft && windowTop>=horizontalTop && windowBottom<=horizontalBottom) { // the axis is between the window (dont draw)
            // do nothing
        } else if (!(horizontalLeft >= windowRight || horizontalRight <= windowLeft || horizontalTop <= windowBottom || horizontalBottom >= windowTop)) {// &&  ) { // check the horizontal line with the window box
            if(windowRight> horizontalRight) {
                // do nothing
            } else {
                SetLineDash(3,2);
                DrawLine(rect_llx+rect_lx,cy,cx+(lx/2),cy);
            }

            if(windowLeft<horizontalLeft) {
                // do nothing
            } else {
                SetLineDash(3,2);
                DrawLine(cx-(lx/2),cy,rect_llx,cy);
            }

        } else {
            SetLineDash(3,2);
            DrawLine(cx-(lx/2),cy,cx+(lx/2),cy);
        }

        if (windowRight>=verticalRight && windowLeft <=verticalLeft && windowTop>=verticalTop && windowBottom<=verticalBottom) { // the axis is between the window (dont draw)
            // do nothing
        } else if (!(verticalLeft > windowRight || verticalRight < windowLeft || verticalTop < windowBottom || verticalBottom > windowTop)) {// && (verticalRight>=windowRight)) && verticalLeft <=windowLeft && verticalTop>=windowTop && verticalBottom<=windowBottom)) {
            if (windowBottom < verticalBottom) {
                // do nothing
            } else {
                SetLineDash(3,2);
                DrawLine(cx,cy-(ly/2),cx,rect_lly);
            }
            if (windowTop>verticalTop) {
                // do nothing
            } else {
                SetLineDash(3,2);
                DrawLine(cx,rect_lly+rect_ly,cx,cy+(ly/2));
            }
        } else {
            SetLineDash(3,2);
            DrawLine(cx,cy-(ly/2),cx,cy+(ly/2));
        }
        drawAxis(quadTreeNode->spcSon[NW],rect_llx, rect_lly, rect_lx, rect_ly, cx-(lx/4), cy+(ly/4), lx/2,ly/2, 4*position+1);
        drawAxis(quadTreeNode->spcSon[NE],rect_llx, rect_lly, rect_lx, rect_ly, cx+(lx/4), cy+(ly/4), lx/2,ly/2, 4*position+2);
        drawAxis(quadTreeNode->spcSon[SW],rect_llx, rect_lly, rect_lx, rect_ly, cx-(lx/4), cy-(ly/4), lx/2,ly/2, 4*position+3);
        drawAxis(quadTreeNode->spcSon[SE],rect_llx, rect_lly, rect_lx, rect_ly, cx+(lx/4), cy-(ly/4), lx/2,ly/2, 4*position+4);
    }
}

bool cNode::canFit(Rectangle *r, int cx, int cy, int lx, int ly, int newExpansion, int quadrant) {
    int rRight = r->getCenterX()+(r->getLengthX()/2);
    int rLeft = r->getCenterX()-(r->getLengthX()/2);
    int rTop = r->getCenterY()+(r->getLengthY()/2);
    int rBottom = r->getCenterY()-(r->getLengthY()/2);

    int newX = (lx/2*(1+newExpansion))/2;
    int newY = (ly/2*(1+newExpansion))/2;

    if (quadrant == NW ) {
        if(contains(((cx-(lx/4))+newX),((cx-(lx/4))-newX),((cy+(ly/4))+newY),((cy+(ly/4))-newY),rRight,rLeft,rTop,rBottom)) {
            return true;
        }
    } else if (quadrant ==NE) {
        if(contains(((cx-(lx/4))+newX),((cx+(lx/4))-newX),((cy+(ly/4))+newY),((cy+(ly/4))-newY),rRight,rLeft,rTop,rBottom)) {
            return true;
        }
    } else if (quadrant == SW) {
        if(contains(((cx-(lx/4))+newX),((cx-(lx/4))-newX),((cy-(ly/4))+newY),((cy-(ly/4))-newY),rRight,rLeft,rTop,rBottom)) {
            return true;
        }
    } else if (quadrant == SE) {
        if(contains(((cx+(lx/4))+newX),((cx+(lx/4))-newX),((cy-(ly/4))+newY),((cy-(ly/4))-newY),rRight,rLeft,rTop,rBottom)) {
            return true;
        }
    } else if (quadrant = 5) {
        if(contains(cx+(lx/2*(1+newExpansion)),cx-(lx/2*(1+newExpansion)),cy+(lx/2*(1+newExpansion)),cy-(lx/2*(1+newExpansion)),rRight,rLeft,rTop,rBottom)) {
            return true;
        }
    }
    return false;
}

// TODO: Figure out why changeExpansion is being a fucking whore.  FUCK QUADTREES
void cNode::changeExpansion(cNode **quadTreeNode,int ocx, int ocy, int olx, int oly, int cx, int cy, int lx, int ly, float old_expansion,float new_expansion, int position,  bNode ** list) {
    int quadrant = 0;
    if((*quadTreeNode) != NULL) {
        if (trace == true)
            cout << position << " ";
        if ((*quadTreeNode)->binSon != NULL && (*quadTreeNode)->binSon->length > 0) {
            for(int i=(*quadTreeNode)->binSon->length-1; i>=0; i--) {
                Rectangle * s = (*quadTreeNode)->binSon->getNode(i);

                if ((*quadTreeNode)->binSon->length == 1) {
                    (*quadTreeNode)->binSon = new bNode();
                } else {
                    (*quadTreeNode)->binSon->removeNode(s);
                }

                if ((*list)->length == 0)
                    (*list) = new bNode(s);
                else
                    (*list)->insertNode(s);
            }
            if ((*quadTreeNode)->spcSon[NW] == NULL && (*quadTreeNode)->spcSon[NE] == NULL && (*quadTreeNode)->spcSon[SW] == NULL && (*quadTreeNode)->spcSon[SE] == NULL && ((*quadTreeNode)->binSon == NULL || (*quadTreeNode)->binSon->length == 0) && (*quadTreeNode)!=this) {
                (*quadTreeNode) = NULL;
                return;
            }
        }
        changeExpansion(&(*quadTreeNode)->spcSon[NW], ocx, ocy, olx, oly,cx-(lx/4), cy+(ly/4), lx/2,ly/2, old_expansion, new_expansion, 4*position+1 , &(*list));
        changeExpansion(&(*quadTreeNode)->spcSon[NE], ocx, ocy, olx, oly,cx+(lx/4), cy+(ly/4), lx/2,ly/2, old_expansion, new_expansion, 4*position+2 , &(*list));
        changeExpansion(&(*quadTreeNode)->spcSon[SW], ocx, ocy, olx, oly,cx-(lx/4), cy-(ly/4), lx/2,ly/2, old_expansion, new_expansion, 4*position+3 , &(*list));
        changeExpansion(&(*quadTreeNode)->spcSon[SE], ocx, ocy, olx, oly,cx+(lx/4), cy-(ly/4), lx/2,ly/2,old_expansion, new_expansion, 4*position+4 , &(*list));
        // post traversal

        if((*list)!=NULL && (*list)->length>0) {
            for(int i=((*list)->length)-1; i>=0; i--) { // check all the nodes
                Rectangle * currentRect = (*list)->getNode(i);
                if (canFit(currentRect,cx-(lx/4),cy+(ly/4),lx/2,ly/2,new_expansion,NW)) {
                    (*list)->removeNode(currentRect);
                    cout << "NW " << currentRect->getName()  <<endl;
                    if ((*quadTreeNode)->spcSon[NW] == NULL)
                        (*quadTreeNode)->spcSon[NW] = new cNode();
                    //    insertcNodeRectangle(currentRect,(*quadTreeNode)->spcSon[NW],cx-(lx/4), cy+(ly/4), lx/2,ly/2,position,new_expansion);
                } else if (canFit(currentRect,cx+(lx/4), cy+(ly/4),lx/2,ly/2,new_expansion,NE)) {
                    (*list)->removeNode(currentRect);
                    cout << "NE  " << currentRect->getName()  <<endl;
                    if ((*quadTreeNode)->spcSon[NE] == NULL)
                        (*quadTreeNode)->spcSon[NE] = new cNode();
                    //   insertcNodeRectangle(currentRect,(*quadTreeNode)->spcSon[NE],cx+(lx/4), cy+(ly/4), lx/2,ly/2,position,new_expansion);
                } else if (canFit(currentRect,cx-(lx/4),cy-(ly/4),lx/2,ly/2,new_expansion,SW)) {
                    (*list)->removeNode(currentRect);
                    cout << "SW  " << currentRect->getName()  <<endl;
                    if ((*quadTreeNode)->spcSon[SW] == NULL)
                        (*quadTreeNode)->spcSon[SW] = new cNode();
                    // insertcNodeRectangle(currentRect,(*quadTreeNode)->spcSon[SW],cx-(lx/4), cy-(ly/4), lx/2,ly/2,position,new_expansion);
                } else if (canFit(currentRect,cx+(lx/4),cy-(ly/4),lx/2,ly/2,new_expansion,SE)) {
                    (*list)->removeNode(currentRect);
                    cout << "SE " << currentRect->getName()  <<endl;
                    if ((*quadTreeNode)->spcSon[SE] == NULL)
                        (*quadTreeNode)->spcSon[SE] = new cNode();
                    //  insertcNodeRectangle(currentRect,(*quadTreeNode)->spcSon[SE],cx+(lx/4), cy-(ly/4), lx/2,ly/2,position,new_expansion);
                } else if (canFit(currentRect,cx,cy,lx,ly,new_expansion,5)) { // here
                    (*list)->removeNode(currentRect);
                    cout << "Inserting at " << position << endl;
                    insertcNodeRectangle(currentRect,(*quadTreeNode),cx, cy, lx,ly,position,new_expansion);
                }
            }
        }
        // clean up the axis as we move up
        if ((*quadTreeNode)->spcSon[NW] == NULL && (*quadTreeNode)->spcSon[NE] == NULL && (*quadTreeNode)->spcSon[SW] == NULL && (*quadTreeNode)->spcSon[SE] == NULL && ((*quadTreeNode)->binSon == NULL || (*quadTreeNode)->binSon->length == 0) && (*quadTreeNode)!=this) {
            (*quadTreeNode) = NULL;
        }
    }
}


Rectangle *cNode::nearestNeighbor(cNode **quadTreeNode, Rectangle * n, int cx, int cy, int lx, int ly, int position, float p) {
    CompareField checkNode;
    checkNode.rect = n;
    checkNode.setCords(n->getCenterX(),n->getCenterY(),n->getLengthX()/2, n->getLengthY()/2);
    checkNode.isQuad = false;
    checkNode.type = checkNode.Rectangle_Type;
    
    PriorityQueue *queue = new PriorityQueue();
    queue->Enqueue(*quadTreeNode,0,cx,cy,lx/2,ly/2, 0,0);
    while(!queue->IsEmpty()) {
        CompareField currentQueue = queue->Dequeue();
        if (trace == true) {
            if (currentQueue.position!=9999)
                cout << currentQueue.position << " " ;
        }
        if(currentQueue.isQuadrant()) {
            cNode *quadrant = currentQueue.node;
            for(int i=0; i<quadrant->binSon->length;i++) {  // check all the rectangles in the node
                Rectangle *currentRectangle = quadrant->binSon->getNode(i);
                CompareField tempRect;
                tempRect.rect = currentRectangle;
                tempRect.setCords(currentRectangle->getCenterX(),currentRectangle->getCenterY(),currentRectangle->getLengthX()/2, currentRectangle->getLengthY()/2);

                if (currentRectangle->getName().compare(n->getName()) != 0) {                	
         		   int left  = max(tempRect.cx-tempRect.lx,checkNode.cx-checkNode.lx);
         		   int top = min(tempRect.cy+tempRect.ly,checkNode.cy+checkNode.ly);
         		   int right = min(tempRect.cx+tempRect.lx ,checkNode.cx+checkNode.lx);
         		   int bottom = max(tempRect.cy-tempRect.ly,checkNode.cy-checkNode.ly);
         		   
         		   if ((left-right)*(top-bottom)==0){
         			  int distanceHorizontal = horDistance(tempRect,checkNode,p);
                      int distanceVertical = vertDistance(tempRect,checkNode,p);
                      
                      double totalDistance = sqrt(distanceHorizontal*distanceHorizontal+distanceVertical*distanceVertical);
                      //cout << "Rectangle " << currentRectangle->getName() << " distanceHorizontal: " << distanceHorizontal << " distanceVertical: " << distanceVertical << " distance: " << totalDistance << endl;
                      queue->Enqueue(currentRectangle,totalDistance);
         		   }
         		   
                    
                }
            }
            nearestAddChildrenNodes(&queue,quadrant,checkNode,currentQueue,p,currentQueue.position);
        } else { // we have a rectangle element
        	//cout << "Rectangle: " << currentQueue.rect->getName() << endl;
            return (currentQueue.rect);
        }
    }
}

Rectangle *cNode::lexicallyNearestNeighbor(cNode **quadTreeNode, Rectangle * n, int cx, int cy, int lx, int ly, int position, float p) {
    CompareField checkNode;
    checkNode.rect = n;
    checkNode.setCords(n->getCenterX(),n->getCenterY(),n->getLengthX()/2, n->getLengthY()/2);
    checkNode.isQuad = false;
    checkNode.type = checkNode.Rectangle_Type;

    PriorityQueue *queue = new PriorityQueue();
    queue->Enqueue(*quadTreeNode,0,cx,cy,lx/2,ly/2, 0,0);
    while(!queue->IsEmpty()) {
        CompareField currentQueue = queue->Dequeue();
        if (trace == true) {
            if (currentQueue.position!=9999)
                cout << currentQueue.position << " " ;
        }
        if(currentQueue.isQuadrant()) {
            cNode *quadrant = currentQueue.node;
            for(int i=0; i<quadrant->binSon->length;i++) {  // check all the rectangles in the node
                Rectangle *currentRectangle = quadrant->binSon->getNode(i);
                CompareField tempRect;
                tempRect.rect = currentRectangle;
                tempRect.setCords(currentRectangle->getCenterX(),currentRectangle->getCenterY(),currentRectangle->getLengthX()/2, currentRectangle->getLengthY()/2);

                if (currentRectangle->getName().compare(n->getName()) != 0 && currentRectangle->getName().compare(n->getName()) > 0) {
                    int distanceHorizontal = horDistance(tempRect,checkNode,p);
                    int distanceVertical = vertDistance(tempRect,checkNode,p);
                    double totalDistance = sqrt(distanceHorizontal*distanceHorizontal+distanceVertical*distanceVertical);
                    //cout << "Rectangle " << currentRectangle->getName() << " distanceHorizontal: " << distanceHorizontal << " distanceVertical: " << distanceVertical << " distance: " << totalDistance << endl;
                    queue->Enqueue(currentRectangle,totalDistance);
                }
            }
            nearestAddChildrenNodes(&queue,quadrant,checkNode,currentQueue,p,currentQueue.position);
        } else { // we have a rectangle element
            //cout << "Rectangle: " << currentQueue.rect->getName() << endl;
            return (currentQueue.rect);
        }
    }
}

// TODO: make sure you only visit nodes that intersect the ray.  add a helper function
Rectangle *cNode::rayTrace(cNode **quadTreeNode, int a, int b, int cx, int cy, int lx, int ly, int position, float p) {
    CompareField checkPoint;
    checkPoint.type = checkPoint.Point_Type;

    Rectangle *checkRect = new Rectangle("TEMP_RECTANGLE", a,0,0,0);
    checkPoint.rect = checkRect;
    checkPoint.setCords(a,0,0,0);
    checkPoint.isQuad = false;
    
    PriorityQueue *queue = new PriorityQueue();
    queue->Enqueue(*quadTreeNode,0,cx,cy,lx/2,ly/2, 0,0);
    while(!queue->IsEmpty()) {
        CompareField currentQueue = queue->Dequeue();
        if (trace == true) {
            if (currentQueue.position!=9999)
                cout << currentQueue.position << " " ;
        }
        if(currentQueue.isQuadrant()) {
            cNode *quadrant = currentQueue.node;
            for(int i=0; i<quadrant->binSon->length;i++) {  // check all the rectangles in the node
                Rectangle *currentRectangle = quadrant->binSon->getNode(i);
                CompareField tempRect;
                
                int rRight = currentRectangle->getCenterX()+(currentRectangle->getLengthX()/2);
                int rLeft = currentRectangle->getCenterX()-(currentRectangle->getLengthX()/2);
                int rTop = currentRectangle->getCenterY()+(currentRectangle->getLengthY()/2);
                int rBottom = currentRectangle->getCenterY()-(currentRectangle->getLengthY()/2);
                
                //cout << "Rectangle " << currentRectangle->getName()  << endl;
                tempRect.rect = currentRectangle;
                tempRect.setCords(currentRectangle->getCenterX(),currentRectangle->getCenterY(),currentRectangle->getLengthX()/2, currentRectangle->getLengthY()/2);
                //cout << "a " << a << " b " << b-1 << " WorldTop " << cx+lx/2-1 << " rRight " << rRight << " rLeft " << rLeft << " rTop " << rTop << " rBottom " << rBottom << endl;
                if (rayIntersect(a,0,0,b,cx+(lx/2),0,rLeft,rBottom,0,rRight,rTop,0)){
                    int distanceHorizontal = horDistance(tempRect,checkPoint,p);
                    int distanceVertical = vertDistance(tempRect,checkPoint	,p);
                    double totalDistance = sqrt(distanceHorizontal*distanceHorizontal+distanceVertical*distanceVertical);
                    queue->Enqueue(currentRectangle,totalDistance);
                }
            }
            raytraceAddChildrenNodes(&queue,quadrant,checkPoint,currentQueue,p,currentQueue.position,a,b,cx+(lx/2));
        } else { // we have a rectangle element
            //cout << "Rectangle: " << currentQueue.rect->getName() << endl;
            return (currentQueue.rect);
        }
    }
}

//	rox,roy,roz = ray start point
//	rdx,rdy,rdz = ray destination point
//	bminx,bminy,bminz = box min corner
//	bmaxx,bmaxy,bmaxz = box max corner
bool cNode::rayIntersect(double rox,double roy,double roz,double rdx,double rdy,double rdz,double bminx, double bminy,double bminz,double bmaxx, double bmaxy, double bmaxz){
	double txmin, txmax, tymin,tymax;
	double ddx = 1.0/(rox-rdx);
	double ddy=1.0/(roy-rdy);
	
	if(ddx >=0){
		txmin = (bminx-rox)*ddx;
		txmax = (bmaxx-rox)*ddx;
	}
	else{
		txmin=(bmaxx-rox)*ddx;
		txmax=(bminx-rox)*ddx;
	}
	if(ddy>=0){
		tymin = (bminy-roy)*ddy;
		tymax = (bmaxy - roy) *ddy;	
	}
	else{
		tymin = (bmaxy-roy)*ddy;
		tymax = (bminy-roy)*ddy;
	}
	
	if ( (txmin > tymax) || (tymin > txmax))
		return 0;
	
	if(tymin > txmax)
		txmin = tymin;
	if(tymax < txmax)
		txmax = tymax;
	
	double tzmin, tzmax;
	double ddz = 1.0/(roz-rdz);
	
	if (ddz>=0){
		tzmin = (bminz-roz)*ddz;
		tzmax = (bmaxz -roz)*ddz;
	}
	else {
		tzmin = (bmaxz-roz)*ddz;
		tzmax = (bminz-roz)*ddz;
	}
	
	if (txmin > tzmax || (tzmin > txmax)){
		return 0;
	}
	return 1;
}


void cNode::raytraceAddChildrenNodes(PriorityQueue **queue, cNode *quadrant, CompareField point, CompareField quad, double p, int position, int a, int b, int top) {
    double distance;
    int distanceHorizontal, distanceVertical;    
    
    if (quadrant->spcSon!=NULL ) { 	
        if(quadrant->spcSon[NW]!=NULL) {
            CompareField tempNode;
            tempNode.type = tempNode.Quadrant_Type;
            tempNode.setCords(quad.cx-(quad.lx/2),quad.cy+(quad.ly/2),quad.lx/2,quad.ly/2);
            tempNode.quadrant = NW;

            int rRight = tempNode.cx+(tempNode.lx)*(1+p);
            int rLeft =  tempNode.cx-(tempNode.lx)*(1+p);
            int rTop =  tempNode.cy+(tempNode.lx)*(1+p);
            int rBottom = tempNode.cy-(tempNode.lx)*(1+p);

            if (rayIntersect(a,0,0,b,top,0,rLeft,rBottom,0,rRight,rTop,0)){
	            distanceHorizontal = horDistance(tempNode,point,p);
	            distanceVertical = vertDistance(tempNode,point,p);
	            distance = sqrt(distanceHorizontal*distanceHorizontal+distanceVertical*distanceVertical);
	            (*queue)->Enqueue(quadrant->spcSon[NW],distance,tempNode.cx,tempNode.cy,tempNode.lx,tempNode.ly, NW, 4*position+1);
	            //nearestAddChildrenNodes(queue,quadrant->spcSon[NW],point,tempNode,p,4*position+1);
            }
        }
        if(quadrant->spcSon[NE]!=NULL) {
            CompareField tempNode;
            tempNode.type = tempNode.Quadrant_Type;
            tempNode.setCords(quad.cx+(quad.lx/2),quad.cy+(quad.ly/2),quad.lx/2,quad.ly/2);
            tempNode.quadrant = NE;
            
            int rRight = tempNode.cx+(tempNode.lx)*(1+p);
            int rLeft =  tempNode.cx-(tempNode.lx)*(1+p);
            int rTop =  tempNode.cy+(tempNode.lx)*(1+p);
            int rBottom = tempNode.cy-(tempNode.lx)*(1+p);
            
            if (rayIntersect(a,0,0,b,top,0,rLeft,rBottom,0,rRight,rTop,0)){
	            distanceHorizontal = horDistance(tempNode,point,p);
	            distanceVertical = vertDistance(tempNode,point,p);
	            distance = sqrt(distanceHorizontal*distanceHorizontal+distanceVertical*distanceVertical);
		        (*queue)->Enqueue(quadrant->spcSon[NE],distance, tempNode.cx,tempNode.cy,tempNode.lx,tempNode.ly, NE, 4*position+2);
	            //nearestAddChildrenNodes(queue,quadrant->spcSon[NE],point,tempNode, p,4*position+2);
            }
        }
        if(quadrant->spcSon[SW]!=NULL) {
            CompareField tempNode;
            tempNode.type = tempNode.Quadrant_Type;
            tempNode.setCords(quad.cx-(quad.lx/2),quad.cy-(quad.ly/2),quad.lx/2,quad.ly/2);
            tempNode.quadrant = SW;           

            int rRight = tempNode.cx+(tempNode.lx)*(1+p);
            int rLeft =  tempNode.cx-(tempNode.lx)*(1+p);
            int rTop =  tempNode.cy+(tempNode.lx)*(1+p);
            int rBottom = tempNode.cy-(tempNode.lx)*(1+p);
                        
            if (rayIntersect(a,0,0,b,top,0,rLeft,rBottom,0,rRight,rTop,0)){
	            distanceHorizontal = horDistance(tempNode,point,p);
	            distanceVertical = vertDistance(tempNode,point,p);
	            distance = sqrt(distanceHorizontal*distanceHorizontal+distanceVertical*distanceVertical);
	            (*queue)->Enqueue(quadrant->spcSon[SW],distance,tempNode.cx,tempNode.cy,tempNode.lx,tempNode.ly, SW,  4*position+3);
	            //nearestAddChildrenNodes(queue,quadrant->spcSon[SW],point,tempNode,p,4*position+3);
            }
        }
        if(quadrant->spcSon[SE]!=NULL) {
            CompareField tempNode;
            tempNode.type = tempNode.Quadrant_Type;
            tempNode.setCords(quad.cx+(quad.lx/2),quad.cy-(quad.ly/2),quad.lx/2,quad.ly/2);
            tempNode.quadrant = SE;

            int rRight = tempNode.cx+(tempNode.lx)*(1+p);
            int rLeft =  tempNode.cx-(tempNode.lx)*(1+p);
            int rTop =  tempNode.cy+(tempNode.lx)*(1+p);
            int rBottom = tempNode.cy-(tempNode.lx)*(1+p);
            if (rayIntersect(a,0,0,b-1,top,0,rLeft,rBottom,0,rRight,rTop,0)){
		        distanceHorizontal = horDistance(tempNode,point,p);
		        distanceVertical = vertDistance(tempNode,point,p);
		        distance = sqrt(distanceHorizontal*distanceHorizontal+distanceVertical*distanceVertical);       
		         (*queue)->Enqueue(quadrant->spcSon[SE],distance,tempNode.cx,tempNode.cy,tempNode.lx,tempNode.ly, SE, 4*position+4);
		        //nearestAddChildrenNodes(queue,quadrant->spcSon[SE],point,tempNode,p,4*position+4);
            }
        }
    }
}


