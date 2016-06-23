#include "Platform.h"
#include "myrectangle.h"


Platform::Platform(float posX, float posY, float posZ, float height, float width, float depth)
{
	MyPoint A = MyPoint(posX, posY, posZ);
	MyPoint B = MyPoint(posX + width, posY, posZ);
	MyPoint C = MyPoint(posX + width, posY + height, posZ);
	MyPoint D = MyPoint(posX, posY + height, posZ);

	this->LeftTop = D;
	this->RightTop = C;

	MyPoint E = A;
	E.posZ += depth;
	MyPoint F = B;
	F.posZ += depth;
	MyPoint G = C;
	G.posZ += depth;
	MyPoint H = D;
	H.posZ += depth;

	//Front
	MyRectangle* front = new MyRectangle(A, B, C, D);
	this->add(front);
	//Back
	MyRectangle* back = new MyRectangle(E, F, G, H);
	this->add(back);
	//Left
	MyRectangle* left = new MyRectangle(A, D, H, E);
	left->flipNormals();
	this->add(left);
	//Right
	MyRectangle* right = new MyRectangle(B, F, G, C);
	right->flipNormals();
	this->add(right);
	//Bottom
	MyRectangle* bottom = new MyRectangle(A, B, F, E);
	bottom->flipNormals();
	this->add(bottom);
	//Top
	MyRectangle* top = new MyRectangle(D, C, G, H);
	top->flipNormals();
	this->add(top);

}

void Platform::move(float x, float y, float z)
{
	this->LeftTop.posX += x;
	this->LeftTop.posY += y;
	this->LeftTop.posZ += z;

	this->RightTop.posX += x;
	this->RightTop.posY += y;
	this->RightTop.posZ += z;

	for (std::list<Graphic*>::iterator it = this->_graphic.begin(); it != this->_graphic.end(); it++) {
		(*it)->move(x, y, z);
	}
}