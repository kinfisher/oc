#include "pointOctree.h"



pointOctree::pointOctree()
{
}

pointOctree::pointOctree(double _x,double _y)
{
	coords[0] = _x;
	coords[1] = _y;
}

pointOctree::pointOctree(double _x, double _y,double _z)
{
	coords[0] = _x;
	coords[1] = _y;
	coords[2] = _z;

}




pointOctree::~pointOctree()
{
}

