#ifndef COMPOSITEGRAPHIC_H
#define COMPOSITEGRAPHIC_H

#include <iterator>
#include <list>

#include "graphic.h"
#include "mypoint.h"

class CompositeGraphic : public Graphic {
public:
	virtual void draw();
	virtual void move(float x,float y,float z);
	virtual void scale(float x,float y,float z);

	virtual void add(Graphic* graphic);
	virtual void remove(Graphic* graphic);
	virtual typename std::list<typename Graphic*>::iterator* CreateIterator();

protected:
	CompositeGraphic(float x=-1.0f,float y=-1.0f, float z=1.0);
	MyPoint position;
private:
	std::list<Graphic*> _graphic;
};

#endif