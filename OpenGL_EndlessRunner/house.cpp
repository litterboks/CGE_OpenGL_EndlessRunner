#include "house.h"
#include "myrectangle.h"
#include "mytriangle.h"

#include <glut.h>
#include <GL/gl.h>  
#include <GL/glu.h>

#include "tga.h"


House::House(float x, float y, float z)
{
	MyRectangle* rect_front = new MyRectangle(x, y, z, 2.0f, 2.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	rect_front->setTexture("house.tga");
	MyRectangle* rect_left = new MyRectangle(x, y, z, 2.0f, 2.0f, 0.0f, -90.0f, 0.0f, 1.0f, 0.0f, 0.0f);
	rect_left->setTexture("houseside.tga");
	MyRectangle* rect_right = new MyRectangle(x + 2, y, z, 2.0f, 2.0f, 0.0f, -90.0f, 0.0f, 1.0f, 0.0f, 0.0f);
	rect_right->setTexture("houseside.tga");
	MyRectangle* rect_back = new MyRectangle(x, y, z - 2, 2.0f, 2.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	rect_back->setTexture("houseside.tga");
	MyRectangle* rect_bottom = new MyRectangle(x, y, z, 2.0f, 2.0f, -90.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f);
	rect_bottom->setTexture("houseside.tga");
	MyTriangle* tri_front = new MyTriangle(x, y + 2, z, 1.4142135f, 2.0f, -45.0f, 0.0f, 0.0f, 0.0f, 0.5f, 0.5f);
	tri_front->setTexture("roof.tga");
	MyTriangle* tri_left = new MyTriangle(x, y + 2, z, 1.4142135f, 2.0f, 0.0f, -90.0f, 45.0f, 0.5f, 0.5f, 0.0f);
	tri_left->setTexture("roof.tga");
	MyTriangle* tri_right = new MyTriangle(x + 2, y + 2, z, 1.4142135f, 2.0f, 0.0f, -90.0f, 135.0f, 0.5f, 0.5f, 0.0f);
	tri_right->setTexture("roof.tga");
	MyTriangle* tri_back = new MyTriangle(x, y + 2, z - 2, 1.4142135f, 2.0f, 45.0f, 0.0f, 0.0f, 0.0f, 0.5f, 0.5f);
	tri_back->setTexture("roof.tga");
	this->add(rect_front);
	this->add(rect_left);
	this->add(rect_right);
	this->add(rect_back);
	this->add(rect_bottom);
	this->add(tri_front);
	this->add(tri_left);
	this->add(tri_right);
	this->add(tri_back);
}
