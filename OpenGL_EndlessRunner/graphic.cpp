#include "graphic.h"
#include "mypoint.h"

Graphic::Graphic()
{
}

Graphic::~Graphic()
{
}

void Graphic::draw()
{
}

void Graphic::move(float, float, float)
{
}

void Graphic::scale(float, float, float)
{
}

void Graphic::rotate(MyPoint basePoint, float, float)
{
}


void Graphic::add(Graphic * graphic)
{
}

void Graphic::remove(Graphic * graphic)
{
}

typename std::list<typename Graphic*>::iterator* Graphic::CreateIterator()
{
	return new std::list<typename Graphic*>::iterator();
}