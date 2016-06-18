#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include "myrectangle.h"
#include "mypoint.h"
#ifndef _GLUT
#define _GLUT
#include <glut.h> 
#include <GL/gl.h>  
#include <GL/glu.h>  
#endif
#include "tga.h"

MyRectangle::MyRectangle(float posX = 0, float posY = 0, float posZ = 0, float height = 1, float width = 1, float rotX = 0, float rotY = 0, float rotZ = 0) {

	MyTriangle* triA = new MyTriangle(posX, posY, posZ, height, width, rotX, rotY, rotZ);
	triA->mapTexture(0, 0.f, 0.f);
	triA->mapTexture(1, 1.f, 0.f);
	triA->mapTexture(2, 1.f, 1.f);

	MyTriangle* triB = new MyTriangle(MyPoint(posX, posY, posZ), MyPoint(posX, posY+height, posZ), MyPoint(posX+width,posY+height,posZ));
	triB->flipNormals();
	triB->calculateNormal();
	triB->mapTexture(0, 0.f, 0.f);
	triB->mapTexture(1, 0.f, 1.f);
	triB->mapTexture(2, 1.f, 1.f);

	this->add(triA);
	this->add(triB);
}

//constructor for given points
MyRectangle::MyRectangle(MyPoint A, MyPoint B, MyPoint C, MyPoint D) {
	triA = new MyTriangle(A, B, C);
	triA->mapTexture(0, 0.f, 0.f);
	triA->mapTexture(1, 1.f, 0.f);
	triA->mapTexture(2, 1.f, 1.f);

	triB = new MyTriangle(C, D, A);
	triB->mapTexture(0, 1.f, 1.f);
	triB->mapTexture(1, 0.f, 1.f);
	triB->mapTexture(2, 0.f, 0.f);

	this->add(triA);
	this->add(triB);
}
