#ifndef MYRECTANGLE_H
#define MYRECTANGLE_H

#include "graphic.h"
#include "mypoint.h"
#include "mytriangle.h"
#include <string>

class MyRectangle : public Graphic {
public:
	MyRectangle(float posX, float posY, float posZ, float height, float width, float rotX, float rotY, float rotZ);

	virtual void draw();
	virtual void move(float, float, float);
	virtual void scale(float, float, float);
	virtual void rotate(MyPoint basePoint, float transformAngle, char axis);
	virtual void setTexture(std::string texture);

private:
	MyTriangle triA;
	MyTriangle triB;
	char* texture;
};

#endif