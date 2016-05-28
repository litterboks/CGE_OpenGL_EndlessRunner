#define _CRT_SECURE_NO_DEPRECATE

#include "myrectangle.h"
#include "mypoint.h"
#ifndef _GLUT
#define _GLUT
#include <glut.h> 
#include <GL/gl.h>  
#include <GL/glu.h>  
#endif
#include "tga.h"
//#include "glerror.h"



MyRectangle::MyRectangle(float posX = 0, float posY = 0, float posZ = 0, float height = 1, float width = 1, float rotX = 0, float rotY = 0, float rotZ = 0) {

	triA = MyTriangle(posX, posY, posZ, height, width, rotX, rotY, rotZ);
	triA.mapTexture(0, 0.f, 0.f);
	triA.mapTexture(1, 1.f, 0.f);
	triA.mapTexture(2, 1.f, 1.f);

	triB = MyTriangle(MyPoint(posX, posY, posZ), MyPoint(posX, posY+height, posZ), MyPoint(posX+width,posY+height,posZ));
	triB.flipNormals();
	triB.calculateNormal();
	triB.mapTexture(0, 0.f, 0.f);
	triB.mapTexture(1, 0.f, 1.f);
	triB.mapTexture(2, 1.f, 1.f);
}


void MyRectangle::draw()
{
	triA.draw();
	triB.draw();
}

void MyRectangle::move(float x, float y, float z)
{
	triA.move(x, y, z);
	triB.move(x, y, z);
}

void MyRectangle::scale(float x, float y, float z)
{
	triA.scale(x, y, z);
	triB.scale(x, y, z);
}

void MyRectangle::rotate(MyPoint basePoint, float transformAngle, char axis)
{
	triA.rotate(basePoint, transformAngle, axis);
	triB.rotate(basePoint, transformAngle, axis);
}

void MyRectangle::setTexture(std::string texture)
{
	triA.setTexture(texture);
	triB.setTexture(texture);
}
