#ifndef PRIORITYQUEUE_H_
#define PRIORITYQUEUE_H_
#include <iostream>
#include "Rectangle.h"

class cNode;

struct CompareField {
    typedef enum {Quadrant_Type, Rectangle_Type, Point_Type} quads;
    bool isQuadrant();
    bool isRectangle();
    void setCords(int centerx, int centery, int lengthx, int lengthy);
    bool isQuad;
    Rectangle *rect;
    cNode *node;
    int cx, cy, lx, ly;
    int position;
    int type;
    double distance; // how far it is
    int quadrant; // what quadrant its in
    tName name;
};

class PriorityQueue {
public:
    typedef enum {NW,NE,SW,SE} quads;
    PriorityQueue();
    PriorityQueue(const PriorityQueue& p);
    ~PriorityQueue();
    void ReheapDown(int root, int bottom);
    void ReheapUp(int root, int bottom);

    void Enqueue(Rectangle* element, double distance, int quadrant);
    void Enqueue(Rectangle* element, double distance);
    void Enqueue(cNode* element, double distance, int cx, int cy, int lx, int ly, int quadrant, int position);
    CompareField Dequeue();
    void MakeEmpty();
    bool IsFull();
    bool IsEmpty();
    void PrintQueue();
    void swap(int element1, int element2);
    int numElements;
    CompareField* elements;
};

void CompareField::setCords(int centerx, int centery, int lengthx, int lengthy) {
    cx = centerx;
    cy = centery;
    lx = lengthx;
    ly = lengthy;
}
bool CompareField::isQuadrant() {
    if (node != NULL && rect == NULL) {
        return true;
    }
    return false;
}
bool CompareField::isRectangle() {
    if (rect != NULL && node == NULL) {
        return true;
    }
    return false;
}

PriorityQueue::PriorityQueue()  // Class constructor
{
    numElements = 0;
    elements = new CompareField;
}
PriorityQueue::PriorityQueue(const PriorityQueue &p) {
    numElements = p.numElements;
    for (int i=0; i< p.numElements; i++) {
        // (elements[i]) = p.elements[i];
        cout << p.elements[i].distance << endl;
    }
}
PriorityQueue::~PriorityQueue()  // Class constructor
{
    if (numElements > 0) {
        delete elements;
    }
}

// for testing only.  make sure to delete
void PriorityQueue::Enqueue(Rectangle* element, double distance, int quadrant) {
    numElements++;
    CompareField * temp = new CompareField [numElements];
    if (elements !=NULL) { // copy the elements over
        for (int i=0; i< numElements; i++) {
            (temp[i]) = elements[i];
        }
    }
    CompareField tmp;
    tmp.rect = element;
    tmp.node = NULL;
    tmp.distance = distance;
    tmp.isQuad = false;
    tmp.type = tmp.Rectangle_Type;
    tmp.cx = element->getCenterX();
    tmp.cy = element->getCenterY();
    tmp.lx = element->getLengthX();
    tmp.ly = element->getLengthY();
    tmp.position = 9999;
    tmp.quadrant = quadrant;
    tmp.name = element->getName();
    temp[numElements-1] = tmp;

    elements = temp;
    ReheapUp(0,numElements-1);
}

void PriorityQueue::Enqueue(Rectangle* element, double distance) {
    numElements++;
    CompareField * temp = new CompareField [numElements];
    if (elements !=NULL) { // copy the elements over
        for (int i=0; i< numElements; i++) {
            (temp[i]) = elements[i];
        }
    }
    CompareField tmp;
    tmp.rect = element;
    tmp.node = NULL;
    tmp.distance = distance;
    tmp.isQuad = false;
    tmp.type = tmp.Rectangle_Type;
    tmp.cx = element->getCenterX();
    tmp.cy = element->getCenterY();
    tmp.lx = element->getLengthX();
    tmp.ly = element->getLengthY();
    tmp.position = 9999;
    tmp.quadrant = 0;
    tmp.name =element->getName();
    temp[numElements-1] = tmp;

    elements = temp;
    ReheapUp(0,numElements-1);
}

