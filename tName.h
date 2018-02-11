// Julian Moyse
// CMSC 420 Fall 2007
// LooseQuadTree Project 4.3
//
#include <iostream>
#if !defined _TNAME_H
#define _TNAME_H
using namespace std;

class tName {
public:
    tName();
    tName(const char * input);
    ~tName();
    int length();
    int compare(tName* string);
    int compare(tName string);
    tName* substring(int start, int end);
    char at(int position);

    tName* append(tName* string);
    tName* append(char character);
    char * toString();

    friend ostream& operator << (ostream& os, tName fraction);
    friend istream& operator >> (istream& is, tName* string);

private:
	char * name;
    //const char * name;
    int strLen;
};
#endif
