// Julian Moysef
// CMSC 420 Fall 2007
// LooseQuadTree Project 4.3
#include <iostream>
#include "LooseQuadTreeDecoder.h"
#include "LooseQuadTree.h"
#include "tName.h"

extern "C" {
#include "drawing_c.h"
}
using namespace std;
// TODO: Destroy everybook with a quadtree reference in it.  they're the work of the devil
// TODO: Fix the incorrect error message on one of the traces.  has a "THE" in it.
// TODO: move is totally fucked up.  better fix it
// TODO: bNodes do not sort correctly with numers and letters

// Part 1 - DONE
// Part 2 - DONE
// Part 3 - DONE
// Part 4 - COMPLETED - 11, 12, 13
// PART 4 - UNFINISHED - 14, 15
// Optional Part - 16, 17, 18


int main(int argc, char *argv[]) {
//	bool value = rayIntersect(5,0,0,24,32,0, 0,20,0,32,20,0);
//	cout << "rayIntersect(5,0,0,24,32,0, 0,20,0,32,20,) ";
//	if (value == true)
//			cout << "intersects" << endl;
//	else 
//		cout << "does not intersect" << endl;
//	
//	value = rayIntersect(5,0,0,24,32,0,5,0,0,24,32,0);
//		cout << "rayIntersect(5,0,0,24,32,0,5,0,0,24,32,0) ";
//		if (value == true)
//				cout << "intersects" << endl;
//		else 
//			cout << "does not intersect" << endl;
//
//		
//		value = rayIntersect(5,0,0,24,32,0,4,22,0,10,24,0);
//			cout << "rayIntersect(5,0,0,24,32,0,4,22,0,10,24,0) ";
//			if (value == true)
//					cout << "intersects" << endl;
//			else 
//				cout << "does not intersect" << endl;

	
	
//   if (rayIntersect(0,0,0,128,128,0,59,59,0,69,69,0)){                	
//	   cout << "INTERSECTS " << endl;
//   }
//   else{
//	   cout << "DOESN'T :( " << endl;
//   }
	
//	 if (rayIntersect(0,0,0,128,128,0,59,59,0,69,69,0)){             
//	   cout << "INTERSECTS " << endl;
//   }
   
//	   
   Quadtree QTREE;
    while(!cin.eof()) {
        char input[256];
        cin.getline(input,256);
        tName *test = new tName(input);
        QTREE.parse_command(test);
    }
    return 0;
}

