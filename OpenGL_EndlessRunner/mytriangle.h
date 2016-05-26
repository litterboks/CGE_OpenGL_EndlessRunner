#ifndef MYTRIANGLE_H
#define MYTRIANGLE_H

#include "graphic.h"
#include "mypoint.h"

class MyTriangle : public Graphic {
public:
	MyTriangle(float posX, float posY, float posZ, float height, float width, float rotX, float rotY, float rotZ, float normalX, float normalY, float normalZ);

	virtual void draw();
	virtual void move(float, float, float);
	virtual void scale(float, float, float);

	void setTexture(std::string texture);

private:
	//corners of the triangle, counter clockwise
	MyPoint cornerA;
	MyPoint cornerB;
	MyPoint cornerC;
	float normalX;
	float normalY;
	float normalZ;
	char* texture;
};

#endif