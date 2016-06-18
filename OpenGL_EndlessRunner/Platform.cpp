#include "Platform.h"
#include "myrectangle.h"


Platform::Platform(float posX, float posY, float posZ, float height, float width, float depth)
{
	MyPoint A = MyPoint(posX, posY, posZ);
	MyPoint B = MyPoint(posX + width, posY, posZ);
	MyPoint C = MyPoint(posX + width, posY + height, posZ);
	MyPoint D = MyPoint(posX, posY + height, posZ);

	MyPoint E = A;
	E.posZ += depth;
	MyPoint F = B;
	F.posZ += depth;
	MyPoint G = C;
	G.posZ += depth;
	MyPoint H = D;
	H.posZ += depth;

	//Front
	this->add(new MyRectangle(A, B, C, D));
	//Back
	this->add(new MyRectangle(E, F, G, H));
	//Left
	this->add(new MyRectangle(A, D, H, E));
	//Right
	this->add(new MyRectangle(B, F, G, C));
	//Bottom
	this->add(new MyRectangle(A, B, F, E));
	//Top
	this->add(new MyRectangle(D, C, G, H));

}

void Platform::setTexture(std::string texture) {
	for (std::list<Graphic*>::iterator it = _graphic.begin(); it != _graphic.end(); ++it) {
		(*it)->setTexture(texture);
	}
}

Platform::~Platform()
{
	for (std::list<Graphic*>::iterator it = _graphic.begin(); it != _graphic.end(); ++it) {
		delete(*it);
	}
}