void Quadtree::parse_command(tName *input) {
    tName *output[5];

    if (input->compare(new tName("TRACE ON")) == 0) {
        traceOn();
        return;
    } else if (input->compare(new tName("TRACE OFF")) == 0) {
        traceOff();
        return;
    }
    int currentCommand = 0;
    tName *temp = new tName();
    bool valid = false;

    for (int i=0; i<input->length(); i++) {
        if (input->at(i) == '(' ||input->at(i) == ',' ||input->at(i) == ')' ) {
            output[currentCommand++] = temp;
            valid = true;
            temp  = new tName();
        } else {
            temp->append(input->at(i));
            output[currentCommand] = temp;
        }
    }
    if (valid == false) {
        //cout << "INVALID COMMAND" << endl;
        return;
    }
    if (output[0]->compare(new tName("INIT_QUADTREE")) == 0) {
        INIT_QUADTREE(atoi(output[1]->toString()), atoi(output[2]->toString()));
    }
    if (output[0]->compare(new tName("DISPLAY")) == 0) {
        DISPLAY();
    }
    if (output[0]->compare(new tName("LIST_RECTANGLES")) == 0) {
        LIST_RECTANGLES();
    }
    if (output[0]->compare(new tName("CREATE_RECTANGLE")) == 0) {
        CREATE_RECTANGLE(output[1]->toString(),atoi(output[2]->toString()), atoi(output[3]->toString()),atoi(output[4]->toString()),atoi(output[5]->toString()));
    }
    if (output[0]->compare(new tName("INSERT")) == 0) {
        INSERT(output[1]->toString());
    }
    if (output[0]->compare(new tName("MOVE")) == 0) {
        MOVE(output[1]->toString(),atoi(output[2]->toString()),atoi(output[3]->toString()));
    }
    if (output[0]->compare(new tName("SEARCH_POINT")) == 0) {
        SEARCH_POINT(atoi(output[1]->toString()),atoi(output[2]->toString()));
    }
    if (output[0]->compare(new tName("DELETE_RECTANGLE")) == 0) {
        DELETE_RECTANGLE(output[1]->toString());
    }
    if (output[0]->compare(new tName("DELETE_POINT")) == 0) {
        DELETE_POINT(atoi(output[1]->toString()),atoi(output[2]->toString()));
    }
    if (output[0]->compare(new tName("REGION_SEARCH")) == 0) {
        REGION_SEARCH(output[1]->toString());
    }
    if (output[0]->compare(new tName("TOUCH")) == 0) {
        TOUCH(output[1]->toString());
    }
    if (output[0]->compare(new tName("WITHIN")) == 0) {
        WITHIN(output[1]->toString(), atoi(output[2]->toString()));
    }
    if (output[0]->compare(new tName("VERT_NEIGHBOR")) == 0) {
        VERT_NEIGHBOR(output[1]->toString());
    }
    if (output[0]->compare(new tName("HORIZ_NEIGHBOR")) == 0) {
    	HORIZ_NEIGHBOR(output[1]->toString());
    }
    if (output[0]->compare(new tName("NEAREST_RECTANGLE")) == 0) {
    	NEAREST_RECTANGLE(atoi(output[1]->toString()),atoi(output[2]->toString()));
    }
    if (output[0]->compare(new tName("WINDOW")) == 0) {
    	WINDOW(atoi(output[1]->toString()),atoi(output[2]->toString()),atoi(output[3]->toString()),atoi(output[4]->toString()));
    }
    if (output[0]->compare(new tName("CHANGE_EXPANSION_FACTOR")) == 0) {
    	CHANGE_EXPANSION_FACTOR(atoi(output[1]->toString()));
    }
    if (output[0]->compare(new tName("NEAREST_NEIGHBOR")) == 0) {
    	NEAREST_NEIGHBOR(output[1]->toString());
    }
    if (output[0]->compare(new tName("LEXICALLY_GREATER_NEAREST_NEIGHBOR")) == 0) {
    	LEXICALLY_GREATER_NEAREST_NEIGHBOR(output[1]->toString());
    }
    if (output[0]->compare(new tName("RAYTRACE")) == 0) {
    	RAYTRACE(atoi(output[1]->toString()),atoi(output[2]->toString()));
    }
    return;
}

void Quadtree::traceOn() {
    looseQuadTree.traceOn();
}
void Quadtree::traceOff() {
    looseQuadTree.traceOff();
}

void Quadtree::INIT_QUADTREE(int width, double p) {
    rectTree = new bNode();
    double newWidth = pow(2.0, (double)width);
    looseQuadTree = LooseQuadTree("World",newWidth/2,newWidth/2,newWidth,newWidth, p);
    cout << "LOOSE QUADTREE INITIALIZED WITH PARAMETERS " <<  width << " " << p << endl;
}

void Quadtree::DISPLAY() {
    int cx = looseQuadTree.World.getCenterX();
    int cy = looseQuadTree.World.getCenterY();
    int lx = looseQuadTree.World.getLengthX();
    int ly = looseQuadTree.World.getLengthY();

    // Dotted Line the size of World
    StartPicture(lx+1,ly+1);

    // Draw the cords and rectangles
    looseQuadTree.looseQuadRoot->drawQuadrants(looseQuadTree.looseQuadRoot, cx,cy,lx,ly,0);

    // End the Picture
    EndPicture();
}

void Quadtree::LIST_RECTANGLES() {
    if (rectTree->length == 0)
        cout << "NO RECTANGLES IN DATABASE" << endl;
    else {
        rectTree->listNodes();
        cout << endl;
    };
}
void Quadtree::CREATE_RECTANGLE(tName name,int cx,int cy,int lx, int ly) {
    Rectangle *temp = new Rectangle(name,cx,cy,lx*2,ly*2);

    if (rectTree->length == 0)
        rectTree = new bNode(temp);
    else
        rectTree->insertNode(temp);
    cout << "RECTANGLE " << name << " CREATED WITH PARAMETERS " << cx << " " << cy << " " << lx << " " << ly << endl;
}

