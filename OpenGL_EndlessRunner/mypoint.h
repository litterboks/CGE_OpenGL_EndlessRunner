#ifndef MYPOINT_H
#define MYPOINT_H

//Class to store coordinates, MyPoint can be used to construct Gaphic Objects

class MyPoint {
public:
	MyPoint();
	//Constructor with 3 coordinates
	MyPoint(float posX, float posY, float posZ);
	//Moves the MyPoint in given directions
	void move(float offsetX, float offsetY, float offsetZ);
	//Scale function for MyPoint
	void multiply(float multiplierX, float multiplierY, float multiplierZ);
	//Stored coordinates
	float posX;
	float posY;
	float posZ;
	//Rotates MyPoint around given basePoint, transformAngle in degrees, axis as char 'x', 'y' or 'z'
	void rotate(MyPoint basePoint, float transformAngle, char axis);
};

#endif