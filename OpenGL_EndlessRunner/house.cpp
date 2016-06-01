#include "house.h"
#include "myrectangle.h"
#include "mytriangle.h"

#include <glut.h>
#include <GL/gl.h>  
#include <GL/glu.h>
#include "tga.h"


House::House(float x, float y, float z)
{
	MyPoint roofTip = MyPoint(x + 1, y + 3, z + 1);
	MyPoint topA = MyPoint(x, y + 2, z);
	MyPoint topB = MyPoint(x + 2, y + 2, z);
	MyPoint topC = MyPoint(x + 2, y + 2, z + 2);
	MyPoint topD = MyPoint(x, y + 2, z + 2);

	MyTriangle* tri_front = new MyTriangle(topA,topB,roofTip);
	tri_front->setTexture("roof.tga");
	MyTriangle* tri_left = new MyTriangle(topB, topC, roofTip);
	tri_left->setTexture("roof.tga");
	MyTriangle* tri_right = new MyTriangle(topC, topD, roofTip);
	tri_right->setTexture("roof.tga");
	MyTriangle* tri_back = new MyTriangle(topD, topA, roofTip);
	tri_back->setTexture("roof.tga");

	this->add(tri_front);
	this->add(tri_left);
	this->add(tri_right);
	this->add(tri_back);
}

House::~House() {
	for (std::list<Graphic*>::iterator it = _graphic.begin(); it != _graphic.end(); ++it) {
		delete((*it));
	}
}

void House::rotate(float rot) {
	for (std::list<Graphic*>::iterator it = _graphic.begin(); it != _graphic.end(); ++it) {
		(*it)->rotate(MyPoint(0,0,0), rot, 'y');
	}
}