void Quadtree::INSERT(tName n) {
    bNode *temp = rectTree->searchNode(n);
    if (temp != NULL) {
        int RRectMaxX = temp->getRectangle()->getCenterX()+(temp->getRectangle()->getLengthX()/2);
        int RRectMinX = temp->getRectangle()->getCenterX()-(temp->getRectangle()->getLengthX()/2);
        int RRectMaxY = temp->getRectangle()->getCenterY()+(temp->getRectangle()->getLengthY()/2);
        int RRectMinY = temp->getRectangle()->getCenterY()-(temp->getRectangle()->getLengthY()/2);

        int WorldRectMaxX = looseQuadTree.World.getCenterX()+(looseQuadTree.World.getLengthX()/2);
        int WorldRectMinX = looseQuadTree.World.getCenterX()-(looseQuadTree.World.getLengthX()/2);
        int WorldRectMaxY = looseQuadTree.World.getCenterY()+(looseQuadTree.World.getLengthY()/2);
        int WorldRectMinY = looseQuadTree.World.getCenterY()-(looseQuadTree.World.getLengthY()/2);

        if ((RRectMinX < WorldRectMinX) || (RRectMaxX > WorldRectMaxX) || (RRectMinY < WorldRectMinY) || (RRectMaxY > WorldRectMaxY)) {
            cout << "INSERTION OF " << temp->getRectangle()->getName() << " FAILED AS " <<  temp->getRectangle()->getName()<< " LIES PARTIALLY OUTISDE SPACE SPANNED BY LOOSEQUADTREE" << endl;
            return;
        }

        looseQuadTree.AddRectangle(temp->getRectangle());
        if (looseQuadTree.trace == true)
            cout << endl;
        cout << "RECTANGLE " << n << " HAS BEEN INSERTED" << endl;
    } else {
        cout << "INSERT FAILED ON " <<  n  <<  ". DOES NOT EXIST IN DATABASE." << endl;
    }
}

// RECTANGLE N WOULD BE OUTSIDE LOOSE QUADTREE SPACE
void Quadtree::MOVE(tName n, int offsetx, int offsety) {
    bNode * rect = rectTree->searchNode(n);

    if (rectTree->searchNode(n) == NULL) { // doesn't exist in rectTree
        cout << "RECTANGLE " << n << " NOT FOUND IN RECTANGLE DATABASE" << endl;
        return;
    }
    bNode * value = new bNode();

    int RRectMaxX = rect->getRectangle()->getCenterX()+(offsetx)+(rect->getRectangle()->getLengthX()/2);
    int RRectMinX = rect->getRectangle()->getCenterX()+(offsetx)-(rect->getRectangle()->getLengthX()/2);
    int RRectMaxY = rect->getRectangle()->getCenterY()+(offsety)+(rect->getRectangle()->getLengthY()/2);
    int RRectMinY = rect->getRectangle()->getCenterY()+(offsety)-(rect->getRectangle()->getLengthY()/2);

    int WorldRectMaxX = looseQuadTree.World.getCenterX()+(looseQuadTree.World.getLengthX()/2);
    int WorldRectMinX = looseQuadTree.World.getCenterX()-(looseQuadTree.World.getLengthX()/2);
    int WorldRectMaxY = looseQuadTree.World.getCenterY()+(looseQuadTree.World.getLengthY()/2);
    int WorldRectMinY = looseQuadTree.World.getCenterY()-(looseQuadTree.World.getLengthY()/2);

    if ((RRectMinX < WorldRectMinX) || (RRectMaxX > WorldRectMaxX) || (RRectMinY < WorldRectMinY) || (RRectMaxY > WorldRectMaxY)) {
        cout << "RECTANGLE " <<  rect->getRectangle()->getName() << " N WOULD BE OUTSIDE LOOSE QUADTREE SPACE" << endl;
        return;
    }

    int cx = looseQuadTree.World.getCenterX();
    int cy = looseQuadTree.World.getCenterY();
    int lx = looseQuadTree.World.getLengthX();
    int ly = looseQuadTree.World.getLengthY();

    looseQuadTree.looseQuadRoot->moveRectangle(&looseQuadTree.looseQuadRoot,rect->Rect,offsetx, offsety, cx,cy,lx,ly, looseQuadTree.p,0, &value);
    if (looseQuadTree.trace == true)
        cout << endl;
    cout << "RECTANGLE " << n << " HAS BEEN MOVED BY " << offsetx << " " << offsety << endl;
}

