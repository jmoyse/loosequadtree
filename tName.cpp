// Julian Moyse
// CMSC 420 Fall 2007
// LooseQuadTree Project 4.3
//
#include <iostream>
#include "tName.h"
using namespace std;

tName::tName() {
    strLen = 0;
    name = new char[strLen];
}

tName::tName(const char * input) {
    strLen = 0;
    
    name = (char *)input;
    
    int position = 0;
    while(name[position++]!='\0') {
        strLen++;
    }
}

ostream& operator<<(ostream& out, tName str) // output
{
    out << str.toString();
    return out;
}

istream& operator >> (istream& is, tName* string) {
    is >> string->toString();
    return is;
}

int tName::compare(tName* string) {
    if (strLen > string->length()) {
        return 1;
    } else if (strLen < string->length()) {
        return -1;
    } else {
        for(int i=0; i<strLen; i++) {
            if (name[i] > string->at(i))
                return 1;
            else if (name[i] < string->at(i))
                return -1;
        }
        return 0;
    }
}

int tName::compare(tName string) {
    if (strLen > string.length()) {
        return 1;
    } else if (strLen < string.length()) {
        return -1;
    } else {
        for(int i=0; i<strLen; i++) {
            if (name[i] > string.at(i))
                return 1;
            else if (name[i] < string.at(i))
                return -1;
        }
        return 0;
    }
}
char * tName::toString() {
    return name;
}
int tName::length() {
    return strLen;
}
char tName::at(int position) {
    if (position > strLen)
        return NULL;
    return name[position];
}
tName* tName::substring(int start, int end) {
    if (0<= start < end <=strLen) {
        int position = 0;
        char* temp = new char[end-start];
        for(int i=start; i<=end; i++) {
            temp[position++]=name[i];
        }
        temp[position++] = '\0';

        tName * tempName = new tName(temp);
        return (tempName);
    }
    return new tName("");
}


tName* tName::append(tName* string) {
    int newLength = string->length() + strLen;
    cout << newLength << endl;
    char * temp = new char[newLength];
    // copy name over
    for(int i =0;i< strLen; i++) {
        temp[i] = name[i];
    }
    int position = 0;
    // copy string over
    for (int i=strLen; i<newLength; i++) {
        temp[i] = string->at(position);
        position++;
    }
    temp[newLength] = '\0';
    name = temp;
    strLen = newLength;
    
    return new tName(temp);
}
tName* tName::append(char character) {
    //cout << "YESSSSSSSSSS" << endl;
    int newLength = strLen+1;
    char * temp = new char[newLength];

    for(int i=0;i<strLen; i++) {
        temp[i] = name[i];
        //	cout << temp[i];
    }
    //cout << character << endl;
    temp[strLen] = character;
    temp[newLength] = '\0';
    strLen = newLength;
    
    name = temp;
    return new tName(temp);
}

tName::~tName() {
	
}

