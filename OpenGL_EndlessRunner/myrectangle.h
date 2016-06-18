#ifndef MYRECTANGLE_H
#define MYRECTANGLE_H

#include "compositeGraphic.h"
#include "mypoint.h"
#include "mytriangle.h"
#include <string>


/*The MyRectangle Class is our Class for drawing rectangles. We could have used the GL_QUADS for drawing a rectangle but we wanted to 
implement our own by drawing two triangles which basically does the same as GL_QUADS. 
Every function of MyRectangle calls the same function in triA and triB.*/

class MyRectangle : public CompositeGraphic {
public:

	//Constructor with position, size and rotation of rectangle
	MyRectangle(float posX, float posY, float posZ, float height, float width, float rotX, float rotY, float rotZ);

	//Constructor with given Points
	MyRectangle(MyPoint A, MyPoint B, MyPoint C, MyPoint D);

	~MyRectangle();

private:
	//Stored texture string
	char* texture;
};

#endif