void Quadtree::SEARCH_POINT(int px, int py) {
    bNode * value = new bNode();
    int cx = looseQuadTree.World.getCenterX();
    int cy = looseQuadTree.World.getCenterY();
    int lx = looseQuadTree.World.getLengthX();
    int ly = looseQuadTree.World.getLengthY();

    looseQuadTree.looseQuadRoot->searchPoint(&looseQuadTree.looseQuadRoot,px,py, cx,cy,lx,ly,0, looseQuadTree.p,&value);
    if (looseQuadTree.trace == true)
        cout << endl;
    if (value->length ==0) {
        cout << "NO RECTANGLE CONTAINS QUERY POINT " << px << " " << py << endl;
    } else {
        cout << "POINT " << px << " " << py << " FALLS IN RECTANGLES ";
        value->printNodes();
        cout << endl;
    }
}

void Quadtree::DELETE_RECTANGLE(tName n) {
    if (rectTree->searchNode(n) == NULL) { // doesn't exist in rectTree
        cout << "RECTANGLE " << n << " NOT FOUND IN RECTANGLE DATABASE" << endl;
        return;
    }
    bNode * value = new bNode();
    bNode * rect = rectTree->searchNode(n);

    int cx = looseQuadTree.World.getCenterX();
    int cy = looseQuadTree.World.getCenterY();
    int lx = looseQuadTree.World.getLengthX();
    int ly = looseQuadTree.World.getLengthY();

    looseQuadTree.looseQuadRoot->deleteRectangle(&looseQuadTree.looseQuadRoot,rect->Rect, cx,cy,lx,ly,0, looseQuadTree.p,&value);
    if (looseQuadTree.trace == true)
        cout << endl;
    if (value->length ==0) {
        cout << "RECTANGLE " << n << " NOT FOUND IN THE LOOSE QUADTREE"  << endl;
    } else {
        cout << "DELETED RECTANGLE " << n << " FROM QUADTREE" << endl;
    }
}
void Quadtree::DELETE_POINT(int px, int py) {
    bNode * value = new bNode();
    int cx = looseQuadTree.World.getCenterX();
    int cy = looseQuadTree.World.getCenterY();
    int lx = looseQuadTree.World.getLengthX();
    int ly = looseQuadTree.World.getLengthY();

    looseQuadTree.looseQuadRoot->deletePoint(&looseQuadTree.looseQuadRoot,px,py, cx,cy,lx,ly,0, looseQuadTree.p, &value);
    if (looseQuadTree.trace == true)
        cout << endl;
    if (value->length ==0) {
        cout << "NO RECTANGLES DELETED USING POINT " << px << " " << py << endl;
    } else {
        cout << "DELETED RECTANGLES ";
        value->printNodes();
        cout << endl;
    }
}

void Quadtree::REGION_SEARCH(tName n) {
    if (rectTree->searchNode(n) == NULL) { // doesn't exist in rectTree
        cout << "RECTANGLE " << n << " NOT FOUND IN RECTANGLE DATABASE" << endl;
        return;
    }
    bNode * value = new bNode();
    bNode * rect = rectTree->searchNode(n);

    int cx = looseQuadTree.World.getCenterX();
    int cy = looseQuadTree.World.getCenterY();
    int lx = looseQuadTree.World.getLengthX();
    int ly = looseQuadTree.World.getLengthY();

    looseQuadTree.looseQuadRoot->regionNodeSearch(&looseQuadTree.looseQuadRoot,rect->Rect, cx,cy,lx,ly,0,looseQuadTree.p, &value);
    if (looseQuadTree.trace == true)
        cout << endl;
    if (value->length ==0) {
        cout << "RECTANGLE " << n << " INTERSECTS NO RECTANGLES" << endl;
    } else {
        cout << "RECTANGLE " << n << " INTERSECTS RECTANGLES ";
        value->printNodes();
        cout << endl;
    }
}

