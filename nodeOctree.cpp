#include "nodeOctree.h"



nodeOctree::nodeOctree()
{
}

nodeOctree::nodeOctree(pointOctree _x,pointOctree _y, pointOctree _z)
{
	valuesX = _x;
	valuesY = _y;
	valuesZ = _z;
	hijos[0] = hijos[1] = hijos[2] = hijos[3] = hijos[4] = hijos[5] = hijos[6] = hijos[7] = NULL;
	hoja = true;

}


nodeOctree::~nodeOctree()
{
}
