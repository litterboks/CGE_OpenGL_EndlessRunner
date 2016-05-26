#define _CRT_SECURE_NO_DEPRECATE


#include "mytriangle.h"
#include "mypoint.h"

#ifndef _GLUT
#define _GLUT
#include <glut.h> 
#include <GL/gl.h>  
#include <GL/glu.h>
#endif // !GLUT

//#include "glerror.h"
#include "tga.h"


GLuint texture2;
tgaInfo *info2 = 0;

MyTriangle::MyTriangle(float posX = 0, float posY = 0, float posZ = 0, float height = 1, float width = 1, float rotX = 0, float rotY = 0, float rotZ = 0, float normalX=0, float normalY=0, float normalZ=0) {

	this->normalX = normalX;
	this->normalY = normalY;
	this->normalZ = normalZ;

	cornerA.posX = posX;
	cornerA.posY = posY;
	cornerA.posZ = posZ;

	cornerB.posX = posX + width;
	cornerB.posY = posY;
	cornerB.posZ = posZ;

	cornerC.posX = posX + width/2;
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
}
void MyTriangle::draw()
{
	GLsizei w, h;
	int mode;

	info2 = tgaLoad("roof.tga");

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

	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, texture2);

	glBegin(GL_TRIANGLES);
	glNormal3f(normalX, normalY, normalZ);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(cornerA.posX, cornerA.posY, cornerA.posZ);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(cornerB.posX, cornerB.posY, cornerB.posZ);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(cornerC.posX, cornerC.posY, cornerC.posZ);
	glEnd();
} 

void MyTriangle::move(float x, float y, float z)
{
	cornerA.move(x, y, z);
	cornerB.move(x, y, z);
	cornerC.move(x, y, z);
}

void MyTriangle::scale(float x, float y, float z)
{
	cornerA.multiply(x, y, z);
	cornerB.multiply(x, y, z);
	cornerC.multiply(x, y, z);
}

void MyTriangle::setTexture(std::string texture)
{
	char* cstr = new char[texture.length() + 1];
	strcpy(cstr, texture.c_str());
	this->texture = cstr;
}