void Quadtree::TOUCH(tName n) {
    if (rectTree->searchNode(n) == NULL) { // doesn't exist in rectTree
        cout << "RECTANGLE " << n << " NOT FOUND IN RECTANGLE DATABASE" << endl;
        return;
    }
    bNode * value = new bNode();
    bNode * rect = rectTree->searchNode(n);

    int cx = looseQuadTree.World.getCenterX();
    int cy = looseQuadTree.World.getCenterY();
    int lx = looseQuadTree.World.getLengthX();
    int ly = looseQuadTree.World.getLengthY();

    looseQuadTree.looseQuadRoot->touch(&looseQuadTree.looseQuadRoot,rect->Rect, cx,cy,lx,ly,0,looseQuadTree.p, &value);
    if (looseQuadTree.trace == true)
        cout << endl;
    if (value->length ==0) {
    	cout << "NO RECTANGLES IN LOOSE QUADTREE TOUCH RECTANGLE " << n << endl;
    } else {
    	cout << "RECTANGLE " << n << " TOUCHES RECTANGLES ";        
        value->printNodes();
        cout << endl;
    }
}


void Quadtree::WITHIN(tName n, int d) {
    if (rectTree->searchNode(n) == NULL) { // doesn't exist in rectTree
        cout << "RECTANGLE " << n << " NOT FOUND IN RECTANGLE DATABASE" << endl;
        return;
    }
    bNode * value = new bNode();
    bNode * rect = rectTree->searchNode(n);

    int cx = looseQuadTree.World.getCenterX();
    int cy = looseQuadTree.World.getCenterY();
    int lx = looseQuadTree.World.getLengthX();
    int ly = looseQuadTree.World.getLengthY();

    Rectangle * temp = new Rectangle("NONAME",rect->Rect->getCenterX(),rect->Rect->getCenterY(),rect->Rect->getLengthX()+d*2,rect->Rect->getLengthY()+d*2);
    looseQuadTree.looseQuadRoot->within(&looseQuadTree.looseQuadRoot,rect->Rect,temp, cx,cy,lx,ly,0,looseQuadTree.p, &value);
    if (looseQuadTree.trace == true)
        cout << endl;
    if (value->length ==0) {
       cout << "find this error emssage" <<endl;
    } else {
    	cout << "RECTANGLE " << n << " EXPANDED BY " << d << " OVERLAPS RECTANGLES ";
        value->printNodes();
        cout << endl;
    }
}
void Quadtree::VERT_NEIGHBOR(tName n) {
    if (rectTree->searchNode(n) == NULL) { // doesn't exist in rectTree
        cout << "RECTANGLE " << n << " NOT FOUND IN RECTANGLE DATABASE" << endl;
        return;
    }
    bNode * rect = rectTree->searchNode(n);
    int cx = looseQuadTree.World.getCenterX();
    int cy = looseQuadTree.World.getCenterY();
    int lx = looseQuadTree.World.getLengthX();
    int ly = looseQuadTree.World.getLengthY();

    
    Rectangle *temp = looseQuadTree.looseQuadRoot->verticalNeighbor(&looseQuadTree.looseQuadRoot,rect->Rect,cx,cy,lx,ly,0,looseQuadTree.p);
    if (looseQuadTree.trace == true)
        cout << endl;
    if(temp !=NULL) {
    	cout << "RECTANGLE " << n << " HAS VERTICAL NEIGHBOR " << temp->getName()  << endl;
    } else {
        cout << n << " HAS NO VERTICAL NEIGHBORS" << endl;
    }
}

