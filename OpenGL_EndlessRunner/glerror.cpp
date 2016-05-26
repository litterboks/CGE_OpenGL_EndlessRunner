#include "glerror.h"

#ifndef _GLUT
#define _GLUT
#include <glut.h> 
#include <GL/gl.h>  
#include <GL/glu.h>
#endif

#include <stdio.h>

void reportGLError(const char * msg)
{
	GLenum errCode;
	const GLubyte *errString;
	while ((errCode = glGetError()) != GL_NO_ERROR) {
		errString = gluErrorString(errCode);
		fprintf(stderr, "OpenGL Error: %s %s\n", msg, errString);
	}
	return;
}