void PriorityQueue::Enqueue(cNode* element, double distance, int cx, int cy, int lx, int ly, int quadrant, int position) {
    numElements++;
    CompareField * temp = new CompareField [numElements];
    if (elements !=NULL) { // copy the elements over
        for (int i=0; i< numElements; i++) {
            (temp[i]) = elements[i];
        }
    }
    CompareField tmp;
    tmp.rect = NULL;
    tmp.node = element;
    tmp.distance = distance;
    tmp.cx = cx;
    tmp.cy = cy;
    tmp.lx = lx;
    tmp.ly =ly;
    tmp.position = position;
    tmp.quadrant = quadrant;
    tmp.isQuad = true;
    tmp.type = tmp.Quadrant_Type;
    tName *name = new tName("");
    tmp.name = (*name);
    
    temp[numElements-1] = tmp;

    elements = temp;
    ReheapUp(0,numElements-1);
}

void PriorityQueue::ReheapUp(int root, int bottom) {
    int parent;
    if(bottom > root) {
        parent = (bottom-1)/2;
        CompareField ele1 = elements[parent];
        CompareField ele2 = elements[bottom];
        bool doReHeap = false;

        if (ele1.distance > ele2.distance) {
            doReHeap = true;
        } else if(ele1.distance == ele2.distance) {
            if(ele1.position > ele2.position) {
                doReHeap = true;
            } else if(ele1.position == ele2.position) {
                if (ele1.name.compare(ele2.name) > 0) {
                    doReHeap = true;
                }
            }
        }

        if(doReHeap) {
            swap(parent, bottom);
            ReheapUp(root,parent);
        }


        //        if (elements[parent].distance > elements[bottom].distance || (elements[parent].distance == elements[bottom].distance && elements[parent].position > elements[bottom].position) || (elements[parent].distance == elements[bottom].distance && elements[parent].position > elements[bottom].position && elements[parent].name.compare(elements[bottom].position)>0)) {
        //            swap(parent, bottom);
        //            ReheapUp(root,parent);
        //        }

    }
}

void PriorityQueue::swap(int element1, int element2) {
    if (element1<=numElements && element2<=numElements) {
        CompareField temp = elements[element1];
        elements[element1] = elements[element2];
        elements[element2] = temp;
    }
}

void PriorityQueue::ReheapDown(int root, int bottom) {
    int maxChild, rightChild, leftChild;
    leftChild = root*2+1;
    rightChild = root*2+2;

    CompareField ele1, ele2;

    if(leftChild <= bottom) {
        if(leftChild == bottom)
            maxChild = leftChild;
        else {
            CompareField ele1 = elements[leftChild];
            CompareField ele2 = elements[rightChild];

            if (ele1.distance == ele2.distance) {
                if (ele1.position > ele2.position) {
                    maxChild = rightChild;
                } else if(ele1.position == ele2.position) {
                    if (ele1.name.compare(ele2.name) > 0) {
                        maxChild = rightChild;
                    } else {
                        maxChild = leftChild;
                    }
                } else {
                    maxChild = leftChild;
                }
            } else if(ele1.distance > ele2.distance) {
                maxChild = rightChild;
            } else {
                maxChild = leftChild;
            }
        }
    }

    bool doReheap = false;
    ele1 = elements[root];
    ele2 = elements[maxChild];
    if (ele1.distance > ele2.distance) {
        doReheap = true;
    } else if (ele1.distance == ele2.distance) {
        if (ele1.position == ele2.position) {
            if (ele1.name.compare(ele2.name) > 0) {
                doReheap = true;
            }
        } else if (ele1.position > ele2.position) {
            doReheap = true;
        }
    }

    if (doReheap) {
        swap(root, maxChild);
        ReheapDown(maxChild,bottom);
    }


}


void PriorityQueue::PrintQueue() {
    for (int i=0; i<numElements; i++) {
        cout << elements[i].distance << " ";
        if (elements[i].isQuadrant())
            cout << elements[i].quadrant;
        cout << endl;
    }

}

CompareField PriorityQueue::Dequeue() {
    if (numElements >0) {
        CompareField firstElement = elements[0];
        elements[0] = elements[numElements-1];
        numElements--;
        ReheapDown(0,numElements-1);
        return (firstElement);
    }
    CompareField temp;
    return temp;
}

void PriorityQueue::MakeEmpty() {
    numElements = 0;
    elements =  NULL;
}

bool PriorityQueue::IsEmpty() {
    if (numElements == 0)
        return true;
    return false;
}

#endif /*PRIORITYQUEUE_H_*/
