#ifndef MYTRIANGLE_H
#define MYTRIANGLE_H

#include "graphic.h"
#include "mypoint.h"


/*MyTriangle is our Base Graphic, other Graphic elements consist either of compositeGraphic elements like MyRectangle or of the base Graphic MyTriangles.
Composite Graphics have the same interface as MyTriangle so if I call draw() on a compositeGraphic it calls draw() of all its children which can
be triangles or compositeGraphics*/

class MyTriangle : public Graphic {
public:
	MyTriangle();
	~MyTriangle();
	//Constructor via MyPoints
	MyTriangle(MyPoint cornerA, MyPoint cornerB, MyPoint cornerC);
	//Constructor via position, size and rotation around lower left point of the triangle
	MyTriangle(float posX, float posY, float posZ, float height, float width, float rotX, float rotY, float rotZ);

	//Calculates Normal of the Triangle
	void calculateNormal();

	//Flips the normal
	void flipNormals();

	//Draws the triangle with OpenGL
	void draw() override;

	//Sets texture coordinate of the corners of the triangle, int texCoordSel selects point A, B or C of the triangle and assigns u and v coordinates to it
	//Example 0, 0, 0 Sets cornerA of the triangle to u coordinate 0 and v coordinate 0
	//Example 1, 1, 0 Sets cornerB of the triangle to u cooridnate 1 and v coordinate 0
	void mapTexture(int texCoordSel, float u, float v);

	//Moves the triangle
	virtual void move(float, float, float);

	//Scales the triangle around Point(0,0,0)
	virtual void scale(float, float, float);

	//Rotates the triangle around given basePoint, transformAngle in degrees, axis as char 'x', 'y' or 'z'
	void rotate(MyPoint basePoint, float transformAngle, char axis);

	//Sets the texture via path string
	void setTexture(std::string texture);

	//Getter and setter for corners
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

	//Texture cooridnates for cornerA, B, C
	//texCoord[corner][uv]
	float texCoord[3][2];
	float normalX=0.f;
	float normalY=0.f;
	float normalZ=0.f;
	char* texture = nullptr;
	bool flipped = false;
	void InitTexture();
};

#endif