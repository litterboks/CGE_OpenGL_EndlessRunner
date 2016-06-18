#ifndef COMPOSITEGRAPHIC_H
#define COMPOSITEGRAPHIC_H

#include <iterator>
#include <list>

#include "graphic.h"

/*The CompositeGraphic class implements the functions for a Graphic which is supposed to consist of subgraphic
For example the Platform consisting of 6 MyRectangles*/

class CompositeGraphic : public Graphic {
public:
	//Draws all subgraphics
	virtual void draw() override;
	//Moves all subgraphics
	virtual void move(float x,float y,float z);
	//Scales all subgraphics
	virtual void scale(float x,float y,float z);
	//Rotates all subgraphics around the same base point
	void rotate(MyPoint basePoint, float angle, char axis);
	//Sets texture to all subgraphics
	void setTexture(std::string texture);
	~CompositeGraphic();
	//Adds a subgraphic
	void add(Graphic* graphic);
	//Removes a subgraphic
	void remove(Graphic* graphic);

protected:
	//Constructor with standardvalues
	CompositeGraphic(float x=0.0f,float y=0.0f, float z=0.0);

	//List that holds all subgraphics
	std::list<Graphic*> _graphic;

	//basePoint for compositeGraphic
	MyPoint position;
private:

};

#endif