#include "pointOctree.h"

class nodeOctree
{
public:
	nodeOctree();
	nodeOctree(pointOctree,pointOctree,pointOctree); // limites x,limits y, lmiites z,
	nodeOctree *hijos[8];
	bool hoja;
	vector<pointOctree> vectorPuntos;
	pointOctree valuesX;
	pointOctree valuesY;
	pointOctree valuesZ;
	~nodeOctree();
};
