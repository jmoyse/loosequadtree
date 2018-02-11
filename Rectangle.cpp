// Julian Moyse
// CMSC 420 Fall 2007
// LooseQuadTree Project 4.3
//
#include "Rectangle.h"
#include "bNode.h"
using namespace std;

Rectangle::Rectangle() {
    Name = "";
    Center[X] = 0;
    Center[Y] = 0;
    Length[X] = 0;
    Length[Y] = 0;
    binSon[LEFT] = NULL;
    binSon[RIGHT] = NULL;
}

Rectangle::Rectangle(tName name, int centerX, int centerY, int lengthX,int lengthY) {
    Name = name;
    Center[X] = centerX;
    Center[Y] = centerY;
    Length[X] = lengthX;
    Length[Y] = lengthY;
    binSon[LEFT] = NULL;
    binSon[RIGHT] = NULL;
}

int Rectangle::getCenterX() {
    return Center[X];
}
int Rectangle::getCenterY() {
    return Center[Y];
}
int Rectangle::getLengthX() {
    return Length[X];
}
int Rectangle::getLengthY() {
    return Length[Y];
}
void Rectangle::setCenter(int x, int y) {
    Center[X] = x;
    Center[Y] = y;
}

void Rectangle::setLength(int x, int y) {
    Length[X] = x;
    Length[Y] = y;
}

void Rectangle::setName(tName name) {
    Name = name;
}

tName Rectangle::getName() {
    return Name;
}
Rectangle* Rectangle::search(tName r) {
    Rectangle * nodePtr = this;
    Rectangle * parentPtr = NULL;
    bool found = false;

    while(nodePtr != NULL && !found) {
        if(r.compare(nodePtr->getName())==0) {
            return nodePtr;
        } else if(r.compare(nodePtr->getName())<0) {
            parentPtr = nodePtr;
            nodePtr = nodePtr->binSon[LEFT];
        } else if(r.compare(nodePtr->getName())>0) {
            parentPtr = nodePtr;
            nodePtr = nodePtr->binSon[RIGHT];
        } else {
            //found = true;
            cout << "big problem";
        }
    }
    return NULL;
}

Rectangle* Rectangle::findNode(tName r) {
    Rectangle * nodePtr = this;
    Rectangle * parentPtr = NULL;
    bool found = false;

    while(nodePtr != NULL && !found) {
        if(r.compare(nodePtr->getName())==0) {
            return parentPtr;
        } else if(r.compare(nodePtr->getName())<0) {
            parentPtr = nodePtr;
            nodePtr = nodePtr->binSon[LEFT];
        } else if(r.compare(nodePtr->getName())>0) {
            parentPtr = nodePtr;
            nodePtr = nodePtr->binSon[RIGHT];
        } else {
            //found = true;
            cout << "big problem";
        }
    }
    return parentPtr;
}

void Rectangle::insertNode(Rectangle *r) {
    Rectangle* parentPtr = findNode(r->getName());

    if (parentPtr == NULL) {
        cout << "problem";
    } else if (r->getName().compare(parentPtr->getName())<0) {
        //cout << "Added " << r->getName() << " to the LEFT" << endl;
        r->binSon[LEFT] = NULL;
        r->binSon[RIGHT] = NULL;
        parentPtr->binSon[LEFT] = r;
        parentPtr->binSon[LEFT]->binSon[LEFT] = NULL;
        parentPtr->binSon[LEFT]->binSon[RIGHT] = NULL;


    } else {
        //cout << "Added " << r->getName() << " to the RIGHT of " <<parentPtr->getName() <<endl;
        r->binSon[LEFT] = NULL;
        r->binSon[RIGHT] = NULL;
        parentPtr->binSon[RIGHT] = r;
        parentPtr->binSon[RIGHT]->binSon[LEFT] = NULL;
        parentPtr->binSon[RIGHT]->binSon[RIGHT] = NULL;
    }
}


void Rectangle::removeNode(tName r) {
    int side;
    Rectangle * nodeToDelete = findNode(r);
    Rectangle * tree;


    if (nodeToDelete == NULL && r.compare(this->getName()) == 0) {
        //cout << "We're deleting the head node.  This shouldn't happen  EVER" << endl;
        return;
    } else if (nodeToDelete == NULL) {
        return;
    }

    if(nodeToDelete->binSon[LEFT]!=NULL && nodeToDelete->binSon[LEFT]->getName().compare(r) == 0) {
        tree = nodeToDelete->binSon[LEFT];
        side = LEFT;
    } else if(nodeToDelete->binSon[RIGHT]!=NULL && nodeToDelete->binSon[RIGHT]->getName().compare(r) == 0) {
        tree = nodeToDelete->binSon[RIGHT];
        side = RIGHT;
    } else {
        cout << "this really shouldn't happen";
    }
    tree = search(r);
    Rectangle *& temp = tree;

    if (tree->binSon[LEFT] == NULL) {
        nodeToDelete->binSon[side] = tree->binSon[RIGHT];
    } else if (tree->binSon[RIGHT] == NULL) {
        nodeToDelete->binSon[side] = tree->binSon[LEFT];
    } else {
        Rectangle * pred = findPredessor(tree->binSon[LEFT]);
        removeReference(pred);

        tree->Name = pred->getName();
    }
}

void Rectangle::removeReference(Rectangle *r) {
    Rectangle * nodePtr = this;
    Rectangle * parentPtr = NULL;
    bool found = false;

    while(nodePtr != NULL && !found) {
        if(r->getName().compare(nodePtr->getName()) == 0 && nodePtr == r) {
            if (parentPtr->binSon[LEFT]->getName().compare(r->getName()) ==0) // left side
                parentPtr->binSon[LEFT] = NULL;
            else if (parentPtr->binSon[RIGHT]->getName().compare(r->getName()) ==0) // left side
                parentPtr->binSon[RIGHT] = NULL;
            else {
                cout << "another problem";
            }
            return;
        } else if(r->getName().compare(nodePtr->getName())<0) {
            parentPtr = nodePtr;
            nodePtr = nodePtr->binSon[LEFT];
        } else if(r->getName().compare(nodePtr->getName())>0) {
            parentPtr = nodePtr;
            nodePtr = nodePtr->binSon[RIGHT];
        } else {
            cout << "big problem";
        }
    }
}

Rectangle* Rectangle::findPredessor(Rectangle * tree) {
    Rectangle * temp = tree;
    while(temp->binSon[RIGHT]!= NULL)
        temp = temp->binSon[RIGHT];
    return temp;
}

Rectangle* Rectangle::getLeft() {
    return binSon[LEFT];
}
Rectangle* Rectangle::getRight() {
    return binSon[RIGHT];
}

Rectangle::~Rectangle() {
	//delete binSon;
}
