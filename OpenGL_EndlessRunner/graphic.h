#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <list>

class Graphic {
public:
	virtual ~Graphic();

	const char* Name() {
		return _name;
	}

	virtual void draw();
	virtual void move(float,float,float);
	virtual void scale(float,float,float);

	virtual void add(Graphic* graphic);
	virtual void remove(Graphic* graphic);
	typename std::list<typename Graphic*>::iterator* CreateIterator();

protected:
	Graphic();

private:
	const char* _name;
};

#endif