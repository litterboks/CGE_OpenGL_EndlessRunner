#ifndef MYSPHERE_H
#define MYSPHERE_H

#include "graphic.h"
#include "mypoint.h"
#include <glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

using namespace std;

#pragma once
class mySphere : public Graphic
{
public:
	mySphere(float radius, unsigned int slices, unsigned int stacks, MyPoint position);
	~mySphere();
	virtual void draw();
	virtual void move(float, float, float);
	virtual void scale(float, float, float);
	virtual void rotate(MyPoint basePoint, float transformAngle, char axis);
	void jump(float velocity);
	void InitTexture();
	virtual void setTexture(std::string texture);
	bool isJumping;
	bool isFalling;

private:
	float radius;
	unsigned int slices;
	unsigned int stacks;
	MyPoint position;
	char* texture;
	GLuint texture2;
	float inity;
};

#endif