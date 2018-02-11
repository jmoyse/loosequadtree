// Julian Moyse
// CMSC 420 Fall 2007
// LooseQuadTree Project 4.3
//
#include "bNode.h"
using namespace std;

bNode::bNode() {
    prev = NULL;
    next = NULL;
    Rect = NULL;
    length = 0;
}
bNode::bNode(Rectangle *r) {
    length = 0;
    prev = NULL;
    next = NULL;
    Rect = NULL;

    next = new bNode();
    next->prev = this;
    next->Rect = r;

    next->next = new bNode();
    next->next->prev = next;
    length++;
}

Rectangle * bNode::getRectangle() {
    return Rect;
}


bNode* bNode::searchNode(tName name) {
    bool moreToSearch = true;
    bNode* location = next;

    if (location == NULL) {
        return NULL;
    }

    while(moreToSearch) {
        if(name.compare(location->Rect->getName())==0) {
            return location;
        } else {
            location = location->next;
            moreToSearch = (location->Rect!=NULL);
        }
    }
    return NULL;
}

bNode* bNode::findNode(tName name) {
    bool moreToSearch = true;
    bNode* location = next;

    while(moreToSearch) {
        if(name.compare(location->Rect->getName()) < 0) {
            moreToSearch = false;
        } else {
            location = location->next;
            moreToSearch = (location->Rect!=NULL);
        }
    }
    return location;
}

bNode* bNode::findNode(Rectangle *data) {
    bool moreToSearch = true;
    bNode* location = next;

    while(moreToSearch) {
        if(data->getName().compare(location->Rect->getName()) < 0) {
            moreToSearch = false;
        } else {
            location = location->next;
            moreToSearch = (location->Rect!=NULL);
        }
    }
    return location;
}


void bNode::printNodes() {
    if (next == NULL) {
        //	cout << "EMPTY" << endl;
        return;
    }
    bNode* location = next;
    bool moreToSearch;
    moreToSearch = (location->Rect!=NULL);

    while(location->Rect!=NULL) {
        cout << location->Rect->getName() << " " ;
        location = location->next;
    }
}

Rectangle* bNode::getNode(int position) {
    int i = 0 ;
    if (length == 0) {
        return NULL;
    }
    bNode* location = next;
    bool moreToSearch;
    moreToSearch = (location->Rect!=NULL);
    while(location->Rect!=NULL) {
        if (i == position) {
            return location->Rect;
        }
        location = location->next;
        i++;
    }
    return NULL;

}
void bNode::listNodes() {
    if (next == NULL) {
        //	cout << "EMPTY" << endl;
        return;
    }

    bNode* location = next;
    bool moreToSearch;
    moreToSearch = (location->Rect!=NULL);

    while(location->Rect!=NULL) {
        cout << location->Rect->getName() << "," << location->Rect->getCenterX() << "," << location->Rect->getCenterY() << "," << location->Rect->getLengthX()/2 << "," << location->Rect->getLengthY()/2 << " ";
        location = location->next;
    }
}

void bNode::insertNode(Rectangle *data) {

    bNode * location = findNode(data);
    bNode * newNode = new bNode();
    newNode->Rect = data;

    newNode->prev = location->prev;
    newNode->next = location;

    location->prev->next = newNode;
    location->prev = newNode;
    length++;
}

void bNode::removeNode(Rectangle *data) {
    bNode * location = searchNode(data->getName());
    if (location == NULL) {
        return;
    }
    bNode * ptrPrev = location->prev;
    bNode * ptrNext = location->next;

    ptrPrev->next = ptrNext;
    ptrNext->prev = ptrPrev;

    length--;
}
bNode::~bNode() {

}
