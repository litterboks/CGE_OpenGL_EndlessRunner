#ifndef MYPOINT_H
#define MYPOINT_H

class MyPoint {
public:
	MyPoint();
	MyPoint(float posX, float posY, float posZ);
	void move(float offsetX, float offsetY, float offsetZ);
	void multiply(float multiplierX, float multiplierY, float multiplierZ);
	float posX;
	float posY;
	float posZ;
	void rotate(MyPoint basePoint, float transformAngle, char axis);
};

#endif