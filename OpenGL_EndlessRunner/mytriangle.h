#ifndef MYTRIANGLE_H
#define MYTRIANGLE_H

#include "graphic.h"
#include "mypoint.h"


class MyTriangle : public Graphic {
public:
	MyTriangle();
	~MyTriangle();
	MyTriangle(MyPoint cornerA, MyPoint cornerB, MyPoint cornerC);
	MyTriangle(float posX, float posY, float posZ, float height, float width, float rotX, float rotY, float rotZ);

	void calculateNormal();

	void flipNormals();

	void draw() override;
	void mapTexture(int texCoordSel, float u, float v);
	virtual void move(float, float, float);
	virtual void scale(float, float, float);
	void rotate(MyPoint basePoint, float transformAngle, char axis);

	void setTexture(std::string texture);

	MyPoint getCornerA();
	void setCornerA(MyPoint point);
	MyPoint getCornerB();
	void setCornerB(MyPoint point);
	MyPoint getCornerC();
	void setCornerC(MyPoint point);
private:
	//corners of the triangle, counter clockwise
	MyPoint cornerA;
	MyPoint cornerB;
	MyPoint cornerC;
	MyPoint texCornerA;
	MyPoint texCornerB;
	MyPoint texCornerC;
	float texCoord[3][2];
	float normalX=0.f;
	float normalY=0.f;
	float normalZ=0.f;
	char* texture = nullptr;
	bool flipped = false;
	void InitTexture();
};

#endif