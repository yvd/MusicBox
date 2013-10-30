#include "pnt.h"

pnt::pnt(float a, float b, float c)
{
	x = a;
	y = b;
	z = c;
}

pnt::pnt(const pnt& p)
{
	this->x = p.x;
	this->y = p.y;
	this->z = p.z;
}