void Quadtree::HORIZ_NEIGHBOR(tName n) {
    if (rectTree->searchNode(n) == NULL) { // doesn't exist in rectTree
        cout << "RECTANGLE " << n << " NOT FOUND IN RECTANGLE DATABASE" << endl;
        return;
    }
    bNode * rect = rectTree->searchNode(n);
    int cx = looseQuadTree.World.getCenterX();
    int cy = looseQuadTree.World.getCenterY();
    int lx = looseQuadTree.World.getLengthX();
    int ly = looseQuadTree.World.getLengthY();

    Rectangle *temp = looseQuadTree.looseQuadRoot->horizontalNeighbor(&looseQuadTree.looseQuadRoot,rect->Rect,cx,cy,lx,ly,0,looseQuadTree.p);
    if (looseQuadTree.trace == true)
        cout << endl;
    
    if(temp !=NULL) {
    	cout << "RECTANGLE " << n << " HAS HORIZONTAL NEIGHBOR " << temp->getName()  << endl;
    } else {
        cout << n << " HAS NO HORIZONTAL NEIGHBORS" << endl;
    }
}
// TODO: NEAREST_NEIGHBOR needs to deal with stuff not in the tree.  all the functions do for that matter.
void Quadtree::NEAREST_RECTANGLE(int px, int py) {
    int cx = looseQuadTree.World.getCenterX();
    int cy = looseQuadTree.World.getCenterY();
    int lx = looseQuadTree.World.getLengthX();
    int ly = looseQuadTree.World.getLengthY();
    Rectangle *temp = looseQuadTree.looseQuadRoot->nearestRectangle(&looseQuadTree.looseQuadRoot,px,py,cx,cy,lx,ly,0,looseQuadTree.p);
    if (looseQuadTree.trace == true)
        cout << endl;
    if(temp !=NULL) {
    	cout << "THE NEAREST RECTANGLE TO " << px << " " << py << " is " << temp->getName() << endl;
    } 
    else {
    	cout << "NO NEAREST RECTANGLE " << px << " " << py << " FOUND"  << endl;
    } 	
}


void Quadtree::WINDOW(int rect_llx, int rect_lly, int rect_lx, int rect_ly) {	
    bNode * value = new bNode();
    
    int cx = looseQuadTree.World.getCenterX();
    int cy = looseQuadTree.World.getCenterY();
    int lx = looseQuadTree.World.getLengthX();
    int ly = looseQuadTree.World.getLengthY();
    
    looseQuadTree.looseQuadRoot->window(&looseQuadTree.looseQuadRoot,rect_llx, rect_lly, rect_lx, rect_ly, cx,cy,lx,ly,0,looseQuadTree.p, &value);
    
    //Draw the picture
    StartPicture(lx+1,ly+1);
    SetLineDash(2,2);
    DrawRect(rect_llx,rect_lly,rect_llx+rect_lx,rect_lly+rect_ly);
    
    looseQuadTree.looseQuadRoot->drawAxis(looseQuadTree.looseQuadRoot,rect_llx, rect_lly, rect_lx, rect_ly, cx,cy,lx,ly,0);
    looseQuadTree.looseQuadRoot->drawQuadrantsList(looseQuadTree.looseQuadRoot,cx,cy,lx,ly,0,&value);
    EndPicture();
    
    if (looseQuadTree.trace == true)
        cout << endl;
    
    if (value->length ==0) {
        cout << "NO RECTANGLES FALL IN WINDOW " << rect_llx << " " << rect_ly << " " << rect_lx << " " << rect_ly << endl;
    } 
    else {
        cout << "WINDOW " << rect_llx << " " << rect_ly << " " << rect_lx << " " << rect_ly << " CONTAINS RECTANGLES ";
        value->printNodes();
        cout << endl;
    }    
}

void Quadtree::CHANGE_EXPANSION_FACTOR(int newExpansion){
    int cx = looseQuadTree.World.getCenterX();
    int cy = looseQuadTree.World.getCenterY();
    int lx = looseQuadTree.World.getLengthX();
    int ly = looseQuadTree.World.getLengthY();
  
    int oldExpansion = looseQuadTree.p;
    bNode * value = new bNode();
    looseQuadTree.looseQuadRoot->changeExpansion(&looseQuadTree.looseQuadRoot,cx,cy,lx,ly,cx,cy,lx,ly,oldExpansion,newExpansion,0, &value);
    looseQuadTree.p = newExpansion;
    cout << "NODES LEFT ";
    value->printNodes();
    cout << endl;

//    
//    if(temp !=NULL) {
//    	cout << "POINT " << px << "," << py << " IS NEAREST TO RECTANGLE " << temp->getName()  << endl;
//    } else {
//        cout << "POINT " << px << " " << py << " HAS NO NEAREST NEIGHBOR" << endl;
//    }
}

