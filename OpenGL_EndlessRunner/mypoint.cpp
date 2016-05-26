#include "mypoint.h"

#define _USE_MATH_DEFINES
#include <math.h>

void MyPoint::move(float offsetX, float offsetY, float offsetZ) {
	this->posX += offsetX;
	this->posY += offsetY;
	this->posZ += offsetZ;
}

void MyPoint::multiply(float multiplierX, float multiplierY, float multiplierZ) {
	this->posX *= multiplierX;
	this->posY *= multiplierY;
	this->posZ *= multiplierZ;
}

void MyPoint::rotate(MyPoint basePoint, float transformAngle, char axis) {
	float diagonal = 0.0f;
	float angle = 0.0f;
	switch (axis) {
	case 'x':
		diagonal = sqrtf(pow(this->posZ - basePoint.posZ, 2) + pow(this->posY - basePoint.posY, 2));
		angle = atanf((this->posZ - basePoint.posZ) / (this->posY - basePoint.posY));
		if (isnan(angle)) {
			angle = 0;
		}
		this->posY = diagonal*cos((transformAngle + angle) * M_PI / 180) + basePoint.posY;
		this->posZ = diagonal*sin((transformAngle + angle) * M_PI / 180) + basePoint.posZ;
		break;
	case 'y':
		diagonal = sqrtf(pow(this->posZ - basePoint.posZ, 2) + pow(this->posX - basePoint.posX, 2));
		angle = atanf((this->posZ - basePoint.posZ) / (this->posX - basePoint.posX));
		if (isnan(angle)) {
			angle = 0;
		}
		this->posX = diagonal*cos((transformAngle + angle) * M_PI / 180) + basePoint.posX;
		this->posZ = diagonal*sin((transformAngle + angle) * M_PI / 180) + basePoint.posZ;
		break;
	case 'z':
		diagonal = sqrtf(pow(this->posY - basePoint.posY, 2) + pow(this->posX - basePoint.posX, 2));
		angle = atanf((this->posY - basePoint.posY) / (this->posX - basePoint.posX));
		if (isnan(angle)) {
			angle = 0;
		}
		this->posX = diagonal*cos((transformAngle + angle) * M_PI / 180) + basePoint.posX;
		this->posY = diagonal*sin((transformAngle + angle) * M_PI / 180) + basePoint.posY;
		break;
	}
}