#define _CRT_SECURE_NO_DEPRECATE


#include "mytriangle.h"
#include "mypoint.h"
#include <vector>
#include <iostream>

#ifndef _GLUT
#define _GLUT
#include <glut.h> 
#include <GL/gl.h>  
#include <GL/glu.h>
#endif // !GLUT

//#include "glerror.h"
#include "tga.h"
GLuint texture2;
MyTriangle::MyTriangle() {
}

MyTriangle::~MyTriangle() {
	delete(this->texture);
	std::cout << "destroying triangle"<< std::endl;
}

MyTriangle::MyTriangle(MyPoint cornerA, MyPoint cornerB, MyPoint cornerC) {
	this->cornerA = cornerA;
	this->cornerB = cornerB;
	this->cornerC = cornerC;
	calculateNormal();
}	


void MyTriangle::InitTexture()
{
	GLsizei w, h;
	int mode;
	tgaInfo* info2 = tgaLoad(texture);

	if (info2->status != TGA_OK) {
		fprintf(stderr, "error loading texture2 image: %d\n", info2->status);

		return;
	}
	if (info2->width != info2->height) {
		fprintf(stderr, "Image size %d x %d is not rectangular, giving up.\n",
			info2->width, info2->height);
		return;
	}

	mode = info2->pixelDepth / 8;  // will be 3 for rgb, 4 for rgba
	glGenTextures(1, &texture2);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// Upload the texture2 bitmap. 
	w = info2->width;
	h = info2->height;

	//reportGLError("before uploading texture2");

	GLint format = (mode == 4) ? GL_RGBA : GL_RGB;
	glTexImage2D(GL_TEXTURE_2D, 0, format, w, h, 0, format,
		GL_UNSIGNED_BYTE, info2->imageData);
	//reportGLError("after uploading texture2");

	tgaDestroy(info2);
}

MyTriangle::MyTriangle(float posX = 0, float posY = 0, float posZ = 0, float height = 1, float width = 1, float rotX = 0, float rotY = 0, float rotZ = 0) {

	cornerA.posX = posX;
	cornerA.posY = posY;
	cornerA.posZ = posZ;

	cornerB.posX = posX + width;
	cornerB.posY = posY;
	cornerB.posZ = posZ;

	cornerC.posX = posX + width;
	cornerC.posY = posY + height;
	cornerC.posZ = posZ;

	if (fmod(rotX, 360) != 0.0f) {
		cornerB.rotate(cornerA, rotX, 'x');
		cornerC.rotate(cornerA, rotX, 'x');
	}
	if (fmod(rotY, 360) != 0.0f) {
		cornerB.rotate(cornerA, rotY, 'y');
		cornerC.rotate(cornerA, rotY, 'y');
	}
	if (fmod(rotZ, 360) != 0.0f) {
		cornerB.rotate(cornerA, rotZ, 'z');
		cornerC.rotate(cornerA, rotZ, 'z');
	}
	calculateNormal();
}

void MyTriangle::calculateNormal() {
	GLfloat u[4] = { 0.f,0.f,0.f,1.f };
	GLfloat v[4] = { 0.f,0.f,0.f,1.f };

	u[0] = cornerB.posX - cornerA.posX;
	u[1] = cornerB.posY - cornerA.posY;
	u[2] = cornerB.posZ - cornerA.posZ;

	v[0] = cornerC.posX - cornerA.posX;
	v[1] = cornerC.posY - cornerA.posY;
	v[2] = cornerC.posZ - cornerA.posZ;

	normalX = u[1] * v[2] - u[2] * v[1];
	normalY = u[2] * v[0] - u[0] * v[2];
	normalZ = u[0] * v[1] - u[1] * v[0];

	if (flipped) {
		normalX *= -1;
		normalY *= -1;
		normalZ *= -1;
	}
}

void MyTriangle::flipNormals() {
	flipped = !flipped;
}

void MyTriangle::draw()
{
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, texture2);

	glBegin(GL_TRIANGLES);
	glNormal3f(normalX, normalY, normalZ);
	glTexCoord2f(texCoord[0][0], texCoord[0][1]); glVertex3f(cornerA.posX, cornerA.posY, cornerA.posZ);
	glTexCoord2f(texCoord[1][0], texCoord[1][1]); glVertex3f(cornerB.posX, cornerB.posY, cornerB.posZ);
	glTexCoord2f(texCoord[2][1], texCoord[2][1]); glVertex3f(cornerC.posX, cornerC.posY, cornerC.posZ);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void MyTriangle::mapTexture(int texCoordSel, float u, float v) {
	texCoord[texCoordSel][0] = u;
	texCoord[texCoordSel][1] = v;
}

void MyTriangle::move(float x, float y, float z)
{
	cornerA.move(x, y, z);
	cornerB.move(x, y, z);
	cornerC.move(x, y, z);
	calculateNormal();
}

void MyTriangle::scale(float x, float y, float z)
{
	cornerA.multiply(x, y, z);
	cornerB.multiply(x, y, z);
	cornerC.multiply(x, y, z);
	calculateNormal();
}
void MyTriangle::rotate(MyPoint basePoint, float transformAngle, char axis)
{
	cornerA.rotate(basePoint, transformAngle, axis);
	cornerB.rotate(basePoint, transformAngle, axis);
	cornerC.rotate(basePoint, transformAngle, axis);
	calculateNormal();
}


void MyTriangle::setTexture(std::string texture)
{
	char* cstr = new char[texture.length() + 1];
	strcpy(cstr, texture.c_str());
	this->texture = cstr;
	InitTexture();
}

MyPoint MyTriangle::getCornerA() {
	return cornerA;
}

MyPoint MyTriangle::getCornerB() {
	return cornerB;
}

MyPoint MyTriangle::getCornerC() {
	return cornerC;
}

void MyTriangle::setCornerA(MyPoint point) {
	cornerA = point;
}

void MyTriangle::setCornerB(MyPoint point) {
	cornerB = point;
}

void MyTriangle::setCornerC(MyPoint point) {
	cornerC = point;
}