void Quadtree::NEAREST_NEIGHBOR(tName n)
{
    if (rectTree->searchNode(n) == NULL) { // doesn't exist in rectTree
        cout << "RECTANGLE " << n << " NOT FOUND IN RECTANGLE DATABASE" << endl;
        return;
    }
    bNode * rect = rectTree->searchNode(n);
    int cx = looseQuadTree.World.getCenterX();
    int cy = looseQuadTree.World.getCenterY();
    int lx = looseQuadTree.World.getLengthX();
    int ly = looseQuadTree.World.getLengthY();

    Rectangle *temp = looseQuadTree.looseQuadRoot->nearestNeighbor(&looseQuadTree.looseQuadRoot,rect->Rect,cx,cy,lx,ly,0,looseQuadTree.p);
    if (looseQuadTree.trace == true)
        cout << endl;
    
    if(temp !=NULL) {
    	cout << "THE NEAREST NEIGHBOR TO RECTANGLE " << n << " IS RECTANGLE " << temp->getName()  << endl;
    } 
    else {
        cout << n << " NO NEAREST NEIGHBOR TO RECTANGLE N FOUND" << endl;
    }
}

void Quadtree::LEXICALLY_GREATER_NEAREST_NEIGHBOR(tName n){
    if (rectTree->searchNode(n) == NULL) { 	// doesn't exist in rectTree
        cout << "RECTANGLE " << n << " NOT FOUND IN RECTANGLE DATABASE" << endl;
        return;
    }
    bNode * rect = rectTree->searchNode(n);
    int cx = looseQuadTree.World.getCenterX();
    int cy = looseQuadTree.World.getCenterY();
    int lx = looseQuadTree.World.getLengthX();
    int ly = looseQuadTree.World.getLengthY();

    Rectangle *temp = looseQuadTree.looseQuadRoot->lexicallyNearestNeighbor(&looseQuadTree.looseQuadRoot,rect->Rect,cx,cy,lx,ly,0,looseQuadTree.p);
    if (looseQuadTree.trace == true)
        cout << endl;
    
    if(temp !=NULL) {
    	cout << "THE LEXICALLY GREATER NEAREST NEIGHBOR TO RECTANGLE " << n << " IS RECTANGLE " << temp->getName()  << endl;
    } 
    else {
        cout << n << "NO LEXICALLY GREATER NEAREST NEIGHBOR TO RECTANGLE " << n << " FOUND" << endl;
    }
}

//http://www.blitzbasic.com/codearcs/codearcs.php?code=1029
void Quadtree::RAYTRACE(int a, int b){
    int cx = looseQuadTree.World.getCenterX();
    int cy = looseQuadTree.World.getCenterY();
    int lx = looseQuadTree.World.getLengthX();
    int ly = looseQuadTree.World.getLengthY();
    
    StartPicture(lx+1,ly+1);
    looseQuadTree.looseQuadRoot->drawQuadrants(looseQuadTree.looseQuadRoot, cx,cy,lx,ly,0);
    DrawLine(a, 0, b, looseQuadTree.World.getCenterY()+looseQuadTree.World.getLengthY()/2);
    EndPicture();
    
    
    Rectangle *temp = looseQuadTree.looseQuadRoot->rayTrace(&looseQuadTree.looseQuadRoot,a,b,cx,cy,lx,ly,0,looseQuadTree.p);
    if (looseQuadTree.trace == true)
        cout << endl;
    
    if(temp !=NULL) {
    	cout << "RAY FIRST INTERSECTS RECTANGLE " << temp->getName()  << endl;
    } 
    else {
        cout << "RAY INTERSECTS NO RECTANGLES" << endl;
    }
}

Quadtree::Quadtree() {
    rectTree = new bNode();
}


void Quadtree::initLooseQuadTree() {}

void Quadtree::initRectTree() {}




/*
PriorityQueue *queue = new PriorityQueue();	
Rectangle * rect1 = new Rectangle("Rect1",1,2,3,4);	
Rectangle * rect2 = new Rectangle("Rect2",1,2,3,4);
Rectangle * rect3 = new Rectangle("Rect3",1,2,3,4);
Rectangle * rect4 = new Rectangle("Rect4",1,2,3,4);
cNode * node1 = new cNode();	
 
queue->Enqueue(rect1,10);
queue->Enqueue(rect2,100);
queue->Enqueue(rect3,5);
queue->Enqueue(rect4,50);
queue->Enqueue(node1,60);
 
while(!queue->IsEmpty()){
	CompareField temp = queue->Dequeue();
	if (temp.isQuadrant() == true)
		cout << temp.node->binSon->length << endl;
	else
		cout <<temp.rect->getName() << endl;
}*/

